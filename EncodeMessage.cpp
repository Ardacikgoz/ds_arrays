#include "EncodeMessage.h"
#include <cmath>
#include <iostream>



// Default Constructor
EncodeMessage::EncodeMessage() {

}

// Destructor
EncodeMessage::~EncodeMessage() {

}

bool primeFinder(int number)
{
    if(number != 2 && number%2 == 0)
    {
        return false;
    }
    for(int i = 2; i <= sqrt(number) ; i++ )
    {
        if ( number % i == 0)
        {
            return false;
        }
    }
    return true;
}

int fibonacci(int number)
{
    if(number <= 1 )
    {
        return number;
    }
    else
    {
        return fibonacci(number-1) + fibonacci(number-2);
    }
}

std::vector<int> shiftArray(std::vector<int> &vector,int size,int shiftValue)
{
    int * temp;
    temp = new int[size];

    int count = 0;
    for(int i = 0; i < size; i++)
    {
        if(count + shiftValue < size )
        {
            temp[count + shiftValue] = vector[i];
            count++;
        }
    }
    for(int i = 0; i < shiftValue; i++)
    {
        temp[i] = vector[count];
        count++;
    }
    std::vector<int> result;
    for(int i = 0; i < shiftValue; i++)
    {
        result.push_back(temp[i]);
    }

    delete temp;


    return result;
}



// Function to encode a message into an image matrix
ImageMatrix EncodeMessage::encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions)
{

    if(message.length() == 0)
    {
        return img;
    }
    std::vector<int> asciiValues;
    int asciiValuesLength = 0;

    for(int i = 0; i < message.length(); i++)
    {
        asciiValues.push_back(static_cast<int>(message[i]));
        asciiValuesLength++;
    }

    ImageMatrix myImageMatrix(img);

    for(int i = 0 ; i < asciiValuesLength ; i++)
    {
        if(primeFinder(i))
        {
            asciiValues[i] += fibonacci(i);
        }
    }



    for(int i = 0; i < asciiValuesLength; i++)
    {
        if(asciiValues[i] <= 32)
        {
            asciiValues[i] += 33;
        }
        else if (asciiValues[i] >= 127)
        {
            asciiValues[i] = 126;
        }
    }


    int shiftValue = message.length()/ 2;

    std::vector<int> array = shiftArray(asciiValues,asciiValuesLength,shiftValue);


    int counter = 0;
    for (const auto& pair : positions) {
        int i = pair.first;
        int j = pair.second;
        int value =  array[counter];
        int sumThis = value % 2;
        myImageMatrix.set_data(i,j,myImageMatrix.get_data(i,j) + sumThis);
        counter++;
    }


    return myImageMatrix;
}
