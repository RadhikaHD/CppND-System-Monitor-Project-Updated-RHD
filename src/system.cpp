#include <unistd.h>
#include <cstddef>
#include <iostream>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

System::System() {
  this->OSname_ = LinuxParser::OperatingSystem();
  this->kernel_ = LinuxParser::Kernel();
}

Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  vector<int> pids = LinuxParser::Pids();
  // do the following for all pids
  for (auto i : pids) {
    // create process (call constructor using pid??)
    Process process(i);
    // push it back in the vector processes_
    processes_.push_back(process);
  }
  return processes_;
}

std::string System::Kernel() { return kernel_; }

float System::MemoryUtilization() {
  float memory;
  memory = LinuxParser::MemoryUtilization();
  return memory;
}

std::string System::OperatingSystem() { return OSname_; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long System::UpTime() {
  long uptime_;
  uptime_ = LinuxParser::UpTime();
  return uptime_;
}