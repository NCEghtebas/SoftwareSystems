/* Example code for Software Systems at Olin College.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct {
    double **data;
    int rows, cols;
} Matrix;


// Makes a new matrix and sets all elements to zero.
Matrix *make_matrix(int rows, int cols) {
    int i;
    Matrix *matrix = malloc(sizeof(Matrix));

    matrix->data = malloc(rows * sizeof(double *));
    matrix->rows = rows;
    matrix->cols = cols;

    for (i=0; i<rows; i++) {
	// use calloc to initialize to 0
	matrix->data[i] = calloc(cols, sizeof(double));
    }
    return matrix;
}

// Prints the elements of a matrix.
void print_matrix(Matrix *matrix) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    printf("%lf ", matrix->data[i][j]);
	}
	printf("\n");
    }
}

// Adds a scalar to all elements of a matrix.
void increment_matrix(Matrix *matrix, int incr) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    matrix->data[i][j] += incr;
	}
    }
}

// Sets the elements of a matrix to consecutive numbers.
void consecutive_matrix(Matrix *matrix) {
    int i, j;

    for (i=0; i<matrix->rows; i++) {
	for (j=0; j<matrix->cols; j++) {
	    matrix->data[i][j] = i * matrix->cols + j;
	}
    }
}

// Adds two matrices elementwise and stores the result in the given
// destination matrix (C).
void add_matrix(Matrix *A, Matrix *B, Matrix *C) {
    int i, j;

    assert(A->rows == B->rows && B->rows == C->rows);
    assert(A->cols == B->cols && B->cols == C->cols);

    for (i=0; i<A->rows; i++) {
	for (j=0; j<A->cols; j++) {
	    C->data[i][j] =  A->data[i][j] + B->data[i][j];
	}
    }
}

// Adds two matrices elementwise and returns a new matrix.
Matrix *add_matrix_func(Matrix *A, Matrix *B) {
    Matrix *C = make_matrix(A->rows, A->cols);
    add_matrix(A, B, C);
    return C;
}

// Performs matrix multiplication and stores the result in the given
// destination matrix (C).
void mult_matrix(Matrix *A, Matrix *B, Matrix *C) {
    int i, j, k;

    assert(A->rows == B->cols);
    assert(A->rows == C->rows);
    assert(B->cols == C->cols);

    for (i=0; i<C->rows; i++) {
	for (j=0; j<C->cols; j++) {
	    for (k=0; k<A->cols; k++) {
		C->data[i][j] += A->data[i][k] * B->data[k][j];
	    }
	}
    }
}

// Performs matrix multiplication and returns a new matrix.
Matrix *mult_matrix_func(Matrix *A, Matrix *B) {
    Matrix *C = make_matrix(A->rows, B->cols);
    mult_matrix(A, B, C);
    return C;
}

/*
 * Adds up all the elements in the matrix
 * summing the cols first
 */
double matrix_sum1(Matrix *A) {
    double total = 0.0;
    int i, j;

    for (i=0; i<A->rows; i++) {
	for (j=0; j<A->cols; j++) {
	    total += A->data[i][j];
	}
    }
    return total;
}
 
/*
 * Adds up all the elements in the matrix
 * summing the rows first
 */   
double matrix_sum2(Matrix *A) {
    double total = 0.0;
    int i, j;

    for (j=0; j<A->cols; j++) {
	for (i=0; i<A->rows; i++) {
	    total += A->data[i][j];
	}
    }
    return total;
}
    

// Adds up the rows of A and returns a heap-allocated array of doubles.
double *row_sum(Matrix *A) {
    double total;
    int i, j;

    double *res = malloc(A->rows * sizeof(double));

    for (i=0; i<A->rows; i++) {
	total = 0.0;
	for (j=0; j<A->cols; j++) {
	    total += A->data[i][j];
	}
	res[i] = total;
    }
    return res;
}

// Adds up the columns of A and returns a heap-allocated array of doubles.
double *col_sum(Matrix *A) {
    double total;
    int i, j;

    double *res = malloc(A->cols * sizeof(double));

    for (i=0; i<A->cols; i++) {
    total = 0.0;
    for (j=0; j<A->rows; j++) {
        total += A->data[j][i];
    }
    res[i] = total;
    }
    return res;
}

/* 
 * Adds up the forward diagonals of A and returns a double.
 * if matrix is not square, still computes forward diagonal value
 */
double fdiag_sum(Matrix *A) {
    double total= 0.0;
    int i;

    double res;// = (double) malloc(sizeof(double));
    if(A->rows >= A->cols){
        for (i=0; i<A->cols; i++) {
            total += A->data[i][i];
        }
        res = total;
        return res;
    }else if( (A->rows) < (A->cols)){
        for (i=0; i<A->rows; i++) {
            total += A->data[i][i];
        }
        res = total;
        return res;    
    }
    
}

