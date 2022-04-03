//
//  OpenCVCode.cpp
//  MacOS
//
//  Created by AmolChaudhry on 02/08/19. 
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <raspicam_cv.h>
#include <chrono>
#include <ctime>
#include <wiringPi.h>

using namespace std;
using namespace cv;
using namespace raspicam;

Mat matrix;
Mat frame, persFrame, greyscaleFrame, thresholdFrame, edgeOfFrame, finalFrame, finalFrameDup, finalFrameDup1;
Mat interestedRegionLane, interestedRegionLaneEnd;
int laneLeftPosition, laneRightPositon;
int centreOfFrame, centreOfLane, result, endOfLane;
RaspiCam_Cv liveCamera;
stringstream bufferStream;

//Declaring histogram Lanes.
vector<int> histLane;
vector<int> histLaneEnd;

//Points for region of interest.
Point2f src[] = {Point2f(36,130), Point2f(353,130), Point2f(0,179), Point2f(392,179)};
//Points for perspective view.
Point2f destination[] = {Point2f(95,0),Point2f(273,0), Point2f(95,236), Point2f(273,236)};

void CaptureFrame()
{
    liveCamera.grab();
    liveCamera.retrieve(frame);
    cvtColor(frame, frame, COLOR_BGR2RGB);
}

void GetPerspective()
{
    line(frame,src[0], src[1], Scalar(0,0,255), 2);
    line(frame,src[1], src[3], Scalar(0,0,255), 2);
    line(frame,src[3], src[2], Scalar(0,0,255), 2);
    line(frame,src[2], src[0], Scalar(0,0,255), 2);
    
    matrix = getPerspectiveTransform(src, destination);
    warpPerspective(frame, persFrame, matrix, Size(405,250));
}

void GetThreshold()
{
    cvtColor(persFrame, greyscaleFrame, COLOR_RGB2GRAY);
    inRange(greyscaleFrame, 230, 255, thresholdFrame);
    Canny(greyscaleFrame,edgeOfFrame, 650, 720, 3, false);
    add(thresholdFrame, edgeOfFrame, finalFrame);
    cvtColor(finalFrame, finalFrame, COLOR_GRAY2RGB);
    cvtColor(finalFrame, finalFrameDup, COLOR_RGB2BGR);
    cvtColor(finalFrame, finalFrameDup1, COLOR_RGB2BGR);
    
}

void GetHistrogram()
{
    histLane.resize(405);
    histLane.clear();
    
    for(int i=0; i<405; i++) {       //As frame.size().width = 405
        interestedRegionLane = finalFrameDup(Rect(i,140,1,100));
        divide(255, interestedRegionLane, interestedRegionLane);
        histLane.push_back((int)(sum(interestedRegionLane)[0]));
    }
    
    histLaneEnd.resize(405);
    histLaneEnd.clear();
    for (int i = 0; i < 405; i++) {
        interestedRegionLaneEnd = finalFrameDup1(Rect(i, 0, 1, 250));
        divide(255, interestedRegionLaneEnd, interestedRegionLaneEnd);
        histLaneEnd.push_back((int)(sum(interestedRegionLaneEnd)[0]));
    }
    endOfLane = sum(histLaneEnd)[0];
    cout<<"End of Lane= "<<endOfLane<<endl;
}

 void SetupCamera (int argc, char **argv, RaspiCam_Cv &liveCamera)
{
    liveCamera.set(CAP_PROP_FRAME_WIDTH, ("-w", argc, argv, 405));
    liveCamera.set(CAP_PROP_FRAME_HEIGHT, ("-h", argc, argv, 250));
    liveCamera.set(CAP_PROP_BRIGHTNESS, ("-br", argc, argv, 50));
    liveCamera.set(CAP_PROP_CONTRAST , ("-co", argc, argv, 50));
    liveCamera.set(CAP_PROP_SATURATION, ("-sa", argc, argv, 50));
    liveCamera.set(CAP_PROP_GAIN, ("-g", argc, argv , 50));
    liveCamera.set(CAP_PROP_FPS, ("-fps", argc, argv, 0));
}

void GetLaneCentre()
{
    centreOfLane = (laneRightPositon - laneLeftPosition)/2 + laneLeftPosition;
    centreOfFrame = 188;
    line(finalFrame, Point2f(centreOfLane,0), Point2f(centreOfLane,250), Scalar(0,255,0), 3);
    line(finalFrame, Point2f(centreOfFrame,0), Point2f(centreOfFrame,250), Scalar(255,0,0), 3);
    result = centreOfLane - centreOfFrame;
}

void FindLane()
{
    vector<int>::iterator leftIter;
    vector<int>::iterator rightIter;
    
    leftIter = max_element(histLane.begin(), histLane.begin() + 150);
    laneLeftPosition = distance(histLane.begin(), leftIter);
    rightIter = max_element(histLane.begin() +250, histLane.end());
    laneRightPositon = distance(histLane.begin(), rightIter);
    line(finalFrame, Point2f(laneLeftPosition, 0), Point2f(laneLeftPosition, 250), Scalar(0, 255,0), 2);
    line(finalFrame, Point2f(laneRightPositon, 0), Point2f(laneRightPositon, 250), Scalar(0,255,0), 2);
}

