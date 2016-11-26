#pragma once
#include <Dot++/TokenizerStateInterface.hpp>

namespace dot_pp {
    enum class TokenizerState;
    class Token;
}

namespace dot_pp {
    
    class MultiLineCommentState : public TokenizerStateInterface
    {
    public:
        TokenizerState consume(const char c, Token& token, std::deque<Token>& tokens) const override;
    };
}
