//
// Created by Alexander Flohr on 12.03.21.
//

#ifndef ALIGNMENT_MATRIX_H
#define ALIGNMENT_MATRIX_H

#include <iostream>
#include <initializer_list>
#include <bits/unique_ptr.h>

#include <exception>
#include <vector>
// allows lambda functions
#include <functional>

template<typename T>
class Matrix {
public:
    /**
     * Default constructor
     * Create an empty matrix object
     */
    Matrix() {
        data_ = std::make_unique<T[]>(0);
        nrow_ = 0;
        ncol_ = 0;
    }

    /**
     * Simple constructor with number of rows, number of columns
     * @throws exception if the number of rows or columns is negative
     * @details Task 5.1
     */
    Matrix(size_t rows, size_t cols) {
        if (rows < 0 || cols < 0) {
            throw "BAD INDEXING";
        }
        nrow_ = rows;
        ncol_ = cols;
        data_ = std::make_unique<T[]>(nrow_ * ncol_);
    }

    /**
     * Constructor based on input lists, comparable with WolframAlpha's
     * matrix syntax
     * @throws exception if rows have different length
     * @details Task 5.2
     */
    Matrix(std::initializer_list<std::initializer_list<T>> data) {
        nrow_ = data.size();
        // if constructor is called without values, it behaves like
        // the default constructor
        if (nrow_ >= 1) {
            // set number of columns to the size of the first row
            // check if each row has the same size, otherwise throw exception
            ncol_ = data.begin()->size();
            data_ = std::make_unique<T[]>(nrow_ * ncol_);
            for (auto it1 = data.begin(); it1 != data.end(); ++it1) {
                // check row length to ensure matrix form
                if (ncol_ != it1->size()) {
                    throw "BAD INDEXING";
                } else {
                    unsigned current_row = it1 - data.begin();
                    // manually copy data into matrix object
                    for (auto it2 = it1->begin(); it2 != it1->end(); ++it2) {
                        unsigned current_col = it2 - it1->begin();
                        data_[current_row * ncol_ + current_col] = *it2;
                    }
                }
            }
        } else {
            // default settings
            ncol_ = 0;
            data_ = std::make_unique<T[]>(0);
        }
    }

    /**
     * Copy constructor
     * @param other_mat
     * @details Task 5.3
     */
    Matrix(const Matrix<T> &other_matrix) {
        // other matrix must have been initialized,
        // so no need to catch arguments
        nrow_ = other_matrix.nrow();
        ncol_ = other_matrix.ncol();
        data_ = std::make_unique<T[]>(nrow_ * ncol_);
        // manually copy values
        for (unsigned i = 0; i < nrow_; ++i) {
            for (unsigned j = 0; j < ncol_; ++j) {
                data_[i * ncol_ + j] = other_matrix(i, j);
            }
        }
    }

    /**
     * Copy assignment constructor
     * @details Task 5.3
     */
    Matrix<T> &operator=(const Matrix<T> &other_matrix) {
        // perform similar to copy constructor
        nrow_ = other_matrix.nrow();
        ncol_ = other_matrix.ncol();
        data_ = std::make_unique<T[]>(nrow_ * ncol_);
        // manually copy values
        for (unsigned i = 0; i < nrow_; ++i) {
            for (unsigned j = 0; j < ncol_; ++j) {
                data_[i * ncol_ + j] = other_matrix(i, j);
            }
        }
        return *this;
    }

    /**
     * Move constructor
     * @details Task 5.4
     */
    Matrix(Matrix<T> &&other_matrix) {
        nrow_ = std::move(other_matrix.nrow_);
        ncol_ = std::move(other_matrix.ncol_);
        data_ = std::move(other_matrix.data_);
    }

    /**
     * Move assignment operator
     * @details Task 5.4
     */
    Matrix<T> &operator=(Matrix<T> &&other_matrix) {
        nrow_ = std::move(other_matrix.nrow_);
        ncol_ = std::move(other_matrix.ncol_);
        data_ = std::move(other_matrix.data_);
        return *this;
    }

    /**
     * Get number of rows of the matrix
     * @details Task 5.5
     */
    size_t nrow() const {
        return nrow_;
    }

