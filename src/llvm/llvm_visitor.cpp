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
  current_type_.push_back(llvm::Type::getInt32Ty(*context_));
}

void LLVMVisitor::create_void()
{
  current_type_.push_back(llvm::Type::getVoidTy(*context_));
}

void LLVMVisitor::create_function(const std::string& name)
{
  auto fty = llvm::FunctionType::get(current_type_.back(), {}, false);
  current_type_.pop_back();
  current_function_.push_back(llvm::Function::Create(fty, llvm::Function::ExternalLinkage, name, current_module_));
  current_block_.push_back(llvm::BasicBlock::Create(*context_, name + "_entry", current_function_.back()));
  builder_.SetInsertPoint(current_block_.back());
}

void LLVMVisitor::create_constant_int(int val)
{
  current_value_.push_back(llvm::ConstantInt::get(current_type_.back(), val));
  current_type_.pop_back();
}

void LLVMVisitor::create_return()
{
  builder_.CreateRet(current_value_.back());
  current_value_.pop_back();
}

void LLVMVisitor::create_negative()
{
  auto* type = current_value_.back()->getType();
  if (type->isFloatingPointTy())
  {
    auto val = builder_.CreateFNeg(current_value_.back(), "fneg");
    current_value_.pop_back();
    current_value_.push_back(val);
  }
  else if (type->isIntegerTy())
  {
    auto val = builder_.CreateNeg(current_value_.back(), "neg");
    current_value_.pop_back();
    current_value_.push_back(val);
  }
  else
  {
    // TODO ERROR
  }
}

void LLVMVisitor::create_complement()
{
  auto* type = current_value_.back()->getType();
  if (type->isIntegerTy())
  {
    auto val = builder_.CreateNot(current_value_.back(), "not");
    current_value_.pop_back();
    current_value_.push_back(val);
  }
  else
  {
    // TODO error
  }
}

void LLVMVisitor::create_add()
{
  auto rhs = current_value_.back();
  current_value_.pop_back();
  auto lhs = current_value_.back();
  current_value_.pop_back();
  current_value_.push_back(builder_.CreateAdd(lhs, rhs, "Addition"));
}

void LLVMVisitor::create_subtract()
{
  auto rhs = current_value_.back();
  current_value_.pop_back();
  auto lhs = current_value_.back();
  current_value_.pop_back();
  current_value_.push_back(builder_.CreateSub(lhs, rhs, "Subtraction"));
}

void LLVMVisitor::create_multiplication()
{
  auto rhs = current_value_.back();
  current_value_.pop_back();
  auto lhs = current_value_.back();
  current_value_.pop_back();
  current_value_.push_back(builder_.CreateMul(lhs, rhs, "Multiplication"));
}

void LLVMVisitor::create_division()
{
  auto rhs = current_value_.back();
  current_value_.pop_back();
  auto lhs = current_value_.back();
  current_value_.pop_back();
  current_value_.push_back(builder_.CreateSDiv(lhs, rhs, "Signed division"));
}

void LLVMVisitor::create_remainder()
{
  auto rhs = current_value_.back();
  current_value_.pop_back();
  auto lhs = current_value_.back();
  current_value_.pop_back();
  current_value_.push_back(builder_.CreateSRem(lhs, rhs, "Signed remainder"));
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
