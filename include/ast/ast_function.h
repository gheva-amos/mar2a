#ifndef MAR2A_AST_FUNCTION_H__
#define MAR2A_AST_FUNCTION_H__

#include "ast/ast_node.h"
#include <vector>

namespace mar2a
{

class ASTFunction : public ASTNode
{
public:
  virtual void add_child(std::unique_ptr<ASTNode> child) override;
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
private:
  std::unique_ptr<ASTNode> name_{nullptr};
  std::vector<std::unique_ptr<ASTNode>> body_;
};

} // namespace

#endif // MAR2A_AST_FUNCTION_H__
