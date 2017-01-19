#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
using namespace cv;

int main( )
{ 
   Mat blank(1000, 900, CV_8UC3, Scalar(255,255,255));
   
   Point p1((int)(900 * (2880/(double)19268)), (int)(1000 * (960/(double)28892)));
   Point p2(p1.x + (int)(900 * (1920/(double)19268)), p1.y + (int)(1000 * (672/(double)28892)));

   //std::cout << "X: " << p1.x << ", Y: " << p1.y << '\n';

   //circle(blank, p1, 100, Scalar(255, 0, 0), 1);
   //Point p1(0,0);
   //Point p2(900,500);

   rectangle(blank, p1, p2, Scalar(255, 0, 0), 1);

   //putText(blank, "The", Point(50,100), FONT_HERSHEY_SIMPLEX, 1, Scalar(0,0,0), 1);
   imshow("Image",blank);

   waitKey( 0 );
   
   return(0);
}
