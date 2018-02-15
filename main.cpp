#include <iostream>
#include "SparseMatrix.h"

void demoConstructors();

void demoGetAndSet();

void demoMatrixAddition();

void demoMatrixNumberAddition();

void demoMatrixSubtraction();

void demoMatrixNumberSubtraction();

void demoMatrixMultiplication();

void demoMatrixNumberMultiplication();

void demoMatrixInversion();

void demoMatrixDivision();

void demoDetFor1x1();

void demoDetFor2x2();

void demoDetFor3x3();

void demoComplementaryMatrix();

void demoAlgebraicComplement();

void demoDiag();

void demoShift();

using namespace std;

int main() {
//    demoConstructors();
//    demoGetAndSet();
//    demoMatrixAddition();
//    demoMatrixNumberAddition();
//    demoMatrixSubtraction();
//    demoMatrixNumberSubtraction();
//    demoMatrixMultiplication();
//    demoMatrixNumberMultiplication();
//    demoMatrixInversion();
//    demoMatrixDivision();
//    demoDetFor1x1();
//    demoDetFor2x2();
//    demoDetFor3x3();
//    demoComplementaryMatrix();
//    demoAlgebraicComplement();
//    demoDiag();
//    demoShift();
    return 0;
}

void demoShift() {
    cout << "DEMO SHIFT MATRIX: " << endl;
    SparseMatrix matrix;
    matrix(0, 0) = 1;
    matrix(1, 0) = 2;
    matrix(0, 1) = 3;
    matrix(1, 1) = 4;
    SparseMatrix *resultMatrix = matrix.shift(0, -1);
    cout << resultMatrix;
    delete resultMatrix;
}

void demoDiag() {
    cout << "DEMO DIAGONAL MATRIX: " << endl;
    SparseMatrix matrix;
    matrix(0, 0) = 1;
    matrix(1, 0) = 0;
    matrix(2, 0) = 0;
    matrix(0, 1) = 5; //switch to 0 in order to make it diagonal
    matrix(1, 1) = 2;
    matrix(2, 1) = 0;
    matrix(0, 2) = 0;
    matrix(1, 2) = 0;
    matrix(2, 2) = 3;
    double result = matrix.diag();
    cout << "result= " << result;
}

void demoAlgebraicComplement() {
    cout << "DEMO ALGEBRAIC COMPLEMENT: " << endl;
    SparseMatrix matrix;
    matrix(0, 0) = 2;
    matrix(1, 0) = 1;
    matrix(2, 0) = 3;
    matrix(0, 1) = 4;
    matrix(1, 1) = 5;
    matrix(2, 1) = 2;
    matrix(0, 2) = 0;
    matrix(1, 2) = 6;
    matrix(2, 2) = 4;
    double result = matrix.getAlgebraicComplement(1, 0);
    cout << "result= " << result;
}

void demoComplementaryMatrix() {
    cout << "DEMO COMPLEMENTARY MATRIX: " << endl;
    SparseMatrix matrix;
    matrix(0, 0) = 2;
    matrix(1, 0) = 1;
    matrix(2, 0) = 3;
    matrix(0, 1) = 4;
    matrix(1, 1) = 5;
    matrix(2, 1) = 2;
    matrix(0, 2) = 0;
    matrix(1, 2) = 6;
    matrix(2, 2) = 4;
    SparseMatrix *resultMatrix = matrix.getComplementaryMatrix();
    cout << resultMatrix;
    delete resultMatrix;
}

void demoMatrixDivision() {
    cout << "DEMO MATRIX MULTIPLICATION: " << endl;
    SparseMatrix matrixOne;
    matrixOne(1, 0) = 1.21;
    SparseMatrix matrixTwo;
    matrixTwo(1, 0) = 2.91;
    matrixTwo(1, 1) = 3.1;
    SparseMatrix *matrixThree = matrixOne / matrixTwo;
    cout << matrixThree;
    delete matrixThree;
}

void demoDetFor3x3() {
    cout << "DEMO MATRIX DET: " << endl;
    SparseMatrix matrix;
    matrix(0, 0) = 1;
    matrix(1, 0) = 2;
    matrix(2, 0) = 3;
    matrix(0, 1) = 6;
    matrix(1, 1) = 5;
    matrix(2, 1) = 4;
    matrix(0, 2) = 3;
    matrix(1, 2) = 7;
    matrix(2, 2) = 2;
    double det = matrix.countDet();
    cout << "DET = " << det << endl;
}

