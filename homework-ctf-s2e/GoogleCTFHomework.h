#ifndef S2E_PLUGINS_GOOGLE_CTF_HOMEWORK_H
#define S2E_PLUGINS_GOOGLE_CTF_HOMEWORK_H

#include <s2e/CorePlugin.h>
#include <s2e/Plugin.h>
#include <s2e/S2E.h>

namespace s2e {
namespace plugins {

class ProcessExecutionDetector;

class GoogleCTFHomework : public Plugin {
    S2E_PLUGIN

public:
    GoogleCTFHomework(S2E *s2e) : Plugin(s2e) {
    }

    void initialize();

private:
    ProcessExecutionDetector *m_procDetector;
    void onTranslateInstruction(ExecutionSignal *signal, S2EExecutionState *state, TranslationBlock *tb, uint64_t pc);
    void onSuccess(S2EExecutionState *state, uint64_t pc);
    void onFailure(S2EExecutionState *state, uint64_t pc);
};

} // namespace plugins
} // namespace s2e

#endif
