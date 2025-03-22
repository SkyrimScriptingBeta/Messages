#pragma once

#include <memory>

#include "CallbackID.h"
#include "Message.h"

namespace SkyrimScripting::Messages {

    // TODO: if these won't be used frequently, don't put these up in the top-level namespace

    std::unique_ptr<Message> make_message();
    std::unique_ptr<Message> make_request_message();
    std::unique_ptr<Message> make_response_message(void* data = nullptr, CallbackID replyID = 0);
}
