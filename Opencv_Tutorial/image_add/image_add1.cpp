
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>

using namespace cv;
using namespace std;

int main( int argc, char** argv ){
	Mat image1, image2,result;
	image1= imread("night.jpg", 1);// always convert image to the color one
	image2= imread("rain.jpg", 1);// always convert image to the color one

	result = 0.7*image1+0.9*image2;
	imshow("result",result);

	image2= imread("rain.jpg", 0);// always convert image to the color one
	//create vector of 3 images
	vector<Mat>  planes;
	split(image1,planes);
	//add blue
	planes[0] += image2;
	merge(planes,result);
	imshow("result on blue channel",result);

	Mat image = imread("night.jpg");
	Mat logo = imread("logo.jpg");
	Mat imageROI;
	//724,588 is image position
	imageROI = image(Rect(724,588,logo.cols,logo.rows));
	addWeighted(imageROI,1.0,logo,0.3,0.,imageROI);
	imshow("with logo",image);
	
	Mat mask = imread("logo.jpg",0);
	logo.copyTo(imageROI,mask);
	imshow("with logo 2",image);

	logo = imread("logo.jpg",0);
	image1= imread("night.jpg");
	vector<Mat> channels;
	split(image1,channels);
	imageROI = channels.at(0);
	addWeighted(imageROI(Rect(724,588,logo.cols,logo.rows)),1.0,logo,0.5,0.,imageROI(Rect(724,588,logo.cols,logo.rows)));
	merge(channels,image1);
	imshow("with logo 3",image1);

	waitKey(0);
	// Wait for a keystroke in the window
	return 0;
}

