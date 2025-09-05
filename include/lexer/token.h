#ifndef MAR2A_TOKEN_H__
#define MAR2A_TOKEN_H__

#include <string>

namespace mar2a
{

class Token
{
public:
  Token(size_t line, size_t col, std::string value);
  virtual ~Token() = default;
  size_t line() const;
  size_t column() const;
  const std::string& value() const;
private:
  size_t line_;
  size_t column_;
  std::string value_;
};

} // namespace

#endif // MAR2A_TOKEN_H__
