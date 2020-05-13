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


    cv::Mat ifftImori = fourier::idft(fourier::fftshift(fftImori));
    fourier::fftdisplay(ifftImori,"ifftImori");

    cv::Mat mag = fourier::abs(fftImori);
    cv::Mat pha = fourier::angle(fftImori);
    fourier::fftlognormalize(mag);
    fourier::fftlognormalize(pha);
    cv::imshow("magnitude",mag);
    cv::imshow("phase angle",pha);
   // cv::imshow("ifftImori",ifftImori);

//    cv::Mat low(cv::Size(1000,1000),CV_32FC1);
//    fourier::ideal_lowfilter(low,5);
//    cv::imshow("low",low);



    cv::waitKey(0);
    return 0;
}
