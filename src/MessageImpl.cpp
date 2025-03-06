#include "SkyrimScripting/Messages/MessageImpl.h"

#include "SkyrimScripting/Messages/MakeMessage.h"

namespace SkyrimScripting::Messages {
    const char* MessageImpl::sender() const { return _sender.c_str(); }
    const char* MessageImpl::text() const { return _text.c_str(); }
    void*       MessageImpl::data() const { return _data; }
    bool        MessageImpl::is_response() const { return _is_response; }
    bool        MessageImpl::is_request() const { return _is_request; }
    CallbackID  MessageImpl::reply_id() const { return _replyId; }
    void        MessageImpl::set_sender(const char* sender) { _sender = sender; }
    void        MessageImpl::set_text(const char* text) { _text = text; }
    void        MessageImpl::set_data(void* data) { _data = data; }
    void        MessageImpl::set_is_response(bool value) { _is_response = value; }
    void        MessageImpl::set_is_request(bool value) { _is_request = value; }
    void        MessageImpl::set_reply_id(CallbackID id) { _replyId = id; }

    std::unique_ptr<Message> make_message() { return std::make_unique<MessageImpl>(); }

    std::unique_ptr<Message> make_request_message() {
        auto message = make_message();
        message->set_is_request();
        return message;
    }

    std::unique_ptr<Message> make_response_message(void* data, CallbackID replyID) {
        auto message = make_message();
        message->set_is_response();
        message->set_data(data);
        message->set_reply_id(replyID);
        return message;
    }
}
