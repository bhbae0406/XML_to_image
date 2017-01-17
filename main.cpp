//
//  main.cpp
//  XML_to_jpeg
//
//  Created by Bae Byoung Hyun on 1/17/17.
//  Copyright © 2017 Bae Byoung Hyun. All rights reserved.
//

#include <iostream>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

using namespace rapidxml;


int main(int argc, const char * argv[]) {
    rapidxml::file<> xmlFile("0033.xml"); // Default template is char
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());
    
   
    std::cout
    << "Name of my first node is: " << doc.first_node()->name() << "\n";
    xml_node<> *node = doc.first_node("foobar");
    std::cout << "Node foobar has value " << node->value() << "\n";
    for (xml_attribute<> *attr = node->first_attribute();
         attr; attr = attr->next_attribute())
    {
        std::cout << "Node foobar has attribute " << attr->name() << " ";
        std::cout << "with value " << attr->value() << "\n";
    }
    std::cout << "Hello, World!\n";
    return 0;
}