    /**
     * Get number of columns of the matrix
     * @details Task 5.5
     */
    size_t ncol() const {
        return ncol_;
    }

    /**
     * Access and modify value in row i and col j in the matrix
     * @throws exception if the used index is out of range
     * @details Task 5.6
     */
    T &operator()(std::size_t i, std::size_t j) {
        if (i < 0 || j < 0 || i >= nrow_ || j >= ncol_) {
            throw "INDEX OUT OF RANGE";
        }
        return data_[i * ncol_ + j];
    }

    /**
     * Access value in row i and col j of the matrix
     * @throws exception if the used index is out of range
     * @details Task 5.6
     */
    T operator()(std::size_t i, std::size_t j) const {
        if (i < 0 || j < 0 || i >= nrow_ || j >= ncol_) {
            throw "INDEX OUT OF RANGE";
        }
        return data_[i * ncol_ + j];
    }

    /**
     * Write space-separated matrix into ostream
     * @throws exception if type can not be transformed for ostream
     * @details Task 5.7
     */
    friend std::ostream &operator<<(std::ostream &out, Matrix<T> &matrix) {
        // handle if type cannot be printed
        try {
            for (unsigned i = 0; i < matrix.nrow(); ++i) {
                for (unsigned j = 0; j < matrix.ncol(); ++j) {
                    if (j != 0) {
                        out << " ";
                    }
                    out << matrix(i, j);
                }
                out << '\n';
            }
            return out;
        } catch (...) {
            throw "OUTPUT ERROR";
        }
    }

    // Arithmetic operators
    /**
     * operator '+' for matrices
     * @throws exception if matrices have inadequate dimensions of if
     * the operator+ is not defined for the given type
     * @details Task 5.8
     */
    friend Matrix<T> operator+(const Matrix<T> left_matrix, const Matrix<T> right_matrix) {
        // check if matrix addition is allowed fot these matrices
        if (left_matrix.nrow() != right_matrix.nrow() || left_matrix.ncol() != right_matrix.ncol()) {
            throw "INVALID MATRIX DIMENSIONS";
        }
        // create new matrix of which value follows:
        //  result[i,j] = left_matrix[i,j] + right_matrix[i,j]
        try {
            Matrix<T> result(left_matrix);
            for (unsigned i = 0; i < right_matrix.nrow(); ++i) {
                for (unsigned j = 0; j < right_matrix.ncol(); ++j) {
                    result(i, j) += right_matrix(i, j);
                }
            }
            return result;
        } catch (...) {
            throw "TYPE HAS NO OPERATOR+";
        }
    }

    /**
     * operator '-' for matrices
     * @throws exception if matrices have inadequate dimensions of if
     * the operator- is not defined for the given type
     * @details Task 5.8
     */
    friend Matrix<T> operator-(const Matrix<T> left_matrix, const Matrix<T> right_matrix) {
        // check if matrix addition is allowed fot these matrices
        if (left_matrix.nrow() != right_matrix.nrow() || left_matrix.ncol() != right_matrix.ncol()) {
            throw "INVALID MATRIX DIMENSIONS";
        }
        // create new matrix of which value follows:
        //  result[i,j] = left_matrix[i,j] + right_matrix[i,j]
        try {
            Matrix<T> result(left_matrix);
            for (unsigned i = 0; i < right_matrix.nrow(); ++i) {
                for (unsigned j = 0; j < right_matrix.ncol(); ++j) {
                    result(i, j) -= right_matrix(i, j);
                }
            }
            return result;
        } catch (...) {
            throw "TYPE HAS NO OPERATOR-";
        }
    }

