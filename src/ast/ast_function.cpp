#include "ast/ast_function.h"

namespace mar2a
{

void ASTFunction::add_child(std::unique_ptr<ASTNode> child)
{
  if (ret_type_ == nullptr)
  {
    ret_type_ = std::move(child);
  }
  else if (name_ == nullptr)
  {
    name_ = std::move(child);
  }
  else
  {
    body_.push_back(std::move(child));
  }
}

void ASTFunction::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << "Function (" << std::endl;
  out << indent << "name = ";
  name_->pretty_print(out, indent + "\t");
  out << indent << " -> ";
  ret_type_->pretty_print(out, indent + "\t");
  out << indent << "body = {";
  for (const auto& st : body_)
  {
    st->pretty_print(out, indent + "\t");
  }
  out << indent << "}" << std::endl;
  out << indent << ")" << std::endl;
}

} // namespace
