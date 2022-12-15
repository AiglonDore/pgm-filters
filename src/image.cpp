/**
 * @file image.cpp
 * @author Thomas Roiseux (thomas.roiseux@outlook.com)
 * @brief Implements {@link image.h}.
 * @version 0.1
 * @date 2022-12-15
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../header/image.h"

using namespace ensiie;

#include <fstream>
#include <vector>
#include <cstring>

#include <thread>

/**
 * @brief Split a string into tokens.
 *
 * @param str String to be split.
 * @param tokens List of tokens.
 * @param delimiters Delimiters.
 */
void splitString(const std::string &str, std::vector<std::string> &tokens, const std::string &delimiters = " ")
{
    tokens.clear();
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        lastPos = str.find_first_not_of(delimiters, pos);
        pos = str.find_first_of(delimiters, lastPos);
    }
}

Image::Image(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }
    std::string line;

    std::getline(file, line);
    if (line != "P5") // P5 is the magic number for PGM files
    {
        throw std::runtime_error("Invalid file format");
    }

    std::getline(file, line);
    if (sscanf(line.c_str(), "%zu %zu", &width, &height) != 2) // Read width and height
    {
        throw std::runtime_error("Invalid file format");
    }

    std::getline(file, line);
    if (line != "255") // Max value
    {
        throw std::runtime_error("Invalid file format");
    }

    data = new unsigned char[width * height];
    for (size_t i = 0; i < height; i++)
    {
        std::getline(file, line);
        std::vector<std::string> tokens;
        splitString(line, tokens);
        if (tokens.size() != width)
        {
            throw std::runtime_error("Invalid file format");
        }

        for (size_t j = 0; j < width; j++)
        {
            if (sscanf(tokens[j].c_str(), "%hhu", &(data[i * width + j])) != 1)
            {
                throw std::runtime_error("Invalid file format");
            }
        }
    }
    file.close();
}

Image::Image(const Image &other)
{
    height = other.height;
    width = other.width;
    data = new unsigned char[width * height];
    memcpy(data, other.data, width * height);
}

Image::Image(Image &&other)
{
    height = other.height;
    width = other.width;
    data = other.data;
    other.data = nullptr;
}

Image::~Image()
{
    delete[] data;
}

Image &Image::operator=(const Image &other)
{
    delete[] data;
    height = other.height;
    width = other.width;
    data = new unsigned char[width * height];
    memcpy(data, other.data, width * height);
    return *this;
}

Image &Image::operator=(Image &&other)
{
    delete[] data;
    height = other.height;
    width = other.width;
    data = other.data;
    other.data = nullptr;
    return *this;
}

void threadApplyFilter(const Filter &filter, const Image &src, Image &dst, int index) //Function used to apply the filter on a part of the image.
{
    unsigned int nbThreads = std::thread::hardware_concurrency();
    size_t width = src.getWidth();
    for (size_t i = 1; i < src.getHeight() - 1; i++) // Ignoring edge pixels.
    {
        for (size_t j = 1 + index; j < src.getWidth() - 1; j+= nbThreads)
        {
            double value = src[i - 1] * filter[0][0]                   //Computing the new value with the filter.
                            + src[i] * filter[0][1] 
                            + src[i + 1] * filter[0][2] 
                            + src[i - 1 + width] * filter[1][0] 
                            + src[i + width] * filter[1][1] 
                            + src[i + 1 + width] * filter[1][2] 
                            + src[i - 1 + 2 * width] * filter[2][0] 
                            + src[i + 2 * width] * filter[2][1] 
                            + src[i + 1 + 2 * width] * filter[2][2];
            
            dst[i * width + j] = int(value) % 255;                 //Storing the new value modulo 255.
        }
    }
}

void Image::applyFilter(const Filter &filter)
{
    unsigned int nbThreads = std::thread::hardware_concurrency(); //Getting the number of threads available on the computer. Takes in account the hyperthreading.
    std::vector<std::thread> threads(nbThreads);                  //Creating the threads.
    Image cpy = *this;
    for (size_t i = 0; i < nbThreads; i++)                        //Starting the threads.
    {
        threads[i] = std::thread(threadApplyFilter, filter, *this, std::ref(cpy), i);
    }
    for (size_t i = 0; i < nbThreads; i++) //Creating the threads.
    {
        threads[i].join();
    }
    *this = cpy;
}

void Image::applyFilter(const Filter &filter, const Image &src, Image &dst)
{
    dst = src;
    dst.applyFilter(filter);
}

void Image::save(const std::string &filename) const
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Cannot open file");
    }

    file << "P5" << std::endl;

    file << width << " " << height << std::endl;

    file << "255" << std::endl;

    for (size_t i = 0; i < height; i++)
    {
        for (size_t j = 0; j < width; j++)
        {
            file << data[i * width + j] << " ";
        }
        file << std::endl;
    }

    file.close();
}