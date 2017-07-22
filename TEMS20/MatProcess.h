#ifndef MATPROCESS_H
#define MATPROCESS_H

#include <iostream> 
#include <opencv2\core\core.hpp>
#include <opencv\cv.hpp>
#include <opencv2\opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

//������С��Ч����
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
	*	@brief	ѡ������(SAD)
	*/
	void SAD();

	/**
	*	@brief	�߷ֱ���(HRF)
	*/
	void HRF();

	/**
	*	@brief	������(BF)
	*/
	void BF();

	/**
	*	@brief	������(DF)
	*/
	void DF();

private:
	/**
	*	@brief	����ͨ�������
	*	@param	ͼ����������������
	*/
	void FindBarycenter(std::vector<Point2f> &mc);
	
public:
	double distance;		//����

private:
	cv::Mat src;			//ԭͼ��
};
#endif