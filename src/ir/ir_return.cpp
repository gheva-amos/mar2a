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

} // namespace
