#ifndef MAR2A_IR_TYPE_H__
#define MAR2A_IR_TYPE_H__

#include "ir/ir_node.h"
#include "ast/ast_type.h"

namespace mar2a
{

class IRType : public IRNode
{
public:
  enum class Type
  {
    type_int,
    type_void,
    type_unknown,
  };
  IRType(ASTType::Type type);
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
  static IRType Int();
  static IRType Void();
  static IRType Unknown();
  static IRType factory(ASTType::Type type);

#ifdef MAR2A_USE_LLVM
  virtual void visit(LLVMVisitor* visitor) override;
#endif
private:
  IRType(Type type);
  Type type_;
};

} // namespace

#endif // MAR2A_IR_TYPE_H__
