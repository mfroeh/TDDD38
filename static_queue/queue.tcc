#include <iostream>

template <typename T, size_t N>
void Queue<T, N>::enqueue(T value) {
    if (!full()) {
        queue[tail++ % N] = value;
    } else {
        throw queue_error{"Tried to enqueue into full queue"};
    }
}

template <typename T, size_t N>
T Queue<T, N>::dequeue() {
    if (empty()) {
        throw queue_error{"Tried to dequeue empty queue"};
    }
    T val{queue[head++ % N]};

    return val;
}

template <typename T, size_t N>
bool Queue<T, N>::empty() const {
    // If we have dequeued exactly as many values as we have dequeued
    return head == tail;
}

template <typename T, size_t N>
bool Queue<T, N>::full() const {
    // If we have enqued exactly N more values than we have dequeued the queue is full
    return tail - head == N;
}

template <typename T, size_t N>
void Queue<T, N>::clear() {
    head = tail = 0;
}

template <typename T, size_t N>
T& Queue<T, N>::front() {
    if (empty()) {
        throw queue_error{"Tried to access the front of an empty queue"};
    }
    return queue[head % N];
}

template <typename T, size_t N>
T const& Queue<T, N>::front() const {
    if (empty()) {
        throw queue_error{"Tried to access the front of an empty queue"};
    }
    return queue[head % N];
}

template <typename T, size_t N>
template <size_t M>
Queue<T, N+M> Queue<T, N>::copy_and_expand() const {
    Queue<T, N+M> q{};
    for (size_t i{}; i < N; ++i) {
        q.enqueue(queue[head % N + i]);
    }
    return q;
}
