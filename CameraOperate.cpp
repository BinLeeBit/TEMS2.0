#include "CameraOperate.h"

CameraOperate::CameraOperate()
{
    Id = 0;
    is_Open = false;
    timer = new QTimer();
}

CameraOperate::CameraOperate(const int id)
{
    Id = id;
    is_Open = false;
    timer = new QTimer();
}

CameraOperate::~CameraOperate()
{
    capture.release();
}

bool CameraOperate::OpenCamera()
{
    capture = cv::VideoCapture(Id);
    if (!capture.isOpened()){
        return false;
    }
    is_Open = !is_Open;
    return true;
}

bool CameraOperate::CloseCamera()
{
    if (!capture.isOpened()){
        return false;
    }
    capture.release();
    is_Open = !is_Open;
    return true;
}

bool CameraOperate::isOpen()
{
    return is_Open;
}

bool CameraOperate::SavePicture(std::string filePath)
{
    return false;
}
