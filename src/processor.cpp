#include "processor.h"
#include <iostream>
#include <string>
#include <vector>
#include "linux_parser.h"

float Processor::Utilization() {
  std::vector<std::string> cpu_util = LinuxParser::CpuUtilization();
  // user    nice   system  idle      iowait irq   softirq  steal  guest
  // guest_nice
  float user, nice, system, idle, iowait, irq, softirq, steal;
  float nonidle;
  float Idle;
  float total;

  user = std::stof(cpu_util[0]);
  nice = std::stof(cpu_util[1]);
  system = std::stof(cpu_util[2]);
  idle = std::stof(cpu_util[3]);
  iowait = std::stof(cpu_util[4]);
  irq = std::stof(cpu_util[5]);
  softirq = std::stof(cpu_util[6]);
  steal = std::stof(cpu_util[7]);

  Idle = idle + iowait;
  nonidle = user + nice + system + irq + softirq + steal;
  total = Idle + nonidle;
  utilization_ = nonidle / total;
  return utilization_;
}