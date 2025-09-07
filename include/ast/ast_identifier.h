#ifndef MAR2A_AST_IDENTIFIER_H__
#define MAR2A_AST_IDENTIFIER_H__

#include "ast/ast_node.h"
#include <string>

namespace mar2a
{

class ASTIdentifier : public ASTNode
{
public:
  ASTIdentifier(const std::string id);
  virtual void add_child(std::unique_ptr<ASTNode> child) override;
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
private:
  const std::string id_;
};

} // namespace

#endif // MAR2A_AST_IDENTIFIER_H__
