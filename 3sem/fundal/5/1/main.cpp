#include <string>
#include <iostream>
#include <cmath>
#include <chrono>

using namespace std;

class Matrix {
    friend double getTrace(const Matrix& matrix);
    friend double getDeterminant(const Matrix matrix);
    friend Matrix transpose(const Matrix& matrix);
    friend Matrix reverse(const Matrix& matrix);
    friend Matrix exp(const Matrix& matrix, int n);
    friend ostream& operator<<(ostream& out, const Matrix& matrix);
    friend istream& operator>>(istream& in, Matrix& matrix);
private:
    double **matrix;
    string name;
    int size;

public:

    ~Matrix() {
//        clog << "Destructor for " << this << endl;
        delete[] matrix;
    }

    Matrix(int size): size{size} {
        this->matrix = new double *[size];
        for (int i = 0; i < size; ++i) {
            this->matrix[i] = new double[size];
            for (int j = 0; j < size; ++j) {
                if (i == j)
                    this->matrix[i][j] = 1;
                else
                    this->matrix[i][j] = 0;
            }
        }

        this->name = "E";

    }

    Matrix(string name, int size, double ** matrix): name{name}, size{size}, matrix{matrix} {
    }
//
//    Matrix(string name, int size, double matrix[size][size]): name{name}, size{size} {
//        this->matrix = new double * [size];
//        for (int i = 0; i < size; ++i) {
//            this->matrix[i] = new double[size];
//            for (int j = 0; j < size; ++j) {
//                this->matrix[i][j] = matrix[i][j];
//            }
//
//        }
//    }

    Matrix(const Matrix &matrix) {
//        cout << "Copy constr" << endl;

        this->size = matrix.size;
        this->matrix = new double * [size];
        for (int i = 0; i < size; ++i) {
            this->matrix[i] = new double[size];
            for (int j = 0; j < size; ++j) {
                this->matrix[i][j] = matrix.matrix[i][j];
            }
        }
        this->name = matrix.name;


    }

    Matrix(Matrix&& matrix) : matrix{matrix.matrix}, size{matrix.size}, name{matrix.name} {
//        cout << "Move constr" << endl;
    }

    Matrix& operator=(Matrix&& right) {
        if (this == &right) return *this;
        matrix = right.matrix;
        name = right.name;
        size = right.size;

        right.matrix = nullptr;
        right.size = 0;
//        cout << "Move" << endl;
        return *this;
    }

    Matrix& operator=(const Matrix& right) {
//        cout << "Copy" << endl;
        if (&right == this) return *this;
        delete [] this->matrix;
        this->size = right.size;
        this->matrix = new double * [size];
        for (int i = 0; i < size; ++i) {
            this->matrix[i] = new double[size];
            for (int j = 0; j < size; ++j) {
                this->matrix[i][j] = right.matrix[i][j];
            }
        }

        this->name = right.name;

        return *this;
    }



    Matrix(string name, int size, double num = 0.) : name{name}, size{size} {
        matrix = new double *[size];
        for (int i = 0; i < size; ++i) {
            matrix[i] = new double[size];
            for (int j = 0; j < size; ++j) {
                matrix[i][j] = num;
            }
        }
    }

    Matrix(string name, int size, int num) : name{name}, size{size} {
        matrix = new double *[size];
        for (int i = 0; i < size; ++i) {
            matrix[i] = new double[size];
            for (int j = 0; j < size; ++j) {
                matrix[i][j] = random() % num;
            }
        }
    }


