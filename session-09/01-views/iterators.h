
// Iterator (lat: "step-wise walker", "strider", "wanderer")
// [m], -oris
//

auto           it_a = heap.begin() + 30;
auto           it_b = heap.begin();
decltype(it_a) it_e = heap.end();

// Concept: valid expressions, semantics

auto & v = *it_a;
auto & v = *it_e;

auto d = std::distance(it_a, it_b);
auto d = std::distance(it_a, it_e);

auto it_a_20 = it_a - 20;
auto it_e_20 = it_e - 20;

auto d = std::distance(it_a_20, it_a);
auto d = std::distance(it_e_20, it_e);

auto & v = it_a[-2];
auto & v = it_e[-2];

std::vector<int> v1(20);
std::vector<int> v2(20);

ASSERT_EQ(v1.end(), v2.end());

Container <- Iterator

// sentinel == iterator (!=)
// iterator == sentinel (!=)

template <class Iterator, class T>
bool operator==(
    Iterator                        && it,
    const lazy_sequence_sentinel<T>  & b)
{
  return b == it;
}

for (auto it = std::begin(range);
     not (it.==(std::end(range))); ++it) {

}




