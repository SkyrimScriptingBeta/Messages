#pragma once

#include <memory>

#include "CallbackID.h"
#include "Message.h"

namespace SkyrimScripting::Messages {
    std::unique_ptr<Message> make_message();
    std::unique_ptr<Message> make_request_message();
    std::unique_ptr<Message> make_response_message(void* data = nullptr, CallbackID replyID = 0);
}
