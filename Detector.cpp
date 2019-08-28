#include"pch.h"
#include"Detector.hpp"
#include<iostream>
#include<vector>
#include<opencv2/opencv.hpp>
#include<opencv2/core.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/imgproc/imgproc_c.h>
using namespace std;
using namespace cv;

void Detector::set_img(Mat &img)
{
	_img = img;
}
vector<Point> Detector::detect()
{
	vector<Point> flags;
	int rows = _img.rows;
	int cols = _img.cols;
	for (int i = rows / 10; i < rows * 9 / 10; i++)
	{
		for (int j = cols / 10; j < cols * 9 / 10; j++)
		{
			Point a(i, j);
			if (_img.at<Vec3b>(i, j).val[1] <= 50 && _img.at<Vec3b>(i, j).val[2] <= 50)	//blue
			{
				flags.push_back(a);
				_img.at<Vec3b>(i, j).val[0] = 255; _img.at<Vec3b>(i, j).val[1] = 255; _img.at<Vec3b>(i, j).val[2] = 255;
			}
		}
	}
	if (flags.empty())		cout << "empty" << endl;
	else
	{
		vector<Point>::iterator it;
		/*for (it = flags.begin(); it != flags.end(); it++)
		{
			cout << it->x << " " << it->y << endl;
		}*/
		Point circle((flags.front().x + flags.back().x) / 2, (flags.front().y + flags.back().y) / 2);
		_points.push_back(circle);
	}
	flags.clear();
	for (int i = rows / 10; i < rows * 9 / 10; i++)
	{
		for (int j = cols / 10; j < cols * 9 / 10; j++)
		{
			Point a(i, j);
			if (_img.at<Vec3b>(i, j).val[0] <= 50 && _img.at<Vec3b>(i, j).val[1] >= 200 && _img.at<Vec3b>(i, j).val[1] <= 255 && _img.at<Vec3b>(i, j).val[2] >= 200 && _img.at<Vec3b>(i, j).val[2] <= 255)		//yellow
			{
				flags.push_back(a);
				_img.at<Vec3b>(i, j).val[0] = 255; _img.at<Vec3b>(i, j).val[1] = 255; _img.at<Vec3b>(i, j).val[2] = 255;
			}
		}
	}
	if (flags.empty())		cout << "empty" << endl;
	else
	{
		/*vector<Point>::iterator it;
		for (it = flags.begin(); it != flags.end(); it++)
		{
			cout << it->x << " " << it->y << endl;
		}*/
		Point rectangle((flags.front().x + flags.back().x) / 2, (flags.front().y + flags.back().y) / 2);
		_points.push_back(rectangle);
	}
	flags.clear();
	for (int i = rows / 10; i < rows * 9 / 10; i++)
	{
		for (int j = cols / 10; j < cols * 9 / 10; j++)
		{
			Point a(i, j);
			if (_img.at<Vec3b>(i, j).val[0] <= 90 && _img.at<Vec3b>(i, j).val[1] <= 90)		//red
			{
				flags.push_back(a);
				_img.at<Vec3b>(i, j).val[0] = 255; _img.at<Vec3b>(i, j).val[1] = 255; _img.at<Vec3b>(i, j).val[2] = 255;
			}
		}
	}
	if (flags.empty())		cout << "empty" << endl;
	else
	{
		vector<Point>::iterator it;
		/*for (it = flags.begin(); it != flags.end(); it++)
		{
			cout << it->x << " " << it->y << endl;
		}*/
		int l, r = flags.back().y;
		for (it = flags.begin(); it != flags.end(); it++)
		{
			if (it->x == flags.back().x)
			{
				l = it->y;
				break;
			}
		}
		//Point triangle(((flags.back().x - flags.front().x)*(flags.back().x - flags.front().x) + (r - l)*(r - l) / 4) / (2 * (flags.back().x - flags.front().x)) + flags.front().x, (l + r) / 2);		//三角形的中心（重心）的y应该是这个公式
		Point triangle((flags.back().x - flags.front().x) / 2+flags.front().x, (l + r) / 2);		//但是根据答案y取的是高的一半
		_points.push_back(triangle);
	}
	return _points;
}
void Detector::print()
{
	vector<Point>::iterator it;
	int i = 0;
	for (it = _points.begin(); it != _points.end(); it++)
	{
		if (i == 0)	cout << "圆的中心坐标: ";
		else if (i == 1)	cout << "矩形的中心坐标: ";
		else if (i == 2)	cout << "三角形的中心坐标: ";
		i++;
		cout << "X轴(col): " << it->y << " " << "Y轴(row): " << it->x << endl;
	}
	namedWindow("second");
	imshow("second", _img);
}