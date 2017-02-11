#ifndef PARSER_H
#define PARSER_H

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
#include <opencv2/imgproc/improc.hpp>
#include <iostream>

class Parser
{
   public:

      //constructor for Parser object
      /* Initializes pageWidth, pageHeight,
         Xdimension, and Ydimension
      */
      Parser(pWidth, pHeight, Xdim, Ydim);

      void PutText(cv::Mat& img, const std::string& text, const cv::Rect& roi,
            const cv::Scalar& color, int fontFace, double fontScale,
            int thickness = 1, int lineType = 8);

      /* readImage

         Input -- name of xmlFile (will be passed in as argv[1]
         Output -- pointer to node of first textblock

         1) First takes in file name and calls doc.parse<0>
         2) Creates a new matrix that is assigned to outImg (a private variable)
         3) Returns a pointer to the first textblock in the xml file

       */

      rapidxml::xml_node<>* readImage(const std::string& xmlFile);

      //constructs outImg using Xdimension and Ydimension
      void initPicture()

      /* drawBlock will be used to draw textBlocks, textLines, and Strings
         --- Since drawing each of these three objects requires similar
         implementations, the general implementation is included in this function.
         The user can specify the color of the rectangle by passing in a
         Scalar object as a parameter
       */
      void drawBlock(rapidxml::xml_node<>& object, cv::Scalar& color);

      void outImage(cv::Mat& outImg, const std::string& filename);


   private:
      /* Page parameters (in pixels):

         1) Page Width - width of page in pixels
         2) Page Height - height of page in pixels
         3) Xdimension - used to make inch/1200
         to number of pixels in horizontal direction
         4) Ydimension - used to map inch/1200 
         to number of pixels in vertical direction
       */

      int pageWidth;
      int pageHeight;
      int Xdimension;
      int Ydimension;
      std::string fileName; //used when writing output jpeg file
      cv::Mat outImg;
};




#endif
