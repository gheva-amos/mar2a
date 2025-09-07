#include "ast/ast_program.h"

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

} // namespace
