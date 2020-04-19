#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace cv;

int main(){

    Mat frame1;
    Mat frame2;
    Mat result, greyresult;

    int movement;
    int tresh = 50;

    VideoCapture vid(0);

    if(!vid.isOpened()){ 
        std::cout << "No webcam detected\n";
        return 1;
    }

    while(true){

        vid >> frame1;
        vid >> frame2;

        result = frame2 - frame1;

        cvtColor(result, greyresult, CV_RGB2GRAY);

        imshow("Direct Input", frame1);
        imshow("Direct Subtraction", result);
        imshow("Grey Subtraction", greyresult);

        for(int i=0; i<greyresult.rows; i++)
            for(int j=0; j<greyresult.cols; j++)
                if(greyresult.at<uchar>(i,j) > 50) movement++; 
        
        if(movement > tresh) std::cout << "MOVING\n";
        else std::cout << std::endl;

        movement = 0;

        if(waitKey(100) == 27) break;

    }

    return 0;
}