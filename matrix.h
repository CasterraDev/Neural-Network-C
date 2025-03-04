#pragma once

typedef struct {
    double* data;
    int rows;
    int cols;
} Matrix;


/**
 * QoL function to get access to an element without having to do math
 */
#define MAT_AT(mat, r, c) (mat)->data[(r) * (mat)->cols + c]

/**
 * QoL function to print a matrix just by giving the matrix
 */
#define matPrint(m) matrixPrint(m, #m, 0);

/**
 * Create and Return a matrix.
 * Calls Malloc MUST be freed (look at matrixFree)
 * @param rows amount of rows the matrix needs
 * @param cols amount of cols the matrix needs
 * @return The matrix with the requested rows/cols
 */
Matrix* matrixCreate(int rows, int cols);

/**
 * Frees a matrix
 * @param m The matrix to be freed
 */
void matrixFree(Matrix* m);


/**
 * Fills a matrix with `val`
 * @param m The matrix to be filled
 * @param val The value to fill the matrix with
 */
void matrixFill(Matrix* m, double val);

/**
 * Prints the matrix in a pretty way. Might want to look at matPrint for some QoL
 * @param m The matrix to be printed
 * @param name Name to use for the print
 * @param padding Amount of padding to use
 */
void matrixPrint(Matrix* m, const char* name, int padding);

/**
 * Makes a matrix into an identity matrix.
 * @param m The matrix to use. Needs to be a square matrix
 */
void matrixIdentity(Matrix* m);

/**
 * Sees if a matrix is an identity
 * @param m The matrix to look at
 * @return true if it is an identity; false if not
 */
char matrixIsIdentity(Matrix* m);

/**
 * Fills a matrix with random decimal values
 * @param m The matrix to use
 * @param low The low of the random values
 * @param high The high of the random values
 */
void matrixRand(Matrix* m, double low, double high);

/**
 * Adds two matrices together
 * @param dest The matrix where the result is stored
 * @param a The first matrix to use
 * @param b The second matrix to use
 */
void matrixAdd(Matrix* dest, const Matrix* a, const Matrix* b);

/**
 * Subtracts two matrices together
 * @param dest The matrix where the result is stored
 * @param a The first matrix to use
 * @param b The second matrix to use
 */
void matrixSub(Matrix* dest, const Matrix* a, const Matrix* b);

/**
 * Multiples an entire matrix by `val`
 * @param a The matrix to use
 * @param val The value to use
 */
void matrixScalar(Matrix* a, double val);

/**
 * Multiples two matrices together
 * @param dest The matrix where the result is stored
 * @param a The first matrix to use
 * @param b The second matrix to use
 */
void matrixMulti(Matrix* dest, const Matrix* a, const Matrix* b);

/**
 * Transposes a matrix
 * @param dest The matrix where the result is stored
 * @param a The matrix to use
 */
void matrixTranspose(Matrix* dest, const Matrix* a);

/**
 * Copies a matrix
 * @param dest The matrix where the result is stored
 * @param a The matrix to copy
 */
void matrixCopy(Matrix* dest, const Matrix* a);

/**
 * Shuffles the rows in a matrix.
 * @param a The matrix to shuffle
 */
void matrixShuffleRows(Matrix* m);

void matrixRowSwap(Matrix* m1, int row1, Matrix* m2, int row2);
void matrixRowScalar(Matrix* m, int row, double val);
void matrixRowAdd(Matrix* m1, int row1, const Matrix* m2, int row2);
Matrix* matrixRowAddDestCreate(const Matrix* m1, int row1, const Matrix* m2, int row2);
Matrix* matrixSubmatrixCreate(const Matrix* m, int* rowArrIdxs, int rowArrLen, int* colArrIdxs, int colArrLen);

#ifdef MATRIX_IMPLEMENTATION
#include <stdio.h>
#ifndef MATRIX_MALLOC
#include <stdlib.h>
#define MATRIX_MALLOC malloc
#endif

#ifndef MATRIX_FREE
#include <stdlib.h>
#define MATRIX_FREE free
#endif

#ifndef MATRIX_ASSERT
#include <assert.h>
#define MATRIX_ASSERT assert
#endif

Matrix* matrixCreate(int rows, int cols) {
    Matrix* m = MATRIX_MALLOC(sizeof(Matrix));
    m->rows = rows;
    m->cols = cols;
    m->data = MATRIX_MALLOC(sizeof(double) * rows * cols);
    return m;
}

void matrixFill(Matrix* m, double val) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            printf("%d:%d\n", i, j);
            MAT_AT(m, i, j) = val;
        }
    }
}

void matrixIdentity(Matrix* m) {
    assert(m->cols != m->rows);
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            MAT_AT(m, i, j) = (i == j) ? 1 : 0;
        }
    }
}

char matrixIsIdentity(Matrix* m) {
    if (m->cols != m->rows) {
        return 0;
    }
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            if (i == j) {
                if (MAT_AT(m, i, j) != 1) {
                    return 0;
                }
            } else {
                if (MAT_AT(m, i, j) != 0) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

void matrixFree(Matrix* m) {
    if (m->data) {
        MATRIX_FREE(m->data);
    }
    MATRIX_FREE(m);
}

void matrixPrint(Matrix* m, const char* name, int p) {
    printf("%*s%s = [\n", (int)p, "", name);
    for (int i = 0; i < m->rows; i++) {
        printf("%*s    ", (int)p, "");
        for (int j = 0; j < m->cols; j++) {
            printf("%f ", MAT_AT(m, i, j));
        }
        printf("\n");
    }
    printf("%*s]\n", (int)p, "");
}

void matrixRand(Matrix* m, double low, double high) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            MAT_AT(m, i, j) =
                ((float)rand() / (float)RAND_MAX) * (high - low) + low;
        }
    }
}

