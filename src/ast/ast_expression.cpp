#include "ast/ast_expression.h"

namespace mar2a
{

ASTExpression::ASTExpression(const std::string exp) :
  exp_{exp}
{
}

void ASTExpression::add_child(std::unique_ptr<ASTNode> child)
{
}

void ASTExpression::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << exp_ << std::endl;
}

} // namespace
