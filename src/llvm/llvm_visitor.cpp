#include "llvm/llvm_visitor.h"
#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/ExecutionEngine/Orc/ThreadSafeModule.h>
#include <llvm/Support/TargetSelect.h>

namespace mar2a
{

LLVMVisitor::LLVMVisitor() :
  context_{std::make_unique<llvm::LLVMContext>()}, builder_{*context_}
{
}

void LLVMVisitor::add_module(const std::string& m_name)
{
  modules_.emplace_back(std::make_unique<llvm::Module>(m_name, *context_));
  current_module_ = modules_.back().get();
}

void LLVMVisitor::create_i32()
{
  current_type_ = llvm::Type::getInt32Ty(*context_);
}

void LLVMVisitor::create_void()
{
  current_type_ = llvm::Type::getVoidTy(*context_);
}

void LLVMVisitor::create_function(const std::string& name)
{
  auto fty = llvm::FunctionType::get(current_type_, {}, false);
  current_function_ = llvm::Function::Create(fty, llvm::Function::ExternalLinkage, name, current_module_);
  current_block_ = llvm::BasicBlock::Create(*context_, name + "_entry", current_function_);
  builder_.SetInsertPoint(current_block_);
}

void LLVMVisitor::create_constant_int(int val)
{
  current_value_ = llvm::ConstantInt::get(current_type_, val);
}

void LLVMVisitor::create_return()
{
  builder_.CreateRet(current_value_);
}

void LLVMVisitor::print()
{
  modules_.back()->print(llvm::outs(), nullptr);
}

std::optional<int> LLVMVisitor::run()
{
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();

  auto jit = cantFail(llvm::orc::LLJITBuilder().create());
  modules_.back()->setDataLayout(jit->getDataLayout());
  llvm::orc::ThreadSafeModule tsm(std::move(modules_.back()), std::move(context_));
  if (jit->addIRModule(std::move(tsm)))
  {
    llvm::errs() << "addIRModule failed\n";
    return std::nullopt;
  }
  llvm::orc::ExecutorAddr addr = llvm::cantFail(jit->lookup("main"));

  using fpt = int (*)();
  auto fn = addr.toPtr<fpt>();
  auto ret = fn();
  llvm::outs() << "main() returned " << ret << "\n";
  return ret;
}

} // namespace
