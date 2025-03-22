#pragma once

#include <SKSE/SKSE.h>

namespace SkyrimScripting::Messages {
    void HandleMessage(const char* sender, SKSE::MessagingInterface::Message* message);
}
