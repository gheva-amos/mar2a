#include "ast/ast_expression.h"
#include "ir/ir_const_int.h"

namespace mar2a
{

ASTExpression::ASTExpression(const std::string exp, Type type) :
  exp_{exp}, type_{type}
{
}

void ASTExpression::add_child(std::unique_ptr<ASTNode> child)
{
}

void ASTExpression::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << exp_ << std::endl;
}

std::unique_ptr<IRNode> ASTExpression::visit()
{
  switch (type_)
  {
  case Type::const_int:
    return std::make_unique<IRConstInt>("const int", exp_);
  }
  return nullptr;
}

} // namespace
