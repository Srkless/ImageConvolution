#include "Convolution.h"

void convolve(const cv::Mat& in, const std::vector<std::vector<float>>& kernel, cv::Mat& out){
    int kernelRows = kernel.size();
    int kernelCols = kernel[0].size();
    int kernelCenterX = kernelCols / 2;
    int kernelCenterY = kernelRows / 2;
    int rows = in.rows;
    int cols = in.cols;
    int channels = in.channels();

    std::cout << in.channels() << std::endl;
    #pragma omp parallel for
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            cv::Vec3f sum = cv::Vec3f(0, 0, 0); // koristimo float za sumu za svaki kanal
            for(int m = 0; m < kernelRows; m++){
                for(int n = 0; n < kernelCols; n++){
                    int rIndex = i + m - kernelCenterY;
                    int cIndex = j + n - kernelCenterX;
                    if(rIndex >= 0 && rIndex < rows && cIndex >= 0 && cIndex < cols){
                        for(int c = 0; c < channels; c++){
                            sum[c] += in.at<cv::Vec3b>(rIndex, cIndex)[c] * kernel[m][n];
                        }
                    }
                }
            }
            for(int c = 0; c < channels; c++){
                out.at<cv::Vec3b>(i, j)[c] = cv::saturate_cast<uchar>(sum[c]);
            }
        }
    }
}
