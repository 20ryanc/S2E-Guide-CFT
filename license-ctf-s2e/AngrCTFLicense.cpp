#include <s2e/S2E.h>

#include <s2e/Plugins/OSMonitors/Support/ProcessExecutionDetector.h>

#include <klee/util/ExprTemplates.h>

#include <cctype>
#include <sstream>

#include "AngrCTFLicense.h"

static const uint64_t SUCCESS_ADDRESS = 0x400e93;
static const std::unordered_set<uint64_t> FAILURE_ADDRESSES = {0x400bb1, 0x400b8f, 0x400b6d, 0x400a85, 0x400ebf, 0x400a59};

namespace s2e {
namespace plugins {

S2E_DEFINE_PLUGIN(AngrCTFLicense,
                  "Solution for ASIS CTF Finals 2015 - license", "",
                  "ProcessExecutionDetector");

void AngrCTFLicense::initialize() {
    // We need to use the ProcessExecutionDetector plugin to filter out all processes other than the "unbreakable"
    // process
    m_procDetector = s2e()->getPlugin<ProcessExecutionDetector>();

    s2e()->getCorePlugin()->onSymbolicVariableCreation.connect(
        sigc::mem_fun(*this, &AngrCTFLicense::onSymbolicVariableCreation));
    s2e()->getCorePlugin()->onTranslateInstructionStart.connect(
        sigc::mem_fun(*this, &AngrCTFLicense::onTranslateInstruction));
}

void AngrCTFLicense::onSymbolicVariableCreation(S2EExecutionState *state, const std::string &name,
                                                      const std::vector<klee::ref<klee::Expr>> &expr, const klee::ArrayPtr &array) {
    // This check is not strictly required, because we only have one symbolic variable in the analysis.
    //
    // Program arguments made symbolic with the S2E_SYM_ARGS environment variable always have the name "argX", where
    // "X" is the argument index (starting with X = 1 for the first argument)
    if (name != "arg1") {
        return;
    }

    // The following code has been removed because it has varying effects on S2E's performance. For example,
    // constraining that all other characters must be non-NULL slightly improves performance. However,
    // over-constraining the characters so that they must all be printable ASCII characters significantly effects
    // performance.
    //
    // The code is left here so that the user can experiement with constraining the product activation code in
    // different ways and how this can impact performance.
    
    bool success = true;
    
    for (unsigned i = 6; i < expr.size(); i+=7) {
        success = success && state->addConstraint(E_EQ(expr[i], E_CONST('\n', klee::Expr::Int8)));
    }
    for (unsigned i = 0; i < expr.size(); ++i) {
        if(i % 7 == 6){
            continue;
        }
        success = success & state->addConstraint(E_NEQ(expr[i], E_CONST('\n', klee::Expr::Int8)));

        //success = success & state->addConstraint(E_GE(expr[i], E_CONST(' ', klee::Expr::Int8)));
        //success = success & state->addConstraint(E_LE(expr[i], E_CONST('~', klee::Expr::Int8)));
    }
}

void AngrCTFLicense::onTranslateInstruction(ExecutionSignal *signal, S2EExecutionState *state,
                                                  TranslationBlock *tb, uint64_t pc) {
    if (pc == SUCCESS_ADDRESS) {
        signal->connect(sigc::mem_fun(*this, &AngrCTFLicense::onSuccess));
    } else if (FAILURE_ADDRESSES.count(pc)) {
        signal->connect(sigc::mem_fun(*this, &AngrCTFLicense::onFailure));
    }
}

void AngrCTFLicense::onSuccess(S2EExecutionState *state, uint64_t pc) {
    // Ensure that the unbreakable process is executing
    if (!m_procDetector->isTracked(state)) {
        return;
    }

    // `results` is a vector containing pairs of strings and a vector of bytes. The string corresponds to the symbolic
    // variable's name while the vector of bytes is the actual solution
    std::vector<std::pair<std::string, std::vector<unsigned char>>> results;

    // Invoke the constraint solver
    if (!state->getSymbolicSolution(results)) {
        getWarningsStream(state) << "Unable to generate a solution for the flag\n";
        exit(1);
    }

    // Since we only have a single symbolic variable, we will only have a single result. We then iterate over the
    // bytes in this result to print the solution
    std::stringstream ss;
    for (auto c : results[results.size()-1].second) {
        ss << "(" << (int)c << ")";
    }

    getInfoStream(state) << "Flag = " << ss.str() << "\n";

    // No need to continue running S2E - terminate
    exit(0);
}

void AngrCTFLicense::onFailure(S2EExecutionState *state, uint64_t pc) {
    // Ensure that the unbreakable process is executing
    if (!m_procDetector->isTracked(state)) {
        return;
    }

    // There is no reason to continue execution any further. So kill the state
    s2e()->getExecutor()->terminateState(*state, "Invalid path");
}

} // namespace plugins
} // namespace s2e
