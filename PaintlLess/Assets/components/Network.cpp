// This file is part of the course TPV2@UCM - Samir Genaim

#include "Network.h"

#include <SDL_net.h>

#include "../ecs/Manager.h"



Network::Network(const char* host, Uint16 port,
	std::string playerName) :
	host_(host), //
	port_(port), //
	isMaster_(false), //
	isGameReday_(false), //
	id_(0), //
	conn_(), //
	p_(nullptr), //
	m_(nullptr), //
	otherPlayerAddress_(), //
	localPlayerName_(playerName), //
	remotePlayerName_("N/A"), //
	lastTimeActive_(0) {
}

Network::~Network() {

	//
	if (conn_) {
		DissConnectMsg* m = static_cast<DissConnectMsg*>(m_);
		m->_type = _DISCONNECTED_;
		m->id = id_;
		p_->len = sizeof(DissConnectMsg);
		p_->address = otherPlayerAddress_;
		SDLNet_UDP_Send(conn_, -1, p_);
	}

	// close the connection
	if (conn_)
		SDLNet_UDP_Close(conn_);

	// free the packet
	if (p_) {
		SDLNet_FreePacket(p_);
	}

	// close SDLNet
	SDLNet_Quit();
}

void Network::init() {

	// Initialise SDLNet
	if (SDLNet_Init() < 0) {
		throw SDLNet_GetError();
	}

	// allocate the packet to be used for sending data
	p_ = SDLNet_AllocPacket(100);
	m_ = reinterpret_cast<NetworkMessage*>(p_->data);

	if (host_ == nullptr) { // if started as a master player

		// we use id 0, and open a socket to send/receive messages
		isMaster_ = true;
		id_ = 0;
		conn_ = SDLNet_UDP_Open(port_);
		if (!conn_)
			throw SDLNet_GetError();

		names_[0] = localPlayerName_;
		names_[1] = remotePlayerName_;

	}
	else { // if started as  other player

	 // we use id 1, and open a socket to send/receive messages
		isMaster_ = false;

		//		id_ = 1;
		conn_ = SDLNet_UDP_Open(0);
		if (!conn_)
			throw SDLNet_GetError();

		std::cout << "Trying to connect to other player at " << host_ << ":"
			<< port_ << std::endl;

		// resolve the host name into an IPAdrress
		if (SDLNet_ResolveHost(&otherPlayerAddress_, host_, port_) < 0) {
			throw SDLNet_GetError();
		}

		// send a message asking to play
		PlayRequestMsg* m = static_cast<PlayRequestMsg*>(m_);
		m->_type = _I_WANT_TO_PLAY_;
		memset(m->name, 0, 10);
		auto size =
			localPlayerName_.length() > 9 ? 9 : localPlayerName_.length();
		memcpy(m->name, localPlayerName_.c_str(), size);
		p_->len = sizeof(PlayRequestMsg);
		p_->address = otherPlayerAddress_;
		SDLNet_UDP_Send(conn_, -1, p_);

		// we use socket set to allow waiting for response instead of just looping
		SDLNet_SocketSet socketSet = SDLNet_AllocSocketSet(1);
		SDLNet_UDP_AddSocket(socketSet, conn_);

		// wait for response
		if (SDLNet_CheckSockets(socketSet, 3000)) {
			if (SDLNet_SocketReady(conn_)) {
				if (SDLNet_UDP_Recv(conn_, p_) > 0) {
					if (m_->_type == _WELCOME_) {
						isGameReday_ = true;
						WelcomeMsg* m = static_cast<WelcomeMsg*>(m_);
						remotePlayerName_ = std::string(
							reinterpret_cast<char*>(m->name));
						id_ = m->id;
						names_[id_] = localPlayerName_;
						names_[1 - id_] = remotePlayerName_;
					}
				}
			}
		}

		// free the socket set, won't be used anymore
		SDLNet_FreeSocketSet(socketSet);

		// if did not succeed to connect, throw an exception
		if (!isGameReday_)
			throw "Failed to connect!";

	}

}

void Network::update() {

	m_->_type = _ACTIVE_;
	p_->len = sizeof(NetworkMessage);
	p_->address = otherPlayerAddress_;
	SDLNet_UDP_Send(conn_, -1, p_);



	// in each iteration we poll all pending message and process them
	while (SDLNet_UDP_Recv(conn_, p_) > 0) {
		lastTimeActive_ = SDL_GetTicks();
		switch (m_->_type) {

		case _I_WANT_TO_PLAY_: {
			// we accept the connection if the player is the master, and no other player is connected
			if (isMaster_ && !isGameReday_) {
				PlayRequestMsg* m = static_cast<PlayRequestMsg*>(m_);
				otherPlayerAddress_ = p_->address;
				remotePlayerName_ = std::string(
					reinterpret_cast<char*>(m->name));
				names_[1 - id_] = remotePlayerName_;
				WelcomeMsg* mr = static_cast<WelcomeMsg*>(m_);

				mr->_type = _WELCOME_;
				auto size =
					localPlayerName_.size() > 9 ?
					9 : localPlayerName_.size();
				memcpy(mr->name, localPlayerName_.c_str(), size);
				mr->id = 1 - id_;
				p_->len = sizeof(WelcomeMsg);
				SDLNet_UDP_Send(conn_, -1, p_);
				isGameReday_ = true;
			}
			break;
		}

		case _DISCONNECTED_: {
			DissConnectMsg* m = static_cast<DissConnectMsg*>(m_);
			isGameReday_ = false;
			names_[1 - m->id] = remotePlayerName_ = "N/A";
			if (!isMaster_) {
				SDLNet_UDP_Close(conn_);
				conn_ = SDLNet_UDP_Open(port_);
				isMaster_ = true;
			}
		}
		}
	}

	if (isGameReday_ && SDL_GetTicks() - lastTimeActive_ > 3000) {
		isGameReday_ = false;
		names_[1 - id_] = remotePlayerName_ = "N/A";
		if (!isMaster_) {
			SDLNet_UDP_Close(conn_);
			conn_ = SDLNet_UDP_Open(port_);
			isMaster_ = true;
		}

	}

}
