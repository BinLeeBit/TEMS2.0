#pragma once
#include"MatProcess.h"


using namespace std;
using namespace cv;

bool cmp(const Vec2f &a, const Vec2f &b)
{
	return a[0] > b[0];
}

MatProcess::MatProcess()
{
	distance = 0.0;
}
MatProcess::MatProcess(const cv::Mat &_src)
{
	src = _src;
}

MatProcess::~MatProcess()
{

}

void MatProcess::SAD()
{
	std::vector<Point2f> mc;
	FindBarycenter(mc);
	if (mc.size()<=0){
		return;
	}
	cv::Point temp = mc[0];
	int avg_num = 1;
	int num = 0;
	for (int i = 1; i < mc.size(); i++){
		if (mc[i].x > 640 || mc[i].x < 0 || mc[i].y>480 || mc[i].y < 0){
			continue;
		}

		double temp_dis= sqrt((mc[i].x - temp.x)*(mc[i].x - temp.x)
			+ (mc[i].y - temp.y)*(mc[i].y - temp.y));
		/*if (temp_dis < MIN_USEFUL_POINT_D){
			if (avg_num == 1){
				mc[i].x = (mc[i - 1].x + mc[i].x) / 2;
				mc[i].x = (mc[i - 1].y + mc[i].y) / 2;
				avg_num++;
				continue;

			}
			else {
				avg_num++;
				mc[i].x = (mc[i - 1].x * (avg_num - 1) + mc[i].x) / avg_num;
				mc[i].y = (mc[i - 1].y * (avg_num - 1) + mc[i].y) / avg_num;
				continue;
			}
		}*/
		distance += temp_dis;
		avg_num = 1;
		num++;
		temp = mc[i];
		cv::circle(src, mc[i], 10, Scalar(0, 0, 255));
	}
	distance /= (double)num;
}

void MatProcess::HRF()
{
	//������ȡ����ֱ��ʱ����ֵ
	float threshold = 0.1;
	Mat srcImage = src.clone();
	Mat midImage, dstImage;
	//��ԭʼͼ�����ƽ������
	cv::blur(srcImage, srcImage, cv::Size(3, 3));
	//��ͼ�����canny��Ե���
	Canny(srcImage, midImage, 30, 200, 3);
	//����Ե����ͼ��תΪ�Ҷ�ͼ
	cvtColor(midImage, dstImage, CV_GRAY2BGR);

	//����һ�����ֱ�ߵ�ʸ������
	vector<Vec2f> lines;
	//���л���任
	HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);

	sort(lines.begin(), lines.end(), cmp);
	//�ӻ�ȡ��ֱ�߼�������ȡ���õ�ֱ��
	//������ʱ������ʾֱ�߾����ۺ��Լ����õ�ֱ�ߵ�����
	float Temp_Sum = 0;
	int Temp_Num = 0;
	//����ֱ��֮������ƽ��ֵ
	float Distance_Avg = 0;
	for (int i = 1; i < lines.size(); i++)
	{
		float judge = abs(lines[i][1] - lines[i - 1][1]);
		//ȥ��б��ƫ����ֱ��
		if (judge < 0.001)
		{
			Temp_Sum += abs(lines[i][0] - lines[i - 1][0]);
			Temp_Num++;
		}
	}

	//����ֱ��֮������ƽ��ֵ
	if (Temp_Num != 0)
	{
		Distance_Avg = Temp_Sum / (double)Temp_Num;
	}

	Temp_Num = 0;
	Temp_Sum = 0;
	for (int i = 1; i < lines.size(); i++)
	{
		float gap = abs(lines[i][0] - lines[i - 1][0]);
		float judge = abs(gap - Distance_Avg);
		//ȥ��ֱ�߼����ֵƫ����ֱ��
		if (judge < threshold*Distance_Avg)
		{
			Temp_Sum += gap;
			Temp_Num++;
		}
	}
	//�������յ�ֱ��֮��ľ���
	if (Temp_Num != 0)
	{
		Distance_Avg = Temp_Sum / (double)Temp_Num;
	}
	distance = 2 * Distance_Avg;
}

void MatProcess::BF()
{
	Mat srcImage, image;
	srcImage = src.clone();
	//��ͼ��תΪ�Ҷ�ͼ
	cvtColor(src, srcImage, COLOR_BGR2GRAY);
	//ͼ���ƽ������
	blur(srcImage, image, Size(3, 3));
	//ͼ���ֵ��
	threshold(image, image, 0, 255, CV_THRESH_OTSU);
	//imshow("Threshold Image", image);

	//����������vector
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//�������
	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());
	//Mat imageContours = Mat::zeros(image.size(), CV_8UC1); //��С��Ӿ��λ���  
	for (int i = 0; i < contours.size(); i++)
	{
		//��������  
		//drawContours(imageContours, contours, i, Scalar(255), 1, 8, hierarchy);

		//������������С������  
		RotatedRect rect = minAreaRect(contours[i]);
		Point2f P[4];
		rect.points(P);
		float lens[4];//��¼�߳�������
		for (int j = 0; j <= 3; j++)
		{
			line(src, P[j], P[(j + 1) % 4], Scalar(255), 2);
			float xx = P[j].x - P[(j + 1) % 4].x;
			float yy = P[j].y - P[(j + 1) % 4].y;
			lens[j] = sqrt(xx*xx + yy*yy);
		}
		lens[0] = (lens[0] + lens[2]) / 2;
		lens[1] = (lens[1] + lens[3]) / 2;

	}
}

