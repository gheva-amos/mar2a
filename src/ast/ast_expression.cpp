#include "ast/ast_expression.h"
#include "ir/ir_const_int.h"
#include "ir/ir_binary_op.h"

namespace mar2a
{

ASTExpression::ASTExpression(const std::string exp, Type type) :
  exp_{exp}, type_{type}
{
}

void ASTExpression::add_child(std::unique_ptr<ASTNode> child)
{
  children_.push_back(std::move(child));
}

void ASTExpression::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << exp_ << std::endl;
  for (auto& child_ : children_)
  {
    child_->pretty_print(out, indent + "\t");
  }
}

std::unique_ptr<ASTExpression> ASTExpression::factory(std::string value, Token::Type type)
{
  std::unique_ptr<ASTExpression> exp;
  switch (type)
  {
  case Token::Type::plus:
    exp = std::make_unique<ASTExpression>(std::move(value),
        ASTExpression::Type::plus);
    break;
  case Token::Type::negate:
    exp = std::make_unique<ASTExpression>(std::move(value),
        ASTExpression::Type::minus);
    break;
  case Token::Type::times:
    exp = std::make_unique<ASTExpression>(std::move(value),
        ASTExpression::Type::times);
    break;
  case Token::Type::divide:
    exp = std::make_unique<ASTExpression>(std::move(value),
        ASTExpression::Type::divide);
    break;
  case Token::Type::remainder:
    exp = std::make_unique<ASTExpression>(std::move(value),
        ASTExpression::Type::remainder);
    break;
  default:
    exp = nullptr;
    break;
  }
  return exp;
}

std::unique_ptr<IRNode> ASTExpression::visit()
{
  switch (type_)
  {
  case Type::plus:
    {
      auto ret = std::make_unique<IRBinaryOp>("plus", IRBinaryOp::Kind::plus);
      ret->add_left(std::move(children_[0]->visit()));
      ret->add_right(std::move(children_[1]->visit()));

      return ret;
    }
  case Type::minus:
    {
      auto ret = std::make_unique<IRBinaryOp>("minus", IRBinaryOp::Kind::minus);
      ret->add_left(std::move(children_[0]->visit()));
      ret->add_right(std::move(children_[1]->visit()));

      return ret;
    }
  case Type::times:
    {
      auto ret = std::make_unique<IRBinaryOp>("times", IRBinaryOp::Kind::times);
      ret->add_left(std::move(children_[0]->visit()));
      ret->add_right(std::move(children_[1]->visit()));

      return ret;
    }
  case Type::divide:
    {
      auto ret = std::make_unique<IRBinaryOp>("divide", IRBinaryOp::Kind::divide);
      ret->add_left(std::move(children_[0]->visit()));
      ret->add_right(std::move(children_[1]->visit()));

      return ret;
    }
  case Type::remainder:
    {
      auto ret = std::make_unique<IRBinaryOp>("remainder", IRBinaryOp::Kind::remainder);
      ret->add_left(std::move(children_[0]->visit()));
      ret->add_right(std::move(children_[1]->visit()));

      return ret;
    }
  }
  return nullptr;
}

} // namespace
