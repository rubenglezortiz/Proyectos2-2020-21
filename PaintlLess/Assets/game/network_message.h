// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "network_types.h"

#pragma pack(push,1)

enum MsgType : uint8_nt {
	_NONE_,
	_I_WANT_TO_PLAY_,
	_WELCOME_,
	_DISCONNECTED_, //
	_ACTIVE_
};

struct NetworkMessage {
	uint8_nt _type;
};

struct DissConnectMsg : NetworkMessage {
	uint8_nt id;
};

struct PlayRequestMsg : NetworkMessage {
	uint8_nt name[10];
};

struct WelcomeMsg : NetworkMessage {
	uint8_nt id;
	uint8_nt name[10];
};

#pragma pack(pop)