int main(int argc,char **argv)
{
    wiringPiSetup();
    
    pinMode(21, OUTPUT);
    pinMode(22, OUTPUT);
    pinMode(23, OUTPUT);
    pinMode(24, OUTPUT);
    
    SetupCamera(argc, argv, liveCamera);
    cout<<"Connecting to cam"<<endl;
    if (!liveCamera.open()) {
        cout<<"Cam connection failed"<<endl;
    }
    cout<<"Cam Id = "<<liveCamera.getId()<<endl;
     
    while(true) {
        auto startTime = std::chrono::system_clock::now();

        CaptureFrame();
        GetPerspective();
        GetThreshold();
        GetHistrogram();
        FindLane();
        GetLaneCentre();
    
        if (endOfLane > 3000) {
            digitalWrite(21, 1);
            digitalWrite(22, 1);    //decimal = 7
            digitalWrite(23, 1);
            digitalWrite(24, 0);
            cout<<"Lane End"<<endl;
        }
        
        if (result == 0) {
            digitalWrite(21, 0);
            digitalWrite(22, 0);    //decimal = 0
            digitalWrite(23, 0);
            digitalWrite(24, 0);
            cout<<"Frwd"<<endl;
        }
        else if (result >0 && result <10) {
            digitalWrite(21, 1);
            digitalWrite(22, 0);    //decimal = 1
            digitalWrite(23, 0);
            digitalWrite(24, 0);
            cout<<"RightLevel1"<<endl;
        }
        else if (result >=10 && result <20) {
            digitalWrite(21, 0);
            digitalWrite(22, 1);    //decimal = 2
            digitalWrite(23, 0);
            digitalWrite(24, 0);
            cout<<"RightLevel2"<<endl;
        }
        else if (result >20) {
            digitalWrite(21, 1);
            digitalWrite(22, 1);    //decimal = 3
            digitalWrite(23, 0);
            digitalWrite(24, 0);
            cout<<"RightLevel3"<<endl;
        }
        else if (result <0 && result >-10) {
            digitalWrite(21, 0);
            digitalWrite(22, 0);    //decimal = 4
            digitalWrite(23, 1);
            digitalWrite(24, 0);
            cout<<"LeftLevel1"<<endl;
        }
        else if (result <=-10 && result >-20) {
            digitalWrite(21, 1);
            digitalWrite(22, 0);    //decimal = 5
            digitalWrite(23, 1);
            digitalWrite(24, 0);
            cout<<"LeftLevel2"<<endl;
        }
        else if (result <-20) {
            digitalWrite(21, 0);
            digitalWrite(22, 1);    //decimal = 6
            digitalWrite(23, 1);
            digitalWrite(24, 0);
            cout<<"LeftLevel3"<<endl;
        }
    
        if (endOfLane > 3000) {
            bufferStream.str(" ");
            bufferStream.clear();
            bufferStream<<"Lane End";
            putText(frame, bufferStream.str(), Point2f(1,50), 0,1, Scalar(255,0,0), 2);
        }
        else if (result == 0) {
            bufferStream.str(" ");
            bufferStream.clear();
            bufferStream<<"result = "<<result<<" Move Frwd";
            putText(frame, bufferStream.str(), Point2f(1,50), 0,1, Scalar(0,0,255), 2);
        }
        else if (result > 0) {
            bufferStream.str(" ");
            bufferStream.clear();
            bufferStream<<"result = "<<result<<"Move Right";
            putText(frame, bufferStream.str(), Point2f(1,50), 0,1, Scalar(0,0,255), 2);
        }
        else if (result < 0) {
            bufferStream.str(" ");
            bufferStream.clear();
            bufferStream<<"result = "<<result<<" Move Left";
            putText(frame, bufferStream.str(), Point2f(1,50), 0,1, Scalar(0,0,255), 2);
        }
    
        namedWindow("orignal", WINDOW_KEEPRATIO);
        moveWindow("orignal", 0, 100);
        resizeWindow("orignal", 640, 480);
        imshow("orignal", frame);
    
        namedWindow("perspective", WINDOW_KEEPRATIO);
        moveWindow("perspective", 640, 100);
        resizeWindow("perspective", 640, 480);
        imshow("perspective", persFrame);
        
        namedWindow("final", WINDOW_KEEPRATIO);
        moveWindow("final", 1280, 100);
        resizeWindow("final", 640, 480);
        imshow("final", finalFrame);
    
        waitKey(1);
        auto endTime = std::chrono::system_clock::now();
        std::chrono::duration<double> secondsPassed = endTime - startTime;
    
        float t = secondsPassed.count();
        int FPS = 1/t;
    }
    return 0;
}
