#include <dirent.h>
#include <unistd.h>
#include <unistd.h>
#include <iostream>
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
  string os, kernel;
  string line, version;
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

float LinuxParser::MemoryUtilization() {
  // Total used memory = MemTotal - MemFree
  float memory = 0.0;
  float MemTotal, MemFree;

  string line, key, value;
  std::ifstream stream(kProcDirectory + kMeminfoFilename);

  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "MemTotal:") MemTotal = std::stof(value);
        if (key == "MemFree:") MemFree = std::stof(value);
      }
    }
  }

  memory = ((MemTotal - MemFree) / MemTotal);
  return memory;
}

long LinuxParser::UpTime() {
  std::string uptimes, line;
  long uptime;
  std::string::size_type sz;

  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> uptimes;
  }
  uptime = std::stol(uptimes, &sz);
  return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { return 0; }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { return 0; }

vector<string> LinuxParser::CpuUtilization() {
  vector<string> cpu;
  std::string line, value;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
      if (value == "cpu")
        continue;
      else {
        cpu.push_back(value);
      }
    }
  }

  return cpu;
}

int LinuxParser::TotalProcesses() {
  int totalprocess = 0.0;

  string line, key, value;
  std::ifstream stream(kProcDirectory + kStatFilename);

  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") totalprocess = std::stoi(value);
      }
    }
  }
  return totalprocess;
}

int LinuxParser::RunningProcesses() {
  int runningprocess = 0.0;

  string line, key, value;
  std::ifstream stream(kProcDirectory + kStatFilename);

  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") runningprocess = std::stoi(value);
      }
    }
  }
  return runningprocess;
}

string LinuxParser::Command(int pid) {
  std::string line, value, command;

  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    command = linestream.str();
  }
  return command;
}

string LinuxParser::Ram(int pid) {
  std::string ram;
  int ramvalue;

  string line, key, value;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);

  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "VmSize:") ram = value;
      }
    }
  }
  ramvalue = std::stoi(ram) / 1000;
  ram = std::to_string(ramvalue);
  return ram;
}

string LinuxParser::Uid(int pid) {
  std::string line, key, value, uid;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);

  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") uid = value;
      }
    }
  }
  return uid;
}

string LinuxParser::User(int pid) {
  std::string username, uidstr, extra, line, uid;
  uid = LinuxParser::Uid(pid);

  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> username >> extra >> uidstr) {
        if (uidstr == uid) {
          return username;
        }
      }
    }
  }
  return username;
}

long LinuxParser::UpTime(int pid) {
  std::string line, value, starttimestr;
  long starttime, uptime;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    // get the 22nd value from file
    for (int i = 0; i < 22; i++) linestream >> starttimestr;
    starttime = std::stol(starttimestr);
    starttime = starttime / sysconf(_SC_CLK_TCK);
  }
  uptime = LinuxParser::UpTime() - starttime;
  return uptime;
}

float LinuxParser::CpuUtilization(int pid) {
  /*
  /proc/[PID]/stat
#14 utime - CPU time spent in user code, measured in clock ticks
#15 stime - CPU time spent in kernel code, measured in clock ticks
#16 cutime - Waited-for children's CPU time spent in user code (in clock ticks)
#17 cstime - Waited-for children's CPU time spent in kernel code (in clock
ticks)
#22 starttime - Time when the process started, measured in clock ticks
  */

  std::string line, utimestr, stimestr, cutimestr, cstimestr, starttimestr,
      buffer;
  long utime, stime, cutime, cstime, starttime, total_time;
  float seconds, cpu_usage;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    // get the 14, 15, 16, 17, 22 value from file
    for (int i = 0; i < 22; i++) {
      if (i == 13)
        linestream >> utimestr;
      else if (i == 14)
        linestream >> stimestr;
      else if (i == 15)
        linestream >> cutimestr;
      else if (i == 16)
        linestream >> cstimestr;
      else if (i == 21)
        linestream >> starttimestr;
      else
        linestream >> buffer;
    }
  }
  utime = std::stol(utimestr);

  stime = std::stol(stimestr);

  cutime = std::stol(cutimestr);

  cstime = std::stol(cstimestr);
  starttime = std::stol(starttimestr);

  total_time = utime + stime;

  total_time = total_time + cutime + cstime;

  seconds = LinuxParser::UpTime() - (starttime / sysconf(_SC_CLK_TCK));

  cpu_usage = (total_time / sysconf(_SC_CLK_TCK)) / seconds;

  return cpu_usage;
}