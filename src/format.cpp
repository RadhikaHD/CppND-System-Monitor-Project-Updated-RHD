#include <string>

#include "format.h"

using std::string;

// TODO: Complete this helper function
// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
// REMOVE: [[maybe_unused]] once you define the function
string Format::ElapsedTime(long seconds[[maybe_unused]]) {
  long hh, mm, ss;
  std::string h, m, s, time;

  hh = seconds / 3600;
  mm = (seconds % 3600) / 60;
  ss = (seconds % 3600) % 60;

  char* x = new char[h.length() + m.length() + s.length() + 32];
  sprintf(x, "%02ld:%02ld:%02ld", hh, mm, ss);
  time = x;

  delete[] x;
  return time;
}