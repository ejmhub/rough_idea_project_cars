#include "requestpackagetelemetry.h"

#include <iostream>
#include <exception>

#include "decodergeneric.h"
#include "decodertelemetrydata.h"
#include "dataformat1.h"

using namespace std;

namespace pcars {

Request_Package_Telemetry::Request_Package_Telemetry(Process * process, Live * live)
	: post_lap_{process},
	  live_{live},
	  race_racing_{&live_},
	  race_{nullptr, &race_racing_},
	  qualy_racing_{&live_},
	  qualy_{nullptr, &qualy_racing_},
	  practice_racing_{&post_lap_},
	  practice_{nullptr, &practice_racing_} {}

bool Request_Package_Telemetry::request(const PCars_Data & packet) {

	Decoder_Generic gdecoder;

	try {
		unsigned int pos = 0;
		gdecoder.decode(packet, pos);
		pos = 0; // reset pos after decode

		if (gdecoder.packet_type() == Packet_Type::PACKET_TYPE_TELEMETRY) {

			std::shared_ptr<Decoder_Telemetry_Data> decoder = std::make_shared<Decoder_Telemetry_Data>();
			decoder->decode(packet, pos);

			std::shared_ptr<Data> data = std::make_shared<Data_Format_1>(decoder);

			race_.request(data);
			qualy_.request(data);	
			practice_.request(data);

			return true;
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

