#include <iostream>

#include "Convolution.h"

// Default constructor
Convolution::Convolution()
{
}

// Parametrized constructor for custom kernel and other parameters
Convolution::Convolution(double** customKernel, int kh, int kw, int stride_val, bool pad){

    kernelHeight = kh;
    kernelWidth = kw;
    stride = stride_val;
    this-> pad = pad;

    kernel = new double * [kernelHeight];
    for(int i = 0; i  < kernelHeight; i++)
    {
        kernel[i] = new double [kernelWidth];
    }

    for(int i = 0; i < kernelHeight; i++)
    {
        for(int j = 0; j < kernelWidth; j++)
        {
            kernel[i][j] = customKernel[i][j];
        }
    }

}

// Destructor
Convolution::~Convolution() {

    for (int i = 0; i < kernelHeight; i++) {
            delete[] kernel[i];
    }
    delete[] kernel;

}

// Copy constructor
Convolution::Convolution(const Convolution &other){

    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    pad = other.pad;

    kernel = new double * [kernelHeight];
    for(int i = 0 ; i < kernelHeight ;i++)
    {
        kernel[i] = new double [kernelWidth];
    }

    for(int i = 0; i < kernelHeight ;i++)
    {
        for(int j = 0 ; j < kernelWidth ;j++)
        {
            kernel[i][j] = other.kernel[i][j];
        }
    }

}

// Copy assignment operator
Convolution& Convolution::operator=(const Convolution &other) {

    if(this == &other)
    {
        return *this;
    }

    for(int i = 0; i < kernelHeight; i++)
    {
        delete[] kernel[i];
    }
    delete[] kernel;

    kernelHeight = other.kernelHeight;
    kernelWidth = other.kernelWidth;
    stride = other.stride;
    pad = other.pad;

    kernel = new double * [kernelHeight];
    for(int i = 0; i < kernelHeight; i++)
    {
        kernel[i] = new double [kernelWidth];
    }

    for(int i = 0 ; i < kernelHeight; i++)
    {
        for(int j = 0; j < kernelWidth; j++)
        {
            kernel[i][j] = other.kernel[i][j];
        }
    }

    return *this;
}

ImageMatrix Convolution::convolve(const ImageMatrix& input_image) const {
    int inputHeight = input_image.get_height();
    int inputWidth = input_image.get_width();
    int outputHeight = ((inputHeight - kernelHeight + 2 * pad) / stride) + 1;
    int outputWidth = ((inputWidth - kernelWidth + 2 * pad) / stride) + 1;

    ImageMatrix blurredImage(outputHeight, outputWidth);

    for (int i = 0; i < outputHeight; i++) {
        for (int j = 0; j < outputWidth; j++) {
            double sum = 0.0;

            for (int m = 0; m < kernelHeight; m++) {
                for (int n = 0; n < kernelWidth; n++) {
                    int input_i = i * stride + m - pad;
                    int input_j = j * stride + n - pad;

                    if (input_i >= 0 && input_i < inputHeight && input_j >= 0 && input_j < inputWidth) {
                        sum += input_image.get_data(input_i, input_j) * kernel[m][n];
                    }
                }
            }

            blurredImage.set_data(i, j, sum);
        }
    }
    return blurredImage;
}

