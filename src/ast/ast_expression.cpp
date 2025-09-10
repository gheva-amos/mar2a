#include "ast/ast_expression.h"
#include "ir/ir_const_int.h"
#include "ir/ir_unary_op.h"

namespace mar2a
{

ASTExpression::ASTExpression(const std::string exp, Type type) :
  exp_{exp}, type_{type}
{
}

void ASTExpression::add_child(std::unique_ptr<ASTNode> child)
{
  child_ = std::move(child);
}

void ASTExpression::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << exp_ << std::endl;
  if (child_ != nullptr)
  {
    child_->pretty_print(out, indent + "\t");
  }
}

std::unique_ptr<IRNode> ASTExpression::visit()
{
  switch (type_)
  {
  case Type::const_int:
    return std::make_unique<IRConstInt>("const int", exp_);
  case Type::minus:
    {
      auto ret = std::make_unique<IRUnaryOp>("minus", IRUnaryOp::Kind::minus);
      ret->add_expression(std::move(child_->visit()));

      return ret;
    }
  case Type::tilde:
    {
      auto ret = std::make_unique<IRUnaryOp>("tilde", IRUnaryOp::Kind::tilde);
      ret->add_expression(std::move(child_->visit()));

      return ret;
    }
  }
  return nullptr;
}

} // namespace
