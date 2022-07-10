#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <vector>
#include <cstdio>
using namespace std;
using namespace cv;
int facial_clf_demo()
{
	// ��1�����ط�����
	CascadeClassifier cascade;
	cascade.load("haarcascade_frontalface_alt.xml");

	Mat srcImage, grayImage, dstImage;
	// ��2����ȡͼƬ
	srcImage = imread("2.jpg");
	dstImage = srcImage.clone();
	//imshow("��ԭͼ��", srcImage);
	
	cvtColor(srcImage, grayImage, COLOR_BGR2GRAY); // ���ɻҶ�ͼ����߼��Ч��
	//imshow("��ԭͼ��", grayImage);
	//waitKey(0);
	// ����7����ɫ�����ڱ������
	Scalar colors[] =
	{
		// ��Ȼ���������
		CV_RGB(255, 0, 0),
		CV_RGB(255, 97, 0),
		CV_RGB(255, 255, 0),
		CV_RGB(0, 255, 0),
		CV_RGB(0, 255, 255),
		CV_RGB(0, 0, 255),
		CV_RGB(160, 32, 240)
	};

	// ��3�����
	vector<Rect> rect;
	cascade.detectMultiScale(grayImage, rect, 1.1, 3, 0);  // �������������
	printf("��⵽����������%d\n", rect.size()); // ��ʶ���������������ʾ�ڿ���̨��
	// ��4�����--��������Բ
	for (int i = 0; i < rect.size(); i++)
	{
		Point  center;
		int radius;
		center.x = cvRound((rect[i].x + rect[i].width * 0.5));
		center.y = cvRound((rect[i].y + rect[i].height * 0.5));
		radius = cvRound((rect[i].width + rect[i].height) * 0.25);
		circle(dstImage, center, radius, colors[i % 7], 2);

		// ��5����ʾ

		
	}
	imshow("������ʶ��detectMultiScale��", dstImage);

	waitKey(0);
	return 0;
}
Scalar colors[] =
{
	// ��Ȼ���������
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
	// ��1�����ط�����
	

	Mat grayImage;

	//cout << srcImage << endl;
	//imshow("��ԭͼ��", srcImage);

	cvtColor(frame, grayImage, COLOR_BGR2GRAY); // ���ɻҶ�ͼ����߼��Ч��

	// ��3�����
	vector<Rect> rect;
	cascade.detectMultiScale(grayImage, rect, 1.1, 3, 0);  // �������������
	printf("��⵽����������%d\n", rect.size()); // ��ʶ���������������ʾ�ڿ���̨��
	// ��4�����--��������Բ
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
		std::cout << "������";
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
		
		if (27 == waitKey(30)) {//�����̣�ESC����������
			break;              //waitKey(30)���ص�ASCIIֵΪ27����Ӧ�İ�ť��ESC
		}
		
	}
	destroyWindow("test1");
	return 0;
}