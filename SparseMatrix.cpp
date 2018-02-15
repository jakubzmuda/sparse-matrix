#include <iostream>
#include <cmath>
#include "SparseMatrix.h"

using namespace std;

SparseMatrix::SparseMatrix() {
    init();
}

SparseMatrix::SparseMatrix(SparseMatrix &original) {
    init();

    for (int i = 0; i < original.entriesSize; i++) {
        MatrixEntry entry = original.entries[i];
        this->push(entry.column, entry.row, entry.value);
    }
}

SparseMatrix::~SparseMatrix() {
    delete[] entries;
}

void SparseMatrix::init() {
    capacity = 100000;
    rowSize = 0;
    colSize = 0;
    entriesSize = 0;

    entries = new MatrixEntry[capacity];
}

void SparseMatrix::printMatrix(ostream &) const {
    cout << endl << "-----" << endl;
    if (entriesSize == 0) {
        cout << "empty entries" << endl;
    } else {
        for (int i = 0; i < entriesSize; i++) {
            cout << "row: " << entries[i].row;
            cout << " column: " << entries[i].column;
            cout << " value: " << entries[i].value << endl;
        }
    }
    cout << "-----" << endl;
}

void SparseMatrix::push(int column, int row, double val) {
    rowSize = row + 1 > rowSize ? row + 1 : rowSize;
    colSize = column + 1 > colSize ? column + 1 : colSize;
    entriesSize += 1;

    entries[entriesSize - 1] = {.row = row, .column = column, .value = val};
}

void SparseMatrix::add(int column, int row, double val) {
    MatrixEntry *entry = this->getEntry(column, row);
    double value = val + entry->value;
    entry->value = value;
}

void SparseMatrix::subtract(int column, int row, double val) {
    MatrixEntry *entry = this->getEntry(column, row);
    double value = entry->value - val;
    entry->value = value;
}

void SparseMatrix::multiply(int column, int row, double val) {
    MatrixEntry *entry = this->getEntry(column, row);
    double value = entry->value * val;
    entry->value = value;
}

void SparseMatrix::divide(int column, int row, double val) {
    MatrixEntry *entry = this->getEntry(column, row);
    double value = entry->value / val;
    entry->value = value;
}

double &SparseMatrix::operator()(int col, int row) {
    MatrixEntry *entry = this->getEntry(col, row);
    return entry->value;
}

MatrixEntry *SparseMatrix::getEntry(int column, int row) {
    for (int i = 0; i < entriesSize; i++) {
        if (entries[i].row == row && entries[i].column == column) {
            return &entries[i];
        }
    }
    this->push(column, row, 0);
    return &entries[entriesSize - 1];
}

SparseMatrix *SparseMatrix::operator+(const SparseMatrix &operand) {
    SparseMatrix *result = new SparseMatrix(*this);
    for (int i = 0; i < operand.entriesSize; i++) {
        MatrixEntry entry = operand.entries[i];
        result->add(entry.column, entry.row, entry.value);
    }
    return result;
}

SparseMatrix *SparseMatrix::operator+(const double valueToAdd) {
    SparseMatrix *result = new SparseMatrix(*this);
    for (int i = 0; i < result->colSize; i++) {
        for (int j = 0; j < result->rowSize; j++) {
            MatrixEntry *entry = result->getEntry(i, j);
            entry->value += valueToAdd;
        }
    }
    return result;
}

SparseMatrix *SparseMatrix::operator-(const SparseMatrix &operand) {
    SparseMatrix *result = new SparseMatrix(*this);
    for (int i = 0; i < operand.entriesSize; i++) {
        MatrixEntry entry = operand.entries[i];
        result->subtract(entry.column, entry.row, entry.value);
    }
    return result;
}

SparseMatrix *SparseMatrix::operator-(const double valueToSubtract) {
    SparseMatrix *result = new SparseMatrix(*this);
    for (int i = 0; i < result->colSize; i++) {
        for (int j = 0; j < result->rowSize; j++) {
            MatrixEntry *entry = result->getEntry(i, j);
            entry->value -= valueToSubtract;
        }
    }
    return result;
}

SparseMatrix *SparseMatrix::operator*(const SparseMatrix &operand) {
    SparseMatrix *result = new SparseMatrix(*this);
    for (int i = 0; i < operand.entriesSize; i++) {
        MatrixEntry entry = operand.entries[i];
        result->multiply(entry.column, entry.row, entry.value);
    }
    return result;
}

SparseMatrix *SparseMatrix::operator*(const double valueToMultiplyBy) {
    SparseMatrix *result = new SparseMatrix(*this);
    for (int i = 0; i < result->colSize; i++) {
        for (int j = 0; j < result->rowSize; j++) {
            MatrixEntry *entry = result->getEntry(i, j);
            entry->value *= valueToMultiplyBy;
        }
    }
    return result;
}

