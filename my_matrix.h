#ifndef SRC_MY_MATRIX_H_
#define SRC_MY_MATRIX_H_

#include <stdio.h>
#include <stdlib.h>

#define MY_EPS 1e-7
#define SUCCESS 1
#define FAILURE 0

typedef struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int my_create_matrix(int rows, int columns, matrix_t *result);
void my_remove_matrix(matrix_t *A);

int my_eq_matrix(matrix_t *A, matrix_t *B);

int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int my_mult_number(matrix_t *A, double number, matrix_t *result);
int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int my_transpose(matrix_t *A, matrix_t *result);
int my_minor(matrix_t *A, int number_rows, int number_columns,
             matrix_t *result);
int my_calc_complements(matrix_t *A, matrix_t *result);
int my_determinant(matrix_t *A, double *result);
int my_inverse_matrix(matrix_t *A, matrix_t *result);

#endif