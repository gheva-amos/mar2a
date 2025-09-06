#include "lexer/lexer.h"
#include <sstream>
#include <iostream>

namespace mar2a
{

std::string Lexer::enders{"();{}\"'=<>!+-*/."};

Lexer::Lexer(std::string src) :
  src_{std::move(src)}
{
}

bool Lexer::tokenize()
{
  line_ = 0;
  column_ = 0;
  current_ = 0;
  if (!skip_white())
  {
    return false;
  }

  while (current_ < src_.size())
  {
    std::string t{token()};
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
    else
    {
      auto token{Token::factory(line_, column_, t)};
      if (token == nullptr)
      {
        return false;
      }
      tokens_.emplace_back(std::move(token));
    }
    skip_white();
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

std::string Lexer::token()
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
  std::string ret{src_.substr(current_, length)};
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

} // namespace
