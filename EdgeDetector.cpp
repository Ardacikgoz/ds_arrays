// EdgeDetector.cpp

#include "EdgeDetector.h"
#include <cmath>
#include "Convolution.h"
#include <iostream>

// Default constructor
EdgeDetector::EdgeDetector()
{
    Gx = new double * [3];
    Gy = new double * [3];

    Gx[0] = new double[3]{-1.0, 0.0, 1.0};
    Gx[1] = new double[3]{-2.0, 0.0, 2.0};
    Gx[2] = new double[3]{-1.0, 0.0, 1.0};

    Gy[0] = new double[3]{-1.0, -2.0, -1.0};
    Gy[1] = new double[3]{0.0, 0.0, 0.0};
    Gy[2] = new double[3]{1.0, 2.0, 1.0};
}

// Destructor
EdgeDetector::~EdgeDetector()
{
    for(int i = 0 ; i < 3 ;i++)
    {
        delete[] Gx[i];
        delete[] Gy[i];
    }
    delete[] Gx;
    delete[] Gy;
}

// Detect Edges using the given algorithm
std::vector<std::pair<int, int>> EdgeDetector::detectEdges(const ImageMatrix& input_image)
{

    Convolution convolutionX(Gx,3,3,1, true);

    Convolution convolutionY(Gy,3,3,1, true);

    ImageMatrix x = convolutionX.convolve(input_image);

    ImageMatrix y  = (convolutionY.convolve(input_image));

    int height = input_image.get_height();
    int width = input_image.get_width();

    double** magnitude;
    magnitude = new double * [height];
    for(int i = 0; i < height; i++)
    {
        magnitude[i] = new double [width];
    }

    double threshold = 0.0;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0 ; j < width; j++)
        {
            magnitude[i][j] = sqrt(pow(x.get_data(i,j),2) + pow(y.get_data(i,j),2));
            threshold += magnitude[i][j];

        }
    };

    threshold = threshold/(height*width);

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(magnitude[i][j] > threshold)
            {
                list.push_back(std::make_pair(i,j));
            }
        }
    }
    for(int i = 0; i < height; i++)
    {
        delete magnitude[i];
    }
    delete[] magnitude;

    return list;


}

