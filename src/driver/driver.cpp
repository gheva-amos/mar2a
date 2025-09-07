#include "driver/driver.h"
#include "parser/parser.h"
#include "lexer/lexer.h"

namespace mar2a
{

Driver::Driver(std::string file, bool lex, bool parse, bool codegen, bool assemble) :
  lex_only_{lex}, parse_only_{parse}, codegen_only_{codegen}, assemble_only_{assemble},
  source_{std::move(file)}
{
}

bool Driver::run(std::ostream& out)
{
  std::unique_ptr<Lexer> lexer{std::make_unique<Lexer>(source_)};
  if (!lexer->tokenize())
  {
    return false;
  }
  if (lex_only_)
  {
    return true;
  }
  std::unique_ptr<Parser> parser{std::make_unique<Parser>(std::move(lexer), out)};
  if (!parser->parse())
  {
    return false;
  }
  parser->pretty_print();
  if (parse_only_)
  {
    return true;
  }
  return true;
}

} // namespace

