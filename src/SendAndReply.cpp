#include "SkyrimScripting/Messages/MakeMessage.h"
#include "SkyrimScripting/Messages/MessageType.h"
#include "SkyrimScripting/Messages/Reply.h"
#include "SkyrimScripting/Messages/Send.h"

namespace SkyrimScripting::Messages {

    void Reply(std::string_view recipient, CallbackID replyID, void* data) {
        auto message = make_response_message(data, replyID);
        Send(recipient, std::move(message));
    }

    void Send(std::string_view recipient, std::unique_ptr<Message> message) {
        SKSE::GetMessagingInterface()->Dispatch(
            SKYRIM_SCRIPTING_MESSAGE_TYPE, (void*)message.get(), sizeof(void*), recipient.data()
        );
    }

    void Send(std::unique_ptr<Message> message) {
        SKSE::GetMessagingInterface()->Dispatch(
            SKYRIM_SCRIPTING_MESSAGE_TYPE, (void*)message.get(), sizeof(void*), nullptr
        );
    }

    void Send(
        std::string_view recipient, std::string_view text, void* data, bool is_response,
        bool is_request, CallbackID replyId
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
