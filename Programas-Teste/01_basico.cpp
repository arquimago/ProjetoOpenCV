#include<opencv2/highgui/highgui.hpp>
//gcc -o  01_basico` 01_basico.cpp




using namespace cv;

int main()
{
    Mat img = imread("fruits.jpg",CV_LOAD_IMAGE_COLOR);
    imshow("opencvtest",img);
    waitKey(0);

    return 0;
}
