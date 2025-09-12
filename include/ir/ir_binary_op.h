#ifndef MAR2A_IR_BINARY_OP_H__
#define MAR2A_IR_BINARY_OP_H__
#include "ir/ir_node.h"

namespace mar2a
{

class IRBinaryOp : public IRNode
{
public:
  enum class Kind
  {
    plus,
    minus,
    times,
    divide,
    remainder,
  };
  IRBinaryOp(std::string name, Kind kind);
  Kind kind() const;
  void add_left(std::unique_ptr<IRNode> exp);
  void add_right(std::unique_ptr<IRNode> exp);
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
#ifdef MAR2A_USE_LLVM
  virtual void visit(LLVMVisitor* visitor) override;
#endif
private:
  Kind kind_;
  std::unique_ptr<IRNode> left_;
  std::unique_ptr<IRNode> right_;
};

} // namespace

#endif // MAR2A_IR_BINARY_OP_H__