void MatProcess::DF()
{
	Mat srcImage, image;
	srcImage = src.clone();
	//��ͼ��תΪ�Ҷ�ͼ
	cvtColor(src, srcImage, COLOR_BGR2GRAY);
	//ͼ���ƽ������
	blur(srcImage, image, Size(3, 3));
	//ͼ���ֵ��
	threshold(image, image, 0, 255, CV_THRESH_OTSU);
	//imshow("Threshold Image", image);

	//����������vector
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//�������
	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());
	//Mat imageContours = Mat::zeros(image.size(), CV_8UC1); //��С��Ӿ��λ���  
	for (int i = 0; i < contours.size(); i++)
	{
		//��������  
		//drawContours(imageContours, contours, i, Scalar(255), 1, 8, hierarchy);

		//������������С������  
		RotatedRect rect = minAreaRect(contours[i]);
		Point2f P[4];
		rect.points(P);
		float lens[4];//��¼�߳�������
		for (int j = 0; j <= 3; j++)
		{
			line(src, P[j], P[(j + 1) % 4], Scalar(255), 2);
			float xx = P[j].x - P[(j + 1) % 4].x;
			float yy = P[j].y - P[(j + 1) % 4].y;
			lens[j] = sqrt(xx*xx + yy*yy);
		}
		lens[0] = (lens[0] + lens[2]) / 2;
		lens[1] = (lens[1] + lens[3]) / 2;

	}
}

void MatProcess::FindBarycenter(std::vector<Point2f> &mc)
{
	Mat _src = src.clone();		//������ԭͼ(�����ǻҶ�ͼ)
	int thresh = 40;
	if (_src.type() != 0){		//������ǻҶ�ͼת��Ϊ�Ҷ�ͼ
		cv::cvtColor(_src, _src, CV_BGR2GRAY);
	}
	cv::threshold(_src, _src, BINARY_THRESH, 255, CV_THRESH_BINARY);//��ֵ��

	//ƽ������
	cv::blur(_src, _src, cv::Size(3, 3));

	Mat canny_output;			//��Ե�����
	std::vector<vector<Point> > contours;
	std::vector<Vec4i> hierarchy;

	cv::erode(_src, _src, NULL);//��ʴ
	cv::erode(_src, _src, NULL);//��ʴ
	cv::erode(_src, _src, NULL);
	cv::erode(_src, _src, NULL);
	cv::dilate(_src, _src, NULL);//����
	cv::dilate(_src, _src, NULL);//����
	cv::dilate(_src, _src, NULL);//����
	cv::dilate(_src, _src, NULL);//����

	//����canny��Ե���
	cv::Canny(_src, canny_output, thresh, thresh * 2, 3);
	//ֻ����ⲿ����
	cv::findContours(canny_output, contours, hierarchy, CV_RETR_EXTERNAL,
		CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	if (contours.size()>500){
		return;
	}

	//����������
	vector<Moments> mu(contours.size());
	if (contours.size() <= 0){
		return;
	}
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	//��������������(����)
	int len = 0;			//��Ч���ĵĸ���
	for (int i = 0; i < contours.size(); i++){
		if (abs(mu[i].m00 - 0.0)>0.00001){
			len++;
		}
	}
	mc.resize(len);
	for (int i = 0,j = 0; i < contours.size(); i++,j++)
	{
		if (abs(mu[i].m00 - 0.0)<0.00001){
			j--;
			continue;
		}
		mc[j] = Point2f(mu[i].m10 / mu[i].m00, mu[i].m01 / mu[i].m00);

	}
	for (int i = 0; i < mc.size(); i++){
		float max_dis= 1e8;
		int x = i + 1;
		for (int j = i + 1; j < mc.size(); j++){
			int now_dis = sqrt(pow(mc[i].x - mc[j].x, 2) + pow(mc[i].y - mc[j].y, 2));
			if (max_dis > now_dis){
				max_dis = now_dis;
				x = j;
			}
		}
		if (x == i + 1) continue;
		Point2f temp_point = mc[x];
		mc[x] = mc[i+1];
		mc[i + 1] = temp_point;
	}
}