#include <string>

#include "format.h"

using std::string;

string Format::ElapsedTime(long seconds) {
  long hh, mm, ss;
  std::string time;

  hh = seconds / 3600;
  mm = (seconds % 3600) / 60;
  ss = (seconds % 3600) % 60;

  char* x = new char[100];
  sprintf(x, "%02ld:%02ld:%02ld", hh, mm, ss);
  time = x;

  delete[] x;
  return time;
}