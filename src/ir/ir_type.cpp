#include "ir/ir_type.h"

namespace mar2a
{

IRType::IRType(ASTType::Type type) :
  IRNode("type")
{
  switch (type)
  {
  case ASTType::Type::type_int:
    type_ = Type::type_int;
    break;
  case ASTType::Type::type_void:
    type_ = Type::type_void;
    break;
  case ASTType::Type::type_unknown:
    type_ = Type::type_unknown;
    break;
  }
}

IRType::IRType(Type type) :
  IRNode("type"), type_{type}
{
}

IRType IRType::Int()
{
  return IRType{Type::type_int};
}

IRType IRType::Void()
{
  return IRType{Type::type_void};
}

IRType IRType::Unknown()
{
  return IRType{Type::type_unknown};
}

IRType IRType::factory(ASTType::Type type)
{
  switch (type)
  {
  case ASTType::Type::type_int:
    return Int();
  case ASTType::Type::type_void:
    return Void();
  case ASTType::Type::type_unknown:
    return Unknown();
  }
  return Unknown();
}

void IRType::pretty_print(std::ostream& out, const std::string& indent) const
{
  switch (type_)
  {
  case Type::type_int:
    out << "int" << std::endl;
    break;
  case Type::type_void:
    out << "void" << std::endl;
    break;
  case Type::type_unknown:
    out << "unknown" << std::endl;
    break;
  }
}

} // namespace
