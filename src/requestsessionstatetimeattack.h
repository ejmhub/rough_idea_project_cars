#ifndef PCARS_REQUEST_SESSION_STATE_TIME_ATTACK_H_
#define PCARS_REQUEST_SESSION_STATE_TIME_ATTACK_H_

#include "request.h"

#include "recordlap.h"

namespace pcars {

class Request_Session_State_Time_Attack : public Request {
public:
	Request_Session_State_Time_Attack(Record_Lap * = nullptr, Request * = nullptr);
	virtual ~Request_Session_State_Time_Attack() {}

	bool request(std::shared_ptr<Data>) override;

private:
	Record_Lap * record_;
	Request * request_;

	Request_Session_State_Time_Attack(const Request_Session_State_Time_Attack&) = delete;
	Request_Session_State_Time_Attack& operator=(const Request_Session_State_Time_Attack&) = delete;
};

}

#endif
