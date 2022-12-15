/**
 * @file image.h
 * @author your name (you@domain.com)
 * @brief Provides the {@link Image} class.
 * @version 0.1
 * @date 2022-12-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef IMAGE_H
#define IMAGE_H

#include "filter.h"

#include <string>

/**
 * @brief Namespace of the project.
 * 
 */
namespace ensiie {
    /**
     * @brief Class that represents an image.
     * 
     */
    class Image
    {
    private:
        size_t height, width;
        unsigned char* data;
    public:
        /**
         * @brief Construct a new Image object.
         * @throws std::exception if the file cannot be read or is not a valid image.
         * @param filename File to be read.
         */
        Image(const std::string& filename);

        /**
         * @brief Construct a new Image object.
         * 
         * @param other Image to be copied.
         */
        Image(const Image& other);

        /**
         * @brief Construct a new Image object.
         * 
         * @param other Image to be moved.
         */
        Image(Image&& other);

        /**
         * @brief Destroy the Image object.
         * 
         */
        ~Image();

        /**
         * @brief Get the height of the image.
         * 
         * @return size_t Height of the image.
         */
        size_t getHeight() const { return height; };

        /**
         * @brief Get the width of the image.
         * 
         * @return size_t Width of the image.
         */
        size_t getWidth() const { return width; };

        /**
         * @brief Copy operator.
         * 
         * @param other Image to be copied.
         * @return Image& This image.
         */
        Image& operator=(const Image& other);

        /**
         * @brief Move operator.
         * 
         * @param other Image to be moved.
         * @return Image& This image.
         */
        Image& operator=(Image&& other);

        /**
         * @brief Get the value of a pixel.
         * 
         * @param x X coordinate of the pixel.
         * @param y Y coordinate of the pixel.
         * @return unsigned char Value of the pixel.
         * @warning If y * width + x is out of bounds, the behavior is undefined.
         */
        unsigned char operator()(size_t x, size_t y) const { return data[y * width + x]; };
        
        /**
         * @brief Get the value of a pixel.
         * @warning If i is out of bounds, the behavior is undefined.
         * @param i Index.
         * @return unsigned char Value of the pixel.
         */
        unsigned char operator[](size_t i) const { return data[i]; };

        /**
         * @brief Get the value of a pixel.
         * 
         * @param i Indeox of the pixel.
         * @warning If the pixel is modified, the image will be modified.
         * @warning If i is out of bounds, the behavior is undefined.
         * @return unsigned char& Value of the pixel.
         */
        unsigned char& operator[](size_t i) { return data[i]; };

        /**
         * @brief Apply a filter to the image. 
         * @warning Modifies the source image.
         * @param filter Filter to be applied.
         */
        void applyFilter(const Filter& filter);

        /**
         * @brief Applies a filter to an image. Doesn't modify the source image.
         * 
         * @param filter Filter to be applied.
         * @param src Source image.
         * @param dst Destination.
         */
        static void applyFilter(const Filter& filter, const Image& src, Image& dst);

        /**
         * @brief Save the image to a file.
         * @throws std::exception if the file cannot be written.
         * @param filename File to be written.
         */
        void save(const std::string& filename) const;
    };
}

#endif // IMAGE_H