.
   Header     : <memory>
   Signature  : constexpr unique_ptr() noexcept;
                constexpr unique_ptr(nullptr_t) noexcept;
                explicit  unique_ptr(pointer p) noexcept;
                          unique_ptr(pointer p,
                                     typename conditional<is_reference<D>::value,D,const D&> del) noexcept;
                          unique_ptr(pointer p,
                                     typename remove_reference<D>::type&& del) noexcept;
                          unique_ptr(unique_ptr&& x) noexcept;
                template<class U, class E>
                          unique_ptr(unique_ptr<U,E>&& x) noexcept;
                template<class U>
                          unique_ptr(auto_ptr<U>&& x) noexcept;
                          unique_ptr(const unique_ptr&) = delete;

   Description:
       -holds a * raw pointer and releases it when goes out of scope
       -is not copyable
       -releases the internal * raw pointer on release()
       -deletes the internal * raw pointer on reset() and becomes empty

   See also: http://www.cplusplus.com/reference/memory/unique_ptr
