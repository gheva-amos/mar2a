#include "ir/ir_value.h"

namespace mar2a
{

IRValue::IRValue(std::string name, IRType::Type type) :
  IRNode(name), type_{IRType::Unknown()}
{
  switch (type)
  {
  case IRType::Type::type_int:
    type_ = IRType::Int();
    break;
  case IRType::Type::type_void:
    type_ = IRType::Void();
    break;
  case IRType::Type::type_unknown:
    break;
  }
}

} // namespace
