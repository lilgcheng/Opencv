
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <cmath> 
#include <iomanip> 
#include <iostream> 
#include <stdlib.h> 
#include <stdio.h>  
using namespace cv;
using namespace std;
void colorReduce(Mat&image, int n);
int main(int argc, char **argv)
{
	Mat image = imread("bean.jpg", CV_LOAD_IMAGE_COLOR);
	double c = 0;


	int iLowH = 0;
	int iHighH = 40;

	int iLowS = 40; 
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;

	if(!image.data){
		cout<<"no find image"<<endl;
	}
	namedWindow("image",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("image",image);


	Mat imgHSV;
	cvtColor(image, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV
	Mat imgThresholded;
	inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image
	namedWindow("imgHSV",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("imgHSV",imgThresholded);
	// cout<<imgThresholded.rows<<endl;
	// cout<<imgThresholded.cols<<endl;
	int i,j;  
	int cPointR,cPointG,cPointB,cPoint;//currentPoint;  
	for(i=1;i<imgThresholded.rows;i++){  
		for(j=1;j<imgThresholded.cols;j++){  
			cPointB=imgThresholded.at<Vec3b>(i,j)[0];  
			cPointG=imgThresholded.at<Vec3b>(i,j)[1];  
			cPointR=imgThresholded.at<Vec3b>(i,j)[2];  
			cout<<"B = "<<cPointB<<endl;
			cout<<"G = "<<cPointG<<endl;
			cout<<"R = "<<cPointR<<endl;
			//255 = white and 0 = black
			if(cPointB == 255 &cPointR ==255  &cPointG == 255 )  {  
				c++;
				imgThresholded.at<Vec3b>(i,j)[0]=100;  
				imgThresholded.at<Vec3b>(i,j)[1]=100;  
				imgThresholded.at<Vec3b>(i,j)[2]=100;  
			}
		}  
	}  

	double percentage ; 
	double total = image.rows*image.cols;
	percentage = c/total*100;
	cout<<"total = "<<total<<endl;
	cout<<"black piex = "<<c<<endl;
	cout <<  "percentage = "<<percentage<<"%" << endl; 
	namedWindow("imgThresholded",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("imgThresholded",imgThresholded);
	
	Mat image2;
	imgThresholded.copyTo(image2);
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	// Find contours
	findContours( image2, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );	
	// Approximate contours to polygons + get bounding rects and circles
	vector<vector<Point> > contours_poly( contours.size() );
	vector<Rect> boundRect( contours.size() );
	vector<Point2f>center( contours.size() );
	vector<float>radius( contours.size() );
	for( int i = 0; i < contours.size(); i++ ){ 
		// cout << "Area " << "["<<i<<"]=" << contourArea(contours[i]) << endl;
		if(contourArea(contours[i])>2000){
			approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
			boundRect[i] = boundingRect( Mat(contours_poly[i]) );
			minEnclosingCircle( (Mat)contours_poly[i], center[i], radius[i] );
		}
	}	
	//draw rectangle and draw text
	int fontFace = FONT_HERSHEY_SCRIPT_SIMPLEX;
	double fontScale = 2;
	int thickness = 3;
	char str[10];
	int s = 0;
	for( int i = 0; i< contours.size(); i++ ){
		if(contourArea(contours[i])>2000){
			rectangle( image2, boundRect[i].tl(), boundRect[i].br(), Scalar(255,255,255), 2, 8, 0 );
			s++;
			// cout<<s<<endl;
			sprintf(str, "%d", s);
			// cout<<str<<endl;
			 putText(image2, str, boundRect[i].br(), fontFace, fontScale, Scalar(255), 3,8);
		}
	}

	namedWindow("image2",CV_WINDOW_AUTOSIZE);//AUTOSIZE
	imshow("image2",image2);
	waitKey(0);
	return 0;
}
