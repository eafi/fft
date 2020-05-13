//
// Created by Eafi Zhang on 2020/5/7.
//
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
#include "fft.h"

namespace fourier{
    /// fft transform spatial domain to frequency domain
    /// \param img
    /// \return
    cv::Mat fft(const cv::Mat& img)
    {
        cv::Mat tempImg = img.clone();
        cv::Size dftSize;
        dftSize.width = cv::getOptimalDFTSize(tempImg.cols*2-1);
        dftSize.height = cv::getOptimalDFTSize(tempImg.rows*2-1);
        cv::copyMakeBorder(tempImg,tempImg,0,dftSize.height - tempImg.rows,0,dftSize.width-tempImg.cols,
                           cv::BORDER_CONSTANT,cv::Scalar::all(0));
        cv::Mat planes[] = {cv::Mat_<float>(tempImg),cv::Mat::zeros(tempImg.size(),CV_32F)};
        cv::Mat complexI;
        cv::merge(planes,2,complexI);

        cv::dft(complexI,complexI);
        return complexI;
    }

    cv::Mat fft(const cv::Mat& img,const cv::Size &dftSize)
    {
        cv::Mat tempImg = img.clone();
        cv::copyMakeBorder(tempImg,tempImg,0,dftSize.height - tempImg.rows,0,dftSize.width-tempImg.cols,
                           cv::BORDER_CONSTANT,cv::Scalar::all(0));
        cv::Mat planes[] = {cv::Mat_<float>(tempImg),cv::Mat::zeros(tempImg.size(),CV_32F)};
        cv::Mat complexI;
        cv::merge(planes,2,complexI);

        cv::dft(complexI,complexI);
        return complexI;
    }


    cv::Mat idft(const cv::Mat& img)
    {
        cv::Mat inverseT;
        cv::Mat tempImg = img.clone();
        cv::dft(tempImg, inverseT, cv::DFT_INVERSE | cv::DFT_REAL_OUTPUT);
        std::cout<<inverseT.channels()<<std::endl;
        return inverseT;
    }

    void fftdisplay(const cv::Mat& img,const std::string& winname)
    {
        //实部和虚部都有
        cv::Mat cloneImg = img.clone();
        if(img.channels() == 2)
        {
            cv::Mat splitImg[2];
            cv::split(cloneImg,splitImg);
            cv::Mat mag,pha;
            cv::magnitude(splitImg[0],splitImg[1],mag);
            cv::phase(splitImg[0],splitImg[1],pha);
            fourier::fftlognormalize(mag);
            cv::imshow(winname+",magnitude",mag);
            fourier::fftlognormalize(pha);
            cv::imshow(winname+",pha",pha);
        }else if(img.channels() == 1) //只有实部
        {
            cv::normalize(cloneImg,cloneImg,0,1,cv::NORM_MINMAX); //映射到只在0~1范围
            cv::imshow(winname+",without phase angle",cloneImg);
        }

    }

    void fftlognormalize(cv::Mat &img)
    {
        img += cv::Scalar::all(1);
        cv::log(img,img);   //log(1+img)
        cv::normalize(img,img,0,1,cv::NORM_MINMAX); //映射到只在0~1范围
    }

    cv::Mat fftshift(cv::Mat& img)
    {

        int cx = img.cols/2;
        int cy = img.rows/2;
        cv::Mat q0(img, cv::Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
        cv::Mat q1(img, cv::Rect(cx, 0, cx, cy));  // Top-Right
        cv::Mat q2(img, cv::Rect(0, cy, cx, cy));  // Bottom-Left
        cv::Mat q3(img, cv::Rect(cx, cy, cx, cy)); // Bottom-Right
        cv::Mat tmp;
        q0.copyTo(tmp);
        q3.copyTo(q0);
        tmp.copyTo(q3);
        q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
        q2.copyTo(q1);
        tmp.copyTo(q2);
        return img;
    }

    void ideal_lowfilter(cv::Mat &ideallf,unsigned int d)
    {
        ideallf.zeros(ideallf.size(),CV_32FC1);
        //sub-rectangle of idealfw
        cv::Rect2i middleRect(ideallf.size().width/2-d/2,ideallf.size().height/2-d/2,d,d);
        cv::Mat subRect = ideallf(middleRect);
        int radii = d/2;
        d = std::pow(radii,2);
        for(int i=0;i<subRect.rows;++i)
        {
            for(int j=0;j<subRect.cols;++j)
            {
                int sum = std::pow(radii-i,2)+std::pow(radii-j,2);
                if(sum<(int)d)
                {
                    float* p = subRect.ptr<float>(i);
                    p[j] = 1.0f;
                }
            }
        }
    }

    cv::Mat abs(const cv::Mat& img)
    {
        cv::Mat splitImg[2];
        cv::split(img,splitImg);
        cv::magnitude(splitImg[0],splitImg[1],splitImg[0]);
        return splitImg[0];
    }

    cv::Mat angle(const cv::Mat& img)
    {
        cv::Mat splitImg[2];
        cv::split(img,splitImg);
        cv::phase(splitImg[0],splitImg[1],splitImg[0]);
        return splitImg[0];
    }

}


