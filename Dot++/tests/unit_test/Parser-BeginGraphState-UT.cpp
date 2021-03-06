#include "./platform/UnitTestSupport.hpp"

#include <Dot++/Exceptions.hpp>
#include <Dot++/lexer/TokenInfo.hpp>
#include <Dot++/parser/states/BeginGraphState.hpp>

namespace {
    
    using namespace dot_pp::lexer;
    using namespace dot_pp::parser;

    struct NullConstructionPolicy
    {
        NullConstructionPolicy()
            : finalized(false)
        {
        }
        
        void createGraph(const std::string&) {}
        void createDigraph(const std::string&) {}
        
        void createVertex(const std::string&) {}
        void createEdge(const std::string&, const std::string&){}
        
        void applyGraphAttribute(const std::string&, const std::string&){}
        void applyVertexAttribute(const std::string&, const std::string&, const std::string&) {}
        
        void applyEdgeAttribute(const std::string&, const std::string&, const std::string&, const std::string&) {}
        void finalize() { finalized = true; }
        
        bool finalized;
    };
    
    struct BeginGraphStateFixture
    {
        TokenStack attributes;
        TokenStack stack;
        
        NullConstructionPolicy constructor;
        states::BeginGraphState<NullConstructionPolicy> state;
    };
    
    TEST_FIXTURE(BeginGraphStateFixture, verifyInstatiation)
    {
    }
    
    TEST_FIXTURE(BeginGraphStateFixture, verifyTransitionsToReadStringToken)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("a", TokenType::string), FileInfo("test.dot"));

        auto handle = tokens.cbegin();
        
        CHECK_EQUAL(ParserState::ReadStringToken, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(1U, stack.size());
    }

    TEST_FIXTURE(BeginGraphStateFixture, verifyTransitionsToIgnoreSubgraphs)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("{", TokenType::l_paren), FileInfo("test.dot"));

        auto handle = tokens.cbegin();
        
        CHECK_EQUAL(ParserState::IgnoreSubgraphs, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(0U, stack.size());
    }

    TEST_FIXTURE(BeginGraphStateFixture, verifyTransitionsToInit)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("}", TokenType::r_paren), FileInfo("test.dot"));

        auto handle = tokens.cbegin();
        
        CHECK_EQUAL(ParserState::Init, state.consume(handle++, stack, attributes, constructor));
        CHECK_EQUAL(0U, stack.size());
        CHECK(constructor.finalized);
    }
    
    TEST_FIXTURE(BeginGraphStateFixture, verifySyntaxErrorOnOtherTokenTypes)
    {
        std::deque<TokenInfo> tokens;
        tokens.emplace_back(Token("keyword", TokenType::keyword), FileInfo("test.dot"));
        tokens.emplace_back(Token("string_lit", TokenType::string_literal), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("edge", TokenType::directed_edge), FileInfo("test.dot"));
        tokens.emplace_back(Token("l_bracket", TokenType::l_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("r_bracket", TokenType::r_bracket), FileInfo("test.dot"));
        tokens.emplace_back(Token("equal", TokenType::equal), FileInfo("test.dot"));
        tokens.emplace_back(Token("end_statement", TokenType::end_statement), FileInfo("test.dot"));
        tokens.emplace_back(Token("string_lit", TokenType::string_literal), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah blah", TokenType::comment), FileInfo("test.dot"));
        tokens.emplace_back(Token("blah \n blah", TokenType::multiline_comment), FileInfo("test.dot"));
        
        for(auto handle = tokens.cbegin(), end = tokens.cend(); handle != end; ++handle)
        {
            CHECK_THROW(state.consume(handle, stack, attributes, constructor), dot_pp::SyntaxError);
        }
    }
}
