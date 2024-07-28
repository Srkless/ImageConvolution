#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h> 
#include <opencv2/opencv.hpp>
#include <chrono>
#include <functional>
#include <cstdio>
#include <immintrin.h>

void convolve(const cv::Mat& in, const std::vector<std::vector<float>>& kernel, cv::Mat& out);
