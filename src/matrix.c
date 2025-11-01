#include <stdlib.h>
#define MATRIX_H_EXPORT
#include "matrix.h"

typedef struct matrix {
    void** data; // Puntero a un array de punteros a void
    int size; // Número actual de elementos de la matiz de forma unidimensional
    int rows;    // Número de filas de la matriz
    int columns;  //Número de columnas de la matriz
} matrix;

matrix* matrix_new(int rows, int columns)
{
    matrix *m = (matrix *)malloc(sizeof(matrix));
    if (m == NULL) {
        return NULL;
    }
    if (rows <= 0 || columns <= 0) {
        return NULL;
    }
    m->data = NULL;
    m->rows = rows;
    m->columns = columns;
    m->size = rows*columns;
    m->data = (void **)malloc((m->size) * sizeof(void *));
    if (m->data == NULL) {
        free(m);
        return NULL;
    }
    return m;
}

int matrix_resize(matrix* m, int new_rows, int new_columns)  //Redimensiona la matriz y retorna 1 si tuvo exito
{
    if(m == NULL || new_rows <= 0 || new_columns <= 0) return 0;

    int rows = m->rows;
    int columns = m->columns;
    int new_size = new_rows*new_columns;

    void** new_data = (void**)calloc(new_size, sizeof(void*));
    if(new_data == NULL) return 0;

    int min_rows = (new_rows < rows) ? new_rows : rows;
    int min_columns = (new_columns < columns) ? new_columns : columns;

    for(int i=0; i<min_rows; i++) {
        for(int j=0; j<min_columns; j++) {
            int index = i*columns + j;
            int new_index = i*new_columns + j;
            new_data[new_index] = m->data[index];
        }
    }

    free(m->data);
    m->data = new_data;
    m->rows = new_rows;
    m->columns = new_columns;
    m->size = new_size;
    
    return 1;
}

void matrix_remove_row(matrix* m, int row)
{
    if(m == NULL || row < 0 || row >= m->rows) return;

    for(int i=row; i<m->rows-1; i++) {
        for(int j=0; j<m->columns; j++)
            m->data[i*m->columns + j] = m->data[(i + 1)*m->columns + j];
    }
    m->rows--;
    m->size = m->rows*m->columns;
}

void matrix_remove_column(matrix* m, int column)
{
    if(m == NULL || column < 0 || column >= m->columns) return;

    int write_idx = 0; 
    for(int i=0; i<m->rows; i++) {
        for(int j=0; j<m->columns; j++) {
            if (j != column) {
                int read_idx = i*m->columns + j;
                m->data[write_idx] = m->data[read_idx]; 
                write_idx++;
            }
        }
    }
    m->columns--;
    m->size = m->rows*m->columns;
}

void matrix_free(matrix* m)
{
    if (m != NULL) {
        free(m->data);
        free(m);
    }
    return;
}

int matrix_rows(matrix* m)
{
    if (m != NULL) {
        return m->rows;
    }
    return -1; // Indica error
}

int matrix_columns(matrix* m)
{
    if (m != NULL) {
        return m->columns;
    }
    return -1; // Indica error
}

void* matrix_get(matrix* m, int row, int column)
{
    if (m != NULL && row >= 0 && column >= 0 && row < m->rows && column < m->columns) {
        return m->data[row*(m->columns) + column];
    }
    return NULL; // Indica error
}

void* matrix_set(matrix* m, int row, int column, void* value)
{
    if (m != NULL && row >= 0 && column >= 0 && row < m->rows && column < m->columns) {
        void *old_value = m->data[row*(m->columns) + column];
        m->data[row*(m->columns) + column] = value;
        return old_value;
    }
    return NULL; // Indica error
}