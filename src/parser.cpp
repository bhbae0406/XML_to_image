#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

//void arguments for now - maybe add some later ...

using namespace rapidxml;
using namespace std;

int main(void)
{
   rapidxml::file<> xmlFile("0033_copy.xml");
   rapidxml::xml_document<> doc;

   doc.parse<0>(xmlFile.data());

   //the root node is alto
   xml_node<> * root_node = doc.first_node();

   xml_node<> * layout_node = root_node->first_node("Layout");

   xml_node<> * first_textblock = layout_node->first_node("Page")->
      first_node("PrintSpace")->first_node("TextBlock");

   cout << "Words: " << '\n';
   
   //cout << first_textblock->next_sibling()->name() << '\n';
   
   
   /*
   cout << first_textblock->next_sibling()->first_node("TextLine")->
      first_node("String")->first_attribute("CONTENT")->value() << '\n';
   */
   

   for (xml_node<> * textBlock = first_textblock; textBlock != 0;
         textBlock = textBlock->next_sibling("TextBlock"))
   {
      for (xml_node<> * textLine = textBlock->first_node("TextLine"); textLine != 0;
            textLine = textLine->next_sibling("TextLine"))
      {
         for (xml_node<> * word = textLine->first_node("String"); word != 0;
               word = word->next_sibling("String"))
         {
            //cout << word->name() << '\n';
            cout << word->first_attribute("CONTENT")->value() << '\n';
         }
      }
   }

   return 0;
}
            
             

   



   



   
