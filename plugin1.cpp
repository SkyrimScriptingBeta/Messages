#include <RE/Skyrim.h>
#include <SKSE/SKSE.h>
#include <SkyrimScripting/Messages.h>

#include "shared_header.h"

const auto THIS_PLUGIN_NAME  = "Test plugin 1 for SkyrimScripting.Messages";
const auto OTHER_PLUGIN_NAME = "Test plugin 2 for SkyrimScripting.Messages";

SomeStruct plugin1Struct = {69, "Sixty-nine"};

void on_all_plugins_loaded() {
    // Send a message to the other plugin
    SkyrimScripting::Messages::Send(OTHER_PLUGIN_NAME, "Hello from Plugin 1!");

    // This get is async
    SkyrimScripting::Messages::GetAsync<SomeStruct*>(
        OTHER_PLUGIN_NAME, "GimmeYourStruct",
        [](SomeStruct* structPtr) {
            if (structPtr != nullptr) {
                SKSE::log::info(
                    "(async) Received struct from Plugin 2: a={}, b='{}'", structPtr->a,
                    structPtr->b
                );
            } else {
                SKSE::log::info("(async) Failed to receive struct from Plugin 2");
            }
        }
    );
}

OnMessage(SkyrimScripting::Messages::Message* message) {
    SKSE::log::info("Received message from '{}': '{}'", message->sender(), message->text());
    if (message->is_request() && strcmp(message->text(), "GimmeYourStruct") == 0) {
        SkyrimScripting::Messages::Reply(message, &plugin1Struct);
    }
}

extern "C" __declspec(dllexport) bool SKSEPlugin_Load(const SKSE::LoadInterface* a_skse) {
    SKSE::Init(a_skse);

    spdlog::default_logger()->set_level(spdlog::level::trace);

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
