#ifndef MAR2A_DRIVER_H__
#define MAR2A_DRIVER_H__

#include <string>
namespace mar2a
{

class Driver
{
public:
  Driver(std::string file, bool lex, bool parse, bool codegen, bool assemble);
private:
  bool lex_only_{false};
  bool parse_only_{false};
  bool codegen_only_{false};
  bool assemble_only_{false};
  std::string source_;
};

} // namespace

#endif // MAR2A_DRIVER_H__

