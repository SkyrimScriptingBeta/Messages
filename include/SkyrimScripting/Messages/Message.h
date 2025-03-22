#pragma once

#include "CallbackID.h"

namespace SkyrimScripting::Messages {

    /*
     * Pure virtual interface to represent a message.
     */
    struct Message {
        virtual ~Message() = default;

        virtual const char* sender() const      = 0;
        virtual const char* text() const        = 0;
        virtual void*       data() const        = 0;
        virtual bool        is_response() const = 0;
        virtual bool        is_request() const  = 0;
        virtual CallbackID  reply_id() const    = 0;

        virtual void set_sender(const char* sender)     = 0;
        virtual void set_text(const char* text)         = 0;
        virtual void set_data(void* data)               = 0;
        virtual void set_is_response(bool value = true) = 0;
        virtual void set_is_request(bool value = true)  = 0;
        virtual void set_reply_id(CallbackID id)        = 0;
    };
}
