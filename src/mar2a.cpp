#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <fstream>

#include "driver/driver.h"

std::string read_file(const std::string& path);

int main(int argc, char** argv)
{
  std::string source_file{};
  bool lex_only{false};
  bool parse_only{false};
  bool codegen_only{false};
  bool assemble_only{false};
  if (argc == 1)
  {
    throw std::runtime_error("Need one file to compile");
  }
  if (argc == 2)
  {
    source_file = argv[1];
  }
  else
  {
    for (int i{1}; i < argc; ++i)
    {
      if (argv[i][0] == '-')
      {
        if (argv[i][1] == '-')
        {
          switch (argv[i][2])
          {
          case 'l':
            lex_only = true;
            break;
          case 'p':
            parse_only = true;
            break;
          case 'c':
            codegen_only = true;
            break;
          case 'S':
            assemble_only = true;
            break;
          default:
            throw std::runtime_error("invalid argument");
          }
        }
        else
        {
          throw std::runtime_error("invalid argument");
        }
      }
      else
      {
        source_file = argv[i];
      }
    }
  }

  if (source_file.empty())
  {
    return -2;
  }
  std::string source_code{read_file(source_file)};

  if (source_code.empty())
  {
    return -3;
  }

  mar2a::Driver driver(source_code, lex_only, parse_only, codegen_only, assemble_only);
  if (driver.run(std::cout))
  {
    return 0;
  }
  return -1;
}

std::string read_file(const std::string& path)
{
  std::ifstream in(path, std::ios::in | std::ios::binary);
  if (!in)
  {
    return "";
  }

  std::ostringstream ss;
  ss << in.rdbuf();
  return ss.str();
}
