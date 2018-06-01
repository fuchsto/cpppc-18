
#include <iterator>


namespace cpppc {
  template <
    typename ValueT,
    ValueT   default_value = ValueT()>
  class list;

  template <
    typename ValueT,
    ValueT   default_value >
  class list {
    typedef list<ValueT, default_value> self_t;

  public:
    class iterator {
       typedef typename
         list<ValueT, default_value>
         list_t;
       typedef typename
         list_t::list_node
         list_node_t;
       typedef typename
         list_t::iterator
         self_t;
    public:
       iterator() = delete;

       iterator(const list_t & list)
       : _list(list)
       { }

       iterator & operator++() {
          _list_node = _list_node.next;
          return *this;
       }

       iterator operator++(int) {
          iterator old = *this;
          _list_node = _list_node.next;
          return old;
       }

       const ValueT & operator*() const {
         return _list_node->value;
       }

       ValueT & operator*() {
         return _list_node->value;
       }

       bool operator==(const self_t & rhs) {
         return  (this == &rhs || // identity
                   ( _list == rhs._list &&
                     ... )
       }

    private:
       list_node_t * _list_node;
    };

    struct list_node {
       list_node * next;
       ValueT      value;
    };
    
  public:
    list()
    : _begin(iterator(*this))
    , _end(iterator(*this))
    { }

    // list<uint32_t>(list<int32_t>()) says 'nouh'
    list(const self_t & other)             = default;
    self_t & operator=(const self_t & rhs) = default;

    iterator begin()  { _begin; }
    iterator end()    { _end; }
    
  private:
    list_node _head        = { nullptr, default_value };
    static list_node _tail = { nullptr, default_value };

    iterator  _begin = *this;
    iterator  _end;
  };

}

