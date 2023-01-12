#pragma once
#include <cstddef>
#include <stdexcept>

template <typename T, size_t N> class Queue {
  static_assert(N > 0, "A queue must have atleast 1 value");

public:
  void enqueue(T value);
  T dequeue();
  bool empty() const;
  bool full() const;
  void clear();
  T &front();
  T const &front() const;

  template <size_t M> Queue<T, N + M> copy_and_expand() const;

private:
  T queue[N]{};
  size_t head{};
  size_t tail{};
};

class queue_error : public std::runtime_error {
public:
  using std::runtime_error::runtime_error;
};

#include "queue.tcc"
