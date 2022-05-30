/* A naive implementation of the std::initializer_list

   Maybe this is happening only with g++ (4.8.5) but so far I cannot implement
   an initializer_list in a non-std namespace. It must be in std:: namespace.

   error: no matching function for call to ‘C::C(<brace-enclosed initializer list>)’
     C c {1, 2, 3, 4};
                    ^
 */
#include <stdio.h>

namespace std
{

// copied from /usr/include/c++/4.8.2/initializer_list
template<typename T>
class initializer_list
{
public:
    typedef T           value_type;
    typedef const T&    reference;
    typedef const T&    const_reference;
    typedef size_t      size_type;
    typedef const T*    iterator;
    typedef const T*    const_iterator;

private:
    iterator    m_array;
    size_type   m_len;

private:
// the compiler can call a private constructor !! (holly ...)
    constexpr initializer_list(const_iterator arr, size_type len)
        : m_array(arr),
          m_len(len)
    { }

public:
    constexpr initializer_list() noexcept
        : m_array(0),
          m_len(0)
    { }

// number of elements
    constexpr size_type size() const noexcept { return m_len; }
// first element
    constexpr const_iterator begin() const noexcept { return m_array; }
// one past the last element
    constexpr const_iterator end() const noexcept { return begin() + size(); }
};

template<typename T>
constexpr const T* begin(initializer_list<T> ils) noexcept
{
    return ils.begin();
}

template<typename T>
constexpr const T* end(initializer_list<T> ils) noexcept
{
    return ils.end();
}

} // namespace std;


class C
{
private:
    // disable default construction
    C();
    C& operator=(const C&);

public:
    C(std::initializer_list<int> ils)
    {
        m_array = new int[ils.size()];
        m_len = ils.size();

        *this = (ils);
    }

    C& operator=(std::initializer_list<int> ils)
    {
        std::initializer_list<int>::const_iterator it = ils.begin();
        for (size_t i = 0; i < ils.size(); ++i)
        {
            m_array[i] = *(it + i);
        }
        return *this;
    }

    void show() const
    {
        printf("m_len=%d m_array={", m_len);
        for(int i = 0; i < m_len; i++)
            printf("%d ", m_array[i]);
        printf("}\n");
    }

    ~C()
    {
        if(m_array)
            delete [] m_array;
    }

private:
    int*  m_array;
    int   m_len;
};

main()
{
    C c {1, 2, 3, 4};
    c.show();
}

/*
  m_len=4 m_array={1 2 3 4 }
*/
