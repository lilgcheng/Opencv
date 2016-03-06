
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
	Mat image = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	if(!image.data){
		cout<<"no find image"<<endl;
	}

	Mat image1;
	image.copyTo(image1);
	flip(image,image1,1);
	//0 垂直翻轉
	//1 水平翻轉

	namedWindow("image",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("image",image);

	namedWindow("image1",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("image1",image1);
	waitKey(0);
	return 0;
}