#include "Pipelines/Pipelines.h"
#include "Conversion/TOSA/Passes.h"
#include "Conversion/ConvertToMlirLLVM/Passes.h"
#include "CodeGen/CPU/Passes.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/raw_ostream.h"
#include <elf.h>
#include <string>


static llvm::cl::opt<std::string> codeGenTarget(
      "nisl-codeGen-target",
      llvm::cl::desc(
          "llvm-cpu / cuda CodeGen"),
      llvm::cl::init("llvm-cpu"));



namespace mlir {
namespace compiler {
//===----------------------------------------------------------------------===//
// Pipelines
//===----------------------------------------------------------------------===//
    void bulidNISLTransformPassPipeline(OpPassManager &passManager){
        // TOSA Input Conversion Pipeline
        InputTosa::buildTransformPassPipeline(passManager);
        
        // Convert to Mlir LLVM
        ConvertToMlirLLVM::buildTransformPassPipeline(passManager);

        // CPU/GPU codeGen: convert the mlir LLVM to LLVM IR
        if (!codeGenTarget.compare("llvm-cpu")){
            CPUCodeGen::buildTransformPassPipeline(passManager);}
        else if(!codeGenTarget.compare("cuda")){
            return ;
        }else {
            llvm::errs() << "The target was not achieved! " << "\n";
        }
        

    

        

    }








    void registerNISLTransformPipeline(){
      PassPipelineRegistration<> transformPassPipeline(
      "NISL-transformation-pipeline",
      "Runs the full NISL input to LLVM transformation pipeline",
      [](OpPassManager &passManager) {
      bulidNISLTransformPassPipeline(passManager);
      });
    }
}
}
// void registerTOSAConversionPasses();