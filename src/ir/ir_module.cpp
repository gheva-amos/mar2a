#include "ir/ir_module.h"

namespace mar2a
{

IRModule::IRModule(std::string name) :
  IRNode(name)
{
}

void IRModule::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << name() << std::endl;
  for (const auto& child : children_)
  {
    child->pretty_print(out, indent + "\t");
  }
}

void IRModule::add_child(std::unique_ptr<IRNode> child)
{
  children_.push_back(std::move(child));
}

} // namespace
