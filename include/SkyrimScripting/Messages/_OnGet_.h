#pragma once

#include <global_macro_functions.h>

#include "Message.h"             // IWYU pragma: export
#include "MessagesController.h"  // IWYU pragma: export

#define __SkyrimScriptingMessages_OnGet_Body(symbol, messageText, count)                           \
    inline void* _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)();      \
    namespace {                                                                                    \
        _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME_FROM_COUNT(symbol, count){ \
            []() {                                                                                 \
                SkyrimScripting::Messages::MessagesController::GetSingleton().RegisterGetHandler(  \
                    messageText,                                                                   \
                    &_GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)     \
                );                                                                                 \
            }                                                                                      \
        };                                                                                         \
    }                                                                                              \
    inline void* _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_NAME_FROM_COUNT(symbol, count)()

#define _OnGet_(symbol, messageText) \
    __SkyrimScriptingMessages_OnGet_Body(symbol, messageText, __COUNTER__)
