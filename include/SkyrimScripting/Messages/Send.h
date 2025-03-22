#pragma once

#include <SKSE/SKSE.h>

#include <memory>
#include <string_view>

#include "Message.h"

namespace SkyrimScripting::Messages {

    void Send(std::string_view recipient, std::unique_ptr<Message> message);
    void Send(std::unique_ptr<Message> message);
    void Send(
        std::string_view recipient, std::string_view text = "", void* data = nullptr,
        bool is_response = false, bool is_request = false, CallbackID replyId = 0
    );
}
