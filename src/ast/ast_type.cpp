#include "ast/ast_type.h"

namespace mar2a
{

ASTType::ASTType(const std::string exp, Token::Type type) :
  exp_{exp}
{
  switch (type)
  {
  case Token::Type::voidt:
    type_ = Type::type_void;
    break;
  case Token::Type::intt:
    type_ = Type::type_int;
    break;
  default:
    type_ = Type::type_unknown;
  }
}

void ASTType::add_child(std::unique_ptr<ASTNode> child)
{
}

void ASTType::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << exp_ << std::endl;
}

ASTType::Type ASTType::type() const
{
  return type_;
}

} // namespace
