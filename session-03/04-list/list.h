
#include <iterator>


int x = 10;
int y = 10;

int pre  = --x;  //  9;
int post = y--;  // 10;



// 
// A misleading example of SFINAE:
//
template <class T>
class Variant
{
    static_assert(
        std::is_same<T, int>::value);
}

template <class T>
class Variant
{
    static_assert(
        !std::is_same<T, int>::value);
}

Variant<int>;
Variant<double>;


//
// How the above example is actually implemented:
//
template <class T, class X>
class Variant;


template <class X>
class Variant<int, X> {

};

template <class X>
class Variant<double, X> {

};




// const_int ci;
// int       i;
//
// foo<const int> -> Type = const int
template <typename Type>
void foo(Type & t) {
  do_stuff(t);
}

// foo<const int> -> Type = int
template <typename Type>
void foo(const Type & t) {
  do_stuff(t);
}

void do_stuff(const Type & t);
void do_stuff(Type & t);



// it++; -> old position
iterator operator++(int) {
  iterator old = *this;
  --_pos;
  return old;
}

// ++it; -> new position
iterator & operator++() {
  _pos = 0;
  return *this;
}




namespace cpppc {

  // list<int32_t, -1>
  template <
    typename ValueT,
    ValueT   default_value = ValueT()>
  class list {
    typedef list<ValueT, default_value> self_t;
  public:
    // list<T>::iterator
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

       // const my_container & c;
       // c[23] = "foo";
       // c.push_back("foo"); <-- 'nouh'

       iterator & operator++() {
          _list_node = _list_node.next;
          return *this;
       }

       iterator operator++(int) {
          iterator old = *this;
          _list_node = _list_node.next;
          return old;
       }

       // int * ptr;
       //
       // ptr[3]     = 4;
       // *(ptr + 3) = 4;
       //
       // auto it = list.begin();
       // *it = 3;
       //
       // list<X> l;
       // auto it  =  l.begin();
       // auto val = *it;
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

    // list<int> l;
    // l_begin = l.begin();
    // ++l_begin;
    iterator begin()  { _begin; }
    // list<T> l;
    // *l.end();
    iterator end()    { _end; }
    
  private:
    // same as = { }
    list_node _head        = { nullptr, default_value };
    static list_node _tail = { nullptr, default_value };

    // self_t * this

    iterator  _begin = *this;
    iterator  _end;
  };

}



