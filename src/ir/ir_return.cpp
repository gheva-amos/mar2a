#include "ir/ir_return.h"

namespace mar2a
{

IRReturn::IRReturn() :
  IRNode("return")
{
}

void IRReturn::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << "return ";
  value_->pretty_print(out, "");
  out << std::endl;
}

void IRReturn::add_value(std::unique_ptr<IRNode> child)
{
  value_ = std::move(child);
}

#ifdef MAR2A_USE_LLVM

void IRReturn::visit(LLVMVisitor* visitor)
{
  value_->visit(visitor);
  visitor->create_return();
}

#endif

} // namespace
