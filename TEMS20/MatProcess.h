#ifndef MATPROCESS_H
#define MATPROCESS_H

#include <iostream> 
#include <opencv2\core\core.hpp>
#include <opencv\cv.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

//定义最小有效点间距
#define MIN_USEFUL_POINT_D 10
#define BINARY_THRESH 80

using namespace cv;

class MatProcess
{
public:
	MatProcess();
	MatProcess(const cv::Mat &src);
	~MatProcess();
	/**
	*	@brief	选区衍射(SAD)
	*/
	void SAD();

	/**
	*	@brief	高分辨像(HRF)
	*/
	void HRF();

	/**
	*	@brief	明场像(BF)
	*/
	void BF();

	/**
	*	@brief	暗场像(DF)
	*/
	void DF();

private:
	/**
	*	@brief	求连通域的重心
	*	@param	图中所有轮廓的重心
	*/
	void FindBarycenter(std::vector<Point2f> &mc);
	
public:
	double distance;		//距离

private:
	cv::Mat src;			//原图像
};
#endif