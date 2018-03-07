#ifndef PCARS_REQUEST_RACE_STATE_DNF_H_
#define PCARS_REQUEST_RACE_STATE_DNF_H_

#include "request.h"

namespace pcars {

class Request_Race_State_DNF : public Request {
public:
	Request_Race_State_DNF(Request * request = nullptr);
	virtual ~Request_Race_State_DNF() {}

	bool request(std::shared_ptr<Data>) override;

private:
	Request * request_;

	Request_Race_State_DNF(const Request_Race_State_DNF&) = delete;
	Request_Race_State_DNF& operator=(const Request_Race_State_DNF&) = delete;
};

}

#endif

