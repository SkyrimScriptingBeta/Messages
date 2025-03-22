#pragma once

#include <SKSE/SKSE.h>

#include <string_view>

#include "CallbackID.h"
#include "Message.h"

namespace SkyrimScripting::Messages {

    void Reply(std::string_view recipient, CallbackID replyID, void* data = nullptr);

    template <typename T>
    inline void Reply(std::string_view recipient, CallbackID replyID, T data) {
        Reply(recipient, replyID, (void*)data);
    }

    template <typename T>
    inline void Reply(Message* message, T data) {
        Reply(message->sender(), message->reply_id(), (void*)data);
    }
}
