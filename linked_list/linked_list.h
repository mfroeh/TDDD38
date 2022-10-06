#pragma once
#include <ostream>
#include <string>

class LinkedList {
public:
  // Default ctor
  LinkedList() = default;
  // Copy ctor
  LinkedList(LinkedList const &list);
  // Move ctor
  LinkedList(LinkedList &&list);
  // Destructor
  ~LinkedList();

  // Copy assignment
  LinkedList &operator=(LinkedList const &list);
  // Move assignment
  LinkedList &operator=(LinkedList &&list);

  // Insert a value into list
  void insert(int value);
  // Remove value
  bool remove(int value);
  // Remove value at index
  bool remove_at(unsigned int index);
  // Get value at index
  bool at(unsigned int index, int &value) const;
  // Get a string representation of the list
  std::string to_string() const;
  // Write a string representation of the list to an ostream
  friend std::ostream &operator<<(std::ostream &os, LinkedList const &list);
  // Gets the length
  unsigned int length() const;

private:
  // Represents a link
  struct Link {
    // The value of the link
    int value{};
    // The next link
    Link *next{};
  };

  // The first Link in the list
  Link *first{};
};
