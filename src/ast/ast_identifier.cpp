#include "ast/ast_identifier.h"

namespace mar2a
{

ASTIdentifier::ASTIdentifier(const std::string id) :
  id_{id}
{
}

void ASTIdentifier::add_child(std::unique_ptr<ASTNode> child)
{
}

void ASTIdentifier::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << id_ << std::endl;
}

const std::string& ASTIdentifier::id() const
{
  return id_;
}

} // namespace
