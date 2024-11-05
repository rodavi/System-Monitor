#include <string>
#include <iostream>
#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds) { 
  int hours_, rem_hours;
  int minutes_, rem_minutes;
  
  hours_ = seconds/3600.0; 
  rem_hours = seconds%3600;
  minutes_ = rem_hours/60.0;
  rem_minutes = rem_hours%60;
  string str_h, str_m, str_s;
    
  if(hours_<10) str_h = "0"+std::to_string(hours_);
  else str_h = std::to_string(hours_);
  if(minutes_<10) str_m = "0"+std::to_string(minutes_);
  else str_m = std::to_string(minutes_);
  if(rem_minutes<10) str_s = "0"+std::to_string(rem_minutes);
  else str_s = std::to_string(rem_minutes);
  string str_time = str_h+":"+str_m+":"+str_s;
  return str_time; 
}