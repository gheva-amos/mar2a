#include "ir/ir_unary_op.h"

namespace mar2a
{

IRUnaryOp::IRUnaryOp(std::string name, Kind kind) :
  IRNode(name), kind_{kind}
{
}

void IRUnaryOp::set_kind(Kind kind)
{
  kind_ = kind;
}

IRUnaryOp::Kind IRUnaryOp::kind() const
{
  return kind_;
}

void IRUnaryOp::add_expression(std::unique_ptr<IRNode> exp)
{
  expression_ = std::move(exp);
}

void IRUnaryOp::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << name();
  expression_->pretty_print(out, indent + "\t");
}

#ifdef MAR2A_USE_LLVM

void IRUnaryOp::visit(LLVMVisitor* visitor)
{
  if (expression_ != nullptr)
  {
    expression_->visit(visitor);
  }
  if (kind_ == Kind::minus)
  {
    visitor->create_negative();
  }
  else if (kind_ == Kind::tilde)
  {
    visitor->create_complement();
  }
}

#endif

} // namespace
