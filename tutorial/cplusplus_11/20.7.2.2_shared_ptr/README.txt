.
    Header     : <memory>
    Signature  : constexpr shared_ptr() noexcept;
                 constexpr shared_ptr(nullptr_t);
                 template<class U>
                 explicit  shared_ptr(U* p);
                 template<class U, class D>
                           shared_ptr(U* p, D del);
                 template<class D>
                           shared_ptr(nullptr_t p, D del);
                 template<class U, class D, class Alloc>
                           shared_ptr(U* p, D del, Alloc alloc);
                 template<class D, class Alloc>
                           shared_ptr(nullptr_t p, D del, Alloc alloc);
                           shared_ptr(const shared_ptr& x) noexcept;
                 template<class U>
                           shared_ptr(const shared_ptr<U>& x) noexcept;
                 template<class U>
                 explicit  shared_ptr(const weak_ptr<U>& x);
                           shared_ptr(hared_ptr&& x) noexcept;
                 template<class U>
                           shared_ptr(shared_ptr<U>&& x) noexcept;
                 template<class U>
                           shared_ptr(auto_ptr<U>&& x);
                 template<class U, class D>
                           shared_ptr(unique_ptr<U,D>&& x);
                 template<class U>
                           shared_ptr (const shared_ptr<U>& x, element_type* p) noexcept;

    Description:
        - shared_ptr is a smart pointer that retains shared ownership of an
          object through a pointer. Several shared_ptr objects may own the same
          object. The object is detroyed and its memory deallocated when either
          of the following happens:
             * the last remaining shared_ptr owning the object is detroyed
             * the last remaining shared_ptr owning the object is assigned
               another pointer via operator= or reset()
        - the object is detroyed using delete-expression or a custom deleter
          that is supplied to shared_ptr during construction
        - shared_ptr can be accessed safely from multiple thread only by using
          std::atomic...<std::shared_ptr> functions, defined in header <atomic>

    See also: http://www.cplusplus.com/reference/memory/shared_ptr
              http://en.cppreference.com/w/cpp/memory/shared_ptr
