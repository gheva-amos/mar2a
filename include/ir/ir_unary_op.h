#ifndef MAR2A_IR_UNARY_OP_H__
#define MAR2A_IR_UNARY_OP_H__
#include "ir/ir_node.h"

namespace mar2a
{

class IRUnaryOp : public IRNode
{
public:
  enum class Kind
  {
    tilde,
    minus,
  };
  IRUnaryOp(std::string name, Kind kind);
  void set_kind(Kind kind);
  Kind kind() const;
  void add_expression(std::unique_ptr<IRNode> exp);
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
#ifdef MAR2A_USE_LLVM
  virtual void visit(LLVMVisitor* visitor) override;
#endif
private:
  Kind kind_;
  std::unique_ptr<IRNode> expression_;
};

} // namespace

#endif // MAR2A_IR_UNARY_OP_H__
