#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>
#include <SkyrimScripting/Messages.h>

const auto THIS_PLUGIN_NAME  = "Test plugin 2 for SkyrimScripting.Messages";
const auto OTHER_PLUGIN_NAME = "Test plugin 1 for SkyrimScripting.Messages";

void on_all_plugins_loaded() {
    // Send a message to the other plugin
    SkyrimScripting::Messages::Send(OTHER_PLUGIN_NAME, "Hello from Plugin 2!");
}

OnMessage(SkyrimScripting::Messages::Message* message) {
    SKSE::log::info("Received message from '{}': '{}'", message->sender(), message->text());
}

extern "C" __declspec(dllexport) bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse) {
    SKSE::Init(a_skse);
    // Listen for SKSE event messages
    SKSE::GetMessagingInterface()->RegisterListener(
        "SKSE",
        [](SKSE::MessagingInterface::Message* a_msg) {
            if (a_msg->type == SKSE::MessagingInterface::kPostLoad) on_all_plugins_loaded();
        }
    );
    // Listen for messages from ALL SKSE plugins
    // (limited to just SkyrimScripting.Messages messages)
    SKSE::GetMessagingInterface()->RegisterListener(
        nullptr,
        [](SKSE::MessagingInterface::Message* message) {
            SkyrimScripting::Messages::MessagesController::GetSingleton().HandleIncomingMessage(
                message
            );
        }
    );
    return true;
}