#include "lexer/token.h"

namespace mar2a
{

std::vector<std::string> Token::keywords{
  "int", "void", "return"
};

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

Token::Type Token::type() const
{
  return type_;
}

std::unique_ptr<Token> Token::factory(size_t line, size_t col, const std::string& value)
{
  if (value.size() == 1)
  {
    switch (value[0])
    {
    case '(':
      return std::make_unique<OpenParen>(line, col, value);
    case ')':
      return std::make_unique<CloseParen>(line, col, value);
    case '{':
      return std::make_unique<OpenBrace>(line, col, value);
    case '}':
      return std::make_unique<CloseBrace>(line, col, value);
    case ';':
      return std::make_unique<SemiColon>(line, col, value);
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return std::make_unique<Number>(line, col, value);
    case '~':
      return std::make_unique<Tilde>(line, col, value);
    default:
      return std::make_unique<Identifier>(line, col, value);
    }
  }
  if (std::find(keywords.begin(), keywords.end(), value) != keywords.end())
  {
    return std::make_unique<Keyword>(line, col, value);
  }
  return std::make_unique<Identifier>(line, col, value);
}

OpenBrace::OpenBrace(size_t line, size_t col, std::string value) :
  Token{line, col, "{"}
{
  type_ = Type::open_brace;
}

CloseBrace::CloseBrace(size_t line, size_t col, std::string value) :
  Token{line, col, "}"}
{
  type_ = Type::close_brace;
}

OpenParen::OpenParen(size_t line, size_t col, std::string value) :
  Token{line, col, "("}
{
  type_ = Type::open_paren;
}

CloseParen::CloseParen(size_t line, size_t col, std::string value) :
  Token{line, col, ")"}
{
  type_ = Type::close_paren;
}

SemiColon::SemiColon(size_t line, size_t col, std::string value) :
  Token{line, col, ";"}
{
  type_ = Type::semicolon;
}

Number::Number(size_t line, size_t col, std::string value) :
  Token{line, col, value}
{
  type_ = Type::number;
}

Identifier::Identifier(size_t line, size_t col, std::string value) :
  Token{line, col, value}
{
  type_ = Type::identifier;
}

Keyword::Keyword(size_t line, size_t col, std::string value) :
  Token{line, col, value}
{
  type_ = Type::keyword;
  if (value == "int")
  {
    type_ = Type::intt;
  }
  else if (value == "void")
  {
    type_ = Type::voidt;
  }
}

String::String(size_t line, size_t col, std::string value) :
  Token{line, col, value}
{
  type_ = Type::string;
}

Minus::Minus(size_t line, size_t col, std::string value) :
  Token{line, col, value}
{
  type_ = Type::minus;
}

Decrement::Decrement(size_t line, size_t col, std::string value) :
  Token{line, col, value}
{
  type_ = Type::decrement;
}

Tilde::Tilde(size_t line, size_t col, std::string value) :
  Token{line, col, value}
{
  type_ = Type::tilde;
}

} // namespace

