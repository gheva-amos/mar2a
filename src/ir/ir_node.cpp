#include "ir/ir_node.h"

namespace mar2a
{

IRNode::IRNode(std::string name) :
  name_{name}
{
}

const std::string& IRNode::name() const
{
  return name_;
}

} // namespace
