#pragma once 
#include <Dot++/TokenizerStateInterface.hpp>
#include <deque>

namespace dot_pp {
    enum class TokenizerState;
    class Token;
}

namespace dot_pp { namespace states {
    
    class HashLineCommentState : public TokenizerStateInterface
    {
    public:
        TokenizerState consume(const char c, Token& token, std::deque<Token>& tokens) const override;
    };
}}
