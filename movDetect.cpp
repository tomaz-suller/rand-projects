#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace cv;

Mat processing(Mat frame){

    cvtColor(frame, frame, CV_RGB2GRAY);

    int dilation_size = 4;
        
    threshold(frame, frame, 50, 255, 0);
    dilate(frame, frame, getStructuringElement(MORPH_RECT, Size(1.5*dilation_size, 1.5*dilation_size), Point(dilation_size, dilation_size)) );

    return frame;

}

int main(){

    Mat frame1, fgm1;
    Mat frame2, fgm2;
    Mat result;

    int movement;
    int tresh = 250;
    VideoCapture vid(0);

    if(!vid.isOpened()){ 
        std::cout << "No webcam detected\n";
        return 1;
    }

    vid >> frame1;

    while(true){

        vid >> frame2;

        result = processing(frame2-frame1);
        Rect movarea = boundingRect(result);

        for(int i = movarea.y; i < movarea.height + movarea.y; i++)
            for(int j = movarea.x; j < movarea.width + movarea.x; j++)
                if(result.at<uchar>(i,j) > 0) movement++;
        
        if(movement > tresh){
            std::cout << "MOVING\n";
            rectangle(frame1, movarea, Scalar(255, 0, 0), 2);
        }else std::cout << std::endl;

        imshow("Original", frame1);
        
        rectangle(result, movarea, Scalar(255, 0, 0));
        imshow("Processing", result);

        vid >> frame1;
        movement = 0;

        if(waitKey(10) == 27) break;

    }

    return 0;
}