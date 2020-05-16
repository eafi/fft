#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "fft.h"

int main() {

    cv::Mat imori = cv::imread("imori.jpg",cv::IMREAD_GRAYSCALE);
    cv::imshow("origin",imori);
    cv::Mat fftImori = fourier::fft(imori);
    fourier::fftshift(fftImori);
    fourier::fftdisplay(fftImori,"fftImori");

  //  cv::imshow("ffshift",fourier::fftshift(fftImori));

    cv::Mat idellf(fftImori.size(),CV_32F); //必须强调低通滤波器的尺寸
    fourier::ideal_lowfilter(idellf,30); //创建截止频率30的滤波器
    cv::Mat mult;
    cv::mulSpectrums(fftImori,idellf,mult,0); //OpenCV内建,fft结果与低通滤波器相乘,返回结果到mult
    fourier::fftdisplay(mult,"mu"); //以频谱和相位角图显示滤波结果
    cv::Mat ifftImori = fourier::idft(fourier::fftshift(mult)); //将结果由频率域向空间域转化
    cv::imshow("filtering",ifftImori(cv::Rect(0,0,imori.cols,imori.rows)));
    //从两倍尺寸向原始尺寸裁剪并显示

    cv::waitKey(0);
    return 0;
}
