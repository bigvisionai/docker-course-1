#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>

#include "xtl/xbase64.hpp"
#include "xeus/xjson.hpp"

#include "matplotlibcpp.h"

namespace plt = matplotlibcpp;

namespace im
{
    struct image
    {   
        inline image(const std::string& filename)
        {
            std::ifstream fin(filename, std::ios::binary);   
            m_buffer << fin.rdbuf();
        }
        
        std::stringstream m_buffer;
    };
    
    xeus::xjson mime_bundle_repr(const image& i)
    {
        auto bundle = xeus::xjson::object();
        bundle["image/png"] = xtl::base64encode(i.m_buffer.str());
        return bundle;
    }
}
/* backup
auto displayImage(cv::Mat image){
    if (image.channels() < 3){
        cv::imwrite("tmp.png",image);
        cv::Mat newImage = cv::imread("tmp.png");
        plt::imshow(newImage);
        plt::save("tmp.png");
    } else {
        plt::save("tmp.png");
    }
    auto img = im::image("tmp.png");
    return img;
}
*/
auto displayImage(){
    plt::save("tmp.png");
    auto img = im::image("tmp.png");
    return img;
}

int min(int x, int y) {
    if(x < y) {
        return x;
    } else {
        return y;
    }
}

cv::Mat generateSampleGrayImage() {
    cv::Mat demoImage = cv::Mat::zeros(cv::Size(4,4),CV_8U);
    demoImage.at<uchar>(0,0) = 0.7003673*255;
    demoImage.at<uchar>(0,1) = 0.74275081*255;
    demoImage.at<uchar>(0,2) = 0.70928001*255;
    demoImage.at<uchar>(0,3) = 0.56674552*255;
    demoImage.at<uchar>(1,0) = 0.97778533*255;
    demoImage.at<uchar>(1,1) = 0.70633485*255;
    demoImage.at<uchar>(1,2) = 0.24791576*255;
    demoImage.at<uchar>(1,3) = 0.15788335*255;
    demoImage.at<uchar>(2,0) = 0.69769852*255;
    demoImage.at<uchar>(2,1) = 0.71995667*255;
    demoImage.at<uchar>(2,2) = 0.25774443*255;
    demoImage.at<uchar>(2,3) = 0.34154678*255;
    demoImage.at<uchar>(3,0) = 0.96876117*255;
    demoImage.at<uchar>(3,1) = 0.6945071*255;
    demoImage.at<uchar>(3,2) = 0.46638326*255;
    demoImage.at<uchar>(3,3) = 0.7028127*255;
    return demoImage;
}

cv::Mat generateSampleColorImage() {
    cv::Mat demoImage = cv::Mat::zeros(cv::Size(3,3),CV_8UC3);
    demoImage.at<cv::Vec3b>(0,0) = cv::Vec3b(0,100,0);
    demoImage.at<cv::Vec3b>(0,1) = cv::Vec3b(0,255,0);
    demoImage.at<cv::Vec3b>(0,2) = cv::Vec3b(255,0,0);
    demoImage.at<cv::Vec3b>(1,0) = cv::Vec3b(0,0,255);
    demoImage.at<cv::Vec3b>(1,1) = cv::Vec3b(255,100,0);
    demoImage.at<cv::Vec3b>(1,2) = cv::Vec3b(0,255,0);
    demoImage.at<cv::Vec3b>(2,0) = cv::Vec3b(255,0,0);
    demoImage.at<cv::Vec3b>(2,1) = cv::Vec3b(0,0,255);
    demoImage.at<cv::Vec3b>(2,2) = cv::Vec3b(0,100,255);
    return demoImage;
}

int getBilinearPixelGray(cv::Mat imArr, float posX, float posY) {
    std::vector<int> out;
    // Get integer and fractional parts of numbers
    float modXi = int(posX);
    float modYi = int(posY);
    float modXf = posX - modXi;
    float modYf = posY - modYi;
    float modXiPlusOneLim = min(modXi+1, imArr.rows-1);
    float modYiPlusOneLim = min(modYi+1, imArr.cols-1);

    // Get pixels in four corners
    float bottom_left = int(imArr.at<uchar>(modYi, modXi));
    float bottom_right = int(imArr.at<uchar>(modYi, modXiPlusOneLim));
    float top_left = int(imArr.at<uchar>(modYiPlusOneLim, modXi));
    float top_right = int(imArr.at<uchar>(modYiPlusOneLim, modXiPlusOneLim));
    float b = modXf*bottom_right + (1. - modXf)*bottom_left;
    float t = modXf*top_right + (1. - modXf)*top_left;
    float pxf = modYf*t + (1. - modYf)*b;

    return int(pxf+0.5); 
}

