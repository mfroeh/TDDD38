#include "catch.hpp"
#include "time.h"
#include <sstream>

TEST_CASE("is_valid") {
  Time t1{0, 0, 0};
  Time t2{23, 59, 59};
  CHECK(is_valid(t1));
  CHECK(is_valid(t2));
  Time t3{24, 0, 0};
  Time t4{12, 60, 0};
  Time t5{12, 0, 61};
  CHECK_FALSE(is_valid(t3));
  CHECK_FALSE(is_valid(t4));
  CHECK_FALSE(is_valid(t5));
}

TEST_CASE("to_string") {
  Time t1{12, 34, 34};
  CHECK(to_string(t1) == "12:34:34");
  Time t2{0, 0, 12};
  CHECK(to_string(t2) == "00:00:12");
}

TEST_CASE("is_am") {
  Time t1{12, 34, 34};
  CHECK_FALSE(is_am(t1));
  Time t2{0, 12, 34};
  CHECK(is_am(t2));
  Time t3{2, 23, 23};
  CHECK(is_am(t3));
}

TEST_CASE("+") {
  Time t1{12, 12, 12};
  Time t2{t1 + 60};
  CHECK(t1.minutes == 12);
  CHECK(t2.minutes == 13);
  Time t3{3623 + t1};
  CHECK(t3.hour == 13);
  CHECK(t3.minutes == 12);
  CHECK(t3.seconds == 35);
  Time t4{23, 59, 58};
  Time t5{t4 + 2};
  CHECK(t5.hour == 0);
  CHECK(t5.minutes == 0);
  CHECK(t5.seconds == 0);
}

TEST_CASE("-") {
  Time t1{12, 12, 12};
  Time t2{t1 - 60};
  CHECK(t1.minutes == 12);
  CHECK(t2.minutes == 11);
  Time t3{12, 0, 11};
  Time t4{12 - t3};
  CHECK(t4.hour == 11);
  CHECK(t4.minutes == 59);
  CHECK(t4.seconds == 59);
  Time t5{t1 - 20302320};
  CHECK(t5.hour == 0);
  CHECK(t5.minutes == 0);
  CHECK(t5.seconds == 0);
}

TEST_CASE("++") {
  Time t1{0, 0, 0};
  Time t2{t1++};
  CHECK(t1.seconds == 1);
  CHECK(t2.seconds == 0);
  Time t3{0, 0, 0};
  Time t4{++t3};
  CHECK(t3.seconds == 1);
  CHECK(t4.seconds == 1);
  Time t6{23, 59, 59};
  ++t6;
  CHECK(t6.hour == 0);
  CHECK(t6.minutes == 0);
  CHECK(t6.seconds == 0);
}

TEST_CASE("--") {
  Time t1{0, 0, 1};
  Time t2{t1--};
  CHECK(t1.seconds == 0);
  CHECK(t2.seconds == 1);
  Time t3{0, 0, 2};
  Time t4{--t3};
  CHECK(t3.seconds == 1);
  CHECK(t4.seconds == 1);
  Time t6{0, 0, 0};
  --t6;
  CHECK(t6.hour == 23);
  CHECK(t6.minutes == 59);
  CHECK(t6.seconds == 59);
}

TEST_CASE("> & >=") {
  Time t1{0, 1, 0};
  Time t2{0, 0, 1};
  CHECK(t1 > t2);
  Time t3{23, 59, 59};
  CHECK(t3 > t2);
  Time t4{0, 0, 1};
  CHECK(t4 >= t2);
  CHECK_FALSE(t4 >= t3);
}

TEST_CASE("== & !=") {
  Time t1{23, 59, 58};
  Time t2{23, 59, 59};
  CHECK(t1 != t2);
  Time t3{23, 59, 59};
  CHECK(t3 == t2);
  CHECK(t3 == Time{23, 59, 59});
}

TEST_CASE("< & <=") {
  Time t1{23, 59, 58};
  Time t2{23, 59, 59};
  CHECK(t1 < t2);
  Time t3{23, 59, 59};
  CHECK_FALSE(t3 < t2);
  CHECK(t3 <= t2);
  Time t4{0, 0, 0};
  CHECK(t4 <= t3);
}

TEST_CASE(">>") {
  Time t1{};
  std::istringstream iss{"01:23:33"};
  iss >> t1;
  CHECK(t1.hour == 1);
  CHECK(t1.minutes == 23);
  CHECK(t1.seconds == 33);
}

TEST_CASE("<<") {
  Time t1{23, 42, 1};
  std::ostringstream oss{};
  oss << t1;
  CHECK(oss.str() == "23:42:01");
}
