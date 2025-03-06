#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>
#include <SkyrimScripting/Logging.h>
#include <SkyrimScripting/Messages.h>
#include <_Log_.h>

_OnMessage_(SkyrimScripting::Messages::Message* message) {
    _Log_("Received message from sender [{}]: '{}'", message->GetSender(), message->GetText());
}

extern "C" __declspec(dllexport) bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse) {
    SKSE::Init(a_skse);

    SKSE::GetMessagingInterface()->RegisterListener(
        "SKSE",
        [](SKSE::MessagingInterface::Message* a_msg) {
            if (a_msg->type == SKSE::MessagingInterface::kDataLoaded) {
                if (auto* consoleLog = RE::ConsoleLog::GetSingleton()) {
                    consoleLog->Print("Hello, from 'Messages'");
                    // SkyrimScripting::Me
                }
            }
        }
    );

    return true;
}