    Matrix &operator+=(const Matrix &right) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                this->matrix[i][j] += right.matrix[i][j];
            }
        }

        return *this;
    }

    Matrix &operator-=(const Matrix &right) {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                this->matrix[i][j] -= right.matrix[i][j];
            }
        }

        return *this;
    }

    const Matrix &operator/=(int n) const{
        for (int i = 0; i < this->size; ++i) {
            for (int j = 0; j < this->size; ++j) {
                this->matrix[i][j] /= n;
            }
        }
        return *this;
    }

    const Matrix &operator/(int n) const {
        return *this/=n;
    }

    Matrix &operator*=(const Matrix &right) {
        double tmp[size][size];
        for (int l = 0; l < size; ++l) {
            for (int i = 0; i < size; ++i) {
                tmp[l][i] = 0;
            }
        }

        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                for (int k = 0; k < size; ++k) {
                    tmp[i][j] += this->matrix[i][k] * right.matrix[k][j];
                }
            }
        }

        for (int m = 0; m < size; ++m) {
            for (int i = 0; i < size; ++i) {
                this->matrix[m][i] = tmp[m][i];
            }
        }

        return *this;
    }

    Matrix &operator*(const Matrix& right) {
        return *this *= right;
    }

    bool operator==(const Matrix &right) {
        if (this->size != right.size) return false;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (this->matrix[i][j] != right.matrix[i][j]) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator!=(const Matrix &right) {
        return !(*this == right);
    }

    Matrix &operator+(Matrix right) {
        Matrix *result = new Matrix{this->name, this->size};
        *result += *this;
        *result += right;
        return *result;
    }


    Matrix &operator-(Matrix right) {
        Matrix *result = new Matrix{this->name, this->size};
        *result -= *this;
        *result -= right;
        return *result;
    }


    void print() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    const Matrix reduceColRow(int row, int col) const {
        double ** temp_matr = new double *[size-1];
        for (int i = 0; i < size - 1; ++i) {
            temp_matr[i] = new double[size-1];
        }

        int ki = 0;
        for (int i = 0; i < size; i++){
            if(i != row){
                for (int j = 0, kj = 0; j < size; j++){
                    if (j != col){
                        temp_matr[ki][kj] = matrix[i][j];
                        kj++;
                    }
                }
                ki++;
            }
        }
        Matrix result(name, size - 1, temp_matr);

        return result;
    }



};

double getTrace(const Matrix& matrix) {
    double result = 0;
    for (int i = 0; i < matrix.size; ++i) {
        result += matrix.matrix[i][i];
    }
    return result;
}

double getDeterminant(const Matrix matrix) {
    if (matrix.size == 1) return matrix.matrix[0][0];
    double det = 0;
    double sg = -1;
    for (int i = 0; i < matrix.size; ++i) {
        sg *= -1;
        Matrix add = matrix.reduceColRow(i, 0);
        det+= matrix.matrix[i][0]*sg*(getDeterminant(add));
    }
    return det;
}

Matrix reverse(const Matrix& matrix) {
    int sgn = 1;
    double det = getDeterminant(matrix);
    Matrix adj(matrix.name, matrix.size);
    for (int i = 0; i < matrix.size; ++i) {
        for (int j = 0; j < matrix.size; ++j) {

            sgn = (((i+j) % 2 == 0) ? 1:-1);
            adj.matrix[i][j] = (sgn * getDeterminant(matrix.reduceColRow(i, j)) )/ det;
        }
    }
    adj = transpose(adj);
    return adj;
}

Matrix transpose(const Matrix& matrix) {
    Matrix result(matrix.name, matrix.size);
    for (int i = 0; i < matrix.size; ++i) {
        for (int j = 0; j < matrix.size; ++j) {
            result.matrix[i][j] = matrix.matrix[j][i];
        }
    }
    return result;
}

Matrix exp(const Matrix &matrix, int n) {
    int d = 1;
    Matrix result = Matrix(matrix.size);
    Matrix a = matrix;
    for (int i = 0; i < matrix.size; ++i) {
        result = result + a/d++;
        a*= matrix;
    }

    return result;

}


ostream& operator<<(ostream &out, const Matrix& matrix) {
    out << matrix.name << " " << matrix.size << " ";
    for (int i = 0; i < matrix.size; ++i) {
        for (int j = 0; j < matrix.size; ++j) {
            out << matrix.matrix[i][j] << " ";
        }
    }
    return out;
}

istream &operator>>(istream &in, Matrix &matrix) {
    in >> matrix.name;
    in >> matrix.size;
    for (int i = 0; i < matrix.size; ++i) {
        for (int j = 0; j < matrix.size; ++j) {
            in >> matrix.matrix[i][j];
        }
    }

    return in;
}

int main() {
    srand(time(NULL));


    Matrix forTime("test", 5, 100);

    auto begin = chrono::steady_clock::now();

    for (int i = 0; i < 10000; ++i) {
        getDeterminant(forTime);
    }

    auto end = chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "By value " << elapsed_ms.count() << endl;

//------------------------------------------
    begin = chrono::steady_clock::now();

    for (int i = 0; i < 10000; ++i) {
        exp(forTime, 4);
    }

    end = chrono::steady_clock::now();

    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "By ref " << elapsed_ms.count() << endl;



    Matrix matrix("matr", 5, 100);
    matrix.print();
    cout << endl << getDeterminant(matrix) << " " << getTrace(matrix) << endl << endl;
    Matrix e = exp(matrix, 5);
    e.print();
    cout << endl;
    e = transpose(e);
    e.print();
    cout << endl;
    Matrix eReverse = reverse(e);
    Matrix result = eReverse * e;
    result.print();
}