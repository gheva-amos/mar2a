#include "lexer/token.h"

namespace mar2a
{

Token::Token(size_t line, size_t col, std::string value) :
  line_{line}, column_{col}, value_{std::move(value)}
{
}

size_t Token::line() const
{
  return line_;
}

size_t Token::column() const
{
  return column_;
}

const std::string& Token::value() const
{
  return value_;
}

} // namespace

