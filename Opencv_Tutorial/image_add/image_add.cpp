
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv ){
	Mat image1, image2;
	image1= imread("night.jpg", 1);// always convert image to the color one
	image2= imread("ghost.jpg", 1);// always convert image to the color one
	Mat combimage(image1.rows ,image1.cols ,image1.type() );

	addWeighted(image1,0.7,image2,0.5,0.0,combimage);//image1 and image2 add 

	namedWindow("image1");
	imshow("image1",image1);

	namedWindow("image2");
	imshow("image2",image2);

	namedWindow("result");
	imshow("result",combimage);

	waitKey(0);
	// Wait for a keystroke in the window
	return 0;
}

