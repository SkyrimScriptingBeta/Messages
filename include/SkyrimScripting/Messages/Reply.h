#pragma once

#include <SKSE/SKSE.h>

#include <string_view>

#include "CallbackID.h"
#include "MakeMessage.h"
#include "Send.h"

namespace SkyrimScripting::Messages {

    inline void Reply(std::string_view recipient, CallbackID replyID, void* data = nullptr) {
        auto message = make_response_message(data, replyID);
        Send(recipient, std::move(message));
    }

    template <typename T>
    inline void Reply(std::string_view recipient, CallbackID replyID, T data) {
        Reply(recipient, replyID, (void*)data);
    }

    template <typename T>
    inline void Reply(Message* message, T data) {
        Reply(message->GetSender(), message->GetReplyID(), (void*)data);
    }
}
