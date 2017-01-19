#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;

void PutText(cv::Mat& img, const std::string& text, const cv::Rect& roi, const cv::Scalar& color, int fontFace, double fontScale, int thickness = 1, int lineType = 8)
{
   CV_Assert(!img.empty() && (img.type() == CV_8UC3 || img.type() == CV_8UC1));
   CV_Assert(roi.area() > 0);
   CV_Assert(!text.empty());

   int baseline = 0;

   // Calculates the width and height of a text string
   cv::Size textSize = cv::getTextSize(text, fontFace, fontScale, thickness, &baseline);

   // Y-coordinate of the baseline relative to the bottom-most text point
   baseline += thickness;

   // Render the text over here (fits to the text size)
   cv::Mat textImg(textSize.height + baseline, textSize.width, img.type());

   if (color == cv::Scalar::all(0)) textImg = cv::Scalar::all(255);
   else textImg = cv::Scalar::all(0);

   // Estimating the resolution of bounding image
   cv::Point textOrg((textImg.cols - textSize.width) / 2, (textImg.rows + textSize.height - baseline) / 2);

   // TR and BL points of the bounding box
   cv::Point tr(textOrg.x, textOrg.y + baseline);
   cv::Point bl(textOrg.x + textSize.width, textOrg.y - textSize.height);

   cv::putText(textImg, text, textOrg, fontFace, fontScale, color, thickness);

   // Resizing according to the ROI
   cv::resize(textImg, textImg, roi.size());

   cv::Mat textImgMask = textImg;
   if (textImgMask.type() == CV_8UC3)
      cv::cvtColor(textImgMask, textImgMask, cv::COLOR_BGR2GRAY);

   // Creating the mask
   cv::equalizeHist(textImgMask, textImgMask);

   if (color == cv::Scalar::all(0)) cv::threshold(textImgMask, textImgMask, 1, 255, cv::THRESH_BINARY_INV);
   else cv::threshold(textImgMask, textImgMask, 254, 255, cv::THRESH_BINARY);

   // Put into the original image
   cv::Mat destRoi = img(roi);
   textImg.copyTo(destRoi, textImgMask);
}

int main( )
{ 
   Mat blank(1000, 900, CV_8UC3, Scalar(255,255,255));

   Point p1((int)(900 * (2880/(double)19268)), (int)(1000 * (960/(double)28892)));
   Point p2(p1.x + (int)(900 * (1920/(double)19268)), p1.y + (int)(1000 * (672/(double)28892)));

   //std::cout << "X: " << p1.x << ", Y: " << p1.y << '\n';

   //circle(blank, p1, 100, Scalar(255, 0, 0), 1);
   //Point p1(0,0);
   //Point p2(900,500);

   //rectangle(blank, p1, p2, Scalar(255, 0, 0), 1);

   cv::Rect roi(p1.x, p1.y, (p2.x-p1.x), (p2.y-p1.y));

   PutText(blank, "THE", roi, Scalar(255,0,0), FONT_HERSHEY_SCRIPT_SIMPLEX, 2.5, 2);

   //putText(blank, "The", Point(50,100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,0), 1);
   imshow("Image",blank);

   waitKey( 0 );

   return(0);
}