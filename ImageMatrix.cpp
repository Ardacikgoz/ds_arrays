#include "ImageMatrix.h"
#include <iostream>


// Default constructor
ImageMatrix::ImageMatrix(){

}


// Parameterized constructor for creating a blank image of given size
ImageMatrix::ImageMatrix(int imgHeight, int imgWidth) : height(imgHeight), width(imgWidth) {

    data = new double * [height];
    for(int i = 0; i < height; i++)
    {
        data[i] = new double [width];
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++)
        {
            data[i][j] = 0;
        }
    }

}

// Parameterized constructor for loading image from file. PROVIDED FOR YOUR CONVENIENCE
ImageMatrix::ImageMatrix(const std::string &filepath) {
    // Create an ImageLoader object and load the image
    ImageLoader imageLoader(filepath);

    // Get the dimensions of the loaded image
    height = imageLoader.getHeight();
    width = imageLoader.getWidth();

    // Allocate memory for the matrix
    data = new double*[height];
    for (int i = 0; i < height; ++i) {
        data[i] = new double[width];
    }

    // Copy data from imageLoader to data
    double** imageData = imageLoader.getImageData();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; j++) {
            data[i][j] = imageData[i][j];
        }
    }
}



// Destructor
ImageMatrix::~ImageMatrix() {
    for(int i = 0; i < height; i++)
    {
        delete[] data[i];
    }
    delete[] data;

}

// Parameterized constructor - direct initialization with 2D matrix
ImageMatrix::ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth)
{
    height = imgHeight;
    width = imgWidth;

    data = new double * [height];

    for(int i = 0 ; i < height; i++)
    {
        data[i] = new double [width];
    }

    for(int i = 0 ; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            data[i][j] = inputMatrix[i][j];
        }
    }
}

// Copy constructor
ImageMatrix::ImageMatrix(const ImageMatrix &other)
{
    height = other.height;
    width = other.width;

    data = new double * [height];
    for(int i = 0; i < height; i++)
    {
        data[i] = new double[width];
    }

    for(int i = 0 ; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            data[i][j] = other.get_data(i,j);
        }
    }
}

// Copy assignment operator
ImageMatrix& ImageMatrix::operator=(const ImageMatrix &other)
{
    if (this == &other) {
        return *this;
    }

    clear();

    height = other.height;
    width = other.width;

    data = new double * [height];

    for(int i = 0; i < height; i++)
    {
        data[i] = new double[width];
    }

    for(int i = 0 ; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            data[i][j] = other.get_data(i,j);
        }
    }
}


// Overloaded operators

// Overloaded operator + to add two matrices
ImageMatrix ImageMatrix::operator+(const ImageMatrix &other) const
{
    if(height != other.height)
    {
        std::cout << "bir sorun var"<<std::endl;
    }
    ImageMatrix imageMatrix(height,width);

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            imageMatrix.data[i][j]  = data[i][j] + other.data[i][j];
        }
    }

    return imageMatrix;

}

// Overloaded operator - to subtract two matrices
ImageMatrix ImageMatrix::operator-(const ImageMatrix &other) const
{
    if(height != other.height)
    {
        std::cout << "bir sorun var mines"<<std::endl;
    }
    ImageMatrix imageMatrix(height,width);


    for(int i = 0; i < other.height; i++)
    {
        for(int j = 0; j < other.height; j++)
        {
            imageMatrix.data[i][j]  = data[i][j] - other.data[i][j];
        }
    }

    return imageMatrix;
}

// Overloaded operator * to multiply a matrix with a scalar
ImageMatrix ImageMatrix::operator*(const double &scalar) const
{
    ImageMatrix imageMatrix(height,width);

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            imageMatrix.data[i][j]  = data[i][j] * scalar;
        }
    }
    return imageMatrix;
}


// Getter function to access the data in the matrix
double** ImageMatrix::get_data() const {
    return data;
}

// Getter function to access the data at the index (i, j)
double ImageMatrix::get_data(int i, int j) const {
    return data[i][j];
}

double ImageMatrix::get_height() const
{
    return height;
}
double ImageMatrix::get_width() const
{
    return width;
}

void ImageMatrix::clear() {
    if (data != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] data[i];
        }
        delete[] data;
        data = nullptr;
    }
}

void ImageMatrix::display()
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            std::cout << data[i][j] << " ";
        }
        std::cout<<std::endl;
    }
}

void ImageMatrix::set_data(int i, int j, double value)
{
    //std::cout<<"i: " << i  <<"   j: "<< j <<"   value: "<< value <<std::endl;
    if (i >= 0 && i < height && j >= 0 && j < width) {
        data[i][j] = value;

    }
    else {
        std::cerr << "Hatalı indeksler: (" << i << "YANLIŞ BİŞİLER VAR" << j << "). Veri değiştirilemedi." << std::endl;
    }
}

