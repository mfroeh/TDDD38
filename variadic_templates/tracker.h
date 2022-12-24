template <class T>
class Tracker : public T {
  public:
    static unsigned counter;

    template <typename ...Ts>
    Tracker(Ts... args);
    ~Tracker();

    Tracker(T const& rhs);
    Tracker<T>& operator=(T const& rhs);
};

template <typename T>
unsigned count() {
  return Tracker<T>::counter;
}

template <class T>
template <typename ...Ts>
Tracker<T>::Tracker(Ts... args) : T{args...} {
  counter++;
}

template <typename T>
Tracker<T>::~Tracker() {
  counter--;
  (*this).~T();
}

template <class T>
Tracker<T>::Tracker(T const& rhs) {
  counter++;
  T::T(rhs);
}

template <class T>
Tracker<T>& Tracker<T>::operator=(T const& rhs) {
  // TODO
}
