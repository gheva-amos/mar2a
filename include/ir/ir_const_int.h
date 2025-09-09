#ifndef MAR2A_IR_CONST_INT_H__
#define MAR2A_IR_CONST_INT_H__

#include "ir/ir_value.h"

namespace mar2a
{

class IRConstInt : public IRValue
{
public:
  IRConstInt(std::string name, const std::string& value);
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
#ifdef MAR2A_USE_LLVM
  virtual void visit(LLVMVisitor* visitor) override;
#endif
private:
  int value_;
};

} // namespace

#endif // MAR2A_IR_CONST_INT_H__
