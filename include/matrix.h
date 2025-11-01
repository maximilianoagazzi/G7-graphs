#ifdef MATRIX_H_EXPORT
#define MATRIX_API __declspec(dllexport)
#else
#define MATRIX_API __declspec(dllimport)
#endif

typedef struct matrix matrix;

MATRIX_API matrix* matrix_new(int rows, int columns); //Crea la matriz
MATRIX_API int matrix_resize(matrix* m, int new_rows, int new_columns); //Redimensiona la matriz agregando espacio
MATRIX_API void matrix_remove_row(matrix* m, int row); //remueve una fila, no redimensiona
MATRIX_API void matrix_remove_column(matrix* m, int column); //remueve una columna, no redimensiona
MATRIX_API void matrix_free(matrix* m); //Elimina la matriz
MATRIX_API int matrix_rows(matrix* m); //Obtener la cantidad de filas
MATRIX_API int matrix_columns(matrix* m); //Obtener la cantidad de columnas
MATRIX_API void* matrix_get(matrix* m, int row, int column); //Devuelve el elem. en posición
MATRIX_API void* matrix_set(matrix* m, int row, int column, void* value); //Asignar un elem.