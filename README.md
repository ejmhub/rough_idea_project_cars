# Rough Idea Project Cars

## Description

A set of cpp classes for capturing Project Cars Version 1 UDP Format.

## Contents
* [Install Binarys](#T-Installation)
* [Roll Your Own Post Lap](#T-post_lap)
* [Roll Your Own Live Feed](#T-live_feed)
* [Class Structure](#T-classes)
* [Build Library](#T-Build)
  
## <a name="T-Installation"></a>Install Binarys

### Capture Lap Data Demo
Capture lap data creates a lap_data.json file with all the previous laps data.
You can either write your on html file to view the json in a browser or use track_9.html,
however there is only currenlty three race lines recorded zolder, dubai club and oulton park island. 
TODO add instructions on creating more track data.

#### OSX
* cd capture_lap_data
  * ```# cd ./bin/capture_lap_data```
* Export DYLD_LIBRARY_PATH to ./lib
  * ```# export DYLD_LIBRARY_PATH=../../lib```
* Run pcars
  * ```# ./pcars```
  
* To capture post lap data you need to be doing practice i.e. not warmup, qualy or race.
* Recording starts once you begin a full lap, however it will not be recorded until you finish that lap.
* There should be a lap_data.json file which has the results of all your laps.
* You can use track_9.html to veiw lap_data.json in a browser or write your own javascript.( [track_9 screen shot](img/track_9.png) )

* To see live feed you need to be doing either race or qualy. 
* Currently the live feed only uses std out to show braking as a demo.
* You can edit live.cpp Live_Feed::live() to display more live telemetry. 
* See decodertelemetrydata.h for available telemetery data. (rebuild [Build Library](#T-Build))

## <a name="T-post_lap"></a>Roll Your Own Post Lap
Currently I have written two Post Lap Processes (process.h), both create json files one for capturing telemetry (Process_Lap) to be used with track_9.html and the other for captureing track data (Process_Track), which I use with track_map.html to create track data for track_9.html.  

I then pass one of these Process objects to Capture_Telemetry's constructor (capturetelemetry.h).

You can dervie a new Process class that can then be used with Capture_Telemetery to create your own post lap processing.

## <a name="T-live_feed"></a>Roll Your Own Live Feed

Take a look at live.h there is one Abstract class (Live) and one Concrete class (Live_Feed). I'm more into post lap analysis but I thought others would like a live feed this is why i just print brake data to the std out.

To create your own live feed you can implement the current live feed (Live_Feed) and rebuild the library, however I only have the live feed for race and qualy.  If you need live feed for practice you will need to go to requestpackagetelemetry.cpp and in the constructors initialisation list remove recordlap_ and replace with recordlive_.

Once you have rebuilt the library you can just run the executable "pcars" in capture_lap_data to get the live feed up and running.


## <a name="T-classes"></a>Class Structure
### Transport

```
  8 class Transport {
  9 public:
 10         virtual ~Transport() {};
 11 
 12         virtual PCars_Data read(const Amount) = 0;
 13         virtual void write(const PCars_Data &) = 0;
 14 };
```

Transport is simply the type that reads or writes (interface for write but no impl) to and from a peer. 
Transport_UDP is a Transport Type that reads UDP packets.  
PCars_Data is a std::vector of unsigned chars.

##### Summary

If you just want to capture the data and process it yourself this is for you.

### Decoder

```
  8 class Decoder {
  9 public:
 10         virtual ~Decoder() {}
 11 
 12         virtual void decode(const PCars_Data &, Position &) = 0;
 13 };
```

Decoder is loosely based on the interpreter pattern which decodes specific elements of a packet e.g.

```
  8 class Decoder_F32: public Decoder {
  9 public:
 10         Decoder_F32();
 11         virtual ~Decoder_F32() {}
 12 
 13         void decode(const PCars_Data &, Position &) override;
 14 
 15         float f32() const;
 16 
 17 private:
 18         float num_;
 19 };
``` 

Decoder_F32 is a Decoder that decodes a Float 32bit element such as a "f32   sBestLapTime;"
Position is the position of the current element in the packet and may get incremeneted to the next packet e.g. for f32 we would increment by 4 because 32/8 is 4, however if it was a bit wise operation say MS 3bit it would not increment the value because the next decoder may need the LS 3bit. Anyway this is done under the covers in the Decoder and the Decoder_Composite.


### Decoder_Compiste

```
  8 class Decoder_Composite : public Decoder {
  9 public:
 10         using Vector_Decoder = std::vector<Decoder *>;
 11 
 12         virtual ~Decoder_Composite() {}
 13 
 14         virtual void decode(const PCars_Data &, Position &);
 15 
 16         void add(Decoder *);
 17 
 18 private:
 19         Vector_Decoder decoders_;
 20         Vector_Decoder::iterator iter_;
 21 };

```

Decoder_Composite is a Decoder it is the Composite Pattern and is used to string together Packages, Decoder_Telemetry_Data is Decoder_Composite and is an example of creating a package decoder by adding Decoders.

Decoder Note: I know just copying a package to a struct is QUICK and my decoder is slow in comparison however copying a struct is not as fun as implementing a design pattern :-). 

##### Summary

In conjuction with the Transport_UDP class you can decode packetes using the Decoders and deriving from the Decoder_Composite 

### Request_Package

```
 11 class Request_Package {
 12 public:
 13         virtual ~Request_Package() {}
 14 
 15         virtual bool request(const PCars_Data &) = 0;
 16 };
```

This is really a nothing class my thoughts were to us it as a Chain of Responsabilty pattern for different packages but did not work out that way. Anyway I think it still gives a bit of flexabilty at this point in the code but does nothing really.

### Request

```
  8 namespace pcars {
  9 
 10 class Request {
 11 public:
 12         virtual ~Request() {}
 13 
 14         virtual bool request(Decoder *) = 0;
 15 };
```

Ok so now we can do something this is a Chain of Responsability Pattern, because the Project Cars 1 Format combines the state and the telemetry this pattern is used to tell where we are in the game.  For example the Request_Session_State_Race is where all the action happens so pass the decoded data straight to the request and you know you are recording actual telemetry.

I like these classes because it has all different states like Pit Mode out and in etc, so I always wanted to do some analytics of the fuel consumption which could be done with these classes. I'm thinking this is not the case for Project Cars 2 Format because these two packets i.e. State and Telemetry Data are now seperate :-( 

##### Summary

You pass the next state to the previous state constructor like a chain, a chain of states and given the State you are in is what object will be responiable for that telemetry.

```
 11 Request_Package_Telemetry::Request_Package_Telemetry(Process * process, Live     * live, Request_Package * request)
 12         : request_{request},
 13           recordlap_{process},
 14           recordlive_{live},
 15           practice_{&recordlap_},             <--- I want to record lap data in practice
 16           qualy_{&recordlive_, &practice_},   <--- add practice to qualy (begining of chain) however record live or show live data
 17           race_{&recordlive_, &qualy_} {}     <--- add qualy to race and get live feed
 18 

```
### Record_Lap

```
 14 class Record_Lap
 15 {
 16 public:
 17 
 18         virtual ~Record_Lap() {};
 19 
 20         virtual void record(Decoder *) = 0;
 21 };
```

Record_Lap is a type for recording laps currently I have Record_Post_Lap record and Record_Live_Data, say if you wanted to do both in practice post lap record and live lap record you would derive a class from Record_lap and call it something like Record_Both and pass it two processes to its constructor one for post and one for live (see Proces and Live next) and possible have a Record_Post_Lap and a Record_Live_Data to do the implementation.

Record_Post_Lap is a bit complex that is why it would be simpler to just derive from Process and pass it to Record_Post_Lap. 

##### Summary

Record_Lap does the grunt work, not the nice telemetry work, always leave this class to do the recording and leave the exciting part to the Process and Live classes.

### Process

```
  8 class Process {
  9 public:
 10         using Lap_Data = std::vector<Decoder_Telemetry_Data>;
 11 
 12         virtual ~Process() {}
 13 
 14         virtual void process(const Lap_Data& lap_data) const = 0;
 15 };
```

The fun part this is where all the action happens, note that the Record_Post_Lap creates a thread to run this so you have a whole lap to get it done. Take the time to have a look at Process_lap where I create the json file.

##### Summart

This is it this where all the awesome work is done

### Live

```
  8 class Live {
  9 public:
 10         virtual ~Live() {}
 11 
 12         virtual void live(Decoder *) const = 0;
 13 };
 ```
 
 Ok this is cool as well I just not very good at driving around corners and looking at my tyre temp ;-) , anyway I imagine you have a engineer sitting there analysing your progress this is where this would happen but I'm not a GUI designer but would love to have a look at creating a live graph that shows live data that would be cool. (one day)
 
 ##### Summary
 
 You want a live feed do something here.
 
 ### Capture_Telemetery
 
 ```
  11 class Capture_Telemetry {
 12 public:
 13         Capture_Telemetry(Process *, Live *);
 14 };
 15 
 ```
 
 Is the main loop, simple as that, start here!  For Project Cars 2 Format I'm thinking I will have a Capture_Telemetery_V2 :-).


## <a name="T-Build"></a>Build Library
#### OSX
##### Library
* Download.
* Copy to your working directory
* Open a terminal
* cd to src directory. 
  * ```# cd ./src```
* Run "make install"
  * ```# make install```
* Run "make"
  * ```# make```
* To clean the build run "make clean"
  * ```# make clean```
* For debug edit the make file e.g. add -g to compiler and link flags (there are commented out flags showing debug)
##### Executable
* cd ./bin/capture_lap_data
  * ```# cd ./bin/capture_lap_data```
* Edit main.cpp if necessary 
* Run "make"
  * ```# make```
