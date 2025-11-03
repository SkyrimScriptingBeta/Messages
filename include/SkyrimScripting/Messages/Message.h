#pragma once

#include <algorithm>
#include <cctype>
#include <string_view>

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

        inline bool sender_equals(std::string_view name, bool match_case = false) const {
            std::string_view sender_view(sender());
            if (match_case) return sender_view == name;
            return std::equal(
                sender_view.begin(), sender_view.end(), name.begin(), name.end(),
                [](char a, char b) {
                    return std::tolower(static_cast<unsigned char>(a)) ==
                           std::tolower(static_cast<unsigned char>(b));
                }
            );
        }

        inline bool text_equals(std::string_view msg_text, bool match_case = false) const {
            std::string_view text_view(text());
            if (match_case) return text_view == msg_text;
            return std::equal(
                text_view.begin(), text_view.end(), msg_text.begin(), msg_text.end(),
                [](char a, char b) {
                    return std::tolower(static_cast<unsigned char>(a)) ==
                           std::tolower(static_cast<unsigned char>(b));
                }
            );
        }
    };
}
