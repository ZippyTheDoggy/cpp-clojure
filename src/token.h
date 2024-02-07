#pragma once

#include "./include.h"

void print_token(Token token, int tabs = 0, int indent_start = false) {
    if(indent_start) for(int i = 0; i < tabs; i++) std::cout << "\t";
    std::cout << "{\n";
    for(int i = 0; i < tabs; i++) std::cout << "\t";
    std::cout << "\ttype: \"" << token_type_string(token.type) << "\"\n";
    for(int i = 0; i < tabs; i++) std::cout << "\t";
    std::cout << "\tvalue: \"" << token.value << "\",\n";
    for(int i = 0; i < tabs; i++) std::cout << "\t";
    std::cout << "\tblock: ";
    if(token.block != nullptr) {
        std::cout << "{\n";
        for(int i = 0; i < tabs; i++) std::cout << "\t";
        std::cout << "\t\tchildren: ";
        for(size_t i = 0; i < token.block->children.size(); i++) {
            print_token(*token.block->children[i], tabs + 2, i > 0);
        }
        std::cout << "\t}," << std::endl;
    } else {
        std::cout << "nullptr\n";
        for(int i = 0; i < tabs; i++) std::cout << "\t";
        std::cout << "}," << std::endl;
    }
    if(tabs != 0) return;
    for(int i = 0; i < tabs; i++) std::cout << "\t";
    std::cout << "};\n";
};
void print_token(Token* token) {
    print_token(*token);
};

Token* make_token(TokenType tt, std::string value, Block* block = nullptr) {
    Token* tok = new Token {
        .type = tt, .value = value,
        .block = block
    };
    return tok;
};