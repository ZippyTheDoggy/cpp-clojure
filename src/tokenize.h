#pragma once

#include "./include.h"

std::vector<Token*> tokenize(std::string code, Logger* logger) {
    std::vector<Block*> scope = { // our global scope
        new Block {}
    };
    int current_scope = 0; // the global scope
    StringReader sr(code);
    std::string buf = "";
    while(!sr.eos()) {
        char c = sr.at();
        if(sr.last() == '\n') {
            // new line;
            continue;
        }
        if(is::enter_block(c)) {
            scope.push_back(new Block {});
            current_scope++; // increment the currnet scope
        } else if(is::leave_block(c)) {
            current_scope--;  // decrease the scope
            // and append to that second to last scope, the last scope that was just exited out of
            scope[current_scope]->children.push_back(make_token(
                TokenType::BLOCK, "", scope[current_scope + 1]
            ));
            scope.pop_back(); // and then remove the last scope from the scope;
            // note it's still in memory, just as a child of the now-last scope.
        } else if(is::number(c)) {
            buf += sr.at(); // add the current character (starting number) to the buffer
            // append the next character only if it's a number.
            while(is::number(sr.seek())) buf += sr.next();
            // since we end when it's not a number, there's no need to decrement position
            scope[current_scope]->children.push_back(make_token(
                TokenType::NUMBER, buf
            ));
            buf = "";
        } else if(is::math_operator(c)) {
            buf += sr.at();
            while(is::math_operator(sr.seek())) buf += sr.next();
            scope[current_scope]->children.push_back(make_token(
                TokenType::OPERATOR, buf
            ));
            buf = "";
        }
        sr.next();
    }
    if(current_scope > 0) {
        logger->Log(LogType::Critical, "A block scope has not been exited.");
    }
    return scope[0]->children;
};