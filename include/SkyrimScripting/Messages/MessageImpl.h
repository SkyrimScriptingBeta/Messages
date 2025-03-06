#pragma once

#include <string>

#include "Message.h"

namespace SkyrimScripting::Messages {

    class MessageImpl : public Message {
        std::string _sender      = "";
        std::string _text        = "";
        void*       _data        = nullptr;
        bool        _is_response = false;
        bool        _is_request  = false;
        CallbackID  _replyId     = 0;

    public:
        const char* sender() const override;
        const char* text() const override;
        void*       data() const override;
        bool        is_response() const override;
        bool        is_request() const override;
        CallbackID  reply_id() const override;

        void set_sender(const char* sender) override;
        void set_text(const char* text) override;
        void set_data(void* data) override;
        void set_is_response(bool value = true) override;
        void set_is_request(bool value = true) override;
        void set_reply_id(CallbackID id) override;
    };

}
