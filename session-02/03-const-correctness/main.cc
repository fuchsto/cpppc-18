#include "macro.h"
#include "shared_config.h"

#include <iostream>
#include <cstdlib>


using cpppc::SharedConfig;
using cpppc::ConfigEntry;

using std::cout;
using std::endl;

// NOTE:
// You would not implement this as a user specified algorithm in the real
// world (see std::find).
SharedConfig::entries_type::const_iterator  // <-- Q: why const_iterator?
find_brown_entry(const SharedConfig & config)
{
  for (auto it = config.entries().begin();
       it != config.entries().end(); ++it) {
    if (it->value().find("brown") != std::string::npos) {
      return it;
    }
  }
  return config.entries().end();
}

int main(int argc, char * argv[])
{
  wno_unused_(argc);
  wno_unused_(argv);

  SharedConfig config_1("config_1", 3);

  config_1[0].update("color", "snot yellow");
  config_1[1].update("color", "vomit green");
  config_1[2].update("color", "spit white");

  cout << config_1 << endl;

  cout << endl
       << "Config entry [0]:"
       << endl;

  ConfigEntry entry_1_0 = config_1[0];
  cout << entry_1_0 << endl;

  // ---------------------------------------------------------------------

  cout << endl
       << "Config entry [1]:"
       << endl;

  ConfigEntry & entry_1_1 = config_1[1];
  cout << entry_1_1 << endl;

  entry_1_1 = ConfigEntry("color", "panty brown");

  cout << endl
       << "Find a config entry with value containing \"brown\":"
       << endl;

  cout << *find_brown_entry(config_1) << endl;

  // ---------------------------------------------------------------------
#if 1

  cout << endl
       << "Iterating config entries (auto):"
       << endl;

  for (auto e : config_1.entries()) {
    cout << "       - " << e << endl;
  }

  cout << endl
       << "Iterating config entries (auto &):"
       << endl;

  for (auto & e : config_1.entries()) {
    cout << "       - " << e << endl;
  }

#endif

  // ---------------------------------------------------------------------
#if 0

  cout << endl
       << "Copying config:"
       << endl;

  SharedConfig config_2(config_1);
  config_2.rename("config_2");

  cout << endl
       << "Config copy:"
       << endl;

#endif

  // ---------------------------------------------------------------------
#if 0

  cout << config_2 << endl;

  cout << endl
       << "Assigning config:"
       << endl;

  SharedConfig config_3("config_3");
  config_3 = config_2;
  config_3.rename("config_3");

  cout << config_3 << endl;

#endif

  // ---------------------------------------------------------------------
#if 0

  cout << endl
       << "Reference nastyness:" << endl
       << "(real hackers know and exploit this, good programmers don't)"
       << endl;

  auto config_heap_1 = new SharedConfig("config_heap_1", 1);
  ConfigEntry & entry_heap_ref_1 = (*config_heap_1)[0];

  auto config_heap_2 = new SharedConfig("config_heap_2", 1);
  ConfigEntry & entry_heap_ref_2 = (*config_heap_2)[0];
  entry_heap_ref_2               = ConfigEntry("color", "heap lilac");

  delete config_heap_1;
  delete config_heap_2;

#endif

  cout << endl
       << "Leaving main()"
       << endl;

  return EXIT_SUCCESS;
}
