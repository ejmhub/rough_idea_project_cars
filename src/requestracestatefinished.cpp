#include "requestracestatefinished.h"

#include "decodertelemetrydata.h"

namespace pcars {

Request_Race_State_Finished::Request_Race_State_Finished(Request * request)
	: request_{request} {}

bool Request_Race_State_Finished::request(Decoder * decoder) {

	Decoder_Telemetry_Data * tdecoder = dynamic_cast<Decoder_Telemetry_Data *>(decoder);

	if (tdecoder) {
		if (tdecoder->race_state_flags() == Race_State::RACESTATE_FINISHED) {
			return true;
		}
		else if (request_) {
			return request_->request(decoder);
		}
	}
	return true;
}

}

