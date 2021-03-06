#pragma once
#include <Dot++/parser/TokenInfoHandle.hpp>
#include <Dot++/parser/TokenStack.hpp>
#include <Dot++/parser/ParserState.hpp>

namespace dot_pp { namespace parser {

    template<class ConstructionPolicy>
    class ParserStateInterface
    {
    public:
        virtual ~ParserStateInterface(){}
        virtual ParserState consume(const TokenInfoHandle& token, TokenStack& stack, TokenStack& attributes, ConstructionPolicy& constructor) = 0;
    };
}}
