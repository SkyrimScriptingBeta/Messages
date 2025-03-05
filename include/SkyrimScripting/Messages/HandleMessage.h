#pragma once

#include "MessagesController.h"

namespace SkyrimScripting::Messages {

    inline void HandleMessage(const char* sender, SKSE::MessagingInterface::Message* message) {
        MessagesController::GetSingleton().HandleIncomingMessage(sender, message);
    }
}
