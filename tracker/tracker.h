template <class T>
class Tracker : public T { 
    public:
        inline static unsigned counter{};

        template <typename ...Ts>
        Tracker(Ts... args);
        ~Tracker();
};

template <class T>
unsigned count();

#include "tracker.tcc"
