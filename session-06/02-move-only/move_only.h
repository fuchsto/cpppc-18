#ifndef CPPPC__SESSION_07__MOVE_ONLY_H__INCLUDED
#define CPPPC__SESSION_07__MOVE_ONLY_H__INCLUDED

//
// Real-world examples in the STL:
//
// - std::future
// - std::thread
// - std::unique_ptr
//

template <class ResourceType>
class MoveOnly
{
  typedef MoveOnly<ResourceType> self_t;

  ResourceType _resource; // may again be move-only

public:

  explicit MoveOnly(ResourceType && resource)
    : _resource(std::move(resource))
  { }

  MoveOnly(self_t &&)                = default;
  self_t & operator=(self_t &&)      = default;

  MoveOnly(const self_t &)           = delete;
  self_t & operator=(const self_t &) = delete;

  ~MoveOnly() { }
}

#endif // CPPPC__SESSION_07__MOVE_ONLY_H__INCLUDED
