#pragma once 
#include <deque>

namespace dot_pp { namespace lexer {
    class FileInfo;
    class Token;
    class TokenInfo;
    enum class TokenizerState;
}}

namespace dot_pp { namespace lexer {
    
    class TokenizerStateInterface
    {
    public:
        virtual ~TokenizerStateInterface() {}
        virtual TokenizerState consume(const char c, FileInfo& position, Token& token, std::deque<TokenInfo>& tokens) const = 0;
    };
}}