void matrixAdd(Matrix* dest, const Matrix* a, const Matrix* b) {
    assert(a->rows == b->rows && dest->rows == a->rows);
    assert(a->cols == b->cols && dest->cols == a->cols);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            MAT_AT(dest, i, j) = MAT_AT(a, i, j) + MAT_AT(b, i, j);
        }
    }
}

void matrixSub(Matrix* dest, const Matrix* a, const Matrix* b) {
    assert(a->rows == b->rows && dest->rows == a->rows);
    assert(a->cols == b->cols && dest->cols == a->cols);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            MAT_AT(dest, i, j) = MAT_AT(a, i, j) + (-1 * MAT_AT(b, i, j));
        }
    }
}

void matrixScalar(Matrix* a, double val) {
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            MAT_AT(a, i, j) *= val;
        }
    }
}

void matrixMulti(Matrix* dest, const Matrix* a, const Matrix* b) {
    assert(a->cols == b->rows && dest->rows == a->rows &&
           dest->cols == b->cols);
    int n = a->cols;
    for (int i = 0; i < dest->rows; i++) {
        for (int j = 0; j < dest->cols; j++) {
            for (int k = 0; k < n; k++) {
                MAT_AT(dest, i, j) += MAT_AT(a, i, k) * MAT_AT(b, k, j);
            }
        }
    }
}

void matrixTranspose(Matrix* dest, const Matrix* a) {
    assert(dest->cols == a->rows && dest->rows == a->cols);
    for (int i = 0; i < dest->rows; i++) {
        for (int j = 0; j < dest->cols; j++) {
            MAT_AT(dest, i, j) = MAT_AT(a, j, i);
        }
    }
}

void matrixCopy(Matrix* dest, const Matrix* a) {
    assert(dest->cols == a->cols && dest->rows == a->rows);
    for (int i = 0; i < a->rows; i++) {
        for (int j = 0; j < a->cols; j++) {
            MAT_AT(dest, i, j) = MAT_AT(a, i, j);
        }
    }
}

Matrix matRow(Matrix* m, int row) {
    return (Matrix){.rows = 1, .cols = m->cols, .data = &MAT_AT(m, row, 0)};
}

void matFunc(Matrix* m, double (*callbackFunc)(double d)) {
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            MAT_AT(m, i, j) = callbackFunc(MAT_AT(m, i, j));
        }
    }
}

void matrixShuffleRows(Matrix* m) {
    for (int i = 0; i < m->rows; i++) {
        int randRow = (i + rand()) & (m->rows - i);
        for (int j = 0; j < m->cols; j++) {
            double save = MAT_AT(m, i, j);
            MAT_AT(m, i, j) = MAT_AT(m, randRow, j);
            MAT_AT(m, randRow, j) = save;
        }
    }
}

void matrixRowSwap(Matrix* m1, int row1, Matrix* m2, int row2) {
    double save = MAT_AT(m1, row1, row2);
    MAT_AT(m1, row1, row2) = MAT_AT(m2, row2, row1);
    MAT_AT(m2, row2, row1) = save;
}

void matrixRowScalar(Matrix* m, int row, double val) {
    for (int j = 0; j < m->cols; j++) {
        MAT_AT(m, row, j) *= val;
    }
}

void matrixRowAdd(Matrix* m1, int row1, const Matrix* m2, int row2) {
    assert(m1->rows == m2->rows && m1->cols == m2->cols);
    for (int j = 0; j < m1->cols; j++) {
        MAT_AT(m1, row1, j) += MAT_AT(m2, row2, j);
    }
}

Matrix* matrixRowAddDestCreate(const Matrix* m1, int row1, const Matrix* m2,
                               int row2) {
    assert(m1->rows == m2->rows && m1->cols == m2->cols);
    Matrix* dest = matrixCreate(1, m1->cols);
    for (int j = 0; j < m1->cols; j++) {
        MAT_AT(dest, 0, j) = MAT_AT(m1, row1, j) + MAT_AT(m2, row2, j);
    }
    return dest;
}

Matrix* matrixSubmatrixCreate(const Matrix* m, int* rowArrIdxs, int rowArrLen,
                           int* colArrIdxs, int colArrLen) {
    assert(m->rows > rowArrLen && m->cols > colArrLen);
    Matrix* dest = matrixCreate(m->rows - rowArrLen, m->cols - colArrLen);

    int ic = 0;
    int jc = 0;
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            char shouldAssign = 1;
            for (int ia = 0; ia < rowArrLen; ia++) {
                if (i == rowArrIdxs[ia]) {
                    shouldAssign = 0;
                }
            }
            if (!shouldAssign) {
                continue;
            }
            for (int ja = 0; ja < colArrLen; ja++) {
                if (j == colArrIdxs[ja]) {
                    shouldAssign = 0;
                }
            }
            if (shouldAssign) {
                // TODO: For some reason you need to flip jc and ic for it to work. I don't understand why. Look into this
                MAT_AT(dest, jc, ic) = MAT_AT(m, i, j);
                ic++;
                if (ic >= m->rows - rowArrLen){
                    ic = 0;
                    jc++;
                }
            }
        }
    }

    return dest;
}
#endif