void demoDetFor1x1() {
    cout << "DEMO MATRIX DET: " << endl;
    SparseMatrix matrix;
    matrix(0, 0) = 12;
    double det = matrix.countDet();
    cout << "DET = " << det << endl;
}

void demoDetFor2x2() {
    cout << "DEMO MATRIX DET: " << endl;
    SparseMatrix matrix;
    matrix(0, 0) = 3;
    matrix(1, 0) = 2;
    matrix(0, 1) = 1;
    matrix(1, 1) = 0;
    double det = matrix.countDet();
    cout << "DET = " << det << endl;
}

void demoMatrixInversion() {
    cout << "DEMO MATRIX INVERSION: " << endl;
    SparseMatrix matrix;
    matrix(0, 0) = 3;
    matrix(1, 0) = 2;
    matrix(0, 1) = 1;
    matrix(1, 1) = 0;
    SparseMatrix *resultMatrix = !matrix;
    cout << resultMatrix;
    delete resultMatrix;
}

void demoMatrixNumberMultiplication() {
    cout << "DEMO MATRIX NUMBER MULTIPLICATION: " << endl;
    SparseMatrix matrix;
    matrix(3, 0) = 0.67;
    SparseMatrix *resultMatrix = matrix * 60.72;
    cout << resultMatrix;
    delete resultMatrix;
}

void demoMatrixMultiplication() {
    cout << "DEMO MATRIX MULTIPLICATION: " << endl;
    SparseMatrix matrixOne;
    matrixOne(1, 0) = 1.21;
    SparseMatrix matrixTwo;
    matrixTwo(1, 0) = 2.91;
    matrixTwo(1, 1) = 3.1;
    SparseMatrix *matrixThree = matrixOne * matrixTwo;
    cout << matrixThree;
    delete matrixThree;
}

void demoMatrixNumberSubtraction() {
    cout << "DEMO MATRIX NUMBER SUBTRACTION: " << endl;
    SparseMatrix matrix;
    matrix(3, 0) = 50.67;
    SparseMatrix *resultMatrix = matrix - 60.72;
    cout << resultMatrix;
    delete resultMatrix;
}

void demoMatrixSubtraction() {
    cout << "DEMO MATRIX SUBTRACTION: " << endl;
    SparseMatrix matrixOne;
    matrixOne(1, 0) = 1.21;
    SparseMatrix matrixTwo;
    matrixTwo(1, 0) = 2.91;
    matrixTwo(1, 1) = 3.1;
    SparseMatrix *matrixThree = matrixOne - matrixTwo;
    cout << matrixThree;
    delete matrixThree;
}

void demoMatrixNumberAddition() {
    cout << "DEMO MATRIX NUMBER ADDITION: " << endl;
    SparseMatrix matrix;
    matrix(3, 0) = 50.67;
    SparseMatrix *resultMatrix = matrix + 60.72;
    cout << resultMatrix;
    delete resultMatrix;
}

void demoMatrixAddition() {
    cout << "DEMO MATRIX ADDITION: " << endl;
    SparseMatrix matrixOne;
    matrixOne(1, 0) = 1.21;
    SparseMatrix matrixTwo;
    matrixTwo(1, 0) = 2.91;
    matrixTwo(1, 1) = 3.1;
    SparseMatrix *matrixThree = matrixOne + matrixTwo;
    cout << matrixThree;
    delete matrixThree;
}

void demoGetAndSet() {
    cout << "DEMO GET AND SET: " << endl;
    SparseMatrix sparseMatrix;
    cout << sparseMatrix(50, 10);
    sparseMatrix(50, 10) = 1.68;
    cout << sparseMatrix(50, 10);
}

void demoConstructors() {
    cout << "DEMO CONSTRUCTORS: " << endl;
    SparseMatrix sparseMatrix;
    cout << sparseMatrix;
    sparseMatrix(1, 0) = 4.23;
    SparseMatrix copiedSparseMatrix(sparseMatrix);
    cout << copiedSparseMatrix;
}