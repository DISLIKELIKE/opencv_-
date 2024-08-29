#include "mainwindow.h"
#include<opencv2/opencv.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include <QApplication>
#include<QDebug>
using namespace cv;

int main(int argc, char *argv[])
{
    // 读取图像
    Mat img, templ, result,dst;
    img = imread("C:/Users/31133/Desktop/002.png",IMREAD_COLOR);
    templ = imread("C:/Users/31133/Desktop/001.png",IMREAD_COLOR);

    //检查图像是否成功加载
    if(img.empty() || templ.empty() )
    {
        qDebug()<<"Could not read the images";
    }


    int result_cols =img.cols - templ.cols  + 1;
    int result_rows =img.rows - templ.rows + 1;
    result.create(result_cols, result_rows, CV_32FC3);

    // 使用模板匹配
    matchTemplate(img, templ, result, TM_SQDIFF_NORMED);//这里我们使用的匹配算法是标准平方差匹配 method=CV_TM_SQDIFF_NORMED，数值越小匹配度越好
    normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());

    double minVal = -1;
    double maxVal;
    Point minLoc;
    Point maxLoc;
    Point matchLoc;
    qDebug()<< "匹配度：" << minVal ;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat());


    qDebug()<<"匹配度：" << minVal ;

    matchLoc = minLoc;

    //阈值判别，小于0.01才认为匹配成功，才将头像框出来
    if (minVal < 0.001)
    {
        rectangle(img, matchLoc, Point(matchLoc.x + templ.cols, matchLoc.y + templ.rows), Scalar(0, 255, 0), 2, 8, 0);
    }

    imshow("result", result);

    //在原始图像上绘制矩形
    img.copyTo(dst);
    rectangle(dst,Rect(matchLoc.x,matchLoc.y,templ.cols,templ.rows),Scalar(0,0,255),2);
    //显示结果
    imshow("output",dst);

    waitKey(0);

    return 0;
}
