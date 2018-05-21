
/*
 * See article in Effective Modern C++:
 *
 * https://www.safaribooksonline.com/library/view/effective-modern-c/9781491908419/ch04.html
 *
 */

auto my_deleter = [](Resource * res) {
                    LOG("deleting Resource " << res);
                    // Deallocation must be called explicitly:
                    delete pInvestment;
                    // So that also means: we could decide not
                    // to deallocate.
                  };

template<typename... Ts>
std::unique_ptr<MyResource, decltype(my_deleter)>
make_my_resource(Ts &&... params)
{
  std::unique_ptr<MyResource, decltype(my_deleter)>
    pInv(nullptr, my_deleter);
}


