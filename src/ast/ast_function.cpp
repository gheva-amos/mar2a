#include "ast/ast_function.h"
#include "ast/ast_type.h"
#include "ast/ast_identifier.h"
#include "ir/ir_function.h"
#include "ir/ir_type.h"

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

std::unique_ptr<IRNode> ASTFunction::visit()
{
  ASTType* type{dynamic_cast<ASTType*>(ret_type_.get())};
  if (type == nullptr)
  {
    return nullptr;
  }
  ASTIdentifier* name{dynamic_cast<ASTIdentifier*>(name_.get())};
  if (name == nullptr)
  {
    return nullptr;
  }
  std::unique_ptr<IRFunction> ret{std::make_unique<IRFunction>(name->id())};
  ret->add_type(std::make_unique<IRType>(type->type()));

  for (auto& st : body_)
  {
    ret->add_statement(st->visit());
  }
  return ret;
}

} // namespace
