// See https://llvm.org/docs/WritingAnLLVMNewPMPass.html
// And https://llvm.org/docs/WritingAnLLVMPass.html#building-pass-plugins
// And llvm/examples/Bye/Bye.cpp
// running: clang -fpass-plugin=/path/to/lib.so

#include "llvm/IR/PassManager.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"

using namespace llvm;

// TODO: This name for new plugin should be modified
#define PLUGIN_NAME "NdkSamplePass"

// No need to expose the internals of the pass to the outside world,
// keep everything in an anonymous namespace.
namespace {
    // real function here
    // return true if modified IR
    bool runPass(Function &F) {
        errs() << "I saw a function called " << F.getName() << "\n";
        return false;
    }

    // TODO: This class name for new plugin should be modified
    class NdkSamplePass : public PassInfoMixin<NdkSamplePass> {
    public:
        // Main entry point, takes IR unit to run the pass on (&F) and the
        // corresponding pass manager (to be queried if need be)
        PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM) {
            if (!runPass(F))
                return PreservedAnalyses::all();
            return PreservedAnalyses::none();
        }

        // Without isRequired returning true, this pass will be skipped for functions
        // decorated with the optnone LLVM attribute. Note that clang -O0 decorates
        // all functions with optnone.
        static bool isRequired() { return true; }

        static void registerCallbacks(PassBuilder &PB) {
            //    before any other transformations are
            //    run (i.e. via `EP_EarlyAsPossible` for the Legacy PM) or whenever the
            //    vectorizer is run (i.e. via `registerVectorizerStartEPCallback` for the
            //    new PM).
            PB.registerVectorizerStartEPCallback([](FunctionPassManager &PM, OptimizationLevel level) {
                PM.addPass(NdkSamplePass());
            });

            // REGISTRATION FOR "opt -passes=pass-name", but is useless for clang, we leave it here
            PB.registerPipelineParsingCallback(
                    [](StringRef Name, FunctionPassManager &FPM,
                       ArrayRef<PassBuilder::PipelineElement>) {
                        if (Name == "pass-name") {
                            FPM.addPass(NdkSamplePass());
                            return true;
                        }
                        return false;
                    });
        }

    };


}

// New PM Registration
// This function name should not be modified
extern "C" ::llvm::PassPluginLibraryInfo LLVM_ATTRIBUTE_WEAK
llvmGetPassPluginInfo() {
    errs() << PLUGIN_NAME << " loaded!\n";
    return {
            LLVM_PLUGIN_API_VERSION,
            PLUGIN_NAME,
            LLVM_VERSION_STRING,
            NdkSamplePass::registerCallbacks
    };
};

