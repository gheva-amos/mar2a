#include "lexer/lexer.h"
#include <sstream>
#include <iostream>

namespace mar2a
{

std::string Lexer::enders{"();{}\"'=<>!+-*/~."};

Lexer::Lexer(std::string src) :
  src_{std::move(src)}
{
}

bool Lexer::tokenize()
{
  std::vector<Lexeme> lexemes = split();
  if (lexemes.empty())
  {
    return false;
  }
  size_t idx{0};
  while (idx < lexemes.size())
  {
    Lexeme l{lexemes[idx]};

    std::string& t{l.value};
    if (t.empty())
    {
      break;
    }
    if (t == "\"")
    {
      tokens_.emplace_back(std::make_unique<String>(line_, column_, get_string()));
    }
    else if (std::isdigit(t[0]))
    {
      tokens_.emplace_back(std::make_unique<Number>(line_, column_, get_number(t)));
    }
    else if (t[0] == '-')
    {
      if (lexemes[idx + 1].value == "-")
      {
        tokens_.emplace_back(std::make_unique<Decrement>(l.line, l.column, "--"));
        idx += 1;
      }
      else
      {
        tokens_.emplace_back(std::make_unique<Negate>(l.line, l.column, "-"));
      }
    }
    else if (t[0] == '+')
    {
      if (lexemes[idx + 1].value == "+")
      {
        tokens_.emplace_back(std::make_unique<Increment>(l.line, l.column, "++"));
        idx += 1;
      }
      else
      {
        tokens_.emplace_back(std::make_unique<Plus>(l.line, l.column, "+"));
      }
    }
    else
    {
      auto token{Token::factory(l.line, l.column, t)};
      if (token == nullptr)
      {
        return false;
      }
      tokens_.emplace_back(std::move(token));
    }
    idx += 1;
  }
  return !tokens_.empty();
}

Token* Lexer::at(size_t idx) const
{
  return tokens_.at(idx).get();
}

size_t Lexer::size() const
{
  return tokens_.size();
}

bool Lexer::skip_white()
{
  char c;
  do
  {
    c = next_char();
  } while (std::isspace(c) && current_ < src_.size());
  push_last_char(); // push back the firs non space found
  return current_ < src_.size();
}

Lexer::Lexeme Lexer::lexeme()
{
  size_t length{0};
  size_t iter{current_};
  while (enders.find(src_[iter]) == enders.npos && !std::isspace(src_[iter]))
  {
    iter += 1;
    length += 1;
  }
  if (length == 0 && enders.find(src_[iter]) != enders.npos)
  {
    length = 1;
  }
  column_ += length;
  Lexeme ret {src_.substr(current_, length), line_, column_};
  current_ += length;
  return ret;
}

char Lexer::next_char()
{
  if (current_ > src_.size())
  {
    return '\0';
  }
  char ret{src_[current_]};
  current_ += 1;
  if (ret == '\n')
  {
    line_ += 1;
    column_ = 0;
  }
  else
  {
    column_ += 1;
  }
  return ret;
}

void Lexer::push_last_char()
{
  current_ -= 1;
  column_ -= 1;
}

std::string Lexer::get_string()
{
  char c{'\0'}, prev;
  std::stringstream ss;
  do
  {
    prev = c;
    c = next_char();
    if (c == '"')
    {
      if (prev != '\\')
      {
        break;
      }
    }
    ss << c;
  } while (true);

  return ss.str();
}

std::string Lexer::get_number(std::string ft)
{
  std::stringstream ss;
  ss << ft;
  char c{next_char()};
  if (c != '.')
  {
    push_last_char();
    return ss.str();
  }
  do
  {
    ss << c;
    c = next_char();
    if (c == '\0')
    {
      break;
    }
  } while (std::isdigit(c));
  push_last_char();
  return ss.str();
}

std::vector<Lexer::Lexeme> Lexer::split()
{
  line_ = 0;
  column_ = 0;
  current_ = 0;
  skip_white();
  std::vector<Lexeme> ret;
  while (current_ < src_.size())
  {
    auto l{lexeme()};
    if (l.value.empty())
    {
      break;
    }
    if (l.value == "\"")
    {
      l.value = get_string();
      l.string = true;
    }
    else if (std::isdigit(l.value[0]))
    {
      l.value =  get_number(l.value);
      l.number = true;
    }
    ret.push_back(l);
    skip_white();
  }
  return ret;
}

} // namespace
