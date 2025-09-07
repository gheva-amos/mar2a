#ifndef MAR2A_AST_TYPE_H__
#define MAR2A_AST_TYPE_H__

#include "ast/ast_node.h"
#include <string>

namespace mar2a
{

class ASTType : public ASTNode
{
public:
  ASTType(const std::string exp);
  virtual void add_child(std::unique_ptr<ASTNode> child) override;
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
private:
  const std::string type_;
};

} // namespace

#endif // MAR2A_AST_TYPE_H__
