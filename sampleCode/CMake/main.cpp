#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(){
    
    // Testing the OpenCV installation
    cout << "Hello, World!" << endl;
    cout << "OpenCV version : " << CV_VERSION << endl;
    cout << "Major version : " << CV_MAJOR_VERSION << endl;
    cout << "Minor version : " << CV_MINOR_VERSION << endl;
    cout << "Subminor version : " << CV_SUBMINOR_VERSION << endl;

    Mat testImage = imread("../Extras/Quick_brown_fox.png");
    
    bitwise_not(testImage, testImage);
    
    imwrite("Inverted-Quick_brown_fox.png", testImage);

    return 0;
}
