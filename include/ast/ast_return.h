#ifndef MAR2A_AST_RETURN_H__
#define MAR2A_AST_RETURN_H__

#include "ast/ast_node.h"

namespace mar2a
{

class ASTReturn : public ASTNode
{
public:
  virtual void add_child(std::unique_ptr<ASTNode> child) override;
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
  virtual std::unique_ptr<IRNode> visit() override;
private:
  std::unique_ptr<ASTNode> value_;
};

} // namespace

#endif // MAR2A_AST_RETURN_H__
