#pragma once

#include "./include.h"

class StringReader {
    private:
        std::string full_str;
        size_t lines, cols, pos = 0;
    public:
        StringReader(std::string s) {
            full_str = s;
            if(!full_str.at(full_str.length() - 1) == '\0') full_str.push_back('\0');
        };
        char at() {
            return full_str.at(pos);
        };
        char seek() {
            if(pos + 1 <= full_str.length()) return full_str.at(pos + 1);
            return 0;
        }
        char last() {
            if(pos > 0) return full_str.at(pos - 1);
            return 0;
        }
        char next() {
            if(pos == full_str.length()) return 0;
            if(eol()) {
                lines++;
                cols = 1;
                pos++;
                return at();
            } else {
                pos++;
                cols++;
                return at();
            }
        }
        bool eol() {
            return at() == '\n';
        }
        bool eos() {
            return at() == '\0';
        }
};