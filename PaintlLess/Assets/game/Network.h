// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_net.h>
#include <SDL_stdinc.h>
#include <array>

#include "GameState.h"
#include "network_message.h"

class Vector2D;

class Network {
public:
	Network();
	virtual ~Network();
	void init(GameStateMachine* gameStateMachine);
	void update();

	inline void updateManager(std::unique_ptr<Manager*> mngr) { managerState_ = &mngr; };

	void sendDeckReady();

	inline Uint8 getId() {
		return id_;
	}

	inline bool isMaster() {
		return isMaster_;
	}

	inline bool isGameReady() {
		return isGameReday_;
	}

	auto& getNames() {
		return names_;
	}

	void switchId() {
		if (isMaster_ && !isGameReday_) {
			id_ = 1 - id_;
			std::swap(names_[0], names_[1]);
		}
	}
private:
	const char* host_;
	Uint16 port_;
	bool isMaster_;
	bool isGameReday_;
	Uint8 id_;
	UDPsocket conn_;
	UDPpacket* p_;
	NetworkMessage* m_;
	IPaddress otherPlayerAddress_;
	std::string localPlayerName_;
	std::string remotePlayerName_;
	std::array<std::string, 2> names_;
	Uint32 lastTimeActive_;
	GameStateMachine* gsm;

	std::unique_ptr<Manager*>* managerState_;
};

