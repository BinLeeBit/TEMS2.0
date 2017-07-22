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
	//定义提取有用直线时的阈值
	float threshold = 0.1;
	Mat srcImage = src.clone();
	Mat midImage, dstImage;
	//对原始图像进行平滑操作
	cv::blur(srcImage, srcImage, cv::Size(3, 3));
	//对图像进行canny边缘检测
	Canny(srcImage, midImage, 30, 200, 3);
	//将边缘检测的图像转为灰度图
	cvtColor(midImage, dstImage, CV_GRAY2BGR);

	//定义一个存放直线的矢量集合
	vector<Vec2f> lines;
	//进行霍夫变换
	HoughLines(midImage, lines, 1, CV_PI / 180, 150, 0, 0);

	sort(lines.begin(), lines.end(), cmp);
	//从获取的直线集合中提取有用的直线
	//定义临时变量表示直线距离综合以及有用的直线的总数
	float Temp_Sum = 0;
	int Temp_Num = 0;
	//定义直线之间距离的平均值
	float Distance_Avg = 0;
	for (int i = 1; i < lines.size(); i++)
	{
		float judge = abs(lines[i][1] - lines[i - 1][1]);
		//去除斜率偏差大的直线
		if (judge < 0.001)
		{
			Temp_Sum += abs(lines[i][0] - lines[i - 1][0]);
			Temp_Num++;
		}
	}

	//计算直线之间距离的平均值
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
		//去除直线间距离值偏差大的直线
		if (judge < threshold*Distance_Avg)
		{
			Temp_Sum += gap;
			Temp_Num++;
		}
	}
	//计算最终的直线之间的距离
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
	//将图像转为灰度图
	cvtColor(src, srcImage, COLOR_BGR2GRAY);
	//图像的平滑操作
	blur(srcImage, image, Size(3, 3));
	//图像二值化
	threshold(image, image, 0, 255, CV_THRESH_OTSU);
	//imshow("Threshold Image", image);

	//保存轮廓的vector
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//轮廓检测
	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());
	//Mat imageContours = Mat::zeros(image.size(), CV_8UC1); //最小外接矩形画布  
	for (int i = 0; i < contours.size(); i++)
	{
		//绘制轮廓  
		//drawContours(imageContours, contours, i, Scalar(255), 1, 8, hierarchy);

		//绘制轮廓的最小外结矩形  
		RotatedRect rect = minAreaRect(contours[i]);
		Point2f P[4];
		rect.points(P);
		float lens[4];//记录边长的数据
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
	//将图像转为灰度图
	cvtColor(src, srcImage, COLOR_BGR2GRAY);
	//图像的平滑操作
	blur(srcImage, image, Size(3, 3));
	//图像二值化
	threshold(image, image, 0, 255, CV_THRESH_OTSU);
	//imshow("Threshold Image", image);

	//保存轮廓的vector
	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;
	//轮廓检测
	findContours(image, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_NONE, Point());
	//Mat imageContours = Mat::zeros(image.size(), CV_8UC1); //最小外接矩形画布  
	for (int i = 0; i < contours.size(); i++)
	{
		//绘制轮廓  
		//drawContours(imageContours, contours, i, Scalar(255), 1, 8, hierarchy);

		//绘制轮廓的最小外结矩形  
		RotatedRect rect = minAreaRect(contours[i]);
		Point2f P[4];
		rect.points(P);
		float lens[4];//记录边长的数据
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
	Mat _src = src.clone();		//待处理原图(必须是灰度图)
	int thresh = 40;
	if (_src.type() != 0){		//如果不是灰度图转换为灰度图
		cv::cvtColor(_src, _src, CV_BGR2GRAY);
	}
	cv::threshold(_src, _src, BINARY_THRESH, 255, CV_THRESH_BINARY);//二值化

	//平滑处理
	cv::blur(_src, _src, cv::Size(3, 3));

	Mat canny_output;			//边缘检测结果
	std::vector<vector<Point> > contours;
	std::vector<Vec4i> hierarchy;

	cv::erode(_src, _src, NULL);//腐蚀
	cv::erode(_src, _src, NULL);//腐蚀
	cv::erode(_src, _src, NULL);
	cv::erode(_src, _src, NULL);
	cv::dilate(_src, _src, NULL);//膨胀
	cv::dilate(_src, _src, NULL);//膨胀
	cv::dilate(_src, _src, NULL);//膨胀
	cv::dilate(_src, _src, NULL);//膨胀

	//利用canny边缘检测
	cv::Canny(_src, canny_output, thresh, thresh * 2, 3);
	//只检查外部轮廓
	cv::findContours(canny_output, contours, hierarchy, CV_RETR_EXTERNAL,
		CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	if (contours.size()>500){
		return;
	}

	//计算轮廓矩
	vector<Moments> mu(contours.size());
	if (contours.size() <= 0){
		return;
	}
	for (int i = 0; i < contours.size(); i++)
	{
		mu[i] = moments(contours[i], false);
	}

	//计算轮廓的质心(重心)
	int len = 0;			//有效重心的个数
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