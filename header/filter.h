/**
 * @file filter.h
 * @author Thomas Roiseux (thomas.roiseux@outlook.com)
 * @brief Provides the {@link Filter} class.
 * @version 0.1
 * @date 2022-12-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef FILTER_H
#define FILTER_H

#include <iostream>

/**
 * @brief Namespace of the project.
 * 
 */
namespace ensiie {
    /**
     * @brief Class that represents a filter.
     * 
     */
    class Filter
    {
    private:
        /* data */
        double **m_kernel;
    public:
        /**
         * @brief Construct a new Filter object.
         * 
         */
        Filter();

        /**
         * @brief Construct a new Filter object.
         * 
         * @param other Other filter.
         */
        Filter(const Filter& other);

        /**
         * @brief Construct a new Filter object.
         * 
         * @param other Other filter.
         */
        Filter(Filter&& other);

        /**
         * @brief Construct a new Filter object.
         * 
         * @param kernel Kernel of the filter.
         * @warning if the kernel is not a square matrix of size 3, the behavior is undefined.
         */
        Filter(double **kernel);

        /**
         * @brief Construct a new Filter object.
         * 
         * @param a Kernel value.
         * @param b Kernel value.
         * @param c Kernel value.
         * @param d Kernel value.
         * @param e Kernel value.
         * @param f Kernel value.
         * @param g Kernel value.
         * @param h Kernel value.
         * @param i Kernel value.
         */
        Filter(double a, double b, double c, double d, double e, double f, double g, double h, double i);

        /**
         * @brief Destroy the Filter object.
         * 
         */
        ~Filter();

        /**
         * @brief Get the Kernel object.
         * 
         * @return const double** Kernel of the filter.
         * @param i Row index.
         * @throws Exception if the index is out of range.
         */
        const double *operator[](int i) const;

        /**
         * @brief Get the Kernel object.
         * 
         * @return const double** Kernel of the filter.
         * @param i Row index.
         * @param j Column index.
         * @throws Exception if the index is out of range.
         */
        double operator()(int i, int j) const;

        /**
         * @brief Equality operator.
         * 
         * @param other Other filter.
         * @return true Equals.
         * @return false Different.
         */
        bool operator==(const Filter& other) const;
        
        /**
         * @brief Difference operator.
         * 
         * @param other Other filter.
         * @return false Equals.
         * @return true Different.
         */
        bool operator!=(const Filter& other) const { return !(*this == other); };

        /**
         * @brief Copy assignment operator.
         * 
         * @param other Other filter.
         * @return Filter& This filter.
         */
        Filter& operator=(const Filter& other);

        /**
         * @brief Move assignment operator.
         * 
         * @param other Other filter.
         * @return Filter& This filter.
         */
        Filter& operator=(Filter&& other);

        /**
         * @brief Displays the matrix.
         * 
         * @param os Output stream.
         * @param filter Filter to display.
         * @return std::ostream& Output stream.
         */
        friend std::ostream& operator<<(std::ostream& os, const Filter& filter);
    };
    
}

#endif // FILTER_H