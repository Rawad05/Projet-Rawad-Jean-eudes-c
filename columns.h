#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Enumération pour les types de données de la colonne
enum enum_type {
    NULLVAL = 1, UINT, INT, CHAR, FLOAT, DOUBLE, STRING, STRUCTURE
};
typedef enum enum_type ENUM_TYPE;


// Union pour le type de données de la colonne
union column_type {
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
};
typedef union column_type COL_TYPE;


// Structure pour la colonne
struct column {
    char *title;
    unsigned int size;       // Taille logique
    unsigned int max_size;   // Taille physique
    ENUM_TYPE column_type;   // Type de données de la colonne
    COL_TYPE **data;         // Tableau de pointeurs vers les données
    unsigned long long int *index;  // Tableau d'indices
};
typedef struct column COLUMN;


COLUMN *create_columns(ENUM_TYPE type, char *title);

int insert_value(COLUMN *col,void *value);

void delete_column(COLUMN **col);

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size);

void print_col(COLUMN* col);

int count_occurrences(COLUMN* col, void* value);

void* get_value_at(COLUMN* col, unsigned long long int position);

int count_greater_than(COLUMN* col, void* value);

int count_less_than(COLUMN* col, void* value);

int count_equal_to(COLUMN* col, void* value);
