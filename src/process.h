#ifndef PCARS_PROCESS_DATA_H_
#define PCARS_PROCESS_DATA_H_

#include <memory>

#include "decodertelemetrydata.h"
#include "data.h"
#include "packet.h"


namespace pcars { 

class Process {
public:
	using Lap_Data = std::vector<std::shared_ptr<Data> >;
	using Lap_Data_V2 = std::vector<Packet>;

	virtual ~Process() {}

	virtual void process(const Lap_Data lap_data) const = 0;
};

class Process_Lap : public Process {
public:
	Process_Lap();
	virtual ~Process_Lap() {}

	void process(const Lap_Data lap_data) const override;

};

class Process_Lap_V2 : public Process {
public:
	Process_Lap_V2();
	virtual ~Process_Lap_V2() {}

	void process(const Lap_Data lap_data) const override;

};


class Process_Track : public Process {
public:
	Process_Track();
	virtual ~Process_Track() {}

	void process(const Lap_Data lap_data) const override;
};


}

#endif

