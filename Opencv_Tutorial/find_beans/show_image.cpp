
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
using namespace cv;
using namespace std;
void colorReduce(Mat&image, int n);
int main(int argc, char **argv)
{
	Mat image = imread("bean.jpg", CV_LOAD_IMAGE_COLOR);


	int iLowH = 0;
	int iHighH = 40;

	int iLowS = 40; 
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;

	if(!image.data){
		cout<<"no find image"<<endl;
	}



	Mat imgHSV;

	cvtColor(image, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

	Mat imgThresholded;

	inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

	namedWindow("image",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("image",image);
	
	namedWindow("imgHSV",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("imgHSV",imgThresholded);

	//colorReduce(image,64);
	
	waitKey(0);
	return 0;
}

void colorReduce(Mat&image, int n)
{
    for(int k = 0;k < n;k++)
    {
        //隨機產生白色噪點
        int i = rand()%image.cols;
        int j = rand()%image.rows;
        //如果是灰度圖每個像素的存取類型為uchar，即8bit整型數
        if(image.channels() == 1){     
            image.at<uchar>(j,i) = 255;
        }
        //彩色圖像有三個通道，像素存取類型為cv::Vec3b，即由三個uchar組成的向量，這裏用下標[i]訪問每個通道
        else{
            image.at<Vec3b>(j,i)[0] = 255;
            image.at<Vec3b>(j,i)[1] = 255;
            image.at<Vec3b>(j,i)[2] = 255;
        }
    }
    namedWindow("image1",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("image1",image);
}
