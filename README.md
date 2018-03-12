# Rough Idea Project Cars

## Description

A set of c++ classes for capturing Project Car's Version 1 and Version 2 UDP Telemetry.

## Contents

* [Version 1 Tutorial](#T-Tutorial)

## <a name="T-Tutorial"></a>Tutorial

### <a name="T-Tutorial"></a> Version 1 UDP Format

* [Part 1](#T-Part1)  Running Demo Executable
* [Part 2](#T-Part2)  Roll Your Own Live Feed
* [Part 3](#T-Part3)  Roll Your Post Lap Process (WIP)

## <a name="T-Part1"></a>Part 1  Running Demo Executable

The demo application writes the post lap telemetry to a json file during practice and can be viewed using track_9.html.

JavaScript developers can write their own web app to display the json file.

I only have three track files at the moment oulton park island, dubai club and zolder.

### Prerequisites

Project Cars 2 or 1 running on your console and UDP in options set to "UDP Protocol Version" "Project CARS 1". 

Note for the "UDP Frequency" my PlayStation says higher the value more packets but I think this is back to front I found lower the value more the packets. Anyway experiment with these values to get the right setting for you.

#### Tute

The demo runs in a terminal so I'm just going to use a terminal for the tutorial.

* "Download Zip" of the Repo.
* Open a Terminal
* Copy rough_idea_project_cars-master to your working directory. (if you don't have a working dir, from a terminal run "mkdir ~/your_working_dir").
```
Your_User$ cp -r ~/Downloads/rough_idea_project_cars-master ~/your_working_dir/
```
* Change Directory to ~/your_working_dir/rough_idea_project_cars-master/bin
```
Your_User$ cd ~/your_working_dir/rough_idea_project_cars-master/bin
```
* Change Directory to capture_lap_data
```
Your_User$ cd ./capture_lap_data
```
* List the contents of the directory
```
Your_User$ ls -l
total 97864
-rw-r--r--  1 Your_User  staff    248031  3 Feb 18:37 DubaiAeroDromeClub_raceline_track.json
-rw-r--r--  1 Your_User  staff       214  6 Feb 08:12 main.cpp
-rwxr-xr-x  1 Your_User  staff       449  6 Feb 08:12 makefile
-rw-r--r--  1 Your_User  staff  17027175  3 Feb 18:37 oulton_park_island.json
-rwxr-xr-x  1 Your_User  staff     11180  6 Feb 08:12 pcars
-rw-r--r--  1 Your_User  staff     29181  6 Feb 08:12 track_9.html
-rw-r--r--  1 Your_User  staff    227530  3 Feb 18:37 zolder_raceline_track.json
```
* Add rough ideas pcars library to your library path
```
Your_User$ export DYLD_LIBRARY_PATH=../../lib
```
* Now run the executable and do some PRACTICE laps on Oulton Park Island. Note I don't capture the out lap and the demo writes the previous lap to the json file so you have to complete a full lap before it will be captured.
```
Your_User$ ./pcars
```
* May get a pop up asking to allow this app to read from a network port, press Allow. (Don't leave the app running because this leaves the port open, to close the exe press "control-c" e.g. control button and the letter c at the same time).
* Do some practice laps.

Out lap in practice is not recorded so you must do at least one full lap. Recording happens while you are driving but actually writing to the json file does not happen until the lap is finished. You will see output "Recording Finished #" when that lap has been added to the json file. Open track_9.html in safari or Firefox (browser).

![alt text](https://github.com/leroythelegend/rough_idea_project_cars/blob/master/img/track_9.png)

* Create your own display using JavaScript to read the lap_data.json file.

## <a name="T-Part2"></a>Part 2 Roll Your Own Live feed

### Prerequisites

Do the first tute.

You need command line tools, go to apple developer for instructions on installing these for OSX. 

You will need some VI skills here to follow the tute, VI is just an editor so you can follow along in any editor (except word) or just use xcode to edit the files and use the terminal to build the application or if you are an xcode guru you know what to do ;-) .

WARNING if you change a header file (.h file) you should run "make clean" and "make" from in the src directory. 

#### Tute

I'm just going to use a terminal for the tutorials.

* Download the Repo.
* Open a Terminal
* Copy rough_idea_project_cars-master to your working directory. (if you don't have a working dir, from a terminal run "mkdir ~/your_working_dir").
```
Your_User$ cp -r ~/Downloads/rough_idea_project_cars-master ~/your_working_dir/
```
* Change Directory to ~/your_working_dir/rough_idea_project_cars-master/src
```
Your_User$ cd ~/your_working_dir/rough_idea_project_cars-master/src
```
* Open dataformat1.h in an editor.
```
Your_User$ vi ./dataformat1.h
```
* This is the object for all the "Project Cars 2 and 1" Data Packets.
```
class Data_Format_1 : public Data {
public:
         Data_Format_1(std::shared_ptr<Decoder_Telemetry_Data>);
         virtual ~Data_Format_1() {}
 
         Data_Car_State * car_states() const override;
         Data_Game_State * game_states() const override;
         Data_Input_State * input_states() const override;
         Data_Velocity_State * velocity_states() const override;
         Data_Damage_State * damage_states() const override;
         Data_Control_State * control_states() const override;
         Data_Track_State * track_states() const override;
         Data_Participants * participants() const override;
         Data_Participants_Info * participants_info() const override;
         Data_Participants_Stats * participants_stats() const override;
         Data_Split_Times * split_times() const override;
         Data_Times * times() const override;
```
* Now for this tutorial we will be using the Data_Car_State. Open datacarstateformat1.h
```
Your_User$ vi ./datacarstateformat1.h
```
```
class Data_Car_State_Format_1 : public Data_Car_State {
public:
        Data_Car_State_Format_1(std::shared_ptr<Decoder_Telemetry_Data>);
        virtual ~Data_Car_State_Format_1() {}

        unsigned int car_flags() const override;
        int oil_temp_celsius() const override;
        unsigned int oil_pressure_kpa() const override;
        int water_temp_celsius() const override;
        unsigned int water_pressure_kpa() const override;
        unsigned int fuel_pressure_kpa() const override;
        unsigned int fuel_capacity() const override;
        unsigned int brake() const override;
        unsigned int throttle() const override;
        unsigned int clutch() const override;
        float fuel_level() const override;
        float speed() const override;
        unsigned int rpm() const override;
        unsigned int max_rpm() const override;
        int steering() const override;
        unsigned int gears() const override;
        unsigned int gear() const override;
        unsigned int boost_amount() const override;
        unsigned int crash_state() const override;
        float odometer_km() const override;
        Vector_UInt tyre_flags() const override;
        Vector_UInt terrain() const override;
        Vector_Float tyre_y() const override;
...
```
* Open the implementation file datacarstateformat1.cpp. NOTE there are some hard coded values these are only for the Format 2 Packets. You can see in this snippet that the tyre_temp_left is a Format 2 only data where tyre_internal_air_temp is for Format 1.
```
 
 Vector_UInt Data_Car_State_Format_1::tyre_internal_air_temp() const {
         return telemetry_data_->tyre_internal_air_temp();
 }
 
 Vector_UInt Data_Car_State_Format_1::tyre_temp_left() const {
         Vector_UInt vu;
         return vu;
 }
```
* Now open live.h
```
Your_User$ vi ./live.h
```
* Ok so what I'm going to demonstrate is how you can capture the tyre temp and tread temp during qualifying, so you know when your tyres are up to temp for that one hot lap.
* Add the include vector with rest of the live.h includes. 
```
4 #include <vector>
```
* We want to derive a new Live_Temp class from the Live type, add this code to live.h between the pcars namespace.
```
 class Live_Temp : public Live {
 public:
         enum class TEMP {
                 COLD = 0,
                 GOOD,
                 HOT,
                 UNKNOWN
         };
 
         enum class TREAD {
                 GOOD = 0,
                 HOT,
                 UNKNOWN
         };
 
         using Temp = unsigned int;
         using Temp_Vec = std::vector<TEMP>;
         using Tread_Vec = std::vector<TREAD>;
 
         Live_Temp();
         virtual ~Live_Temp() {}
 
         void live(std::shared_ptr<Data>) override;
 private:
         Temp min_tyre_temp_;
         Temp max_tyre_temp_;
         Temp max_tread_temp_;
 
         Temp_Vec temp_;
         Tread_Vec tread_;
 
         std::string fl_temp;
         std::string fr_temp;
         std::string rl_temp;
         std::string rr_temp;
 
         std::string fl_tread;
         std::string fr_tread;
         std::string rl_tread;
         std::string rr_tread;
  };
```
* Add this to the implementation live.cpp between the pcars namespace. (This could be done better but for this tute I think it is fine)
```
 
 Live_Temp::Live_Temp()
         : min_tyre_temp_{70},
           max_tyre_temp_{80},
           max_tread_temp_{360},
           temp_{TEMP::UNKNOWN, TEMP::UNKNOWN, TEMP::UNKNOWN, TEMP::UNKNOWN},
           tread_{TREAD::UNKNOWN, TREAD::UNKNOWN, TREAD::UNKNOWN, TREAD::UNKNOWN}
 {
 }
 
 void Live_Temp::live(std::shared_ptr<Data> data)
 {
 
          bool changed = false;
  
          if (min_tyre_temp_ > data->car_states()->tyre_temp().at(0) &&
              temp_.at(0) != TEMP::COLD) {
                  temp_.at(0) = TEMP::COLD;
                  changed = true;
                  fl_temp = "FL COLD ";
          }
          if (max_tyre_temp_ < data->car_states()->tyre_temp().at(0) &&
              temp_.at(0) != TEMP::HOT) {
                  temp_.at(0) = TEMP::HOT;
                  changed = true;
                  fl_temp = "FL HOT ";
          }
          if (min_tyre_temp_ < data->car_states()->tyre_temp().at(0) &&
              max_tyre_temp_ > data->car_states()->tyre_temp().at(0) &&
             temp_.at(0) != TEMP::GOOD) {
                 temp_.at(0) = TEMP::GOOD;
                 changed = true;
                 fl_temp = "FL GO-GO ";
         }
 
         if (min_tyre_temp_ > data->car_states()->tyre_temp().at(1) &&
             temp_.at(1) != TEMP::COLD) {
                 temp_.at(1) = TEMP::COLD;
                 changed = true;
                 fr_temp = "FR COLD ";
         }
         if (max_tyre_temp_ < data->car_states()->tyre_temp().at(1) &&
             temp_.at(1) != TEMP::HOT) {
                 temp_.at(1) = TEMP::HOT;
                 changed = true;
                 fr_temp = "FR HOT ";
         }
         if (min_tyre_temp_ < data->car_states()->tyre_temp().at(1) &&
             max_tyre_temp_ > data->car_states()->tyre_temp().at(1) &&
             temp_.at(1) != TEMP::GOOD) {
                 temp_.at(1) = TEMP::GOOD;
                 changed = true;
                 fr_temp = "FR GO-GO ";
         }
 
         if (min_tyre_temp_ > data->car_states()->tyre_temp().at(2) &&
             temp_.at(2) != TEMP::COLD) {
                 temp_.at(2) = TEMP::COLD;
                 changed = true;
                 rl_temp = "RL COLD ";
         }
         if (max_tyre_temp_ < data->car_states()->tyre_temp().at(2) &&
             temp_.at(2) != TEMP::HOT) {
                 temp_.at(2) = TEMP::HOT;
                 changed = true;
                 rl_temp = "RL HOT ";
         }
         if (min_tyre_temp_ < data->car_states()->tyre_temp().at(2) &&
             max_tyre_temp_ > data->car_states()->tyre_temp().at(2) &&
             temp_.at(2) != TEMP::GOOD) {
                 temp_.at(2) = TEMP::GOOD;
                 changed = true;
                 rl_temp = "RL GO-GO ";
         }
 
         if (min_tyre_temp_ > data->car_states()->tyre_temp().at(3) &&
             temp_.at(3) != TEMP::COLD) {
                 temp_.at(3) = TEMP::COLD;
                 changed = true;
                 rr_temp = "RR COLD ";
         }
         if (max_tyre_temp_ < data->car_states()->tyre_temp().at(3) &&
             temp_.at(3) != TEMP::HOT) {
                 temp_.at(3) = TEMP::HOT;
                 changed = true;
                 rr_temp = "RR HOT ";
         }
         if (min_tyre_temp_ < data->car_states()->tyre_temp().at(3) &&
             max_tyre_temp_ > data->car_states()->tyre_temp().at(3) &&
             temp_.at(3) != TEMP::GOOD) {
                 temp_.at(3) = TEMP::GOOD;
                 changed = true;
                 rr_temp = "RR GO-GO ";
         }
 
 
         if (max_tread_temp_ > data->car_states()->tyre_tread_temp().at(0) &&
             tread_.at(0) != TREAD::GOOD) {
                 tread_.at(0) = TREAD::GOOD;
                 changed = true;
                 fl_tread = "FL GOOD ";
         }
         if (max_tread_temp_ < data->car_states()->tyre_tread_temp().at(0) &&
             tread_.at(0) != TREAD::HOT) {
                 tread_.at(0) = TREAD::HOT;
                 changed = true;
                 fl_tread = "FL HOT ";
         }
 
         if (max_tread_temp_ > data->car_states()->tyre_tread_temp().at(1) &&
             tread_.at(1) != TREAD::GOOD) {
                 tread_.at(1) = TREAD::GOOD;
                 changed = true;
                 fr_tread = "FR GOOD ";
         }
         if (max_tread_temp_ < data->car_states()->tyre_tread_temp().at(1) &&
             tread_.at(1) != TREAD::HOT) {
                 tread_.at(1) = TREAD::HOT;
                 changed = true;
                 fr_tread = "FR HOT ";
         }
 
         if (max_tread_temp_ > data->car_states()->tyre_tread_temp().at(2) &&
             tread_.at(2) != TREAD::GOOD) {
                 tread_.at(2) = TREAD::GOOD;
                 changed = true;
                 rl_tread = "FL GOOD ";
         }
         if (max_tread_temp_ < data->car_states()->tyre_tread_temp().at(2) &&
             tread_.at(2) != TREAD::HOT) {
                 tread_.at(2) = TREAD::HOT;
                 changed = true;
                 rl_tread = "RL HOT ";
         }
 
         if (max_tread_temp_ > data->car_states()->tyre_tread_temp().at(3) &&
             tread_.at(3) != TREAD::GOOD) {
                 tread_.at(3) = TREAD::GOOD;
                 changed = true;
                 rr_tread = "RR GOOD ";
         }
         if (max_tread_temp_ < data->car_states()->tyre_tread_temp().at(3) &&
             tread_.at(3) != TREAD::HOT) {
                 tread_.at(3) = TREAD::HOT;
                 changed = true;
                 rr_tread = "RR HOT ";
         }
 
         if (changed) {
                 cout << "TYRE TEMP" << endl;
                 cout << fl_temp << fr_temp << rl_temp << rr_temp << endl;
                 cout << "TYRE TREAD TEMP" << endl;
                 cout << fl_tread << fr_tread << rl_tread << rr_tread;
                 for (int i = 0; i < 20; ++i) {
                         cout << endl;
                 }
         }
 }
```
* in the src directory run make clean then make
```
Your_User$ make clean
rm -f ../obj/*.o *~ ../lib/librough_idea_pcars.dylib
Your_User$ make
g++ -m64 -std=c++14 -Wall -Wextra  -I./ -c capturetelemetry.cpp  -o ../obj/capturetelemetry.o
g++ -m64 -std=c++14 -Wall -Wextra  -I./ -c capturetelemetryv2.cpp  -o ../obj/capturetelemetryv2.o
...
```
* Now we need to add the class to the capture_lap_data. Change directory to rough_idea_project_cars-master/bin/capture_lap_data
```
Your_User$ ~/your_working_dir/rough_idea_project_cars-master/bin/capture_lap_data
```
* Open main.cpp and change Live_Feed to Live_Temp
```
  int main() {
  
          pcars::Process_Lap process;
          //pcars::Live_Feed live;
          pcars::Live_Temp live;
          pcars::Capture_Telemetry telemetry(&process, &live);
  
          return 0;
  
  }
```
* Run make
```
Your_User$ make
```
* Set the library path.
```
Your_User$ export DYLD_LIBRARY_PATH=../../lib
```
* Run pcars and do some qualy laps. 
```
Your_User$ ./pcars
Started
```
* You may have noticed that the out lap does not show the tyre state, which is not realy what we want. We want to see the tyre state coming into the first lap. The API controls the state of the app using the Chain of Responsibility Design Pattern which allows a request to run down a chain and find its response. The set of request classes implement this responsibility open requestsessionstatequalify.h. First we need to include the requestracestatenotstarted.h header file to the qualy header file. So cd back to the src directory.
* Open requestsessionstatequalify.h and add the the include file for the requestracestatenotstarted.h.
```
#include "requestracestatenotstarted.h"
```
* Now add a not started member to the qualy class.
```
  class Request_Session_State_Qualify : public Request {
  public:
          Request_Session_State_Qualify(Record_Lap *, Request * request = nullptr);
          virtual ~Request_Session_State_Qualify() {}
  
          bool request(std::shared_ptr<Data>) override;
  
  private:
          Request * request_;
  
          Request_Race_State_Not_Started notstarted_; <------- HERE
          Request_Race_State_Racing racing_;
  
          Request_Session_State_Qualify(const Request_Session_State_Qualify&) = delete;
          Request_Session_State_Qualify& operator=(const Request_Session_State_Qualify&) = delete;
  };
```
* Now open the implementation file requestsessionstatequalify.cpp and add the not started object to the request chain in the constructors initialisation list. 
```
   Request_Session_State_Qualify::Request_Session_State_Qualify(Record_Lap * record, Request * request)
           : request_{request},
             notstarted_{record},
            racing_{record,&notstarted_} {}
```
* What is happening is the chain first checks not start and if we are in a not started state we will run the recording from there else we move down the chain to racing and see if we are racing.  This class allows us to collect data at all different application states.
* Make clean and Make again
```
Your_User$ make clean
rm -f ../obj/*.o *~ ../lib/librough_idea_pcars.dylib
Your_User$ make
g++ -m64 -std=c++14 -Wall -Wextra  -I./ -c capturetelemetry.cpp  -o ../obj/capturetelemetry.o
g++ -m64 -std=c++14 -Wall -Wextra  -I./ -c capturetelemetryv2.cpp  -o ../obj/capturetelemetryv2.o
...
```
* Go back to the bin directory and start pcars and do some laps you don't need to rebuild, pcars will pick up the changes from the shared library.  
* My idea of the live type was so that GUI developers can use the live feed to create their own unique pcars displays.
* To Be Continued, next will be a tute on the post lap process.
 
## <a name="T-Part3"></a>Part 2 Roll Your Own Post Lap Process

### Prerequisites

Have done tute 1 and 2. 

### Tute

* I'm going to assume that you have done tute 1 and 2 and skip a lot of the basics and just get straight into adding a new process.

