#include <iostream>
#include <math.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <wiringPi.h>
using namespace cv;
using namespace std;
#define	LED	24
void find_moments( Mat imgThresholded,Mat imgOriginal );
void drawing_contours( Mat imgThresholded,Mat imgOriginal );
int main( int argc, char** argv )
{
	VideoCapture cap(0); //capture the video from web cam

	if ( !cap.isOpened() ){  // if not success, exit program
		cout << "Cannot open the web cam" << endl;
		return -1;
	}
	cap.set(CV_CAP_PROP_FRAME_HEIGHT,320);//window height
	cap.set(CV_CAP_PROP_FRAME_WIDTH,240);//window  witdh

	wiringPiSetupGpio () ;	
	pinMode (LED, OUTPUT) ;
	// namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

	int iLowH = 0;
	int iHighH = 10;

	int iLowS = 35; 
	int iHighS = 255;

	int iLowV = 0;
	int iHighV = 255;

	//Create trackbars in "Control" window
	cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
	cvCreateTrackbar("HighH", "Control", &iHighH, 179);

	cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
	cvCreateTrackbar("HighS", "Control", &iHighS, 255);

	cvCreateTrackbar("LowV", "Control", &iLowV, 255); //Value (0 - 255)
	cvCreateTrackbar("HighV", "Control", &iHighV, 255);

	while (true){
			Mat imgOriginal;

			bool bSuccess = cap.read(imgOriginal); // read a new frame from video

			if (!bSuccess) {//if not success, break loop
				cout << "Cannot read a frame from video stream" << endl;
				break;
			}

			Mat imgHSV; //convert imgHSV

			cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

			Mat imgThresholded;

			inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

			//morphological opening (remove small objects from the foreground)
			erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );
			dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 

			//morphological closing (fill small holes in the foreground)
			dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) ); 

			erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(3, 3)) );

			// imshow("Filter area", imgThresholded); //show the thresholded image	
			drawing_contours(imgThresholded,imgOriginal);

			// imshow("Thresholded Image", imgThresholded); //show the thresholded image
			imshow("Original", imgOriginal); //show the original image
			int key =waitKey(30)& 0xFF;
			if(key == 27) {//wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
				cout << "esc key is pressed by user" << endl;
				digitalWrite (LED, 0) ;	//Car Off
				break; 
			}
	}

	return 0;

}



void drawing_contours( Mat imgThresholded,Mat imgOriginal ){
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	// Find contours
	findContours( imgThresholded, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );	

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

	//每個輪廓contour的點座標
	// for(int i= 0; i < contours.size(); i++){
	// 	cout << "-------contour " << i << "-------\n";
	// 	for(int j=0; j < contours[i].size(); j++){
	// 		cout << "[" << j << "]" << ": (" << contours[i][j].x << "," << contours[i][j].y << ")" << endl ; //do whatever
	// 	}
	// 	cout << endl;
	// }

	/// Draw polygonal contour + bonding rects + circles
	for( int i = 0; i< contours.size(); i++ )
	{
		if(contourArea(contours[i])>2000){
			rectangle( imgOriginal, boundRect[i].tl(), boundRect[i].br(), Scalar(0,255,255), 2, 8, 0 );

			circle( imgOriginal,boundRect[i].tl(), 10, Scalar(255,0,0), 2, 8, 0 );

			//center point
			circle( imgOriginal
				,Point( (boundRect[i].br().x-boundRect[i].tl().x)/2+boundRect[i].tl().x  ,  (boundRect[i].tl().y-boundRect[i].br().y)/2+boundRect[i].br().y )
				,10, Scalar(0,0,255), 2, 8, 0 );

			//right point
			circle( imgOriginal
				,Point( boundRect[i].br().x ,  (boundRect[i].tl().y-boundRect[i].br().y)/2+boundRect[i].br().y )
				,10, Scalar(125,125,125), 2, 8, 0 );

			//top point
			circle( imgOriginal
				,Point( (boundRect[i].br().x-boundRect[i].tl().x)/2+boundRect[i].tl().x  ,  (boundRect[i].tl().y) )
				,10, Scalar(255,255,255), 2, 8, 0 );

			// center to right
			line(imgOriginal
				,Point( (boundRect[i].br().x-boundRect[i].tl().x)/2+boundRect[i].tl().x  ,  (boundRect[i].tl().y-boundRect[i].br().y)/2+boundRect[i].br().y )//center point
				,Point( boundRect[i].br().x ,  (boundRect[i].tl().y-boundRect[i].br().y)/2+boundRect[i].br().y )
				, Scalar(0,255,0), 2, 8, 0 );
				
			// top to right
			line(imgOriginal
				,Point( (boundRect[i].br().x-boundRect[i].tl().x)/2+boundRect[i].tl().x  ,  (boundRect[i].tl().y-boundRect[i].br().y)/2+boundRect[i].br().y )//center point
				,Point((boundRect[i].br().x-boundRect[i].tl().x)/2+boundRect[i].tl().x  ,  (boundRect[i].tl().y))
				, Scalar(0,255,255), 2, 8, 0 );

			// drawContours( imgOriginal, contours_poly, i, Scalar(0,255,255), 1, 8, vector<Vec4i>(), 0, Point() );

			int CT_distance,CR_distance;
			int cx,cy;
			int tx,ty;
			int rx,ry;
			int C_area;

			cx =  (boundRect[i].br().x-boundRect[i].tl().x)/2+boundRect[i].tl().x ;
			cy =  (boundRect[i].tl().y-boundRect[i].br().y)/2+boundRect[i].br().y ;

			tx = (boundRect[i].br().x-boundRect[i].tl().x)/2+boundRect[i].tl().x;
			ty =  (boundRect[i].tl().y) ;
			CT_distance = sqrt( ((cx-tx)*(cx-tx)) + ((cy-ty)*(cy-ty)) );
			
			rx = boundRect[i].br().x;
			ry =  (boundRect[i].tl().y-boundRect[i].br().y)/2+boundRect[i].br().y ;
			CR_distance = sqrt( ((cx-rx)*(cx-rx)) + ((cy-ry)*(cy-ry)) );

			C_area = CT_distance*CT_distance*M_PI*0.9;

			// cout << "Area " << "["<<sui<<"]=" << contourArea(contours[i]) << endl;
			// cout<<"Top point = "<<Point( (boundRect[i].br().x-boundRect[i].tl().x)/2+boundRect[i].tl().x  ,  (boundRect[i].tl().y) )<<"\n";//
			// cout<<"CT_distance= "<<CT_distance<<"\n";
			// cout<<"CR_distance= "<<CR_distance<<"\n";
			// cout<<"C_area= "<<C_area<<"\n";

			int difference = abs(C_area- contourArea(contours[i]));
			// cout<<"difference= "<<difference<<"\n";
		
			if(abs(CR_distance-CT_distance)<10 && difference<500 ){
				cout<<"This  is  a circle "<<"\n";
				digitalWrite (LED, 1) ;	//Car On
			}else{
				cout<<"This not a circle "<<"\n";
				digitalWrite (LED, 0) ;	//Car Off
			}
			circle( imgOriginal, center[i], (int)radius[i], Scalar(255,0,255), 2, 8, 0 );
		}else{
			// cout<<"Area to small"<<endl;
			digitalWrite (LED, 0) ;	//Car Off
		}
	}

}
