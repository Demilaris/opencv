#include <iostream>

#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"

using namespace cv;
using namespace std;
int main()
{ Mat scr = imread ("/home/blackhand/demilaris/proj/untitled/morskaya.jpg");
 if (scr.data == 0)
 {
     printf("Incorrect image name or format.\n");
     return 1;
 }
 Mat copy =scr.clone();//copy original image
 Mat gray;
 cvtColor(scr,gray,COLOR_BGR2GRAY);//in gray
Mat grayThresh;
threshold(gray,grayThresh,250,255,THRESH_BINARY);//binary (black-white img)
vector<vector<Point> >  contours;

findContours(grayThresh,contours,RETR_CCOMP,CHAIN_APPROX_SIMPLE);//search contours
const char *scrWinName = "scr", *contourWinName = "contour";
namedWindow(scrWinName,1);
namedWindow(contourWinName,1);
Scalar color(255,192,203);
drawContours(copy,contours,-1,color,2);
imshow(contourWinName,copy);
imshow(scrWinName,scr);
imwrite("/home/blackhand/demilaris/proj/untitled/contoursvinka.jpg",copy);
waitKey(0);

gray.release();
grayThresh.release();
copy.release();
scr.release();
}






























































