#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_(pid){};

int Process::Pid() { return this->pid_; }

float Process::CpuUtilization() const {
  return LinuxParser::CpuUtilization(this->pid_);
}

string Process::Command() { return LinuxParser::Command(this->pid_); }

string Process::Ram() const { return LinuxParser::Ram(this->pid_); }

string Process::User() { return LinuxParser::User(this->pid_); }

long int Process::UpTime() { return LinuxParser::UpTime(this->pid_); }

bool Process::operator<(Process const& a) const {
  return this->CpuUtilization() > a.CpuUtilization();
}