#pragma once

#include <SKSE/SKSE.h>

#include <string_view>

#include "CallbackID.h"
#include "MakeMessage.h"
#include "MessageType.h"

namespace SkyrimScripting::Messages {

    inline void Send(std::string_view recipient, std::unique_ptr<Message> message) {
        SKSE::GetMessagingInterface()->Dispatch(
            SKYRIM_SCRIPTING_MESSAGE_TYPE, (void*)message.get(), sizeof(void*), recipient.data()
        );
    }

    inline void Send(
        std::string_view recipient, std::string_view text = "", void* data = nullptr,
        bool is_response = false, bool is_request = false, CallbackID replyId = 0
    ) {
        auto message = make_message();
        message->set_text(text.data());
        message->set_data(data);
        message->set_is_response(is_response);
        message->set_is_request(is_request);
        message->set_reply_id(replyId);
        Send(recipient, std::move(message));
    }
}
