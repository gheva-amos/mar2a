#include "ast/ast_type.h"

namespace mar2a
{

ASTType::ASTType(const std::string type) :
  type_{type}
{
}

void ASTType::add_child(std::unique_ptr<ASTNode> child)
{
}

void ASTType::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << type_ << std::endl;
}

} // namespace
