#include "ast/ast_program.h"
#include "ir/ir_module.h"

namespace mar2a
{

void ASTProgram::add_child(std::unique_ptr<ASTNode> child)
{
  children_.push_back(std::move(child));
}

void ASTProgram::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << "Program (" << std::endl;
  for (const auto& child : children_)
  {
    child->pretty_print(out, indent + "\t");
  }
  out << indent << ")" << std::endl;
}

std::unique_ptr<IRNode> ASTProgram::visit()
{
  std::unique_ptr<IRModule> ret{std::make_unique<IRModule>("Program")};
  for (const auto& child : children_)
  {
    ret->add_child(child->visit());
  }
  return ret;
}

} // namespace
