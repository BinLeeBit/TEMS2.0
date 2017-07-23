#ifndef CAMERAOPERATE_H
#define CAMERAOPERATE_H
#include <opencv2\opencv.hpp>
#include <iostream>
//#include <filesystem>
#include <qtimer.h>

class CameraOperate
{
private:
    int Id;					//摄像机编号
    bool is_Open;			//摄像机是否打开
public:
    QTimer *timer;			//摄像机打开计时
    cv::VideoCapture capture;//摄像机

    CameraOperate();
    CameraOperate(const int id);
    ~CameraOperate();

    //打开摄像机
    bool OpenCamera();
    //关闭摄像机
    bool CloseCamera();
    //摄像机当前的状态：true为打开，false为关闭
    bool isOpen();

    /**
    *	@brief	保存当前帧图片
    *	@param	保存路径
    *	@return 打开是否成功
    */
    bool SavePicture(std::string filePath);
};

#endif // CAMERAOPERATE_H
