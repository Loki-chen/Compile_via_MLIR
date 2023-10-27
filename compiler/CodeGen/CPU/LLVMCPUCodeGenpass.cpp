

#include "mlir/Dialect/Func/IR/FuncOps.h"
#include "mlir/Dialect/LLVMIR/LLVMDialect.h"
#include "mlir/Dialect/LLVMIR/LLVMTypes.h"
#include "mlir/IR/Attributes.h"
#include "mlir/IR/BuiltinAttributes.h"
#include "mlir/IR/BuiltinOps.h"
#include "mlir/IR/BuiltinTypes.h"
#include "mlir/IR/MLIRContext.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/OperationSupport.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassRegistry.h"
#include "llvm-c/Core.h"
#include "llvm-c/Target.h"
#include "llvm-c/Types.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/CodeGen/CodeGenPassBuilder.h"
#include "llvm/IR/Attributes.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/TargetParser/Triple.h"
#include <memory>
#include <iostream>
#include <string>


#include "mlir/Target/LLVMIR/Dialect/Builtin/BuiltinToLLVMIRTranslation.h"
#include "mlir/Target/LLVMIR/Dialect/LLVMIR/LLVMToLLVMIRTranslation.h"
#include "mlir/Target/LLVMIR/Export.h"

#include "CodeGen/CodeGenTools.h"





namespace mlir {
namespace compiler {

namespace CPUCodeGen {

class LLVMCpuCodeGenPass : public PassWrapper<LLVMCpuCodeGenPass, OperationPass<mlir::ModuleOp>>{
    public:
        LLVMCpuCodeGenPass() = default;
    StringRef getArgument() const override{
        return "nisl-cpu-codegen-pass";
    }

    StringRef getDescription() const override{
        return "llvm.mlir.constant ops to  load ptr";
    }

    void runOnOperation() override {

        auto moduleOp = getOperation();
        llvm::LLVMContext context;


        // target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
        // target triple = "x86_64-unknown-unknown-eabi-elf"
        const std::string targetTripleStr =  "x86_64-unknown-unknown-eabi-elf";
        const std::string dataLayoutStr = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128";
        // TODO----The second parm Type is Attribute 
        moduleOp->setAttr(LLVM::LLVMDialect::getDataLayoutAttrName(), 
                    StringAttr::get(moduleOp->getContext(),dataLayoutStr));
        moduleOp->setAttr(LLVM::LLVMDialect::getTargetTripleAttrName(), 
                    StringAttr::get(moduleOp->getContext(),targetTripleStr));

        auto funcOps = moduleOp.getOps<mlir::LLVM::LLVMFuncOp>();
        std::string funcName; 
        if(!funcOps.empty()){
            for (auto funcOp:funcOps){
                funcName =  CodeGenTools::getfuncName(funcOp);  
            }
        }

        // Convert the llvm to the LLVMIR
        auto llvmModule = mlir::translateModuleToLLVMIR(moduleOp, context, funcName);
        if (!llvmModule) {
            llvm::errs() << "failed to translate the MLIR LLVM "
                                      "dialect to the native llvm::Module";
        }


        // Configure the functions in the module. This may override defaults set
        // during the MLIR->LLVM conversion.
        for (auto &func : *llvmModule) {
        // Enable frame pointers to ensure that stack unwinding works, e.g. in
        // Tracy. In principle this could also be achieved by enabling unwind
        // tables, but we tried that and that didn't work in Tracy (which uses
        // libbacktrace), while enabling frame pointers worked.
        // https://github.com/openxla/iree/issues/3957
        func.addFnAttr("frame-pointer", "all");
        // -ffreestanding-like behavior.
        func.addFnAttr("no-builtins");
        // Our dispatches are all hot - that's kind of the point.
        // This may favor more aggressive optimizations.
        func.addFnAttr("hot");
        }


        // Dump just the codegen LLVM IR to file etc */.bc
        StringRef path="/home/MLIR-Compiler/tests/tosa-mlir/";
        StringRef suffix="llvm_cpu";
        StringRef baseName = funcName;
        StringRef extension = "_codegen.bc";

        CodeGenTools::DumpBitCodeToFile(*llvmModule, path, suffix, baseName, extension);


    }
};

std::unique_ptr<OperationPass<ModuleOp>> createLLVMCpuCodeGenPass(){
    return std::make_unique<LLVMCpuCodeGenPass>();
}

// static PassRegistration<LLVMCpuCodeGenPass> pass;

static PassRegistration<LLVMCpuCodeGenPass> pass([] {
  return std::make_unique<LLVMCpuCodeGenPass>();
});


void registerCPUTargetBackend(){

    // LLVMInitializeAllTargets();
    // LLVMInitializeAllTargetInfos();
    // LLVMInitializeAllTargetMCs();
    // LLVMInitializeAllAsmPrinters();
}


}
}
}