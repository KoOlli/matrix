// "Copyright 2022 Ko Olli"

#include "my_matrix.h"

#include <math.h>

int my_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++)
      result->matrix[i] = calloc(columns, sizeof(double));
  } else if (rows < 1 || columns < 1) {
    result->rows = 0;
    result->columns = 0;
    result->matrix = NULL;
    res = 1;
  }
  return res;
}

void my_remove_matrix(matrix_t *A) {
  if (A->rows > 0 && A->columns > 0 && A->matrix != NULL) {
    for (int j = 0; j < A->rows; j++) free(A->matrix[j]);
    free(A->matrix);
  }
  A->columns = 0;
  A->rows = 0;
}

int my_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(fabs(A->matrix[i][j]) - fabs(B->matrix[i][j])) > 1e-6) {
          res = FAILURE;
        }
      }
    }
  } else {
    res = FAILURE;
  }
  return res;
}

int my_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;

  if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->rows == B->rows && B->columns == A->columns) {
      my_create_matrix(A->rows, A->columns, result);

      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      my_create_matrix(0, 0, result);
      res = 2;
    }
  } else if (A->rows < 1 || A->columns < 1 || B->rows < 1 || B->columns < 1) {
    my_create_matrix(0, 0, result);
    res = 1;
  }
  return res;
}

int my_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;

  if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->rows == B->rows && B->columns == A->columns) {
      my_create_matrix(A->rows, A->columns, result);

      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      my_create_matrix(0, 0, result);
      res = 2;
    }
  } else if (A->rows < 1 || A->columns < 1 || B->rows < 1 || B->columns < 1) {
    my_create_matrix(0, 0, result);
    res = 1;
  }
  return res;
}

int my_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 0;

  if (A->rows < 1 || A->columns < 1) {
    my_create_matrix(0, 0, result);
    res = 1;
  } else if (A->rows > 0 && A->columns > 0) {
    my_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}

int my_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;

  if (A->rows > 0 && A->columns > 0 && B->rows > 0 && B->columns > 0) {
    if (A->columns == B->rows) {
      my_create_matrix(A->rows, B->columns, result);
      for (int n = 0; n < A->rows; n++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[n][j] += A->matrix[n][k] * B->matrix[k][j];
          }
        }
      }
    } else {
      my_create_matrix(0, 0, result);
      res = 2;
    }
  } else if (A->rows < 1 || A->columns < 1 || B->rows < 1 || B->columns < 1) {
    my_create_matrix(0, 0, result);
    res = 1;
  }
  return res;
}

int my_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;

  if (A->columns > 0 && A->rows > 0) {
    my_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  } else if (A->columns < 1 || A->rows < 1) {
    my_create_matrix(0, 0, result);
    res = 1;
  }
  return res;
}

int my_minor(matrix_t *A, int number_rows, int number_columns,
             matrix_t *result) {
  int res = 0;

  my_create_matrix(A->rows - 1, A->columns - 1, result);
  if (number_rows < A->rows && number_columns < A->columns) {
    for (int i = 0, k = 0; i < A->rows && k < result->rows; i++, k++) {
      for (int j = 0, m = 0; j < A->columns && m < result->columns; j++, m++) {
        if (i == number_rows) {
          i++;
        }
        if (j == number_columns) {
          j++;
        }
        result->matrix[k][m] = A->matrix[i][j];
      }
    }
  }
  return res;
}

int my_calc_complements(matrix_t *A, matrix_t *result) {
  int ret = 0;
  if (A->rows == A->columns) {
    if (A->rows > 0 && A->columns > 0) {
      my_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          double determ = 0.0;

          matrix_t promezhut;
          if (A->rows == 1 && A->columns == 1) {
            result->matrix[0][0] = 1;
          } else {
            my_minor(A, i, j, &promezhut);
            my_determinant(&promezhut, &determ);
            my_remove_matrix(&promezhut);
            result->matrix[i][j] = determ * (pow((-1), (i + j)));
          }
        }
      }
    } else if (A->rows < 1 || A->columns < 1) {
      my_create_matrix(0, 0, result);
      ret = 1;
    }
  } else {
    my_create_matrix(0, 0, result);
    ret = 2;
  }
  return ret;
}

int my_determinant(matrix_t *A, double *res) {
  matrix_t res_minor;
  int ret = 0;
  *res = 0;
  if (A->rows == A->columns) {
    if (A->rows > 0 && A->columns > 0) {
      if (A->rows == 1) {
        *res = A->matrix[0][0];
      } else if (A->rows == 2) {
        *res = A->matrix[0][0] * A->matrix[1][1] -
               A->matrix[0][1] * A->matrix[1][0];
      } else {
        int deeple = -1;
        for (int j = 0; j < A->columns; j++) {
          double temp = 0.0;
          deeple = -1 * deeple;
          my_minor(A, 0, j, &res_minor);
          my_determinant(&res_minor, &temp);
          my_remove_matrix(&res_minor);
          *res += deeple * A->matrix[0][j] * temp;
        }
      }
    } else if (A->rows < 1 || A->columns < 1) {
      ret = 1;
    }
  } else {
    ret = 2;
  }
  return ret;
}

int my_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 0;

  matrix_t promezh_calc_compl;
  matrix_t promezh_transp;

  double promezh_determ = 0.0;

  if (A->rows == A->columns) {
    if (A->columns > 0 && A->rows > 0) {
      my_determinant(A, &promezh_determ);
      if (promezh_determ == 0.0) {
        my_create_matrix(0, 0, result);
        res = 2;
      } else {
        my_calc_complements(A, &promezh_calc_compl);
        my_transpose(&promezh_calc_compl, &promezh_transp);

        my_mult_number(&promezh_transp, 1.0 / promezh_determ, result);

        my_remove_matrix(&promezh_calc_compl);
        my_remove_matrix(&promezh_transp);
      }
    } else if (A->columns < 1 || A->rows < 1) {
      my_create_matrix(0, 0, result);
      res = 1;
    }
  } else {
    my_create_matrix(0, 0, result);
    res = 2;
  }
  return res;
}
