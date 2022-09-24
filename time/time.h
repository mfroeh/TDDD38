#pragma once
#include <istream>
#include <ostream>
#include <string>

struct Time {
  unsigned int hour{};
  unsigned int minutes{};
  unsigned int seconds{};
};

bool is_valid(Time const &time);
std::string to_string(Time const &time);
bool is_am(Time const &time);
Time operator+(Time const &time, unsigned int seconds);
Time operator+(unsigned int seconds, Time const &time);
Time operator-(Time const &time, unsigned int seconds);
Time operator-(unsigned int seconds, Time const &time);
Time &operator++(Time &time);
Time &operator--(Time &time);
Time operator++(Time &time, int);
Time operator--(Time &time, int);
bool operator>(Time const &t1, Time const &t2);
bool operator>=(Time const &t1, Time const &t2);
bool operator==(Time const &t1, Time const &t2);
bool operator<=(Time const &t1, Time const &t2);
bool operator<(Time const &t1, Time const &t2);
bool operator!=(Time const &t1, Time const &t2);
std::istream &operator>>(std::istream &istream, Time &time);
std::ostream &operator<<(std::ostream &ostream, Time const &time);
