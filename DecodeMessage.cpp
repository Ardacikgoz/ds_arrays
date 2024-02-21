// DecodeMessage.cpp

#include "DecodeMessage.h"


// Default constructor
DecodeMessage::DecodeMessage() {
    // Nothing specific to initialize here
}

// Destructor
DecodeMessage::~DecodeMessage() {
    // Nothing specific to clean up
}

std::string DecodeMessage::decodeFromImage(const ImageMatrix& image, const std::vector<std::pair<int, int>>& edgePixels)
{
    std::string decodeMessage;
    int number =0;
    int lsb = 0;
    std::string binary = "";

    auto iterator = edgePixels.begin();

    while (iterator != edgePixels.end())
    {
        int first = iterator->first;
        int second = iterator->second;
        number = image.get_data(first,second);
        lsb = number % 2;
        std::string strLsb = std::to_string(lsb);
        binary += strLsb;
        iterator++;
    }


    if(binary .length()%7 != 0){
        for(int i = 0; i < binary.length() % 7; ++i){
            binary.insert(0, "0");
        }
    }

    std::vector<int> asciiValues;

    for(int i =0 ; i < binary.length() / 7; i++)
    {
        std::string subStr = binary .substr(i*7, 7);
        int decimalValue = std::stoi(subStr, 0, 2);
        asciiValues.push_back(decimalValue);
    }

    for(int i = 0; i < binary.length() / 7; i++)
    {
        if(asciiValues[i] <33){
            asciiValues[i] += 33;
        }else if(asciiValues[i]>126){
            asciiValues[i]=126;
        }
    }

    for(int i = 0; i < binary.length()/7; i++) {
        char character = static_cast<char>(asciiValues[i]);
        decodeMessage += character;
    }


    return decodeMessage;
}



