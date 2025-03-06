#include <SkyrimScripting/Entrypoint.h>
#include <SkyrimScripting/Logging.h>
#include <SkyrimScripting/Messages.h>

_OnMessage_(SkyrimScripting::Messages::Message* message) {
    PrintToConsole("Received message from sender [{}]: '{}'", message->sender(), message->text());
}

_SKSEPlugin_Init_ {
    _Log_("INIT: Plugin1");

    SKSE::GetMessagingInterface()->RegisterListener(
        nullptr,
        [](SKSE::MessagingInterface::Message* a_msg) {
            _Log_("Received message from sender [{}]", a_msg->sender);
            SkyrimScripting::Messages::HandleMessage(a_msg->sender, a_msg);
            if (a_msg->type == SKSE::MessagingInterface::kDataLoaded) {
                if (auto* consoleLog = RE::ConsoleLog::GetSingleton()) {
                    PrintToConsole("LOADED: Plugin1");
                }
            }
        }
    );
}
