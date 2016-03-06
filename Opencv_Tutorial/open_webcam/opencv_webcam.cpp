#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
using namespace cv;
using namespace std;

int main(){
	//抓取攝影機
	VideoCapture cap(0);
	//嘗試開啟攝影機
	if(!cap.isOpened()){
		cout<<"Cannot open the web cam\n";
		return -1;
	}
	cap.set(CV_CAP_PROP_FRAME_HEIGHT,640);//window height
	cap.set(CV_CAP_PROP_FRAME_WIDTH,480);//window  witdh
	//用矩陣紀錄抓取的每張frame
	Mat frame;
	//建立一個視窗,名稱為camera
	// namedWindow("camera",1);
	while(1)
	{
		//把取得的影像放置到矩陣中
		cap >> frame;
		// namedWindow("frame",CV_WINDOW_NORMAL);//Custom sizes

		//顯示frame到camera名稱的視窗
		imshow("frame", frame);
		if(waitKey(30) >= 0) break;
	}
	system("PAUSE");
	return 0;
}