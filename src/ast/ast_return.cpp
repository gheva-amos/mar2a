#include "ast/ast_return.h"
#include "ir/ir_return.h"

namespace mar2a
{

void ASTReturn::add_child(std::unique_ptr<ASTNode> child)
{
  value_ = std::move(child);
}

void ASTReturn::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << "Return (" << std::endl;
  value_->pretty_print(out, indent + "\t");
  out << indent << ")" << std::endl;
}

std::unique_ptr<IRNode> ASTReturn::visit()
{
  std::unique_ptr<IRReturn> ret{std::make_unique<IRReturn>()};
  ret->add_value(value_->visit());
  return ret;
}

} // namespace
