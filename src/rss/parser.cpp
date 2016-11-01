#include <iostream>

#include "parser.hpp"
#include "item.hpp"

using namespace item;

#define POCO_WIN32_UTF8
#include "Poco/SAX/Attributes.h"
#include "Poco/SAX/ContentHandler.h"
#include "Poco/SAX/SAXParser.h"

class XML_DataHandler: public Poco::XML::ContentHandler {
public:
    XML_DataHandler() {
        is_item = false;
    };
    virtual ~XML_DataHandler() {};

    // ContentHandler overrides
    void setDocumentLocator(const Poco::XML::Locator* loc) {
        (void)loc;
    }
    void startDocument() {
    }
    void endDocument() {
    }
    void startElement(const Poco::XML::XMLString& namespaceURI,
                      const Poco::XML::XMLString& localName,
                      const Poco::XML::XMLString& qname,
                      const Poco::XML::Attributes& attributes) {
        (void)namespaceURI;
        (void)localName;
        (void)attributes;

        if (qname == "item") {
            is_item = true;
            cur_item.reset();
        }
    }
    void endElement(const Poco::XML::XMLString & uri, const Poco::XML::XMLString & localName, const Poco::XML::XMLString & qname) {
        (void)uri;
        (void)localName;
        (void)qname;

        if (!is_item) return;

        if (qname == "title") cur_item.set_title(cur_content);
        else if (qname == "link") cur_item.set_link(cur_content);
        else if (qname == "guid" or
                 qname == "id") cur_item.set_guid(cur_content);
        else if (qname == "category") cur_item.set_category(cur_content);
        else if (qname == "description" or
                 qname == "summary" or
                 qname == "content") cur_item.set_desc(cur_content);
        else if (qname == "item") {
            //Finished with element parsing.
            std::cout << static_cast<std::string>(cur_item) << std::endl;
            is_item = false;
        }

        cur_content.clear();
    }

    void characters(const Poco::XML::XMLChar ch[], int start, int length) {
        if (!is_item) return;

        cur_content.append(ch + start, length);
    }
    void ignorableWhitespace(const Poco::XML::XMLChar ch[], int start, int length) {
        (void)ch;
        (void)start;
        (void)length;
    }
    void processingInstruction(const Poco::XML::XMLString & target, const Poco::XML::XMLString & data) {
        (void)target;
        (void)data;
    }
    void startPrefixMapping(const Poco::XML::XMLString & prefix, const Poco::XML::XMLString & uri) {
        (void)prefix;
        (void)uri;
    }
    void endPrefixMapping(const Poco::XML::XMLString & prefix) {
        (void)prefix;
    }
    void skippedEntity(const Poco::XML::XMLString & name) {
        (void)name;
    }

private:
    bool is_item;
    std::string cur_content;
    Item cur_item;
};

using namespace parser;

Parser::Parser() {
}

void Parser::parse(const std::string &rss_xml) {
    XML_DataHandler contentHandler;
    Poco::XML::SAXParser parser {};
    parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACES, false);
    parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACE_PREFIXES, true);
    parser.setContentHandler(&contentHandler);

    parser.parseString(rss_xml);
}
