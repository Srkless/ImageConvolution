#include <iostream>
#include "../../convLibrary/src/Image/Image.h"
#include "../../convLibrary/src/Convolution/Convolution.h"

std::vector<std::vector<float>> generateGaussianKernel(int n, double sigma) {
    std::vector<std::vector<float>> kernel(n, std::vector<float>(n, 0));
    float sum = 0.0;
    int half = n / 2;

    for (int i = -half; i <= half; ++i) {
        for (int j = -half; j <= half; ++j) {
            kernel[i + half][j + half] = std::exp(-(i * i + j * j) / (2 * sigma * sigma));
            sum += kernel[i + half][j + half];
        }
    }

    // Normalizacija kernela
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            kernel[i][j] /= sum;
        }
    }

    return kernel;
}

std::vector<std::vector<float>> generateSobelKernel(bool horizontal) {
    std::vector<std::vector<float>> kernel;
    
    if (horizontal) {
        kernel = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
        };
    } else {
        kernel = {
            {-1, -2, -1},
            {0, 0, 0},
            {1, 2, 1}
        };
    }

    return kernel;
}

int main() {
    // Image img("100.png");
    cv::Mat img = cv::imread("slika.png");
    std::vector<std::vector<float>> kernel = {{1,0,0}, {0,0,0}, {0,0,0}};
    std::vector<std::vector<float>> kernel2 = generateSobelKernel(false); 
    cv::Mat output(img.rows, img.cols, CV_8UC3);
    convolve(img, kernel2, output);
    // cv::imshow("Image", output);
    // cv::waitKey(0);
    Image img3(output);
    img3.write("output.png");
    return 0;
}
