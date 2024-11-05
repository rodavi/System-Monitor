#include "processor.h"
#include <string>
#include "linux_parser.h"
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  	std::vector<long> cpu_data;
  	for(std::string data:LinuxParser::CpuUtilization()){
    	cpu_data.push_back(std::stol(data));
    }
	
  
  long Idle = cpu_data[3] + cpu_data[4];
  
  long nonIdle = cpu_data[0] + cpu_data[1] + cpu_data[2] + cpu_data[5] + cpu_data[6] + cpu_data[7];
  
  long Total = Idle + nonIdle;
  long Total_prev = Idle_prev +nonIdle_prev;
  
  long totald = Total -Total_prev;
  long idled = Idle -Idle_prev;
  float usage_percentage = 1-idled/double(totald);
  Idle_prev = Idle;
  nonIdle_prev = nonIdle;
  return  usage_percentage;
}