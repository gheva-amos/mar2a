#include "ir/ir_const_int.h"
#include <cstdlib>

namespace mar2a
{

IRConstInt::IRConstInt(std::string name, const std::string& value) :
  IRValue(name, IRType::Type::type_int)
{
  value_ = std::atoi(value.c_str());
}

void IRConstInt::pretty_print(std::ostream& out, const std::string& indent) const
{
  out << value_;
}

#ifdef MAR2A_USE_LLVM

void IRConstInt::visit(LLVMVisitor* visitor)
{
  visitor->create_i32();
  visitor->create_constant_int(value_);
}

#endif
} // namespace
