#ifndef MAR2A_IR_VALUE_H__
#define MAR2A_IR_VALUE_H__

#include "ir/ir_node.h"
#include "ir/ir_type.h"

namespace mar2a
{

class IRValue : public IRNode
{
public:
  IRValue(std::string name, IRType::Type type);
private:
  IRType type_;
};

} // namespace

#endif // MAR2A_IR_VALUE_H__
