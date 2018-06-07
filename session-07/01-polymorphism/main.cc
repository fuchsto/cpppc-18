
#include "virtual.h"
#include "static_polymorph.h"

#include <memory>


template <class T>
T * make_concrete(std::string name) { return new T(name); }


int main()
{
  std::vector<std::shared_ptr<vrt::Base>> v_vrt;

  std::srand(reinterpret_cast<int>(&v_vrt));

  if (std::rand() % 2) {
    v_vrt.push_back(std::shared_ptr<vrt::Base>(new vrt::Wombat("Theodore")));
  } else {
    v_vrt.push_back(std::shared_ptr<vrt::Base>(new vrt::Kitten("Agatha")));
  }
  v_vrt.push_back(std::shared_ptr<vrt::Base>(new vrt::Wombat("Diederich")));

  for (auto vp : v_vrt) {
    vp->say_name();
  }

  // CRTP version:
  if (std::rand() % 2) {
    v_vrt.push_back(std::shared_ptr<vrt::Base>(
        make_concrete<vrt::Wombat>("Theodore");
    );
  } else {
    v_vrt.push_back(std::shared_ptr<vrt::Base>(
        make_concrete<vrt::Kitten>("Agatha");
    );
  }

}


