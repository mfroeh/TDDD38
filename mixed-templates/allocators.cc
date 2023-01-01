#include <cassert>
#include <iostream>
#include <string>
#include <utility>
using namespace std::literals;

template <typename T> struct New_Allocator {

  template <typename... Ts> static T *create(Ts &&...args) {
    return new T{std::forward<Ts>(args)...};
  }

  static void destroy(T *ptr) { delete ptr; }
};

template <typename T> struct Tracker_Allocator {

  template <typename... Ts> static T *create(Ts &&...args) {
    T *ptr = New_Allocator<T>::create(std::forward<Ts>(args)...);
    std::cout << "Allocated at " << ptr << std::endl;
    return ptr;
  }

  static void destroy(T *ptr) {
    std::cout << "Deallocating at " << ptr << std::endl;
    New_Allocator<T>::destroy(ptr);
  }
};

template <typename T, template <typename> typename Allocator = New_Allocator>
class Stack {

  struct Node;

public:
  Stack() : head{nullptr} {}

  Stack(Stack const &) = delete;
  Stack(Stack &&) = delete;

  Stack &operator=(Stack const &) = delete;
  Stack &operator=(Stack &&) = delete;

  ~Stack() {
    while (!empty()) {
      pop();
    }
  }

  void push(T const &value) { head = Allocator<Node>::create(value, head); }

  T pop() {
    T result{top()};
    Node *old{head};
    head = head->next;
    Allocator<Node>::destroy(old);
    return result;
  }

  T &top() { return head->value; }

  T const &top() const { return head->value; }

  bool empty() const { return head == nullptr; }

private:
  struct Node {
    T value;
    Node *next;
  };

  Node *head;
};

int main() {
  Stack<int> st{};
  assert(st.empty());

  st.push(1);
  assert(!st.empty());
  assert(st.top() == 1);

  st.push(2);
  assert(st.top() == 2);
  assert(st.pop() == 2);

  assert(st.pop() == 1);

  assert(st.empty());

  st.push(3);
  assert(st.pop() == 3);

  st.push(4);

  st.push(5);
  assert(st.pop() == 5);

  Stack<int, Tracker_Allocator> st1{};
  assert(st1.empty());

  st1.push(1);
  assert(!st1.empty());
  assert(st1.top() == 1);

  st1.push(2);
  assert(st1.top() == 2);
  assert(st1.pop() == 2);

  assert(st1.pop() == 1);

  assert(st1.empty());

  st1.push(3);
  assert(st1.pop() == 3);

  st1.push(4);

  st1.push(5);
  assert(st1.pop() == 5);

  Stack<std::string, Tracker_Allocator> st2{};

  st2.push("Some_string"s);
  assert(st2.top() == "Some_string"s);
  assert(st2.pop() == "Some_string"s);
  assert(st2.empty());
}
