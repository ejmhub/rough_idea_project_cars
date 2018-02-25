#include "requestsessionstateformationlapv2.h"

#include "packet.h"

namespace pcars {

Request_Session_State_Formation_Lap_V2::Request_Session_State_Formation_Lap_V2(Record_Lap * record, Request * request)
	: request_{request},
	  racing_{record} {}

bool Request_Session_State_Formation_Lap_V2::request(Data * data) {

	if (static_cast<Session_State>(data->game_states()->session_state()) == Session_State::SESSION_FORMATION_LAP) {
		return racing_.request(data);
	}
	else if (request_) {
		return request_->request(data);
	}
	else {
		return true;
	}
}

}

