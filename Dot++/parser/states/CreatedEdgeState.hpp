#pragma once
#include <Dot++/parser/ParserStateInterface.hpp>

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenType.hpp>

namespace dot_pp { namespace parser { namespace states {

    template<class ConstructionPolicy>
    class CreatedEdgeState : public ParserStateInterface<ConstructionPolicy>
    {
    public:
        ParserState consume(const TokenInfoHandle& handle, TokenStack& stack, ConstructionPolicy&) override
        {
            const auto& token = handle->token();
            
            if((token.type() == lexer::TokenType::edge) || (token.type() == lexer::TokenType::directed_edge))
            {
                return ParserState::ReadEdgeToken;
            }
            
            if(token.type() == lexer::TokenType::end_statement)
            {
                clear(stack);                
                return ParserState::BeginGraph;
            }
            
            if(token.type() == lexer::TokenType::l_bracket)
            {
                stack.pop();
                return ParserState::ReadLeftBracket;
            }
            
            throw dot_pp::SyntaxError("Unexpected token encountered, expected '--', '->', '[', or ';', found '" + token.to_string() + "'", *handle);
        }
    };
}}}