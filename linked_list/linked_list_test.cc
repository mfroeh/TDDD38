#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "linked_list.h"
#include <sstream>

TEST_CASE("insert/at") {
  LinkedList l{};

  // Insert first
  l.insert(1);
  int value{};
  l.at(0, value);
  CHECK(value == 1);

  // Insert larger
  l.insert(2);
  l.at(1, value);
  CHECK(value == 2);

  // Insert smaller
  l.insert(0);
  l.at(0, value);
  CHECK(value == 0);

  // Insert larger
  l.insert(4);
  l.at(3, value);
  CHECK(value == 4);

  // Insert negative
  l.insert(-3);
  l.at(0, value);
  CHECK(value == -3);
}

TEST_CASE("remove") {
  LinkedList l{};

  // Remove from empty list
  CHECK_FALSE(l.remove(0));

  l.insert(0);
  l.insert(1);
  l.insert(3);

  // Remove existing
  CHECK(l.remove(1));
  // Remove not existing
  CHECK_FALSE(l.remove(1));
  // Remove existing
  CHECK(l.remove(0));
  // Remove existing
  CHECK(l.remove(3));
  // Remove not existing
  CHECK_FALSE(l.remove(0));
}

TEST_CASE("remove_at") {
  LinkedList l{};

  // Remove from empty list
  CHECK_FALSE(l.remove_at(1));

  l.insert(0);
  l.insert(1);
  l.insert(3);

  // Remove existing index
  CHECK(l.remove_at(1));
  // Remove existing index
  CHECK(l.remove_at(1));
  // Remove non index
  CHECK_FALSE(l.remove_at(1));
  // Remove existing index
  CHECK(l.remove_at(0));
}

TEST_CASE("at") {
  LinkedList l{};

  // At on empty list
  int value{};
  CHECK_FALSE(l.at(0, value));

  l.insert(1);

  CHECK(l.at(0, value));
  CHECK(value == 1);

  // Index to big
  CHECK_FALSE(l.at(100, value));
}

TEST_CASE("to_string") {
  LinkedList l{};
  l.insert(-1);
  l.insert(1);
  l.insert(2);

  CHECK(l.to_string() == "-1 -> 1 -> 2");
}

TEST_CASE("<<") {
  std::ostringstream os;

  LinkedList l{};
  l.insert(-1);
  l.insert(1);
  l.insert(2);

  os << l << std::flush;

  CHECK(os.str() == "-1 -> 1 -> 2");
}

TEST_CASE("copy") {
  LinkedList l1{};
  l1.insert(1);
  l1.insert(3);

  // Copy ctor
  LinkedList l2{l1};
  l1.remove(1);
  CHECK(l2.remove(1));
  l1.remove(3);
  CHECK(l2.remove(3));
  l1.insert(1);
  CHECK_FALSE(l2.remove(1));
  CHECK(l2.length() == 0);

  // Copy assignment
  LinkedList l3{};
  l3 = l1;

  int value;
  CHECK_FALSE(l3.at(1, value));
  CHECK(l3.at(0, value));
}
TEST_CASE("move") {
  // Copy ctor
  LinkedList l1{};
  l1.insert(1);
  l1.insert(3);

  // Move constructor
  LinkedList l2{std::move(l1)};
  CHECK(l2.length() == 2);
  CHECK(l1.length() == 0);

  // Move assignment
  LinkedList l3{};
  l3.insert(2);
  l2 = std::move(l3);
  CHECK(l3.length() == 0);
  CHECK(l2.length() == 1);
}
