#include <cassert> // assert
#include <utility>
#include <iostream>

template <typename T>
class Counted_Pointer {
    public:
        Counted_Pointer();

        template <typename ...Ts>
        Counted_Pointer(Ts&&... args);

        Counted_Pointer(Counted_Pointer<T> const& other);
        Counted_Pointer(Counted_Pointer<T> && other);

        Counted_Pointer<T>& operator=(Counted_Pointer<T> const& other);
        Counted_Pointer<T>& operator=(Counted_Pointer<T> && other);

        ~Counted_Pointer();

        T& operator*();
        T const& operator*() const;

        T* operator->();
        T const* operator->() const;

        int count() const;

    private:
        struct Counted_Block {
            T data;
            int count;
        };

        Counted_Block* block;
};

template <typename T>
Counted_Pointer<T>::Counted_Pointer() : block{nullptr} {}

template <typename T>
template <typename ...Ts>
Counted_Pointer<T>::Counted_Pointer(Ts&&... args) : 
    block{ new Counted_Block{ T {std::forward<Ts>(args)...}, 1} } {}

template <typename T>
Counted_Pointer<T>::Counted_Pointer(Counted_Pointer<T> const& other) :block{other.block} {
    if (block) {
        block->count++;
    }
}

template <typename T>
Counted_Pointer<T>::Counted_Pointer(Counted_Pointer<T> && other) : block{other.block} {
    other.block = nullptr;
}

template <typename T>
Counted_Pointer<T>& Counted_Pointer<T>::operator=(Counted_Pointer<T> const& other) {
    // Destructor for this is called when we reassign *this
    return *this = Counted_Pointer<T>{other};
}

template <typename T>
Counted_Pointer<T>& Counted_Pointer<T>::operator=(Counted_Pointer<T> && other) {
    // Destructor for other is called with our block when other goes out of scope
    std::swap(block, other.block);
    return *this;
}

template <typename T>
Counted_Pointer<T>::~Counted_Pointer() {
    std::cout << "Hi from dtor" << std::endl;
    if (block) {
        block->count--;
        if (block->count == 0) {
            delete block;
        }
    }
}

template <typename T>
T& Counted_Pointer<T>::operator*() {
    return block->data;
}

template <typename T>
T const& Counted_Pointer<T>::operator*() const {
    return block->data;
}

template <typename T>
T* Counted_Pointer<T>::operator->() {
    return &(block->data);
}

template <typename T>
T const* Counted_Pointer<T>::operator->() const {
    return &(block->data);
}

template <typename T>
int Counted_Pointer<T>::count() const {
    return !block ? 0 : block->count;
}

template <typename T, typename ...Ts>
Counted_Pointer<T> make_counted(Ts&&... args) {
    return Counted_Pointer<T>{std::forward<Ts>(args)...};
}


// Start of testcases (no modification should be needed beyond this point)

struct X { int a; int b; };

Counted_Pointer<int> test(Counted_Pointer<int> ptr)
{
    return ptr;
}

int main()
{
    // Create a counted_pointer to an X object
    auto ptr1 = make_counted<X>(3, 5);

    // Check that the data and count is correct
    assert(ptr1->a == 3);
    assert(ptr1->b == 5);
    assert(ptr1.count() == 1);
    {
	// Create a const copy and check that the count is increased
	// This will call the non-const overload of the copy constructor
        Counted_Pointer<X> const cpy1 = ptr1;
	assert(ptr1.count() == 2);
	assert(cpy1.count() == 2);

	// Check that the data is the same
	assert(cpy1->a == 3);
	assert(cpy1->b == 5);

	// Modify the original pointer...
	++ptr1->a;
	++ptr1->b;

	// ... and check that the change occurs in cpy1
	assert(cpy1->a == 4);
	assert(cpy1->b == 6);

	// Make another copy to check that both copy constructors works
	// This will call the const overload of the copy constructor
	{
	    auto cpy2 = cpy1;
	    assert(ptr1.count() == 3);
	    assert(cpy1.count() == 3);
	    assert(cpy2.count() == 3);
	}

	assert(ptr1.count() == 2);
    }

    // Create an empty pointer
    Counted_Pointer<X> other { };
    assert(other.count() == 0);

    // Test the move assignment
    other = std::move(ptr1);
    assert(ptr1.count() == 0);
    assert(other.count() == 1);

    assert(other->a == 4);
    assert(other->b == 6);

    {
	// Test the move constructor
	auto ptr2 = test(Counted_Pointer<int>{8});
	assert(ptr2.count() == 1);
	assert(*ptr2 == 8);
	
	// Try the const version as well
	Counted_Pointer<int> const ptr3 = ptr2;
	assert(ptr3.count() == 2);
	assert(*ptr3 == 8);
	
	*ptr2 = 1;
	assert(*ptr3 == 1);
    }
    
    // Check with the terminal command:
    // valgrind ./a.out
    // That no memory is leaked.
}
