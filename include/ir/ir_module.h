#ifndef MAR2A_IR_MODULE_H__
#define MAR2A_IR_MODULE_H__
#include "ir/ir_node.h"
#include <vector>

namespace mar2a
{

class IRModule : public IRNode
{
public:
  IRModule(std::string name);
  virtual void pretty_print(std::ostream& out, const std::string& indent) const override;
  void add_child(std::unique_ptr<IRNode> child);
private:
  std::vector<std::unique_ptr<IRNode>> children_;
};

} // namespace

#endif // MAR2A_IR_MODULE_H__
