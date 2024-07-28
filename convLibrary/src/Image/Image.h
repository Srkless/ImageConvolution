#include <iostream>
#include <opencv2/opencv.hpp>

class Image {
  public:
    Image(const std::string &path);
    Image(const cv::Mat &img);
    void print();
    void write(const std::string &path);
    cv::Mat getMat() const;

  private:
    cv::Mat m_img;
};
