#include "vector"
#include "string"

using namespace std;

struct MatrixEntry{
    int row;
    int column;
    double value;
};

class SparseMatrix {

    MatrixEntry* entries;
    int capacity;
    int entriesSize;
    int rowSize;
    int colSize;

    void init();
    MatrixEntry* getEntry(int column, int row);
    void push(int column, int row, double val);
    void add(int column, int row, double val);
    void subtract(int column, int row, double val);
    void multiply(int column, int row, double val);
    void divide(int column, int row, double val);
    SparseMatrix* getTransposedMatrix();
    void assureThatSquare();
    SparseMatrix* getMatrixWithStrippedColumnAndRow(int, int);
    void printMatrix(ostream&)const;

public:
    SparseMatrix();
    SparseMatrix(SparseMatrix &original);

    virtual ~SparseMatrix();
    double& operator()(int col, int row);
    SparseMatrix* operator+(const SparseMatrix&);
    SparseMatrix* operator+(const double);
    SparseMatrix* operator-(const SparseMatrix&);
    SparseMatrix* operator-(const double);
    SparseMatrix* operator*(const SparseMatrix&);
    SparseMatrix* operator*(const double);
    SparseMatrix* operator!();
    SparseMatrix* operator/(const SparseMatrix&);
    friend ostream& operator<<(ostream& os, const SparseMatrix&);
    friend ostream& operator<<(ostream& os, const SparseMatrix*);
    double getAlgebraicComplement(int col, int row);
    double countDet();
    SparseMatrix* getComplementaryMatrix();
    int rows();
    int cols();
    int size();
    bool diag();
    SparseMatrix* shift(int, int);
};