/* 
 * Adds up the backward diagonals of A and returns a double.
 * if matrix is not square, still computes backward diagonal value
 */
double bdiag_sum(Matrix *A) {
    double total= 0.0;
    int i;

    double res;// = (double) malloc(sizeof(double));
    if(A->rows >= A->cols){
        for (i=0; i<A->cols; i++) {
            total += A->data[i][A->cols - (i+1)];
        }
        res = total;
        return res;
    }else if( (A->rows) < (A->cols)){
        for (i=0; i<A->rows; i++) {
            total += A->data[i][A->cols - (i+1)];
        }
        res = total;
        return res;    
    }
    
}



/* 
   http://en.wikipedia.org/wiki/Magic_square

   A magic square is an arrangement of numbers (usually integers) in a
   square grid, where the numbers in each row, and in each column, and
   the numbers in the forward and backward main diagonals, all add up
   to the same number. 

   Write a function called is_magic_square() that takes a matrix and 
   returns an int, 1 if the matrix is a magic square, and 0 otherwise.

   Feel free to use row_sum().
*/

/*
 * Checks to see if sum of all rows are equal. 
 * returns value of row sum if so and a 0 if not equal
 */
double row_equal(Matrix *A){
    double * rsum = row_sum(A);
    int i;
    int res;

    for(i =0; i< (A->rows -1); i++){
        if(rsum[i] == rsum [i+1]){
            res = 1;
        }else{
            res = 0;
        }
    }
    if (res == 1){
        return res* rsum[0];
    }
    return res;
}

/*
 * Checks to see if sum of all cols are equal. 
 * returns value of col sum if so and a 0 if not equal
 */
double col_equal(Matrix *A){
    double * rsum = row_sum(A);
    int i;
    int res;

    for(i =0; i< (A->cols -1); i++){
        if(rsum[i] == rsum [i+1]){
            res = 1;
        }else{
            res = 0;
        }
    }
    if (res == 1){
        return res* rsum[0];
    }
    return res;
}


/*
 *Checks to see if matrix is magic square
 * returns 1 if so and 0 if not
 */
int is_magic_square(Matrix *A){
    double fsumdiag, bsumdiag;
    double requal, cequal;

    if(A->rows != A->cols){
        printf("%s\n",  "Matrix is not square.");
        exit(0);    
    }else{
        fsumdiag= fdiag_sum(A);
        bsumdiag= bdiag_sum(A); 
        requal = row_equal(A); 
        cequal = col_equal(A);

        /* checks to see if the numbers in each row, in each column,
         * the numbers in the forward and backward main diagonals, 
         * all add up to the same number. If so, matrix is a magic square!
         */
        if( (requal == cequal) && (fsumdiag == bsumdiag) && (requal == fsumdiag) && (cequal == bsumdiag)){
            return 1;
        }else{
            return 0;
        }
    }
}


int main() {
    int i;
    double sum;
    double *sums;
    double fsumdiag;
    double bsumdiag;
    double requal;

    Matrix *A = make_matrix(3, 3);
    consecutive_matrix(A);
    //increment_matrix(A, 1);
    printf("A\n");
    print_matrix(A);

    Matrix *C = add_matrix_func(A, A);
    printf("A + A\n");
    print_matrix(C);

    Matrix *B = make_matrix(4, 3);
    increment_matrix(B, 1);
    printf("B\n");
    print_matrix(B);

    Matrix *D = mult_matrix_func(A, B);
    printf("D\n");
    print_matrix(D);

    sum = matrix_sum1(A);
    printf("sum = %lf\n", sum);

    sum = matrix_sum2(A);
    printf("sum = %lf\n", sum);

    sums = row_sum(A);
    requal= row_equal(A);
    printf("Rows arevqual if not vale not 0. val= %f\n", requal);
    for (i=0; i<A->rows; i++) {
	printf("row %d\t%lf\n", i, sums[i]);
    }
    // should print 6, 22, 38

    sums = col_sum(A);
    requal= row_equal(A);
    printf("Cols arevqual if not vale not 0. val = %f\n", requal);
    for (i=0; i<A->cols; i++) {
    printf("column %d\t%lf\n", i, sums[i]);
    }
    //should print 12, 15, 18, 21

    printf("diagonals\n");

    fsumdiag= bdiag_sum(A);
    printf("row %f\n", fsumdiag);

    int yn = is_magic_square(A);
    if(yn == 1){
        printf("Matrix is Magic Square! %d\n", yn);
    }else{
        printf("Matrix is not magic square. %d\n", yn);
    }

    return 0;
}
