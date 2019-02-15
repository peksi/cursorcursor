//
//  Eyetracker.cpp
//  cursorcursor
//
//  Created by Robbert Groenendijk on 10/02/2019.
//

#include "Eyetracker.hpp"

using namespace cv;
using namespace ofxCv;

Eyetracker::Eyetracker() {
    cameraImage.allocate(1280, 720);
    grayscaleFrame.allocate(1280,720);

    eyeFinder.setup("haarcascade_eye.xml");
    eyeFinder.setPreset(ObjectFinder::Fast);
    eyeFinder.setRescale(0.25);
    eyeFinder.getTracker().setSmoothingRate(0.3);

}
void Eyetracker::setup() {

}
void Eyetracker::updateImage(ofImage _cameraImage) {
    cameraImage = _cameraImage;
    grayscaleFrame.setFromColorImage(cameraImage);
}

cv::Vec3f getEyeball(cv::Mat &eye, std::vector<cv::Vec3f> &circles)
{
    std::vector<int> sums(circles.size(), 0);
    for (int y = 0; y < eye.rows; y++)
    {
        uchar *ptr = eye.ptr<uchar>(y);
        for (int x = 0; x < eye.cols; x++)
        {
            int value = static_cast<int>(*ptr);
            for (int i = 0; i < circles.size(); i++)
            {
                cv::Point center((int)std::round(circles[i][0]), (int)std::round(circles[i][1]));
                int radius = (int)std::round(circles[i][2]);
                if (std::pow(x - center.x, 2) + std::pow(y - center.y, 2) < std::pow(radius, 2))
                {
                    sums[i] += value;
                }
            }
            ++ptr;
        }
    }
    int smallestSum = 9999999;
    int smallestSumIndex = -1;
    for (int i = 0; i < circles.size(); i++)
    {
        if (sums[i] < smallestSum)
        {
            smallestSum = sums[i];
            smallestSumIndex = i;
        }
    }
    return circles[smallestSumIndex];
}

cv::Rect getLeftmostEye(std::vector<cv::Rect> &eyes)
{
    int leftmost = 99999999;
    int leftmostIndex = -1;
    for (int i = 0; i < eyes.size(); i++)
    {
        if (eyes[i].tl().x < leftmost)
        {
            leftmost = eyes[i].tl().x;
            leftmostIndex = i;
        }
    }
    return eyes[leftmostIndex];
}

std::vector<cv::Point> centers;
cv::Point lastPoint;
cv::Point mousePoint;

cv::Point stabilize(std::vector<cv::Point> &points, int windowSize)
{
    float sumX = 0;
    float sumY = 0;
    int count = 0;
    for (int i = std::max(0, (int)(points.size() - windowSize)); i < points.size(); i++)
    {
        sumX += points[i].x;
        sumY += points[i].y;
        ++count;
    }
    if (count > 0)
    {
        sumX /= count;
        sumY /= count;
    }
    return cv::Point(sumX, sumY);
}


void Eyetracker::drawHelpers() {
    for (int i = 0; i < eyeFinder.size(); i++) {
        ofRectangle object = eyeFinder.getObjectSmoothed(i);
        
        ofPath eyeBox;
        eyeBox.setColor(ofColor(0,255,0));
        eyeBox.setStrokeWidth(5);
        eyeBox.setFilled(false);
        eyeBox.rectangle(object.x, object.y, object.width, object.height);
        //        eyeBox.draw();
    }


    ofDrawCircle(irisPoint + irisBoxOffset, irisRadius);
}

void Eyetracker::updateDetectedEyes() {
    eyeFinder.update(cameraImage);


    if(eyeFinder.size() == 2){ // was > 0
        vector<cv::Rect> passVector;
        
        for (int i = 0; i < eyeFinder.size(); i++) {
            cv::Rect tempRect = toCv(eyeFinder.getObjectSmoothed(i));
            passVector.push_back(tempRect);
        }
        
        cv::Rect object = getLeftmostEye(passVector);

        // thanks of, but it's openCV for now
        cv::Mat imageMat = toCv(grayscaleFrame);
        
        cv::Rect roi = object;
        cv::Mat roiImg = imageMat(roi);
        cv::equalizeHist(roiImg, roiImg);
        
        std::vector<cv::Vec3f> circles;
        cv::HoughCircles(roiImg, circles, CV_HOUGH_GRADIENT, 1, roiImg.cols / 8, 250, 15, roiImg.rows / 8, roiImg.rows / 3);

        for (int i = 0; i < circles.size(); i++) {
            cout << circles[i] << endl;
        }
        
        if(circles.size() > 0){
            std::vector<cv::Point> centers;
            cv::Vec3f eyeball = getEyeball(roiImg, circles); // choose the circle that contains more "black" pixels in it
            cv::Point center(eyeball[0], eyeball[1]);
            centers.push_back(center);
            center = stabilize(centers, 5);
            if (centers.size() > 1)
            {
                cv::Point diff;
                diff.x = (center.x - lastPoint.x) * 20;
                diff.y = (center.y - lastPoint.y) * -30;
                mousePoint += diff;
            }
            lastPoint = center;
            irisRadius = (int)eyeball[2];
            
            
            irisPoint = toOf(center);
            irisBoxOffset = toOf(roi.tl());
//
            
        }
    }
}