    /**
     * operator '*' for matrices
     * matrix multiplication
     * @throws exception if matrices have inadequate dimensions of if
     * the operator* is not defined for the given type
     * @details Task 5.8
     */
    friend Matrix<T> operator*(const Matrix<T> left_matrix, const Matrix<T> right_matrix) {
        if (left_matrix.ncol() != right_matrix.nrow() || left_matrix.nrow() != right_matrix.ncol()) {
            throw "INVALID MATRIX DIMENSIONS";
        }
        // initialize result matrix with simple constructor
        // just to ensure the correct form
        Matrix<T> result(left_matrix.nrow(), right_matrix.ncol());
        //iterate over resulting matrix
        try {
            for (unsigned i = 0; i < result.nrow(); ++i) {
                for (unsigned j = 0; j < result.ncol(); ++j) {
                    //call each row of the left, each col of the right matrix
                    for (unsigned k = 0; k < left_matrix.ncol_; ++k) {
                        // see definition of matrix multiplication
                        result(i, j) += (left_matrix(i, k) * right_matrix(k, j));
                    }
                }
            }
            return result;
        } catch (...) {
            throw "TYPE HAS NO OPERATOR*";
        }
    }

    /**
     * Matrix division following the Hadamard-division
     * @throws exception if matrices have inadequate dimensions of if
     * the operator/ is not defined for the given type
     * @details Task 5.8
     */
    friend Matrix<T> operator/(const Matrix<T> left_matrix, const Matrix<T> right_matrix) {
        if (left_matrix.nrow() != right_matrix.nrow() || left_matrix.ncol() != right_matrix.ncol()) {
            throw "INVALID MATRIX DIMENSIONS";
        }
        try {
            Matrix<T> result(left_matrix.nrow_, left_matrix.ncol_);
            for (unsigned i = 0; i < result.nrow_; ++i) {
                for (unsigned j = 0; j < result.ncol_; ++j) {
                    result(i, j) = left_matrix(i, j) / right_matrix(i, j);
                }
            }
            return result;
        } catch (...) {
            throw "TYPE HAS NO OPERATOR/";
        }
    }

    // concise operators
    /**
     * operator '+='
     * @throws exception if matrices have inadequate dimensions of if
     * the operator+ is not defined for the given type
     * @details Task 5.8
     */
    Matrix<T> &operator+=(const Matrix<T> matrix) {
        if (nrow_ != matrix.nrow_ || ncol_ != matrix.ncol_) {
            throw "INVALID MATRIX DIMENSIONS";
        }
        try {
            for (unsigned i = 0; i < nrow_; ++i) {
                for (unsigned j = 0; j < ncol_; ++j) {
                    data_[ncol_ * i + j] += matrix(i, j);
                }
            }
            return *this;
        } catch (...) {
            throw "TYPE HAS NO OPERATOR+=";
        }
    }

    /**
     * operator '-'
     * @throws exception if matrices have inadequate dimensions of if
     * the operator- is not defined for the given type
     * @details Task 5.8
     */
    Matrix<T> &operator-=(const Matrix<T> matrix) {
        if (nrow_ != matrix.nrow_ || ncol_ != matrix.ncol_) {
            throw "INVALID MATRIX DIMENSIONS";
        }
        try {
            for (unsigned i = 0; i < nrow_; ++i) {
                for (unsigned j = 0; j < ncol_; ++j) {
                    data_[ncol_ * i + j] -= matrix(i, j);
                }
            }
            return *this;
        } catch (...) {
            throw "TYPE HAS NO OPERATOR-=";
        }
    }

    /**
     * Matrix multiplication
     * @throws nothing, let the operator* exceptions pass through
     * @details Task 5.8
     */
    Matrix<T> &operator*=(const Matrix<T> matrix) {
        // because we cannot change the matrix while computation, we have to define
        // a new one - or use operator+
        Matrix<T> temp(*this);
        *this = temp * matrix;
        return *this;
    }

    /**
     * Matrix division following Hadamard-division
     * @throws nothing, let the operator/ exceptions pass through
     * @details Task 5.8
     */
    Matrix<T> &operator/=(const Matrix<T> matrix) {
        // because we cannot change the matrix while computation, we have to define
        // a new one - or use operator+
        Matrix<T> temp(*this);
        *this = temp / matrix;
        return *this;
    }

