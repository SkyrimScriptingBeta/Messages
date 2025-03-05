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
        bool isResponse = false, bool isRequest = false, CallbackID replyId = 0
    ) {
        auto message = make_message();
        message->SetText(text.data());
        message->SetData(data);
        message->SetIsResponse(isResponse);
        message->SetIsRequest(isRequest);
        message->SetReplyID(replyId);
        Send(recipient, std::move(message));
    }
}
