#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void colorReduce(Mat &image,int div);
int main(int argc, char **argv)
{
	Mat image = imread("lena.jpg", CV_LOAD_IMAGE_COLOR);
	if(!image.data){
		cout<<"no find image"<<endl;
	}
	cout<<image.size().height<<","<<image.size().width<<endl;
	// Mat_<uchar> im2= img; // im2 refers to image  
	// im2(50,100)= 0; // access to row 50 and column 100  
	Mat image2;
	image.copyTo(image2);
	colorReduce(image2,32);
	
	Mat image3;
	image.copyTo(image3);
	colorReduce(image3,64);

	namedWindow("image",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("image",image);

	namedWindow("image2",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("image2",image2);

	namedWindow("image3",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("image3",image3);

	waitKey(0);
	return 0;
}
//用指標掃描一幅圖像
void colorReduce(Mat &image,int div){
	int n1 = image.rows;
	int nc = image.cols * image.channels();
	cout<<n1<<"  "<<nc<<" "<<endl;
	for(int j = 0; j<n1 ; j++){
		uchar* data = image.ptr<uchar>(j);
		for(int i=0; i<nc; i++){
			data[i] = (data[i]/div*div)+(div/2);
		}
	}
}

