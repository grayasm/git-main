.
   Header: <memory>
   Signature: constexpr weak_ptr() noexcept;
                        weak_ptr(const weak_ptr& x) noexcept;
              template<class U>
                        weak_ptr(const weak_ptr<U>& x) noexcept;
              template<class U>
                        weak_ptr(const shared_ptr<U>& x) noexcept;

   Description:
      - weak_ptr is a smart pointer that holds a non-owning "weak" reference
        to an object that is managed by std::shared_ptr. It must be converted
        to std::shared_ptr in order to access the referenced object.
      - weak_ptr is used to break circular references of std::shared_ptr
      - if the original std::shared_ptr is destroyed, the object's lifetime is
        extended until the temporary std::shared_ptr is destroyed as well

   See also: http://en.cppreference.com/w/cpp/memory/weak_ptr
   -----------------------------------------------------------------------------
