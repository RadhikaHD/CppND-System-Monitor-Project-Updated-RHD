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

// TODO: Return this process's ID
int Process::Pid() { return this->pid_; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

string Process::Command() { return LinuxParser::Command(this->pid_); }

string Process::Ram() { return LinuxParser::Ram(this->pid_); }

// TODO: Return the user (name) that generated this process
string Process::User() { return string(); }

long int Process::UpTime() { return LinuxParser::UpTime(this->pid_); }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }