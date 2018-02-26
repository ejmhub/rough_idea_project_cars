#ifndef PCARS_REQUEST_PIT_MODE_IN_GARAGE_H_
#define PCARS_REQUEST_PIT_MODE_IN_GARAGE_H_

#include "request.h"

namespace pcars {

class Request_Pit_Mode_In_Garage : public Request {
public:
	Request_Pit_Mode_In_Garage(Request * request = nullptr);
	virtual ~Request_Pit_Mode_In_Garage() {}

	bool request(std::shared_ptr<Data>) override;

private:
	Request * request_;

	Request_Pit_Mode_In_Garage(const Request_Pit_Mode_In_Garage&) = delete;
	Request_Pit_Mode_In_Garage& operator=(const Request_Pit_Mode_In_Garage&) = delete;
};

}

#endif

