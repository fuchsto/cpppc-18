

template <...>
struct iterator {


     iterator(const iterator & o; int pos);

     // prefix
     //
     //    at = ++it
     //
     iterator & operator++() {
        ++_pos;
        return *this;
     }

     // postfix
     //
     //    it++
     //
     iterator operator++(int) {
        return iterator(*this, _pos++);
     }

     std::vector<iterator> _cached;



}
