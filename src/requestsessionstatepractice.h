#ifndef PCARS_REQUEST_SESSION_STATE_PRACTICE_H_
#define PCARS_REQUEST_SESSION_STATE_PRACTICE_H_

#include "request.h"

#include "requestracestateracing.h"

namespace pcars {

class Request_Session_State_Practice : public Request {
public:
	Request_Session_State_Practice(Request * request = nullptr);
	virtual ~Request_Session_State_Practice() {}

	bool request(Decoder *) override;

private:
	Request * request_;

	Request_Session_State_Practice(const Request_Session_State_Practice&) = delete;
	Request_Session_State_Practice& operator=(const Request_Session_State_Practice&) = delete;
};

}

#endif
