#include "requestpackagetelemetry.h"

#include <iostream>
#include <exception>

#include "decodergeneric.h"
#include "decodertelemetrydata.h"
#include "dataformat1.h"

namespace pcars {

Request_Package_Telemetry::Request_Package_Telemetry(Process * process, Live * live, Request_Package * request)
	: request_{request},
	  recordlap_{process},
	  recordlive_{live},
	  practice_{&recordlap_},
	  qualy_{&recordlive_, &practice_}, 
	  race_{&recordlive_, &qualy_} {}

bool Request_Package_Telemetry::request(const PCars_Data & packet) {

	Decoder_Generic gdecoder;

	try {
		unsigned int pos = 0;
		gdecoder.decode(packet, pos);
		pos = 0; // reset pos after decode

		if (gdecoder.packet_type() == Packet_Type::PACKET_TYPE_TELEMETRY) {

			Decoder_Telemetry_Data decoder;
			decoder.decode(packet, pos);
			Data_Format_1 data(&decoder);

			// Build Version 1200 decoder.build_version();

			return race_.request(&data);
		}

		if (request_) {
			return request_->request(packet);
		}
	}
	catch (const std::out_of_range& oor) {
		std::cerr << "Out of Range error: " << oor.what() << std::endl;
		return false;
	}
	catch (...) {
		std::cerr << "Unknown error: " << std::endl;
		return false;
	}

	return true;
}

}

