#include <iostream>
#include <vector>

template <typename T>
class Matrix {
private:
    std::vector<std::vector<T>> data;

public:
    // Constructor that initializes the matrix with size rows x cols and default value 0
    Matrix(int rows, int cols) {
        data.resize(rows, std::vector<T>(cols, 0));
    }

    // Function to access matrix element (i, j) for non-const objects
    T& at(int i, int j) {
        return data[i][j];
    }

    // Function to access matrix element (i, j) for const objects
    T at(int i, int j) const {
        return data[i][j];
    }

    // Function to display the matrix
    void display() const {
        for (const auto& row : data) {
            for (const auto& elem : row) {
                std::cout << elem << " ";
            }
            std::cout << std::endl;
        }
    }

    // Function to get the inverse of the matrix (Gauss-Jordan elimination)
    Matrix<T> get_inverse() {
        int n = data.size();
        int m = data[0].size();

        // Check if the matrix is square
        if (n != m) {
            std::cout << "The matrix is not square: " << n << " Rows != " << m << " Columns\n";
            return *this;  // Return the original matrix in case of failure
        }

        Matrix<T> current = *this;
        Matrix<T> inverse(n, m);

        // Initialize inverse as an identity matrix
        for (int i = 0; i < n; i++)
            inverse.at(i, i) = 1;

        // Gauss-Jordan elimination
        for (int i = 0; i < n; i++) {
            T ind = current.at(i, i);

            // Ensure the diagonal element is 1
            if (ind != 1.0 && ind != 0) {
                for (int j = 0; j < m; j++) {
                    current.at(i, j) /= ind;
                    inverse.at(i, j) /= ind;
                }
            }

            // Handle zero diagonal elements by row swapping
            else if (ind == 0) {
                bool foundNonZero = false;
                for (int j = 1; j < n - i; j++) {
                    if (current.at(i + j, i) != 0) {
                        for (int col = 0; col < m; col++) {
                            std::swap(current.at(i, col), current.at(i + j, col));
                            std::swap(inverse.at(i, col), inverse.at(i + j, col));
                        }
                        foundNonZero = true;
                        break;
                    }
                }
                if (!foundNonZero) {
                    std::cout << "Matrix is not invertible: det = 0\n";
                    return *this;
                }
                i--;
                continue;
            }

            // Eliminate other elements in the column
            for (int j = 0; j < n; j++) {
                if (j == i) continue;

                T factor = current.at(j, i);
                for (int k = 0; k < m; k++) {
                    current.at(j, k) -= factor * current.at(i, k);
                    inverse.at(j, k) -= factor * inverse.at(i, k);
                }
            }
        }

        return inverse;
    }

    // Matrix multiplication (Matrix * Matrix)
    Matrix<T> multiply(const Matrix<T>& other) const {
        int rowsA = data.size();
        int colsA = data[0].size();
        int rowsB = other.data.size();
        int colsB = other.data[0].size();

        // Check if multiplication is possible (columns of A must equal rows of B)
        if (colsA != rowsB) {
            std::cout << "Matrix dimensions are not compatible for multiplication\n";
            throw std::invalid_argument("Incompatible matrix dimensions for multiplication");
        }

        Matrix<T> result(rowsA, colsB);

        // Perform matrix multiplication
        for (int i = 0; i < rowsA; i++) {
            for (int j = 0; j < colsB; j++) {
                for (int k = 0; k < colsA; k++) {
                    result.at(i, j) += at(i, k) * other.data[k][j];
                }
            }
        }

        return result;
    }
};
