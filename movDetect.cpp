#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

using namespace cv;

Mat processing(Mat frame){

    cvtColor(frame, frame, CV_RGB2GRAY);

    int dilation_size = 2;
        
    threshold(frame, frame, 30, 255, 0);
    dilate(frame, frame, getStructuringElement(MORPH_RECT, Size(1.5*dilation_size, 1.5*dilation_size), Point(dilation_size, dilation_size)) );

    return frame;

}

int main(){

    Mat frame1, frame2, result;

    Rect movarea, checkarea;

    int movement;
    int thresh = 500;

    int i, j;
    i, j = 0;
    
    int x0, y0;
    x0, y0 = 0; 
    int h, w;    

    VideoCapture vid(0);

    if(!vid.isOpened()){ 
        std::cout << "No webcam detected\n";
        return 1;
    }

    vid >> frame1;

    while(true){

        vid >> frame2;

        cvtColor(frame2-frame1, result, CV_RGB2GRAY);

        result = processing(frame2-frame1);
        movarea = boundingRect(result);

        if(2*movarea.area() >= (result.cols*result.rows)){
            
            Size size = result.size();

            resize(result, result, Size(100, 100), 2, 2);
            Rect checkarea = boundingRect(result);
            thresh = 100;

        }else checkarea = movarea;
    
        x0 = checkarea.x;
        y0 = checkarea.y;

        w = checkarea.width + x0;
        h = checkarea.height + y0;
        
        if(sum(result)[0]/255 > thresh){
            std::cout << "MOVING\n";
            rectangle(frame1, movarea, Scalar(255, 0, 0), 2);
        }else std::cout << std::endl;

        imshow("Original", frame1);

        movement = 0;

        if(waitKey(10) == 27) break;

        vid >> frame1;

    }

    return 0;
}