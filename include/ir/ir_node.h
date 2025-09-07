#ifndef MAR2A_IR_NODE_H__
#define MAR2A_IR_NODE_H__

#include <memory>
#include <string>
#include <ostream>

namespace mar2a
{

class IRNode
{
public:
  IRNode(std::string name);
  virtual ~IRNode() = default;
  virtual void pretty_print(std::ostream& out, const std::string& indent) const = 0;
protected:
  const std::string& name() const;
private:
  std::string name_;
};

} // namespace

#endif // MAR2A_IR_NODE_H__