    // Matrix multiplication with scalar
    /**
     * Scalar-matrix multiplication
     * @throws exception if operator* is not defined for the given type
     * @details Task 5.8
     */
    friend Matrix<T> operator*(const T scalar, const Matrix<T> matrix) {
        Matrix<T> result(matrix);
        try {
            for (unsigned i = 0; i < matrix.nrow_; ++i) {
                for (unsigned j = 0; j < matrix.ncol_; ++j) {
                    result(i, j) *= scalar;
                }
            }
            return result;
        } catch (...) {
            throw "TYPE HAS NO OPERATOR*";
        }
    }

    /**
     * Matrix * scalar, calls same function with switched parameters
     * @details Task 5.8
     */
    friend Matrix<T> operator*(const Matrix<T> mtrx, const T scalar) {
        return (scalar * mtrx);
    }

    /**
     * operator *=, defined for scalar multiplication
     * @throws nothing, let the exception of operator* pass if it is not
     * defined on the given type
     * @details Task 5.8
     */
    Matrix<T> &operator*=(const T scalar) {
        for (unsigned i = 0; i < nrow_; ++i) {
            for (unsigned j = 0; j < ncol_; ++j) {
                data_[ncol_ * i + j] *= scalar;
            }
        }
        return *this;
    }

    /**
     * Hadamard-deviation
     * scalar * matrix
     * @details Task 5.8
     */
    friend Matrix<T> operator/(const Matrix<T> matrix, const T scalar) {
        Matrix<T> result(matrix);
        try {
            for (unsigned i = 0; i < matrix.nrow_; ++i) {
                for (unsigned j = 0; j < matrix.ncol_; ++j) {
                    result(i, j) /= scalar;
                }
            }
            return result;
        } catch (...) {
            throw "TYPE HAS NO OPERATOR/";
        }
    }

    /**
     * Hadamard-deviation
     * @throws nothing, let the exception of operator/ pass if it is not
     * defined on the given type
     * @details Task 5.8
     */
    Matrix<T> &operator/=(const T scalar) {
        for (unsigned i = 0; i < nrow_; ++i) {
            for (unsigned j = 0; j < ncol_; ++j) {
                data_[ncol_ * i + j] /= scalar;
            }
        }
        return *this;
    }

    /**
     * apply lambda function to every field in the matrix
     * @throw exception if lambda function violates type safety of
     * if operators are used which are not defined for the given type
     * @details Task 5.9
     */
    Matrix<T> apply(std::function<T(T)> lambda) {
        Matrix<T> result(*this);
        for (unsigned i = 0; i < nrow_ * ncol_; ++i) {
            result.data_[i] = lambda(result.data_[i]);
        }
        return result;
    }

    /**
     * output matrix via standard output
     */
    void print() {
        std::cout << *this;
    }

    // Not task required functions
    /**
     * Get content of row at index
     * @throws invalid argument exception if index is out of range
     */
    std::vector<T> get_row(size_t index) {
        if (index < 0 && index >= nrow_) {
            throw std::invalid_argument("Rowindex out of range");
        }
        std::vector<T> row(0, nrow_);
        for (unsigned i = 0; i < nrow_; ++i) {
            row[i] = data_[index * ncol_ + i];
        }
        return row;
    }

    /**
     * Get content of column at index
     * @throws invalid argument exception if index is out of range
     */
    std::vector<T> get_col(size_t index) {
        if (index < 0 && index >= ncol_) {
            throw std::invalid_argument("Rowindex out of range");
        }
        std::vector<T> col(0, ncol_);
        for (unsigned i = 0; i < ncol_; ++i) {
            col[i] = data_[index * i + index];
        }
        return col;
    }

    /**
     * operator==, for better comprehension of the performance
     */
    bool operator==(const Matrix<T> other_matrix) {
        if (nrow_ == other_matrix.nrow()) {
            if (ncol_ == other_matrix.ncol()) {
                for (unsigned i = 0; i < nrow_; ++i) {
                    for (unsigned j = 0; j < ncol_; ++j) {
                        if (data_[ncol_ * i + j] != other_matrix(i, j)) {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        return false;
    }

private:
    // storage for number of rows and columns
    // to ensure a fast and save access
    size_t nrow_;
    size_t ncol_;
    // data-structure storing the matrix values
    std::unique_ptr<T[]> data_;
};

#endif //ALIGNMENT_MATRIX_H
