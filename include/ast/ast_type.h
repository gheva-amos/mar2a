#ifndef MAR2A_AST_TYPE_H__
#define MAR2A_AST_TYPE_H__

#include "lexer/token.h"
#include "ast/ast_node.h"
#include <string>

namespace mar2a
{

class ASTType : public ASTNode
{
public:
  enum class Type
  {
    type_int,
    type_void,
    type_unknown,
  };
  ASTType(const std::string exp, Token::Type type);
  virtual void add_child(std::unique_ptr<ASTNode> child) override;
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
  Type type() const;
private:
  const std::string exp_;
  Type type_;
};

} // namespace

#endif // MAR2A_AST_TYPE_H__
