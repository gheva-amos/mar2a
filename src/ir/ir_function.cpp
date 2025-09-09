#include "ir/ir_function.h"

namespace mar2a
{

IRFunction::IRFunction(std::string name) :
  IRNode{name}
{
}

void IRFunction::add_type(std::unique_ptr<IRNode> type)
{
  ret_type_ = std::move(type);
}

void IRFunction::add_statement(std::unique_ptr<IRNode> statement)
{
  statements_.push_back(std::move(statement));
}

void IRFunction::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << indent << name() << " -> ";
  ret_type_->pretty_print(out, "");
  for (const auto& st : statements_)
  {
    st->pretty_print(out, indent +"\t");
  }
}

#ifdef MAR2A_USE_LLVM

void IRFunction::visit(LLVMVisitor* visitor)
{
  ret_type_->visit(visitor);
  visitor->create_function(name());
  for (const auto& st : statements_)
  {
    st->visit(visitor);
  }
}

#endif
} // namespace
