#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <functional> 
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid):_pid{pid}{
}
// TODO: Return this process's ID
int Process::Pid() { return _pid; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
  vector<string> cpu_data = LinuxParser::CpuUtilization(Process::Pid());

    int utime = std::stoi(cpu_data[14-1]);
    int stime = std::stoi(cpu_data[15-1]);

    int starttime = std::stoi(cpu_data[22-1]);
    
  	long total_time = utime+stime;
    //int seconds = LinuxParser::UpTime() - (starttime/sysconf(_SC_CLK_TCK));
  int seconds = LinuxParser::UpTime()-(starttime/sysconf(_SC_CLK_TCK));
  cpuusage = (total_time/sysconf(_SC_CLK_TCK))/double(seconds);
  return cpuusage; 
}

// TODO: Return the command that generated this process
string Process::Command() { 
  return LinuxParser::Command(Process::Pid()); 
}

// TODO: Return this process's memory utilization
string Process::Ram() {
  	int ram = std::stoi(LinuxParser::Ram(Process::Pid()))*0.001;
 	return std::to_string(ram); 
}

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(Process::Pid()); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
  return LinuxParser::UpTime(Process::Pid())/sysconf(_SC_CLK_TCK);
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process& a) {
	return a.CpuUtilization() < this->CpuUtilization();
}