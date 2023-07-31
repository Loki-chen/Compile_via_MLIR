
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"


#include "mlir/Pass/Pass.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/Target/LLVMIR/Export.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/Func/IR/FuncOps.h"

#include "CodeGen/CodeGenTools.h"
#include <iostream>
#include <string>




static llvm::cl::opt<std::string> clTargetChip(
    "nisl-cuda-llvm-target-arch", llvm::cl::desc("LLVM target chip."),
    llvm::cl::init("sm_35"));


static std::string translateLlvmIRModuleToPtx(llvm::Module &module,
                                        llvm::TargetMachine &targetMachine) {
    std::string targetPtx;
    {
        llvm::raw_string_ostream stream(targetPtx);
        llvm::buffer_ostream pstream(stream);
        llvm::legacy::PassManager codegenPass;
        targetMachine.addPassesToEmitFile(codegenPass, pstream, nullptr, llvm::CGFT_AssemblyFile);
        codegenPass.run(module);
    }   
    return targetPtx;                                             
 }


namespace mlir {
namespace compiler {
namespace GPUCodeGen {

//===--------------------------------------------------------------------===//
  // Convert mlir LLVM to ptx.
  //
  // Post-conditions:
  //   - The module contains the final llvm.module ready to be serialized.
//===--------------------------------------------------------------------===//
class LLVMGpuCodeGenPass : public PassWrapper<LLVMGpuCodeGenPass, OperationPass<mlir::ModuleOp>>{

    public:
        LLVMGpuCodeGenPass() =default;
    StringRef getArgument() const override{
        return "nisl-gpu-codeGen";
        }
    StringRef getDescription() const override{
        return "llvm.mlir convert to ptx";
    }
    void runOnOperation() override;
};


void LLVMGpuCodeGenPass::runOnOperation(){

    llvm::LLVMContext context;
    auto moduleOp = getOperation(); 

    auto funcOps = moduleOp.getOps<mlir::LLVM::LLVMFuncOp>();
    std::string funcName; 
    if(!funcOps.empty()){
        for (auto funcOp:funcOps){
          funcName =  CodeGenTools::getfuncName(funcOp);  
    }
    }
    // Remove all the functions that are not part of the CUDA kernel.
    // TODO(thomasraoux): remove this? this should not be required.
    auto illegalFuncOps =
        llvm::to_vector<4>(moduleOp.getOps<func::FuncOp>());
    for (auto funcOp : illegalFuncOps) {
        funcOp.erase();
    }


    // Convert the llvm to the LLVMIR
    auto llvmModule = mlir::translateModuleToLLVMIR(moduleOp, context, funcName);
    if (!llvmModule) {
        llvm::errs() << "failed to translate the MLIR LLVM "
                                      "dialect to the native llvm::Module";
    }


      std::unique_ptr<llvm::TargetMachine> targetMachine;
      {
        llvm::Triple triple("nvptx64-nvidia-cuda");
        std::string targetChip = clTargetChip;
        std::string features = "+ptx60";
        std::string error;
        const llvm::Target *target =
            llvm::TargetRegistry::lookupTarget("", triple, error);
        if (target == nullptr) {
          moduleOp.emitError() << "cannot initialize target triple";
        }

        targetMachine.reset(target->createTargetMachine(
            triple.str(), targetChip, features, {}, {}));
        if (targetMachine == nullptr) {
          moduleOp.emitError() << "cannot initialize target machine";
        }
      }

    std::string ptxImage;
    ptxImage = translateLlvmIRModuleToPtx(*llvmModule, *targetMachine);
    std::cout<<"cuda ptx codeGen"<<ptxImage;
}


void registerCUDATargetBackend(){

    LLVMInitializeNVPTXTarget();
    LLVMInitializeNVPTXTargetMC();
    LLVMInitializeNVPTXTargetInfo();
    LLVMInitializeNVPTXAsmPrinter();
}

std::unique_ptr<OperationPass<ModuleOp>> createLLVMGpuCodeGenPass(){
    return std::make_unique<LLVMGpuCodeGenPass>();
}


static PassRegistration<LLVMGpuCodeGenPass> pass([] {
  return std::make_unique<LLVMGpuCodeGenPass>();
});

  } // namespace GpuCodeGen
 }  // namespace compiler
 }  // namespcae mlir