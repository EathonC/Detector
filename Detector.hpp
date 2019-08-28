#ifndef _DETECTOR_HPP_
#define _DETECTOR_HPP_

#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/imgproc/imgproc_c.h>
using namespace std;
using namespace cv;

class Detector
{
private:
	Mat _img;
	vector<Point> _points;
public:
	void set_img(Mat &img);
	vector<Point> detect();
	void print();
};
#endif // !DETECTOR_HPP
#pragma once
