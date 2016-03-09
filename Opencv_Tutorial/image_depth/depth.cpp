#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;
void colorReduce_1(Mat &image,int div);
void colorReduce_2(Mat &image,int div);
void colorReduce_3(Mat &image,int div);
int main(int argc, char **argv)
{
	Mat image = imread("car.jpg", CV_LOAD_IMAGE_COLOR);
	if(!image.data){
		cout<<"no find image"<<endl;
	}
	// cout<<image.size().height<<","<<image.size().width<<endl;
	// Mat_<uchar> im2= img; // im2 refers to image  
	// im2(50,100)= 0; // access to row 50 and column 100  
	double duration1,duration2,duration3;
	
	Mat image1;
	image.copyTo(image1);
	duration1 = static_cast<double>(getTickCount());
	colorReduce_1(image1,64);
	duration1 = static_cast<double>(getTickCount())-duration1;
	duration1 /= getTickFrequency(); // the elapsed time in ms
	cout<<"mode1="<<duration1<<endl;

	Mat image2;
	image.copyTo(image2);
	duration2 = static_cast<double>(getTickCount());
	colorReduce_2(image2,64);
	duration2 = static_cast<double>(getTickCount())-duration2;
	duration2 /= getTickFrequency(); // the elapsed time in ms
	cout<<"mode2="<<duration2<<endl;

	Mat image3;
	image.copyTo(image3);
	duration3 = static_cast<double>(getTickCount());
	colorReduce_3(image3,64);
	duration3 = static_cast<double>(getTickCount())-duration3;
	duration3 /= getTickFrequency(); // the elapsed time in ms
	cout<<"mode3="<<duration3<<endl;

	namedWindow("Oringal image",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("Oringal image",image);

	namedWindow("image1",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("image1",image1);

	namedWindow("image2",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("image2",image2);

	namedWindow("image3",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("image3",image3);

	waitKey(0);
	return 0;
}
//用指標掃描一幅圖像
void colorReduce_1(Mat &image,int div){
	int n1 = image.rows;
	int nc = image.cols * image.channels();
	// cout<<n1<<"  "<<nc<<" "<<endl;
	for(int j = 0; j<n1 ; j++){
		uchar* data = image.ptr<uchar>(j);
		for(int i=0; i<nc; i++){
			data[i] = (data[i]/div*div)+(div/2);
		}
	}
}

void colorReduce_2(Mat &image,int div){
	Mat_<Vec3b>::iterator it = image.begin<Vec3b>();
	Mat_<Vec3b>::iterator itend = image.end<Vec3b>();

	for(;it != itend ;++it){
		(*it)[0] = (*it)[0]/div*div + div/2;
		(*it)[1] = (*it)[1]/div*div + div/2;
		(*it)[2] = (*it)[2]/div*div + div/2;
	}
}

void colorReduce_3(Mat &image,int div){
	int nl = image.rows;
	int nc = image.cols;
	if(image.isContinuous() ){
		nc = nc*nl;
		nl = 1;
	}
	int n = static_cast<int>(
		log(static_cast<double>(div))/log(2.0));
	uchar mask = 0xFF<<n;
	for (int j = 0; j < nl; j++){
		uchar* data = image.ptr<uchar>(j);
		for(int i=0;i<nc;i++){
			*data++= *data&mask + div/2;
			*data++= *data&mask + div/2;
			*data++= *data&mask + div/2;
		}
	}
}
