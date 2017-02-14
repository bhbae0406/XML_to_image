#include <string.h>
#include <string>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <vector>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include "parser.h"

using namespace rapidxml;
using namespace std;
using namespace cv;

int heightThresh = 0;
int numThresh = 0;
int widthCharRatio = 0;

int pageWidth = 19268;
int pageHeight = 28892;
int Xdimension = 9500;
int Ydimension = 9600;

Mat blank(Xdimension, Ydimension, CV_8UC3, Scalar(255,255,255));

xml_node<>* first_textblock;

double getWidthCharRatio(rapidxml::xml_node<>* textLine)
{
   string text;
   int charCount = 0;
   double width = 0;

   for (xml_node<>* word = textLine->first_node("String"); word != 0;
         word = word->next_sibling("String"))
   {
      text = word->first_attribute("CONTENT")->value();
      width += atof(word->first_attribute("WIDTH")->value());
      charCount += text.length();
   }

   //double width = atoi(textLine->first_attribute("WIDTH")->value());

   width = Xdimension * (width / (double)pageWidth);

   return (width / charCount);
}

double getObjectHeight(rapidxml::xml_node<>* block)
{       
   double xmlHeight = 0;
   xmlHeight = atof(block->first_attribute("HEIGHT")->value());

   return (Ydimension * (xmlHeight/pageHeight));
}

void drawBlock(rapidxml::xml_node<>* block, cv::Scalar color)
{
   int rHpos = atoi(block->first_attribute("HPOS")->value());
   int rVpos = atoi(block->first_attribute("VPOS")->value());
   int rHeight = atoi(block->first_attribute("HEIGHT")->value());
   int rWidth = atoi(block->first_attribute("WIDTH")->value());

   Point rP1((int)(Xdimension * (rHpos/(double)pageWidth)), (int)(Ydimension * (rVpos/(double)pageHeight)));

   Point rP2(rP1.x + (int)(Xdimension * (rWidth/(double)pageWidth))
         , rP1.y + (int)(Ydimension * (rHeight/(double)pageHeight)));

   //note - for Scalar - openCV uses BGR color format
   //therefore - Scalar(0, 0, 255) is solid red 
   rectangle(blank, rP1, rP2, color, 7);
}

void displayImage(int, void*)
{
   //double min = 1000.0;
   //double max = 0.0;
   //double ratio = 0.0;
   double tempRatio = 0.0;
   double tempHeight = 0.0;

   for (rapidxml::xml_node<>* textBlock = first_textblock; textBlock != 0;
         textBlock = textBlock->next_sibling("TextBlock"))
   {
      for (rapidxml::xml_node<>* textLine = textBlock->first_node("TextLine");
            textLine != 0; textLine = textLine->next_sibling("TextLine"))
      {
         tempRatio = widthCharRatio / (double)10;
         tempRatio += 1.64348; //so min is 1.64348

         tempHeight = heightThresh / (double)10;
         tempHeight += 11.9618;

         if ((getObjectHeight(textLine) > tempHeight) &&
               (getWidthCharRatio(textLine) > tempRatio))
         {
            drawBlock(textLine, Scalar(0,0,255));
         }

         else
         {
            drawBlock(textLine, Scalar(255,0,0));
         }
         
      }
   }

   imshow("Threshold Result", blank);
}


int main(int argc, char* argv[])
{
   if (argc != 2)
   {
      cerr << "Program Usage: xml_image [xml_file.xml]" << '\n';
      exit(1);
   }
   string inputFile(argv[1]);

   auto const found = inputFile.find_last_of('.');
   auto filename = inputFile.substr(0,found);

   rapidxml::file<> xmlFile(argv[1]);
   rapidxml::xml_document<> doc;
   doc.parse<0>(xmlFile.data());

   //the root node is alto
   xml_node<> * root_node = doc.first_node();
   xml_node<> * layout_node = root_node->first_node("Layout");
   first_textblock = layout_node->first_node("Page")->
      first_node("PrintSpace")->first_node("TextBlock");

   //Mat blank(Xdimension, Ydimension, CV_8UC3, Scalar(255,255,255));

   namedWindow("Threshold Result", WINDOW_NORMAL);

   createTrackbar("heightThresh", "Threshold Result", &heightThresh, 3071,
         displayImage);

   createTrackbar("widthChar", "Threshold Result", &widthCharRatio, 3019,
         displayImage);
   
   displayImage(0,0);
   waitKey();

   return 0;
}


