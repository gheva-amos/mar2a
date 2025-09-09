#ifndef MAR2A_IR_FUNCTION_H__
#define MAR2A_IR_FUNCTION_H__

#include "ir/ir_node.h"
#include <vector>

namespace mar2a
{

class IRFunction : public IRNode
{
public:
  IRFunction(std::string name);
  void add_type(std::unique_ptr<IRNode> type);
  void add_statement(std::unique_ptr<IRNode> statement);
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
#ifdef MAR2A_USE_LLVM
  virtual void visit(LLVMVisitor* visitor) override;
#endif
private:
  std::unique_ptr<IRNode> ret_type_;
  std::vector<std::unique_ptr<IRNode>> statements_;
};

}// namespace

#endif // MAR2A_IR_FUNCTION_H__
