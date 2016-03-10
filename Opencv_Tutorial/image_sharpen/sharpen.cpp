
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
 
using namespace cv;
using namespace std;
void sharpen_1(const Mat &image, Mat &result);
void sharpen_2(const Mat &image, Mat &result);
void sharpen2D(const Mat &image, Mat &result);

int main( int argc, char** argv ){
	Mat image, image_gray;
	image = imread("car.jpg", 1);// always convert image to the color one
	image_gray = imread("car.jpg", 2);//image to the grayscale 

	Mat result1;
	sharpen_1(image_gray, result1);

	Mat result2;
	sharpen_2(image_gray, result2);

	Mat image1;
	image.copyTo(image1);
	sharpen2D(image, image1);

	namedWindow( "image", CV_WINDOW_AUTOSIZE );
	imshow( "image", image );

	namedWindow("result1", CV_WINDOW_AUTOSIZE);
	imshow("result1", result1);

	namedWindow("result2", CV_WINDOW_AUTOSIZE);
	imshow("result2", result2);

	namedWindow("image1", CV_WINDOW_AUTOSIZE);
	imshow("image1", image1);

	waitKey(0);
	// Wait for a keystroke in the window
	return 0;
}


/*
pervuous 	 	-1	 
current		-1	 5	-1
next			-1	 
*/
void sharpen_1(const Mat &image, Mat &result){
	result.create(image.size(), image.type());
	for (int j = 1; j < image.rows - 1; j++){
		const uchar* prevuous = image.ptr<const uchar>(j - 1);
		const uchar* current = image.ptr<const uchar>(j);
		const uchar* next = image.ptr<const uchar>(j + 1);
		uchar* output = result.ptr<uchar>(j);
		for (int i = 1; i < image.cols - 1; i++){
			*output++ = saturate_cast<uchar>(
				5 * current[i] - current[i-1]
				- current[i + 1] - prevuous[i] - next[i]);
		}
	}
	result.row(0).setTo(Scalar(0));
	result.row(result.rows - 1).setTo(Scalar(0));
	result.col(0).setTo(Scalar(0));
	result.col(result.cols - 1).setTo(Scalar(0));
}


/*
pervuous	-1	0	1
current		-2	0	2
next		-1	0	1
*/
void sharpen_2(const Mat &image, Mat &result){
	result.create(image.size(), image.type());
	for (int j = 1; j < image.rows - 1; j++){
		const uchar* prevuous = image.ptr<const uchar>(j - 1);
		const uchar* current = image.ptr<const uchar>(j);
		const uchar* next = image.ptr<const uchar>(j + 1);
		uchar* output = result.ptr<uchar>(j);
		for (int i = 1; i < image.cols - 1; i++){
			*output++ = saturate_cast<uchar>(
				0 * current[i] - (-2)*current[i - 1]
				- (2)*current[i + 1] - (0)*prevuous[i] - (0)*next[i]);
		}
	}
	result.row(0).setTo(Scalar(0));
	result.row(result.rows - 1).setTo(Scalar(0));
	result.col(0).setTo(Scalar(0));
	result.col(result.cols - 1).setTo(Scalar(0));
}


/*
pervuous	 1   2	 1
current			
next		-1	-2	-1
*/
void sharpen2D(const Mat &image, Mat &result){

	Mat kernel(3, 3, CV_32F, Scalar(0));

	 kernel.at<float>(0, 0) = 1.0;
	 kernel.at<float>(0, 1) = 2.0;
	 kernel.at<float>(0, 2) = 1.0;
	 kernel.at<float>(2, 0) = -1.0;
	 kernel.at<float>(2, 1) = -2.0;
	 kernel.at<float>(2, 2) = -1.0;
	filter2D(image, result, image.depth(), kernel);
}