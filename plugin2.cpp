// #include <SkyrimScripting/Entrypoint.h>
// #include <SkyrimScripting/Logging.h>
// #include <SkyrimScripting/Messages.h>

// _OnMessage_(SkyrimScripting::Messages::Message* message) {
//     PrintToConsole("Received message from sender [{}]: '{}'", message->sender(),
//     message->text());
// }

// _SKSEPlugin_Init_ {
//     SKSE::log::info("INIT: Plugin2");

//     SKSE::GetMessagingInterface()->RegisterListener(
//         nullptr,
//         [](SKSE::MessagingInterface::Message* a_msg) {
//             SKSE::log::info("Received message from sender [{}]", a_msg->sender);
//             SkyrimScripting::Messages::HandleMessage(a_msg->sender, a_msg);
//             if (a_msg->type == SKSE::MessagingInterface::kDataLoaded) {
//                 if (auto* consoleLog = RE::ConsoleLog::GetSingleton()) {
//                     PrintToConsole("LOADED: Plugin2");

//                     auto targetPluginName = "Test plugin for SkyrimScripting.Messages-1";
//                     SkyrimScripting::Messages::Send(targetPluginName, "Hello from Plugin2!");
//                 }
//             }
//         }
//     );

//     SKSE::GetMessagingInterface()->RegisterListener(
//         "SKSE",
//         [](SKSE::MessagingInterface::Message* a_msg) {
//             SKSE::log::info("Received message from sender [{}]", a_msg->sender);
//             SkyrimScripting::Messages::HandleMessage(a_msg->sender, a_msg);
//             if (a_msg->type == SKSE::MessagingInterface::kDataLoaded) {
//                 if (auto* consoleLog = RE::ConsoleLog::GetSingleton()) {
//                     PrintToConsole("LOADED: Plugin2");

//                     auto targetPluginName = "Test plugin for SkyrimScripting.Messages-1";
//                     SkyrimScripting::Messages::Send(targetPluginName, "Hello from Plugin2!");
//                 }
//             }
//         }
//     );
// }

#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>

extern "C" __declspec(dllexport) bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse) {
    SKSE::Init(a_skse);
    SKSE::log::info("THIS IS info LOG!");
    return true;
}