SparseMatrix *SparseMatrix::operator!() {
    this->assureThatSquare();
    if (this->countDet() == 0) {
        throw "cannot create inverted matrix for one with det = 0";
    }
    double det = this->countDet();
    SparseMatrix *complementaryMatrix = this->getComplementaryMatrix();
    SparseMatrix *transposedMatrix = complementaryMatrix->getTransposedMatrix();
    SparseMatrix *result = transposedMatrix->operator*(1.0 / det);
    delete complementaryMatrix;
    delete transposedMatrix;
    return result;
}

SparseMatrix *SparseMatrix::operator/(const SparseMatrix &operand) {
    SparseMatrix *result = new SparseMatrix(*this);
    for (int i = 0; i < operand.entriesSize; i++) {
        MatrixEntry entry = operand.entries[i];
        if (abs(entry.value) < 0.1) { // double comparison
            throw "cannot divide by zero";
        }
        result->divide(entry.column, entry.row, entry.value);
    }
    return result;
}

int SparseMatrix::rows() {
    return this->rowSize;
}

int SparseMatrix::cols() {
    return this->colSize;
}

int SparseMatrix::size() {
    return entriesSize;
}

bool SparseMatrix::diag() {
    this->assureThatSquare();
    for (int i = 0; i < this->colSize; i++) {
        for (int j = 0; j < rowSize; j++) {
            if (i == j) continue;
            if (abs(this->getEntry(i, j)->value) > 0.1) { // double comparison
                return false;
            }
        }
    }
    return true;
}

SparseMatrix *SparseMatrix::shift(int x, int y) {
    this->assureThatSquare();
    SparseMatrix *result = new SparseMatrix();
    for (int i = 0; i < this->colSize; i++) {
        for (int j = 0; j < rowSize; j++) {
            if (i + x < 0 || j + y < 0) {
                continue;
            }
            result->operator()(i + x, j + y) = this->getEntry(i, j)->value;
        }
    }
    return result;
}

double SparseMatrix::countDet() {
    this->assureThatSquare();
    if (this->colSize == 0) {
        throw "matrix is empty";
    }
    if (this->colSize == 1) {
        return this->getEntry(0, 0)->value;
    }
    if (this->colSize == 2) {
        double firstDiagonalResult = 1;
        double secondDiagonalResult = 1;
        for (int i = 0; i < this->colSize; i++) {
            firstDiagonalResult *= this->getEntry(i, i)->value;
            secondDiagonalResult *= this->getEntry(colSize - 1 - i, i)->value;
        }
        return firstDiagonalResult - secondDiagonalResult;
    }

    double result = 0;
    for (int i = 0; i < this->colSize; i++) {
        int j = 0;
        SparseMatrix *minor = this->getMatrixWithStrippedColumnAndRow(i, j);
        result += pow(-1, (i + 1) + (j + 1)) * this->getEntry(i, j)->value * minor->countDet();
    }
    return result;
}

SparseMatrix *SparseMatrix::getComplementaryMatrix() {
    this->assureThatSquare();
    SparseMatrix *result = new SparseMatrix();
    for (int i = 0; i < this->colSize; i++) {
        for (int j = 0; j < this->rowSize; j++) {
            result->operator()(i, j) = this->getAlgebraicComplement(i, j);
        }
    }
    return result;
}

SparseMatrix *SparseMatrix::getMatrixWithStrippedColumnAndRow(int col, int row) {
    this->assureThatSquare();
    SparseMatrix *result = new SparseMatrix();
    for (int i = 0; i < this->colSize; i++) {
        if (i == col) continue;
        for (int j = 0; j < this->rowSize; j++) {
            if (j == row) continue;

            int colIndex = col < i ? i - 1 : i;
            int rowIndex = row < j ? j - 1 : j;
            result->operator()(colIndex, rowIndex) = this->getEntry(i, j)->value;
        }
    }
    return result;
}

double SparseMatrix::getAlgebraicComplement(int col, int row) {
    SparseMatrix *strippedMatrix = this->getMatrixWithStrippedColumnAndRow(col, row);
    double det = strippedMatrix->countDet();
    delete strippedMatrix;
    return pow(-1, (col + 1) + (row + 1)) * det;
}

SparseMatrix *SparseMatrix::getTransposedMatrix() {
    SparseMatrix *result = new SparseMatrix();
    for (int i = 0; i < this->colSize; i++) {
        for (int j = 0; j < this->rowSize; j++) {
            result->operator()(j, i) = this->operator()(i, j);
        }
    }
    return result;
}

void SparseMatrix::assureThatSquare() {
    if (this->colSize != this->rowSize) {
        throw "matrix has to be square";
    }
}

ostream &operator<<(ostream &outputStream, const SparseMatrix &matrix) {
    matrix.printMatrix(outputStream);
    return outputStream;
}

ostream &operator<<(ostream &outputStream, const SparseMatrix *matrix) {
    matrix->printMatrix(outputStream);
    return outputStream;
}

void swap(int *first, int *second)
{
    int temp = *first;
    *first = *second;
    *second = temp;
}

void sort(int arr[], int size) {
    for (int i = 0; i < size-1; i++) {
        for (int j = 0; j < size-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}