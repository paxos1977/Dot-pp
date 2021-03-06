#include "./platform/UnitTestSupport.hpp"
#include <Dot++/SerializationPolicy.hpp>

namespace {
    
    struct SerializationFixture
    {
        SerializationFixture()
            : archive(output)
        {
        }
        
        std::stringstream output;
        dot_pp::SerializationPolicy archive;
    };
    
    TEST_FIXTURE(SerializationFixture, verifyInstantiation)
    {
    }
    
    TEST_FIXTURE(SerializationFixture, verifyGraphCreation)
    {
        archive.createGraph("test");
        archive.finalize();
        
        const std::string expected = "graph test {\n}\n";
        CHECK_EQUAL(expected, output.str());
    }

    TEST_FIXTURE(SerializationFixture, verifyGraphCreationWithoutAName)
    {
        archive.createGraph();
        archive.finalize();
        
        const std::string expected = "graph {\n}\n";
        CHECK_EQUAL(expected, output.str());
    }
    
    TEST_FIXTURE(SerializationFixture, verifyDigraphCreation)
    {
        archive.createDigraph("test");
        archive.finalize();
        
        const std::string expected = "digraph test {\n}\n";
        CHECK_EQUAL(expected, output.str());
    }

    TEST_FIXTURE(SerializationFixture, verifyDigraphCreationWithoutAName)
    {
        archive.createDigraph();
        archive.finalize();
        
        const std::string expected = "digraph {\n}\n";
        CHECK_EQUAL(expected, output.str());
    }

    TEST_FIXTURE(SerializationFixture, verifyGraphAttributes)
    {
        archive.applyGraphAttribute("size", "1,1");
        CHECK_EQUAL("\tsize=1,1;\n", output.str());
    }
    
    TEST_FIXTURE(SerializationFixture, verifyCreateVertex)
    {
        archive.createVertex("v1");
        CHECK_EQUAL("", output.str());
    }
    
    TEST_FIXTURE(SerializationFixture, verifyCreateVertexWithAttribute)
    {
        archive.createVertex("v1", "label", "Foo");
        CHECK_EQUAL("\tv1 [label=Foo];\n", output.str());
    }
    
    TEST_FIXTURE(SerializationFixture, verifyCreateEdge)
    {
        archive.createEdge("v1", "v2");
        CHECK_EQUAL("\tv1 -- v2;\n", output.str());
    }
    
    TEST_FIXTURE(SerializationFixture, verifyCreateEdgeWithAttribute)
    {
        archive.createEdge("v1", "v2", "label", "foo");
        CHECK_EQUAL("\tv1 -- v2 [label=foo];\n", output.str());
    }
    
    TEST_FIXTURE(SerializationFixture, verifyCreateDirectedEdge)
    {
        archive.createDigraph();
        archive.createEdge("v1", "v2");
        archive.finalize();
        
        CHECK_EQUAL("digraph {\n\tv1 -> v2;\n}\n", output.str());
    }
    
    TEST_FIXTURE(SerializationFixture, verifyCreateDirectedEdgeWithAttribute)
    {
        archive.createDigraph();
        archive.createEdge("v1", "v2", "label", "foo");
        archive.finalize();
        
        CHECK_EQUAL("digraph {\n\tv1 -> v2 [label=foo];\n}\n", output.str());
    }
    
    TEST_FIXTURE(SerializationFixture, verifyApplyVertexAttributes)
    {
        archive.createDigraph();
        archive.applyVertexAttributes("v1", std::make_pair("filename", "test.cpp"));
        archive.finalize();
        
        CHECK_EQUAL("digraph {\n\tv1 [filename=test.cpp ];\n}\n", output.str());
    }

    TEST_FIXTURE(SerializationFixture, verifyApplyVertexAttributesWithTwoAttributes)
    {
        archive.createDigraph();
        archive.applyVertexAttributes("v1", std::make_pair("filename", "test.cpp"), std::make_pair("type", "Header"));
        archive.finalize();
        
        CHECK_EQUAL("digraph {\n\tv1 [filename=test.cpp type=Header ];\n}\n", output.str());
    }

    TEST_FIXTURE(SerializationFixture, verifyApplyVertexAttributesWithThreeAttributes)
    {
        archive.createDigraph();
        archive.applyVertexAttributes("v1", std::make_pair("filename", "test.cpp"), std::make_pair("type", "Header"), std::make_pair("color", "\"blue\""));
        archive.finalize();
        
        CHECK_EQUAL("digraph {\n\tv1 [filename=test.cpp type=Header color=\"blue\" ];\n}\n", output.str());
    }
    
    TEST_FIXTURE(SerializationFixture, verifyApplyEdgeAttributes)
    {
        archive.createDigraph();
        archive.applyEdgeAttributes("v1", "v2", std::make_pair("filename", "test.cpp"));
        archive.finalize();
        
        CHECK_EQUAL("digraph {\n\tv1 -> v2 [filename=test.cpp ];\n}\n", output.str());
    }

    TEST_FIXTURE(SerializationFixture, verifyApplyEdgeAttributesWithTwoAttributes)
    {
        archive.createDigraph();
        archive.applyEdgeAttributes("v1", "v2", std::make_pair("filename", "test.cpp"), std::make_pair("type", "Header"));
        archive.finalize();
        
        CHECK_EQUAL("digraph {\n\tv1 -> v2 [filename=test.cpp type=Header ];\n}\n", output.str());
    }

    TEST_FIXTURE(SerializationFixture, verifyApplyEdgeAttributesWithThreeAttributes)
    {
        archive.createDigraph();
        archive.applyEdgeAttributes("v1", "v2", std::make_pair("filename", "test.cpp"), std::make_pair("type", "Header"), std::make_pair("color", "\"blue\""));
        archive.finalize();
        
        CHECK_EQUAL("digraph {\n\tv1 -> v2 [filename=test.cpp type=Header color=\"blue\" ];\n}\n", output.str());
    }
    
    TEST_FIXTURE(SerializationFixture, verifyBlankLine)
    {
        archive.createDigraph();
        archive.blankLine();
        archive.finalize();
        
        CHECK_EQUAL("digraph {\n\n}\n", output.str());
    }
    
    TEST_FIXTURE(SerializationFixture, verifyDefaultNodeAttribute)
    {
        archive.createDigraph();
        archive.defaultVertexAttributes(std::make_pair("fontsize", "8"), std::make_pair("color", "black"));
        archive.finalize();
        
        CHECK_EQUAL("digraph {\n\tnode [fontsize=8 color=black ];\n}\n", output.str());
    }
    
    TEST_FIXTURE(SerializationFixture, verifyDefaultEdgeAttribute)
    {
        archive.createDigraph();
        archive.defaultEdgeAttributes(std::make_pair("fontsize", "8"), std::make_pair("color", "black"));
        archive.finalize();
        
        CHECK_EQUAL("digraph {\n\tedge [fontsize=8 color=black ];\n}\n", output.str());
    }
}
