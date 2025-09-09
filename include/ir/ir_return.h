#ifndef MAR2A_IR_RETURN_H__
#define MAR2A_IR_RETURN_H__

#include "ir/ir_node.h"

namespace mar2a
{

class IRReturn : public IRNode
{
public:
  IRReturn();
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
  void add_value(std::unique_ptr<IRNode> child);
#ifdef MAR2A_USE_LLVM
  virtual void visit(LLVMVisitor* visitor) override;
#endif
private:
  std::unique_ptr<IRNode> value_;
};

} // namespace

#endif // MAR2A_IR_RETURN_H__
