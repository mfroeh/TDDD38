#include "time.h"
#include <sstream>

using namespace std;

Time from_seconds(unsigned int seconds) {
  unsigned int hours{seconds / 3600u};
  seconds -= 3600 * hours;
  unsigned int minutes{seconds / 60u};
  seconds -= 60 * minutes;
  return Time{hours % 24, minutes, seconds};
}

unsigned int to_seconds(Time const &time) {
  return time.hour * 3600 + time.minutes * 60 + time.seconds;
}

bool is_valid(Time const &time) {
  return time.hour < 24 && time.minutes < 60 && time.seconds < 60;
}

std::string to_string(Time const &time) {
  ostringstream ostream{};
  if (time.hour < 10) {
    ostream << "0";
  }
  ostream << time.hour << ":";

  if (time.minutes < 10) {
    ostream << "0";
  }
  ostream << time.minutes << ":";

  if (time.seconds < 10) {
    ostream << "0";
  }
  ostream << time.seconds;
  return ostream.str();
}

bool is_am(Time const &time) { return time.hour < 12; }

Time operator+(unsigned int seconds, Time const &time) {
  return time + seconds;
}
Time operator+(Time const &time, unsigned int seconds) {
  unsigned int time_total = to_seconds(time);
  // Be careful of overflow
  if ((time_total + seconds) < time_total) {
    return Time{23, 59, 59};
  }
  return from_seconds(time_total + seconds);
}

Time operator-(Time const &time, unsigned int seconds) {
  unsigned int time_total = to_seconds(time);
  // Be careful of underflow
  if (seconds > time_total) {
    return Time{0, 0, 0};
  }
  return from_seconds(time_total - seconds);
}

Time operator-(unsigned int seconds, Time const &time) {
  return time - seconds;
}

Time &operator++(Time &time) {
  if (++time.seconds == 60) {
    time.seconds = 0;
    if (++time.minutes == 60) {
      time.minutes = 0;
      if (++time.hour == 24) {
        time.hour = 0;
      }
    }
  }
  return time;
}

Time &operator--(Time &time) {
  if (--time.seconds == -1u) {
    time.seconds = 59;
    if (--time.minutes == -1u) {
      time.minutes = 59;
      if (--time.hour == -1u) {
        time.hour = 23;
      }
    }
  }
  return time;
}

Time operator++(Time &time, int) {
  Time temp{time};
  ++time;
  return temp;
}

Time operator--(Time &time, int) {
  Time temp{time};
  --time;
  return temp;
}

bool operator>(Time const &t1, Time const &t2) {
  return to_seconds(t1) > to_seconds(t2);
}

bool operator>=(Time const &t1, Time const &t2) {
  return to_seconds(t1) >= to_seconds(t2);
}

bool operator==(Time const &t1, Time const &t2) {
  return to_seconds(t1) == to_seconds(t2);
}

bool operator<=(Time const &t1, Time const &t2) {
  return to_seconds(t1) <= to_seconds(t2);
}

bool operator<(Time const &t1, Time const &t2) {
  return to_seconds(t1) < to_seconds(t2);
}

bool operator!=(Time const &t1, Time const &t2) { return !(t1 == t2); }

std::basic_istream<char> &operator>>(std::basic_istream<char> &istream,
                                     Time &time) {
  string str{};
  istream >> str;
  time.hour = stoi(str.substr(0, 2));
  time.minutes = stoi(str.substr(3, 5));
  time.seconds = stoi(str.substr(6, 8));
  return istream;
}

std::basic_ostream<char> &operator<<(std::basic_ostream<char> &ostream,
                                     Time const &time) {
  ostream << to_string(time);
  return ostream;
}
