#pragma once

#include "./include.h"

struct Token;
struct Block;

enum TokenType {
    BLOCK, // enter block, leave block; LPAREN & EPAREN
    KEYWORD,
    NUMBER,
    OPERATOR
};
std::vector<std::string> KEYWORD_LIST = {
    "CALL"
};
std::string token_type_string(TokenType tt) {
    switch(tt) {
        case TokenType::BLOCK: return "BLOCK";
        case TokenType::KEYWORD: return "KEYWORD";
        case TokenType::NUMBER: return "NUMBER";
        case TokenType::OPERATOR: return "OPERATOR";
    }
    return "UNKNOWN";
};
struct Token {
    TokenType type;
    std::string value;
    Block* block = nullptr;
};
struct Block {
    std::vector<Token*> children;
};