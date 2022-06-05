http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/

I thought most of the time that N3242 is the last version before
the official announcement. It seems it is not the last one though.

Here https://herbsutter.com/2011/10/10/iso-c11-published/
it is mentioned a new version on the mailing list N3291 with some
additions (constexpr, noexcept, etc) concluding that N3242
is not reliable.

On the first link the N3337 is based on previous version N3291
, with the title "Working Draft, Standard for Programming Language C++"
meaning is the final proposal for the standard. It is also signed
by Stefanus Du Toit which is known as the maintainer.
-----------------------------------------------------------------------

The problem with C++11 is that there is no tutorial to give an in depth
overview on all new additions. That's why I will use the best website
I can find , individually for each topic.
Also the C++11 ISO N3337.pdf is not always the best documentation for
this purpose.
-----------------------------------------------------------------------

1) keywords: auto,char16_t,char32_t,alignas,alignof,decltype(2.12)
   constexpr,nullptr,noexcept,static_assert,thread_local,using(2.12)
2) user defined literals (2.14)
3) lambda,std::function<..> (5.1.2)
4) range-based for loop (6.5.4)
5) enum class (7.2)
6) default and delete methods and operators (8.4)
7) braced-init-list, std::initializer_list (8.5)
8) override and final (10.3)
9) explicit conversion functions (12.3)
10) delegating constructors (12.6)
11) rvalue references, move semantics, std::move, std::forward (12.8)
12) variadic templates (14.5)
13) std::shared_ptr, std::weak_ptr, std::unique_ptr (20.7)
14) std::thread (30.3), std::mutex(30.4), std::condition_variable(30.5)
15) future, shared_future, promise, async, packaged_task (30.6)


TODO (from https://github.com/AnthonyCalandra/modern-cpp-features):
-------------------------------------------------------------------


ref-qualified member functions
trailing return types
raw string literals
std::to_string
type traits
std::chrono
typles; std::tuple, std::tie, std::get
std::arrray
unordered cotainers; std::unordered_set, std::unordered_multiset,
                     std::unordered_map, std::unordered_multimap

std::begin, std::end
