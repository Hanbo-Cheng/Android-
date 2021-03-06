#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cstdio>
using namespace std;
using namespace cv;
int facial_clf_demo()
{
	// 【1】加载分类器
	CascadeClassifier cascade;
	cascade.load("haarcascade_frontalface_alt.xml");

	Mat srcImage, grayImage, dstImage;
	// 【2】读取图片
	srcImage = imread("2.jpg");
	dstImage = srcImage.clone();
	//imshow("【原图】", srcImage);
	
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY); // 生成灰度图，提高检测效率
	//imshow("【原图】", grayImage);
	//waitKey(0);
	// 定义7种颜色，用于标记人脸
	Scalar colors[] =
	{
		// 红橙黄绿青蓝紫
		CV_RGB(255, 0, 0),
		CV_RGB(255, 97, 0),
		CV_RGB(255, 255, 0),
		CV_RGB(0, 255, 0),
		CV_RGB(0, 255, 255),
		CV_RGB(0, 0, 255),
		CV_RGB(160, 32, 240)
	};

	// 【3】检测
	vector<Rect> rect;
	cascade.detectMultiScale(grayImage, rect, 1.1, 3, 0);  // 分类器对象调用
	printf("检测到人脸个数：%d\n", rect.size()); // 将识别的人脸的数量显示在控制台中
	// 【4】标记--在脸部画圆
	for (int i = 0; i < rect.size(); i++)
	{
		Point  center;
		int radius;
		center.x = cvRound((rect[i].x + rect[i].width * 0.5));
		center.y = cvRound((rect[i].y + rect[i].height * 0.5));
		radius = cvRound((rect[i].width + rect[i].height) * 0.25);
		circle(dstImage, center, radius, colors[i % 7], 2);

		// 【5】显示

		
	}
	imshow("【人脸识别detectMultiScale】", dstImage);

	waitKey(0);
	return 0;
}
Scalar colors[] =
{
	// 红橙黄绿青蓝紫
	CV_RGB(255, 0, 0),
	CV_RGB(255, 97, 0),
	CV_RGB(255, 255, 0),
	CV_RGB(0, 255, 0),
	CV_RGB(0, 255, 255),
	CV_RGB(0, 0, 255),
	CV_RGB(160, 32, 240)
};
void facial_clf(Mat &frame, CascadeClassifier cascade)
{
	// 【1】加载分类器
	

	Mat grayImage;

	//cout << srcImage << endl;
	//imshow("【原图】", srcImage);

	cvtColor(frame, grayImage, COLOR_BGR2GRAY); // 生成灰度图，提高检测效率

	// 【3】检测
	vector<Rect> rect;
	cascade.detectMultiScale(grayImage, rect, 1.1, 3, 0);  // 分类器对象调用
	printf("检测到人脸个数：%d\n", rect.size()); // 将识别的人脸的数量显示在控制台中
	// 【4】标记--在脸部画圆
	for (int i = 0; i < rect.size(); i++)
	{
		Point  center;
		int radius;
		center.x = cvRound((rect[i].x + rect[i].width * 0.5));
		center.y = cvRound((rect[i].y + rect[i].height * 0.5));
		radius = cvRound((rect[i].width + rect[i].height) * 0.25);
		circle(frame, center, radius, colors[i % 7], 2);


	}
}

int main() {
	VideoCapture cap(1);
	if (!cap.isOpened()) {
		std::cout << "！！！";
		return -1;
	}
	Mat frame;
	CascadeClassifier cascade;
	cascade.load("haarcascade_frontalface_alt.xml");
	bool judge = true;
	namedWindow("test1");
	while (judge)
	{
		cap >> frame;
		if (frame.empty()) break;
		//cout << frame << endl;
		facial_clf(frame, cascade);
		//cout << frame << endl;
		imshow("test1", frame);
		
		if (27 == waitKey(30)) {//按键盘：ESC键结束程序
			break;              //waitKey(30)返回的ASCII值为27，对应的按钮：ESC
		}
		
	}
	destroyWindow("test1");
	return 0;
}