#include "Image.h"
#include <iostream>

Image::Image(const std::string &path) {
    m_img = cv::imread(path);
    if (m_img.empty()) {
        std::cerr << "Error: Image not loaded" << std::endl;
    }
};

Image::Image(const cv::Mat &img) {
    m_img = img;
};

void Image::write(const std::string &path) {
    bool status = cv::imwrite(path, m_img);
    if (!status) {
        std::cerr << "Error: Image not saved" << std::endl;
    }
};

void Image::print() {
    cv::imshow("Image", m_img);
    cv::waitKey(0);
};

cv::Mat Image::getMat() const {
    return m_img;
};


