#ifndef ALOCATOR_H
#define ALOCATOR_H
#include <iostream>

template <class T>
class Allocator {
    typedef T value_type;
    Allocator() noexcept {}
    template <class U> Allocator (const Allocator<U>&) noexcept {
        std::cout << "Allocator<T>::Allocator(const Allocator<U>&): " << std::endl;
    }
    T* allocate (std::size_t n) {
        std::cout << "Allocating "  << std::endl;
        return reinterpret_cast<T*>( ::operator new(n*sizeof(T)));
    }
    void deallocate (T* p, std::size_t n) {
        std::cout << "Deallocating "  << std::endl;
        ::operator delete(p);
    }
    template<typename U, typename... Args>
     void construct(U* p, Args&&... args) {
       std::cout << "Constructing " << std::endl;
       new (p) U(std::forward<Args>(args)...);
     }

     void destroy(T* p) {
       std::cout << "Destroying " << std::endl;
       p->~T();
     }
};
#endif // ALOCATOR_H
