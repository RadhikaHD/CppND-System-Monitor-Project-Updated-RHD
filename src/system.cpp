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

  vector<int> pids = LinuxParser::Pids();

  for (auto i : pids) {
    Process process(i);
    processes_.push_back(process);
  }
}

Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() {
  std::sort(processes_.begin(), processes_.end());
  return processes_;
}

std::string System::Kernel() { return kernel_; }

float System::MemoryUtilization() {
  float memory;
  memory = LinuxParser::MemoryUtilization();
  return memory;
}

std::string System::OperatingSystem() { return OSname_; }

int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

long System::UpTime() {
  long uptime_;
  uptime_ = LinuxParser::UpTime();
  return uptime_;
}