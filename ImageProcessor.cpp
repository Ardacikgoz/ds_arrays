#include "ImageProcessor.h"

ImageProcessor::ImageProcessor() {

}

ImageProcessor::~ImageProcessor() {

}


std::string ImageProcessor::decodeHiddenMessage(const ImageMatrix &img) {

    ImageSharpening imageSharpening;

    ImageMatrix sharpenedImage = imageSharpening.sharpen(img,2);

    EdgeDetector edgeDetector;

    std::vector<std::pair<int, int>> edges = edgeDetector.detectEdges(sharpenedImage);

    DecodeMessage decodeMessage;

    std::string message = decodeMessage.decodeFromImage(sharpenedImage,edges);

    return message;
}

ImageMatrix ImageProcessor::encodeHiddenMessage(const ImageMatrix &img, const std::string &message)
{
    ImageSharpening imageSharpening;
    ImageMatrix imageMatrix = imageSharpening.sharpen(img,2);

    EdgeDetector edgeDetector;
    std::vector<std::pair<int,int>> vectorOfEdges = edgeDetector.detectEdges(imageMatrix);

    EncodeMessage encodeMessage;

    ImageMatrix res = encodeMessage.encodeMessageToImage(img,message,vectorOfEdges);

    return res;

}
