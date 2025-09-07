#ifndef MAR2A_AST_EXPRESSION_H__
#define MAR2A_AST_EXPRESSION_H__

#include "ast/ast_node.h"
#include <string>

namespace mar2a
{

class ASTExpression : public ASTNode
{
public:
  ASTExpression(const std::string exp);
  virtual void add_child(std::unique_ptr<ASTNode> child) override;
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
private:
  const std::string exp_;
};

} // namespace

#endif // MAR2A_AST_EXPRESSION_H__
