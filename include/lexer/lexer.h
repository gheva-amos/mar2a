#ifndef MAR2A_LEXER_H__
#define MAR2A_LEXER_H__

#include <string>
#include <memory>
#include <vector>
#include "lexer/token.h"

namespace mar2a
{

class Lexer
{
public:
  struct Lexeme
  {
    std::string value;
    size_t line;
    size_t column;
    bool number{false};
    bool string{false};
  };
  Lexer(std::string src);
  bool tokenize();
  Token* at(size_t idx) const;
  size_t size() const;
private:
  bool skip_white();
  Lexeme lexeme();
  std::vector<Lexeme> split();
  char next_char();
  void push_last_char();
  std::string get_string();
  std::string get_number(std::string ft);
  std::string src_;
  size_t line_{0};
  size_t column_{0};
  size_t current_{0};
  static std::string enders;
  std::vector<std::unique_ptr<Token>> tokens_;
  std::vector<std::unique_ptr<Token>> token_stack_;
};

} // namespace

#endif // MAR2A_LEXER_H__
