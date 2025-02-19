#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string line;
  string key;
  string value;
  string units;
  long total_mem{0};
  long free_mem{0};

  std::ifstream filestream(kProcDirectory + kMeminfoFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value >> units) {
        if (key == "MemTotal:") {
          total_mem = std::stol(value);
        }
        else if(key == "MemFree:"){
          free_mem = std::stol(value);
        }
      }
    }
  }
  return (total_mem-free_mem)/double(total_mem); 
}

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
  string line;
  string uptime, uptime2;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if(stream.is_open()){
  	std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptime>> uptime2;
  }
  long uptime_long = std::stoi(uptime); 
  return uptime_long;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
/*long LinuxParser::ActiveJiffies(int pid) { 
return 0;
}*/

vector<string> LinuxParser::CpuUtilization(int pid) { 
  string line;
  string value;
  //long total_time{0};
  vector<string> data_cpu;
  
  string s_pid = std::to_string(pid);
  std::fstream filestream(kProcDirectory+s_pid+kStatFilename);
  if(filestream.is_open()){
  	std::getline(filestream, line);
    std::istringstream linestream(line);
    while(linestream>>value){
    	data_cpu.push_back(value);
    }
  }
  return data_cpu;
}

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() { 
	string line, cpu_string;
  	vector<string> DataCPU;
  	
  	std::ifstream filestream(kProcDirectory+kStatFilename);
  	if(filestream.is_open()){
      	std::getline(filestream, line);
    	std::istringstream linestream(line);
      	
      	while(linestream>>cpu_string){
          DataCPU.push_back(cpu_string);
          //std::cout << cpu_string<<"\t";
        }
    }
  	else{
    	std::cout<<"File not possible to open\n";
    }
  	DataCPU.erase(DataCPU.begin());
  	return DataCPU; 
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  string key, value;
  string line;
  int n_processes{0};
  
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          n_processes = std::stoi(value);
        }
      }
    }
  }
  return n_processes; 
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() { 
  string key, value;
  string line;
  int n_act_processes{0};
  
  std::ifstream filestream(kProcDirectory + kStatFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          n_act_processes = std::stoi(value);
        }
      }
    }
  }
  return n_act_processes; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string command;
  string s_pid = std::to_string(pid);
  std::fstream filestream(kProcDirectory+s_pid+kCmdlineFilename);
  if(filestream.is_open()){
  	std::getline(filestream, command);
    return command;
  }
  return "No command"; 
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string key, value, unit, line;
  string s_pid = std::to_string(pid);
  std::fstream filestream(kProcDirectory+s_pid+kStatusFilename);
  if(filestream.is_open()){
  	while(std::getline(filestream, line)){
    	std::istringstream linestream(line);
      	linestream >> key >> value >> unit;
      	
      	if(key == "VmSize:"){
        	return value;
        }
    }
  }
  return "0.0"; 
}

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
  string line;
  string key;
  string value{"empty"};
  string s_pid = std::to_string(pid);
  std::fstream filestream(kProcDirectory+s_pid+kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) {
  string line, user;
  string key;
  string value{"empty"};
  string uid = LinuxParser::Uid(pid);
  std::fstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> user >> key >> value) {
        if (value == uid) {
          return user;
        }
      }
    }
  }
  return value;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) { 
  string key, value, unit, line;
  string s_pid = std::to_string(pid);
  std::fstream filestream(kProcDirectory+s_pid+kStatFilename);
  if(filestream.is_open()){
  	std::getline(filestream, line);
    std::istringstream linestream(line);
    int i=0;
    while(i<22){
    	linestream >> value;
      	i++;
    }

  }
  return std::stol(value); 
}
