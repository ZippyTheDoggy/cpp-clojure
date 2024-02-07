#pragma once

#include "./include.h"

namespace is {
    bool enter_block(char c) {
        return c == '(';
    };
    bool leave_block(char c) {
        return c == ')';
    };

    bool number(char c) {
        return c >= '0' && c <= '9';
    };
    bool letter(char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
    };
    bool alphanum(char c) {
        return number(c) || letter(c);
    };

    bool math_operator(char c) {
        return (c == '+') || (c == '-') || (c == '/') || (c == '*');
    };
};