# Image Processing Library

This library provides a set of classes and functions for image processing tasks. Core functionalities include image encryption, decryption, sharpening, and edge detection.

## Classes and Functions

### `EncodeMessage`
Encrypts messages into an image. The encryption process modifies the ASCII values of the message and uses Fibonacci and prime numbers to make adjustments.

- **Functions**:
  - `encodeMessageToImage(const ImageMatrix &img, const std::string &message, const std::vector<std::pair<int, int>>& positions)`: Encrypts the message into the image.

### `ImageLoader`
Loads images from files and provides them as `ImageMatrix` objects.

- **Functions**:
  - `ImageLoader(const std::string& filepath)`: Loads an image from a file.
  - `getHeight() const`: Returns the height of the image.
  - `getWidth() const`: Returns the width of the image.
  - `getImageData() const`: Returns the image data.

### `ImageMatrix`
Represents image data and supports various matrix operations (addition, subtraction, scaling).

- **Functions**:
  - `ImageMatrix(int imgHeight, int imgWidth)`: Creates a blank image of the given size.
  - `ImageMatrix(const double** inputMatrix, int imgHeight, int imgWidth)`: Initializes with a 2D matrix.
  - `ImageMatrix(const ImageMatrix &other)`: Creates a copy of the matrix.
  - `ImageMatrix& operator=(const ImageMatrix &other)`: Copy assignment operator.
  - `double get_data(int i, int j) const`: Retrieves data from a specific position.
  - `void set_data(int i, int j, double value)`: Sets data at a specific position.

### `ImageProcessor`
Manages encryption, decryption, sharpening, and edge detection operations on images.

- **Functions**:
  - `std::string decodeHiddenMessage(const ImageMatrix &img)`: Decodes the hidden message from the image.
  - `ImageMatrix encodeHiddenMessage(const ImageMatrix &img, const std::string &message)`: Encrypts a message into the image.

### `ImageSharpening`
Applies convolution operations to sharpen images.

- **Functions**:
  - `ImageMatrix sharpen(const ImageMatrix& input_image, double k)`: Sharpens the image.

## Usage

1. **Loading an Image**:
   ```cpp
   ImageLoader loader("path/to/image.txt");
   ImageMatrix img(loader);
