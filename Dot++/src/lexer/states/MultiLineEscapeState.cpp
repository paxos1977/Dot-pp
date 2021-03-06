#include <Dot++/lexer/states/MultiLineEscapeState.hpp>

#include <Dot++/lexer/Token.hpp>
#include <Dot++/lexer/TokenizerState.hpp>

#include "./ProduceToken.hpp"

namespace dot_pp { namespace lexer { namespace states {
    
    TokenizerState MultiLineEscapeState::consume(const char c, FileInfo&, Token& token, std::deque<TokenInfo>&) const
    {
        if(c == '\n')
        {
            token.append(c);
            token.type(TokenType::multiline_comment);
            
            return TokenizerState::SlashLineComment;
        }
        
        return TokenizerState::Error;
    }
}}}
