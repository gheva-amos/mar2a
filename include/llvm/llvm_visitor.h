#ifndef MAR2A_LLVM_VISITOR_H__
#define MAR2A_LLVM_VISITOR_H__

#include <vector>
#include <memory>
#include <optional>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>

namespace mar2a
{

class LLVMVisitor
{
public:
  LLVMVisitor();
  void add_module(const std::string& m_name);
  void create_i32();
  void create_void();
  void create_function(const std::string& name);
  void create_constant_int(int val);
  void create_return();
  void print();
  std::optional<int> run();
private:
  std::unique_ptr<llvm::LLVMContext> context_;
  std::vector<std::unique_ptr<llvm::Module>> modules_;
  llvm::IRBuilder<> builder_;
  llvm::Module* current_module_;
  llvm::Function* current_function_;
  llvm::BasicBlock* current_block_;
  llvm::Type* current_type_;
  llvm::Value* current_value_;
};

} // namespace

#endif // MAR2A_LLVM_VISITOR_H__
