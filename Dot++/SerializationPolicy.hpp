#pragma once 
#include <ostream>
#include <string>
#include <utility>

namespace dot_pp {

    class SerializationPolicy
    {
    public:
        using AttributeName = std::string;
        using AttributeValue = std::string;
        using Attribute = std::pair<AttributeName, AttributeValue>;
    
        SerializationPolicy(std::ostream& stream);
        
        void createGraph(const std::string& name = "");
        void createDigraph(const std::string& name = "");
        
        void createVertex(const std::string& name);
        void createVertex(const std::string& name, const std::string& attributeName, const std::string& value);
        
        void createEdge(const std::string& vertex1, const std::string& vertex2);
        void createEdge(const std::string& vertex1, const std::string& vertex2, const std::string& attributeName, const std::string& value);
        
        void applyGraphAttribute(const std::string& attributeName, const std::string& value);
        
        template<typename... AttributeList>
        void defaultVertexAttributes(AttributeList&&... attributes)
        {
            stream_ << "\t" << "node [";
            printAttributes(std::forward<AttributeList>(attributes)...);
            stream_ << "];\n";
        }

        template<typename... AttributeList>
        void defaultEdgeAttributes(AttributeList&&... attributes)
        {
            stream_ << "\t" << "edge [";
            printAttributes(std::forward<AttributeList>(attributes)...);
            stream_ << "];\n";
        }

        template<typename... AttributeList>
        void applyVertexAttributes(const std::string& vertex, AttributeList&&... attributes)
        {
            stream_ << "\t" << vertex << " [";
            printAttributes(std::forward<AttributeList>(attributes)...);
            stream_ << "];\n";
        }
        
        template<typename... AttributeList>
        void applyEdgeAttributes(const std::string& vertex1, const std::string& vertex2, AttributeList&&... attributes)
        {
            stream_ << "\t" << vertex1 << " " << edgeStyle_ << " " << vertex2 << " [";
            printAttributes(std::forward<AttributeList>(attributes)...);
            stream_ << "];\n";
        }
        
        void blankLine();
        void finalize();
        
    private:
        void printAttribute(const Attribute& attribute);
        
        template<typename T>
        void printAttributes(const T& attribute)
        {
            printAttribute(attribute);
        }
        
        template<typename T, typename... AttributeList>
        void printAttributes(const T& attribute, AttributeList&&... attributes)
        {
            printAttribute(attribute);
            printAttributes(std::forward<AttributeList>(attributes)...);
        }
        
    private:
        std::ostream& stream_;
        std::string edgeStyle_;
    };
}
