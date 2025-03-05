#pragma once

#include <functional>
#include <memory>

#include "CallbackID.h"
#include "Message.h"

namespace SkyrimScripting::Messages {

    struct OutboundRequestMessage {
        CallbackID                    replyId;
        std::unique_ptr<Message>      message;
        std::function<void(Message*)> receiptCallback;
    };
}
