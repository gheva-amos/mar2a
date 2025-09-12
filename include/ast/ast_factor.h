#ifndef MAR2A_AST_FACTOR_H__
#define MAR2A_AST_FACTOR_H__

#include "ast/ast_node.h"
#include <string>

namespace mar2a
{

class ASTFactor : public ASTNode
{
public:
  enum class Type
  {
    const_int,
    minus,
    decrement,
    tilde,
  };
  ASTFactor(const std::string exp, Type type);
  virtual void add_child(std::unique_ptr<ASTNode> child) override;
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
  virtual std::unique_ptr<IRNode> visit() override;
private:
  const std::string exp_;
  std::unique_ptr<ASTNode> child_;
  Type type_;
};

} // namespace

#endif // MAR2A_AST_FACTOR_H__
