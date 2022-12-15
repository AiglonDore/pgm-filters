/**
 * @file filter.cpp
 * @author Thomas Roiseux (thomas.roiseux@outlook.com)
 * @brief Implements {@link filter.h}.
 * @version 0.1
 * @date 2022-12-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../header/filter.h"

#include <exception>
#include <stdexcept>

using namespace ensiie;

Filter::Filter()
{
    m_kernel = new double*[3];
    for (int i = 0; i < 3; i++)
    {
        m_kernel[i] = new double[3];
        m_kernel[i][0] = 1;
        m_kernel[i][1] = 1;
        m_kernel[i][2] = 1;
    }
}

Filter::Filter(const Filter& other) : Filter()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m_kernel[i][j] = other.m_kernel[i][j];
        }
    }
}

Filter::Filter(Filter&& other) : Filter()
{
    this->m_kernel = other.m_kernel;
    other.m_kernel = nullptr;
}

Filter::Filter(double **kernel) : Filter()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            m_kernel[i][j] = kernel[i][j];
        }
    }
}

Filter::Filter(double a, double b, double c, double d, double e, double f, double g, double h, double i) : Filter()
{
    m_kernel[0][0] = a;
    m_kernel[0][1] = b;
    m_kernel[0][2] = c;
    m_kernel[1][0] = d;
    m_kernel[1][1] = e;
    m_kernel[1][2] = f;
    m_kernel[2][0] = g;
    m_kernel[2][1] = h;
    m_kernel[2][2] = i;
}

Filter::~Filter()
{
    for (int i = 0; i < 3; i++)
    {
        delete[] m_kernel[i];
    }
    delete[] m_kernel;
}

const double *Filter::operator[](int i) const
{
    if (i < 0 || i > 2)
    {
        throw std::out_of_range("Index out of range.");
    }
    return m_kernel[i];
}

double Filter::operator()(int i, int j) const
{
    if (i < 0 || i > 2 || j < 0 || j > 2)
    {
        throw std::out_of_range("Index out of range.");
    }
    return m_kernel[i][j];
}

bool Filter::operator==(const Filter& other) const
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (m_kernel[i][j] != other.m_kernel[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

Filter& Filter::operator=(const Filter& other)
{
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; i < 3; j++)
        {
            m_kernel[i][j] = other.m_kernel[i][j];
        }
    }
    return *this;
}

Filter& Filter::operator=(Filter&& other)
{
    this->m_kernel = other.m_kernel;
    other.m_kernel = nullptr;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Filter& filter)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            os << filter[i][j] << " ";
        }
        os << std::endl;
    }
    return os;
}