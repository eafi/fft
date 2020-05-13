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

//    cv::Mat low(cv::Size(1000,1000),CV_32FC1);
//    fourier::ideal_lowfilter(low,5);
//    cv::imshow("low",low);



    cv::waitKey(0);
    return 0;
}
