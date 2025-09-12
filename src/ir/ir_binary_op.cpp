#include "ir/ir_binary_op.h"

namespace mar2a
{

IRBinaryOp::IRBinaryOp(std::string name, Kind kind) :
  IRNode{name}, kind_{kind}
{
}

IRBinaryOp::Kind IRBinaryOp::kind() const
{
  return kind_;
}

void IRBinaryOp::add_left(std::unique_ptr<IRNode> exp)
{
  left_ = std::move(exp);
}

void IRBinaryOp::add_right(std::unique_ptr<IRNode> exp)
{
  right_ = std::move(exp);
}

void IRBinaryOp::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << name();
  left_->pretty_print(out, indent + "\t");
  right_->pretty_print(out, indent + "\t");
}

#ifdef MAR2A_USE_LLVM
void IRBinaryOp::visit(LLVMVisitor* visitor)
{
  left_->visit(visitor);
  right_->visit(visitor);
  switch (kind())
  {
  case Kind::plus:
    visitor->create_add();
    break;
  case Kind::minus:
    visitor->create_subtract();
    break;
  case Kind::times:
    visitor->create_multiplication();
    break;
  case Kind::divide:
    visitor->create_division();
    break;
  case Kind::remainder:
    visitor->create_remainder();
    break;
  }
}

#endif
} // namespace
