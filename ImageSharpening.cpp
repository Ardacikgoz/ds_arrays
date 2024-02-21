#include "ImageSharpening.h"
#include <iostream>
// Default constructor
ImageSharpening::ImageSharpening()
{
    kernelHeight = 3;
    kernelWidth = 3;

    kernel = new double * [kernelHeight];

    for(int i =0 ; i < kernelHeight ;i++)
    {
        kernel[i] = new double [kernelWidth];
    }

    for(int i = 0; i < kernelHeight ;i++)
    {
        for(int j = 0;j < kernelWidth ;j++)
        {
            kernel[i][j] = (1.0/9.0);
        }
    }


}

ImageSharpening::~ImageSharpening()
{
    for(int i = 0; i < kernelHeight; i++)
    {
        delete[] kernel[i];
    }
    delete[] kernel;
    kernel = nullptr;
}

ImageMatrix clip(ImageMatrix &imageMatrix)
{
    for(int i = 0 ; i < imageMatrix.get_height(); i++)
    {
        for(int j = 0 ; j <imageMatrix.get_width(); j++)
        {
            if(imageMatrix.get_data(i,j) > 255.0)
            {
                imageMatrix.set_data(i,j,255.0);
            }
            else if (imageMatrix.get_data(i,j) < 0.0)
            {
                imageMatrix.set_data(i,j,0.0);
            }
        }
    }
    return imageMatrix;
}

ImageMatrix ImageSharpening::sharpen(const ImageMatrix& input_image, double k)
{

    Convolution convolution(kernel,kernelHeight,kernelWidth,1, true);
    ImageMatrix blurredImg = convolution.convolve(input_image);
    ImageMatrix mines = input_image - blurredImg;
    ImageMatrix multiply = mines *k ;
    ImageMatrix sharpened = multiply + input_image;

    clip(sharpened);


    return sharpened;
}
