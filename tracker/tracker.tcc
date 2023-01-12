template <class T>
template <typename... Ts>
Tracker<T>::Tracker(Ts... args) : T{args...} {
  counter++;
}

template <class T> Tracker<T>::~Tracker() { counter--; }

template <class T> unsigned count() { return Tracker<T>::counter; }
