//
// Created by Eafi Zhang on 2020/5/7.
//

#ifndef LOWFILTER_FFT_H
#define LOWFILTER_FFT_H
namespace fourier{
    ///自适应尺寸的快速傅立叶变换
    /// \param img 单通道8U图像
    /// \return 双通道32F图像，分别存储复数的实部和虚部
    cv::Mat fft(const cv::Mat&img);

    ///自定义尺寸的快速傅立叶变换
    /// \param img 单通道8U图像
    /// \return 双通道32F图像，分别存储复数的实部和虚部
    cv::Mat fft(const cv::Mat& img,const cv::Size &dftSize);

    ///傅立叶逆变换
    /// \param img 双通道32F图像，分别存储复数的实部和虚部
    /// \return 只包含实数部分的单通道32F图像
    cv::Mat idft(const cv::Mat&);

    ///显示谱图和相位角图或谱图,取决于传入的图像
    /// \param img 由上述函数计算出来的任意返回值，不区分单、双通道显示
    /// \param winname winname
    void fftdisplay(const cv::Mat& img,const std::string& winname);

    ///内嵌均一化函数，该函数就地运算，对原图取对数后压缩到0~1显示范围
    /// \param img 由fft计算出的复杂矩阵
    void fftnormalize(cv::Mat& img);

    ///就地产生理想低通滤波器
    /// \param ideallf 就地产生的图像,其必须指定类型为32FC1和目标尺寸
    /// \param d 指定低通滤波器截止频率
    void ideal_lowfilter(cv::Mat &ideallf,unsigned int d);


    /// 频域居中
    /// \param img
    void fftshift(cv::Mat& img);
}

#endif //LOWFILTER_FFT_H
