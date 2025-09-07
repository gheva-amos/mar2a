#ifndef MAR2A_AST_PROGRAM_H__
#define MAR2A_AST_PROGRAM_H__

#include "ast/ast_node.h"
#include <vector>

namespace mar2a
{

class ASTProgram : public ASTNode
{
public:
  virtual void add_child(std::unique_ptr<ASTNode> child) override;
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
private:
  std::vector<std::unique_ptr<ASTNode>> children_;
};

} // namespace

#endif // MAR2A_AST_PROGRAM_H__
