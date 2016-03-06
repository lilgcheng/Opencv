
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void gray(Mat &image);
int main(int argc, char **argv)
{
	Mat image = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	if(!image.data){
		cout<<"no find image"<<endl;
	}
	cout<<image.size().height<<","<<image.size().width<<endl;
	
	namedWindow("image",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("image",image);

	Mat imagegray = imread("lena.jpg", CV_LOAD_IMAGE_GRAYSCALE );//always convert image to the grayscale
	namedWindow("imagegray",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("imagegray",imagegray);
	
	Mat img_gray;
	image.copyTo(img_gray);
	gray(img_gray);
	namedWindow("img_gray",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("img_gray",img_gray);

	waitKey(0);
	return 0;
}

void gray(Mat &image){
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();
	int gray;
	for (; it != itend; ++it){
		gray = (*it)[0] = ((*it)[0] * 0.299) + ((*it)[1] * 0.587) + ((*it)[2] * 0.114);
		(*it)[0] = gray;
		(*it)[1] = gray;
		(*it)[2] = gray;
	}
}