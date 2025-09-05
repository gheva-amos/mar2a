#include "driver/driver.h"

namespace mar2a
{

Driver::Driver(std::string file, bool lex, bool parse, bool codegen, bool assemble) :
  lex_only_{lex}, parse_only_{parse}, codegen_only_{codegen}, assemble_only_{assemble},
  source_{std::move(file)}
{
}

} // namespace

