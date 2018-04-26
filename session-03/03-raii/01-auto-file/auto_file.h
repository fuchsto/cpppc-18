#ifndef AUTO_FILE_H__INCLUDED
#define AUTO_FILE_H__INCLUDED

#include <string>
#include <iostream>

#include <cstdio>
#include <cstdlib>

#include "auto_buffer.h"


class auto_file
{

public:

  auto_file(
    const std::string fname,
    const char *      mode   = nullptr)
  : _fname(fname)
  {
    std::cout << "auto_file:   fopen(" << fname << ")";

    _file = fopen(_fname.c_str(), nullptr == mode ? "r" : mode);

    if (nullptr == _file) {
      std::cout << " (failed)";
    }
    std::cout << std::endl;
  }

  ~auto_file()
  {
    if (nullptr == _file) { return; }

    std::cout << "auto_file:   fclose(" << _fname << ")" << std::endl;
    fclose(_file);

    _file = nullptr;
  }

  const char * string()
  {
    if (_abuf.begin() != nullptr) {
      return _abuf.begin();
    }

    if (nullptr != _file) {
      // get file size in number of characters (= bytes):
      fseek(_file, 0, SEEK_END);
      long size = ftell(_file);
      rewind(_file);

      _abuf = auto_buffer<char>(size);
      if (fread(_abuf.begin(), sizeof(char), size, _file) !=
            static_cast<size_t>(size)) {
        std::cout << "auto_file:   fread failed" << std::endl;
      }
    }

    if (_abuf.size() > 0) {
      return _abuf.begin();
    }
    return "";
  }

private:

  FILE *               _file   = nullptr;
  std::string          _fname;
  auto_buffer<char>    _abuf;
};

#endif // AUTO_FILE_H__INCLUDED
