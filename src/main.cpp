#include "./include.h"

enum ExpType {
    // Definition,
    // FunctionCall, etc.
    Mathematical,
};

enum OpType {
    Unknown,
    Addition,
    Subtraction,
    Multiplication,
    Division
};

OpType op_from_value(std::string val) {
    if(val == "+") return OpType::Addition;
    if(val == "-") return OpType::Subtraction;
    if(val == "*") return OpType::Multiplication;
    if(val == "/") return OpType::Division;
    return OpType::Unknown;
};

struct Expression {
    ExpType type;
    OpType operatorType;
    std::vector<Token*> parameters;
};

std::vector<Expression> restructure(std::vector<Token*> tokens, Logger* logger) {
    if(tokens.size() < 1) {
        logger->Log(LogType::Error, "Compiler unable to complete token restructuring: no tokens found.");
        return {};
    }
    std::vector<Expression> expressions;
    Token* token = tokens[0];

    auto copy_all = [&token](TokenType type) {
        std::vector<Token*> tokens;
        while(token != nullptr) {
            if(token->type == type) tokens.push_back(token);
            token++;
        }
        token -= tokens.size() + 1;
        return tokens;
    };

    while(token != nullptr) {
        switch(token->type) {
            case TokenType::OPERATOR: {
                std::vector<Token*> parameters = copy_all(TokenType::NUMBER);
                if(parameters.size() < 2) {
                    logger->Log(LogType::Error, "Operator expecting at least 2 parameters.");
                    token += parameters.size() - 1;
                } else {
                    expressions.push_back({
                        .type = ExpType::Mathematical, 
                        .operatorType = OpType::Addition,
                        .parameters = parameters
                    });
                    token += parameters.size() - 1;
                }
            } break;
        }
        token++;
    }
    return expressions;
}

int main() {
    
    Logger logger;
    std::string code = "(+ 1 2";
    std::vector<Token*> tokens = tokenize(code, &logger);
    if(logger.any(LogType::ALL)) logger.PrintMessages(LogType::ALL);
    if(logger.any(LogType::Error) || logger.any(LogType::Critical)) return EXIT_FAILURE;

    for(size_t i = 0; i < tokens.size(); i++) print_token(tokens[i]);

    // logger.clear();
    // std::vector<Expression> expressions = restructure(tokens, &logger);
    // if(logger.any(LogType::ALL)) logger.PrintMessages(LogType::ALL);
    // if(logger.any(LogType::Error) || logger.any(LogType::Critical)) return EXIT_FAILURE;

    // TODO:
    /*
        1: Make a parser
            - Take the token input, turn it into operations.  Mathematical, function calls, variable/function definitions, etc.
        2: Interpret the parsed tokens.
            - If mathematical, take the parameters and apply the operation to it.
            - If function call, call the function with parameters and set the value of the function call as the result.
            - If a definition, set a global variable to its value (def 5 x?)
                ! - Remember functions assume local scope if parameter and global variable are both defined.
    */

    return EXIT_SUCCESS;
}