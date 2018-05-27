
#include <functional>
#include <iterator>

namespace cpppc {


template <class T>
class lazy_sequence
{
    using self_t = lazy_sequence<T>;

  public:
    using size_type         = std::size_t;
    using difference_type   = typename std::make_signed<
                                         size_type
                                       >::type;
    
    using value_type        = T;

  public:
    lazy_sequence()                        = default;
    lazy_sequence(const self_t & other)    = default;
    lazy_sequence(self_t && other)         = default;

    self_t & operator=(const self_t & rhs) = default;
    self_t & operator=(self_t && rhs)      = default;

    lazy_sequence(int size, std::function<T(int)> fun)
      : _size(size)
      , _fun(fun)
    { }

  public:
    class iterator {
        using self_t            = iterator;
        using lazy_sequence_t   = lazy_sequence<T>;
      public:
        using iterator_category = std::random_access_iterator_tag;
        using size_type         = std::size_t;
        using difference_type   = typename std::make_signed<
                                             size_type
                                           >::type;
        
        using value_type        = T;
        using reference         = const T &;
        using pointer           = const T *;
        using const_reference   = const T &;
        using const_pointer     = const T *;
      public:
        iterator(const lazy_sequence_t & seq, int pos)
          : _seq(&seq),
            _pos(pos)
        { }

        value_type operator*() const {
          return (*_seq)[_pos];
        }

        self_t & operator+(int) { 
          _pos++;
          return *this;
        }

        self_t operator+() { 
          auto old = *this;
          _pos++;
          return old;
        }

      private:
        const lazy_sequence * _seq = nullptr;
        int                   _pos = 0;
    };

  public:
    T operator[](int pos) const {
      return _fun(pos);
    }

    iterator begin() const {
      return iterator(*this, 0);
    }

    iterator end() const {
      return iterator(*this, _size);
    }

    size_type size() const {
      return _size;
    }

    size_type max_size() const {
      return _size;
    }

    bool empty() const {
      return size() == 0;
    }

    T at(int idx) const {
      return _fun(idx);
    }

    T front() const {
      return _fun(0);
    }

    T back() const {
      return _fun(size() - 1);
    }

    bool operator==(const self_t & other) const = default;
    bool operator!=(const self_t & other) const = default;

  private:
    std::function<T(int)> _fun;
    int                   _size = 0;
};

} // namespace cpppc
