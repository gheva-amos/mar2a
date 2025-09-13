#ifndef MAR2A_AST_EXPRESSION_H__
#define MAR2A_AST_EXPRESSION_H__

#include "ast/ast_node.h"
#include "lexer/token.h"
#include <string>
#include <vector>

namespace mar2a
{

class ASTExpression : public ASTNode
{
public:
  enum class Type
  {
    plus,
    minus,
    times,
    divide,
    remainder
  };
  ASTExpression(const std::string exp, Type type);
  virtual void add_child(std::unique_ptr<ASTNode> child) override;
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
  virtual std::unique_ptr<IRNode> visit() override;
  static std::unique_ptr<ASTExpression> factory(std::string value, Token::Type type);
  Type type() const;
private:
  const std::string exp_;
  std::vector<std::unique_ptr<ASTNode>> children_;
  Type type_;
};

} // namespace

#endif // MAR2A_AST_EXPRESSION_H__
