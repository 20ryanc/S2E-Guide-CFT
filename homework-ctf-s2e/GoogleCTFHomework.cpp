#include <s2e/S2E.h>

#include <s2e/Plugins/OSMonitors/Support/ProcessExecutionDetector.h>

#include <klee/util/ExprTemplates.h>

#include <cctype>
#include <sstream>

#include "GoogleCTFHomework.h"

static const uint64_t SUCCESS_ADDRESS = 0x400724;

namespace s2e {
namespace plugins {

S2E_DEFINE_PLUGIN(GoogleCTFHomework,
                  "Solution for a homework challenge from the Google CTF 2016", "",
                  "ProcessExecutionDetector");

void GoogleCTFHomework::initialize() {
    // We need to use the ProcessExecutionDetector plugin to filter out all processes other than the "homework"
    // process
    m_procDetector = s2e()->getPlugin<ProcessExecutionDetector>();
}

void GoogleCTFHomework::onTranslateInstruction(ExecutionSignal *signal, S2EExecutionState *state,
                                                  TranslationBlock *tb, uint64_t pc) {
    if (pc == SUCCESS_ADDRESS) {
        signal->connect(sigc::mem_fun(*this, &GoogleCTFHomework::onSuccess));
    }
}

void GoogleCTFHomework::onSuccess(S2EExecutionState *state, uint64_t pc) {
    // Ensure that the unbreakable process is executing
    if (!m_procDetector->isTracked(state)) {
        return;
    }

    // `results` is a vector containing pairs of strings and a vector of bytes. The string corresponds to the symbolic
    // variable's name while the vector of bytes is the actual solution
    std::vector<std::pair<std::string, std::vector<unsigned char>>> results;

    // Invoke the constraint solver
    if (!state->getSymbolicSolution(results)) {
        getWarningsStream(state) << "Unable to generate a solution for the product activation code\n";
        exit(1);
    }

    // Since we only have a single symbolic variable, we will only have a single result. We then iterate over the
    // bytes in this result to print the solution
    std::stringstream ss;
    for (auto c : results[0].second) {
        if (!std::isprint(c)) {
            break;
        }
        ss << (char) c;
    }

    getInfoStream(state) << "Code = " << ss.str() << "\n";

    // No need to continue running S2E - terminate
    exit(0);
}
} // namespace plugins
} // namespace s2e
