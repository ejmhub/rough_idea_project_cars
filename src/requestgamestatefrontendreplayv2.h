#ifndef PCARS_REQUEST_GAME_STATE_FRONT_END_REPLAY_V2_H_
#define PCARS_REQUEST_GAME_STATE_FRONT_END_REPLAY_V2_H_

#include "request.h"

namespace pcars {

class Request_Game_State_Front_End_Replay_V2 : public Request {
public:
	Request_Game_State_Front_End_Replay_V2(Request *);
	virtual ~Request_Game_State_Front_End_Replay_V2() {}

	bool request(Data *) override;

private:
	Request * request_;
};

}

#endif

