#ifndef CPPPC__SESSION_02__MACRO_H__INCLUDED
#define CPPPC__SESSION_02__MACRO_H__INCLUDED

#include <iostream>
#include <iomanip>

#define wno_unused_(var) (void)(var)

#define LOG(scope, msg) do { \
  std::cout << "-- LOG | " << std::setw(20) << scope << " | " \
            << msg << std::endl; \
} while(0)

#endif // CPPPC__SESSION_02__MACRO_H__INCLUDED
