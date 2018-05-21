

void foo_nonconst_ref(int & val) {
  // val = 23;
}
void foo_const_ref(const int & val) {
  // val = 323;
}

foo_nonconst_ref(42); // No.
foo_const_ref(42);    // Ok.

int & a       = 34;   // No.  a = 23;
const int & a = 34;   // No.

int & x;




namespace cpppc {

  // T _default_value;
  // _map { index -> non-default-value }
  //
  // T at(i) { return (map[i]) ? map[i] : default_value }
template <class T, std::size_t N>
class sparse_array {

  using index_t = int;

public:
  using value_type = T;

public:
  class proxy_reference {
    using sparse_array_t = sparse_array<T,N>;
    using self_t         = proxy_reference;
  public:
    proxy_reference() = delete;
    proxy_reference(sparse_array_t & sa, index_t offset)
      : _sa(sa), _index(offset)
    { }

    proxy_reference & operator=(const & T value) {
      // _s[_index]  ???
      return *this;
    }

  private:
    sparse_array_t & _sa;
    index_t          _index;
  };

  class iterator {
  public:
    iterator() = default; // ???
    iterator(sparse_array_t & sa, index_t offset)
    : _sa(&sa), _index(offset)
    { }

    proxy_reference operator*() {
      return (*_sa)[_index];
    }

  private:
    sparse_array_t * _sa;
    index_t          _index;
  };


  iterator begin() {
    return iterator(*this, 0);
  }

  const_iterator end() {
    return iterator(*this, N);
  }

  std::size_t size() const noexcept { return N; }

  T operator[](int offset) const {
    auto it_match = _entries.find(offset);
    if (it_match == entries.end() {
        return _default;
    }
    return *it_match;
  }

  proxy_reference operator[](int offset) {
    return proxy_reference(*this, offset);
  }

private:
  T                              _default;
  std::map<index_t, value_type>  _entries;

};


}
