
template <class YadaYada>
class lazy_sequence_sentinel {

  public: 
    lazy_sequence_sentinel(int length) : _num_compares(length) { }
  public:

    // sentinel == iterator
    template <class Iterator>
    bool operator!=(Iterator && rhs) const noexcept {
      return (--_num_compares > 0);
    }

  private:
    mutable int _num_compares = 0;
}

