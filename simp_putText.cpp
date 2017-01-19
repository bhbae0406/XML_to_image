#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;

int main( )
{ 
   Mat blank(1000, 900, CV_8UC3, Scalar(255,255,255));
   
   std::cout << (double) ( 900 * (double)(2880/19268))<< std::endl;

   Point p1( (double)(900 * (double)(2880/19268)), (double)(1000 * (double)(960/28892)));
   //Point p2(p1.x + ( * (1920/19268)), p1.y + (1000 * (672/28892)));

   std::cout << "X: " << p1.x << ", Y: " << p1.y << '\n';

   circle(blank, p1, 100, Scalar(255, 0, 0), 1);
   //Point p1(0,0);
   //Point p2(900,500);

   //rectangle(blank, p1, p2, Scalar(255, 0, 0), 1);

   //putText(blank, "The", Point(50,100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,0), 1);
   imshow("Image",blank);

   waitKey( 0 );
   return(0);
}
