#include "lexer/lexer.h"

namespace mar2a
{

std::string Lexer::enders{"();{}\"'=<>!"};

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
      return false;
    }
    tokens_.emplace_back(std::make_unique<Token>(line_, column_, t));
    skip_white();
  }
  return true;
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
  while (std::isspace(src_[current_]))
  {
    if (src_[current_] == '\n')
    {
      line_ += 1;
      column_ = 0;
    }
    else
    {
      column_ += 1;
    }
    current_ += 1;
  }
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

} // namespace
