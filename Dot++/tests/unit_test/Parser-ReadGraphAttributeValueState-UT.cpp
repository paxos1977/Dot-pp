#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Exceptions.hpp>
#include <Dot++/NullConstructionPolicy.hpp>

#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/states/ReadGraphAttributeValueState.hpp>

#include <string>
#include <utility>

namespace {
    
    using namespace dot_pp::lexer;
    using namespace dot_pp::parser;
    
    struct ReadGraphAttributeValueStateFixture
    {
        TokenStack attributes;
        TokenStack stack;
        
        dot_pp::NullConstructionPolicy constructor;
        states::ReadGraphAttributeValueState<dot_pp::NullConstructionPolicy> state;
    };
    
    TEST_FIXTURE(ReadGraphAttributeValueStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(ReadGraphAttributeValueStateFixture, verifyTransitionsToGraphAttributeValueOnString)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token(";", TokenType::end_statement), FileInfo("test.dot"));
        
        auto handle = tokens.cbegin();
        
        CHECK_EQUAL(ParserState::BeginGraph, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(0U, stack.size());
    }
    
    TEST_FIXTURE(ReadGraphAttributeValueStateFixture, verifyThrowsOnInvalidTokens)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("keyword", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("string", TokenType::string), FileInfo("test.dot"));
        tokens.emplace_back(Token("string_lit", TokenType::string_literal), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("directed_edge", TokenType::directed_edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_paren", TokenType::l_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_paren", TokenType::r_paren), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_bracket", TokenType::l_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_bracket", TokenType::r_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah blah", TokenType::comment), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah \n blah", TokenType::multiline_comment), FileInfo("test.dot"));
        
        for(auto handle = tokens.cbegin(), end = tokens.cend(); handle != end; ++handle)
        {
            CHECK_THROW(state.consume(handle, stack, attributes, constructor), dot_pp::SyntaxError);
        }
    }
}
