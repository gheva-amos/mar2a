#ifndef MAR2A_AST_NODE_H__
#define MAR2A_AST_NODE_H__

#include <memory>
#include <string>
#include <ostream>

namespace mar2a
{

class ASTNode
{
public:
  virtual ~ASTNode() = default;
  virtual void add_child(std::unique_ptr<ASTNode> child) = 0;
  virtual void pretty_print(std::ostream& out, const std::string& indent) const = 0;
};

} // namespace

#endif // MAR2A_AST_NODE_H__