cv::Vec3b getBilinearPixelColor(cv::Mat imArr, float posX, float posY) {
    std::vector<int> out;
    // Get integer and fractional parts of numbers
    float modXi = int(posX);
    float modYi = int(posY);
    float modXf = posX - modXi;
    float modYf = posY - modYi;
    float modXiPlusOneLim = min(modXi+1, imArr.rows-1);
    float modYiPlusOneLim = min(modYi+1, imArr.cols-1);

    // Get pixels in four corners
    // Number of channels
    int no_of_channels = imArr.channels();
    float bottom_left;
    float bottom_right;
    float top_left;
    float top_right;
    float b,t,pxf;
    cv::Vec3b newColor = cv::Vec3b(0,0,0);

    for(int chan=0; chan<no_of_channels; chan++) {
        //std::cout << imArr.at<Vec3b>(modYi,modXi) << std::endl;
        bottom_left = int(imArr.at<Vec3b>(modYi, modXi)[chan]);
        bottom_right = int(imArr.at<Vec3b>(modYi, modXiPlusOneLim)[chan]);
        top_left = int(imArr.at<Vec3b>(modYiPlusOneLim, modXi)[chan]);
        top_right = int(imArr.at<Vec3b>(modYiPlusOneLim, modXiPlusOneLim)[chan]);
        b = modXf*bottom_right + (1. - modXf)*bottom_left;
        t = modXf*top_right + (1. - modXf)*top_left;
        pxf = modYf*t + (1. - modYf)*b;
        
        //std::cout << int(pxf+0.5) << std::endl;

        newColor[chan] = int(pxf+0.5);
    }
    return newColor;
}

void bilinearInterpolation(cv::Mat& inputImg, cv::Mat& outputImg, float scale=25){
    outputImg = inputImg.clone();
    if (outputImg.channels() == 4)
        cvtColor(outputImg,outputImg,COLOR_RGBA2BGR);
    if (outputImg.channels() == 3){
        outputImg = cv::Mat::zeros(Size(inputImg.cols * scale, inputImg.rows * scale), CV_8UC3);
        float rowScale = float(inputImg.rows)/outputImg.rows;
        float colScale = float(inputImg.cols)/outputImg.cols;
        for(float row=0.0; row<outputImg.rows; row++) {
            for(float col=0.0; col<outputImg.cols; col++) {
                float orir = row * rowScale;
                float oric = col * colScale;
                outputImg.at<cv::Vec3b>(row, col) = getBilinearPixelColor(inputImg, oric, orir);
                //std::cout << outputImg.at<Vec3b>(row, col) << std::endl;
            }
        }
    } else if (outputImg.channels() == 1) {
        outputImg = cv::Mat::zeros(Size(inputImg.cols * scale, inputImg.rows * scale), CV_8UC1);
        float rowScale = float(inputImg.rows)/outputImg.rows;
        float colScale = float(inputImg.cols)/outputImg.cols;
        for(float row=0.0; row<outputImg.rows; row++) {
            for(float col=0.0; col<outputImg.cols; col++) {
                float orir = row * rowScale;
                float oric = col * colScale;
                outputImg.at<uchar>(row, col) = getBilinearPixelGray(inputImg, oric, orir);
            }
        }
    }
}

auto displayImage(cv::Mat image){
    if (image.channels() < 3){
        cv::imwrite("tmp.png",image);
        cv::Mat newImage = cv::imread("tmp.png");
        plt::imshow(newImage);
        plt::save("tmp.png");
    } else {
        plt::save("tmp.png");
    }
    auto img = im::image("tmp.png");
    return img;
}

auto displayHist(cv::Mat image){
    if (image.channels() == 1){
        Mat tmp = image.reshape(1, image.rows * image.cols);
        std::vector<uchar> tmpData;
        tmpData.assign(tmp.data, tmp.data + tmp.total());
        plt::hist(tmpData);
        auto pltImg = displayImage();
        return pltImg;
    }
    else if (image.channels() == 3){
        std::vector<cv::Mat>channels;
        split(image,channels);
        std::vector<uchar> tmpData;
        Mat tmp;
        for (int i=0; i<3; i++){
            plt::subplot(1,3,i+1);
            tmp = channels[i].reshape(1, channels[i].rows * channels[i].cols);
            tmpData.assign(tmp.data, tmp.data + tmp.total());
            plt::hist(tmpData);
        }
        auto pltImg = displayImage();
        return pltImg;
    }
    auto pltImg = displayImage();
    return pltImg;
}
