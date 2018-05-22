
#include "virtual.h"
#include "static_polymorph.h"

#include <memory>


int main()
{
  std::vector<std::shared_ptr<vrt::Base>> v_vrt;

  v_vrt.push_back(std::shared_ptr<vrt::Base>(new vrt::Wombat("Theodore")));
  v_vrt.push_back(std::shared_ptr<vrt::Base>(new vrt::Kitten("Agatha")));
  v_vrt.push_back(std::shared_ptr<vrt::Base>(new vrt::Wombat("Diederich")));

  for (auto vp : v_vrt) {
    vp->ducky();
  }


}

