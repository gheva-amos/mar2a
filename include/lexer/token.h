#ifndef MAR2A_TOKEN_H__
#define MAR2A_TOKEN_H__

#include <string>
#include <memory>
#include <vector>

namespace mar2a
{

class Token
{
public:
  enum class Type
  {
    open_brace,
    close_brace,
    open_paren,
    close_paren,
    semicolon,
    number,
    identifier,
    keyword,
    string,
    unknown
  };
  Token(size_t line, size_t col, std::string value);
  virtual ~Token() = default;
  size_t line() const;
  size_t column() const;
  const std::string& value() const;
  Type type() const;

  static std::unique_ptr<Token> factory(size_t line, size_t col, const std::string& value);
protected:
  Type type_;
private:
  size_t line_;
  size_t column_;
  std::string value_;
  static std::vector<std::string> keywords;
};

class OpenBrace : public Token
{
public:
  OpenBrace(size_t line, size_t col, std::string value);
};

class CloseBrace : public Token
{
public:
  CloseBrace(size_t line, size_t col, std::string value);
};

class OpenParen : public Token
{
public:
  OpenParen(size_t line, size_t col, std::string value);
};

class CloseParen : public Token
{
public:
  CloseParen(size_t line, size_t col, std::string value);
};

class SemiColon : public Token
{
public:
  SemiColon(size_t line, size_t col, std::string value);
};

class Number : public Token
{
public:
  Number(size_t line, size_t col, std::string value);
};

class Identifier : public Token
{
public:
  Identifier(size_t line, size_t col, std::string value);
};

class Keyword : public Token
{
public:
  Keyword(size_t line, size_t col, std::string value);
};

class String : public Token
{
public:
  String(size_t line, size_t col, std::string value);
};

} // namespace

#endif // MAR2A_TOKEN_H__
