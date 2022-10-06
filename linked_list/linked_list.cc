#include "linked_list.h"
#include <sstream>

// Copy ctor
LinkedList::LinkedList(LinkedList const &list) {
  Link *last{};
  Link *cur{list.first};
  while (cur != nullptr) {
    Link *mine{new Link{cur->value, nullptr}};
    if (last == nullptr) {
      first = mine;
    } else {
      last->next = mine;
    }
    last = mine;
    cur = cur->next;
  }
}

// Move ctor
LinkedList::LinkedList(LinkedList &&list) {
  first = list.first;
  list.first = nullptr;
}

// Destructor
LinkedList::~LinkedList() {
  Link *cur{first};
  while (cur != nullptr) {
    Link *next{cur->next};
    delete cur;
    cur = next;
  }
}

// Copy assignment
LinkedList &LinkedList::operator=(LinkedList const &list) {
  // Move assignment of a LinkedList created by the copy ctor
  *this = LinkedList{list};
  return *this;
}

// Move assignment
LinkedList &LinkedList::operator=(LinkedList &&list) {
  first = list.first;
  list.first = nullptr;
  return *this;
}

// Insert a value into list
void LinkedList::insert(int value) {
  Link *last{};
  Link *cur{first};
  // Traverse until we find link that is greater or there are no more links
  while (cur != nullptr && value > cur->value) {
    last = cur;
    cur = cur->next;
  }

  // List is empty or value <= first value in the list
  if (last == nullptr) {
    first = new Link{value, cur};
  } else {
    last->next = new Link{value, cur};
  }
}

// Remove value
bool LinkedList::remove(int value) {
  Link *last{};
  Link *cur{first};
  while (cur != nullptr && cur->value < value) {
    last = cur;
    cur = cur->next;
  }

  if (cur == nullptr || cur->value != value) {
    return false;
  } else {
    if (last == nullptr) {
      first = cur->next;
    } else {
      last->next = cur->next;
    }
    delete cur;
    return true;
  }
}

// Remove value at index
bool LinkedList::remove_at(unsigned int index) {
  if (first == nullptr) {
    return false;
  }

  Link *last{};
  Link *cur{first};
  for (unsigned int i{0}; i < index; i++) {
    last = cur;
    cur = cur->next;
    if (cur == nullptr) {
      return false;
    }
  }

  if (last == nullptr) {
    first = nullptr;
  } else {
    last->next = cur->next;
  }
  delete cur;
  return true;
}

// Get value at index
bool LinkedList::at(unsigned int index, int &value) const {
  if (first == nullptr) {
    return false;
  }

  Link *cur{first};
  for (unsigned int i{}; i < index; i++) {
    cur = cur->next;
    if (cur == nullptr) {
      return false;
    }
  }
  value = cur->value;
  return true;
}

// Get a string representation of the list
std::string LinkedList::to_string() const {
  std::ostringstream os;

  Link *cur{first};
  while (cur != nullptr) {
    os << cur->value << " -> ";
    cur = cur->next;
  }
  std::string s = os.str();
  return s.substr(0, s.length() - 4);
}

// Write a string representation of the list to an ostream
std::ostream &operator<<(std::ostream &os, LinkedList const &list) {
  os << list.to_string();
  return os;
}

// Gets the length
unsigned int LinkedList::length() const {
  unsigned int len{};
  Link *cur{first};
  while (cur != nullptr) {
    len++;
    cur = cur->next;
  }
  return len;
}
