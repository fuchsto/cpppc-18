


template <class T>
class lazy_sequence
{
    using self_t = lazy_sequence<T>;

  public:
    lazy_sequence()                        = default;
    lazy_sequence(const self_t & other)    = default;
    lazy_sequence(self_t && other)         = default;

    self_t & operator=(const self_t & rhs) = default;
    self_t & operator=(self_t && rhs)      = default;

    lazy_sequence(std::function<T(int)> fun)
      : _fun(fun)
    { }

  public:
    class iterator {
        using self_t            = iterator;
        using laze_sequence_t   = lazy_sequence<T>;
      public:
        using iterator_category = std::random_access_iterator_tag;
        using difference_type   = std::diff_t;
        using size_type         = std::size_type;
        
        using value_type        = T;
        using reference         = const T &;
        using pointer           = const T *;
        using const_reference   = const T &;
        using const_pointer     = const T *;
      public:
        iterator(const lazy_sequence_t & seq)
          : _seq(&seq)
        { }

        value_type operator*() const {
          return _seq[_pos];
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

  private:
    std::function<T(int)> _fun;
    int                   _size = 0;
};

