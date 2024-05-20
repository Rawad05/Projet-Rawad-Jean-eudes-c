#include "columns.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_CAPACITY 256

COLUMN *create_columns(ENUM_TYPE type, char *title) {
    COLUMN *new_column = (COLUMN *)malloc(sizeof(COLUMN));
    if (new_column == NULL) {
        return NULL; // Échec de l'allocation
    }

    new_column->title = strdup(title);
    if (new_column->title == NULL) {
        free(new_column);
        return NULL;
    }

    new_column->size = 0;
    new_column->max_size = INITIAL_CAPACITY;
    new_column->column_type = type;
    new_column->data = (COL_TYPE **)malloc(INITIAL_CAPACITY * sizeof(COL_TYPE *));
    if (new_column->data == NULL) {
        free(new_column->title);
        free(new_column);
        return NULL;
    }
    memset(new_column->data, 0, INITIAL_CAPACITY * sizeof(COL_TYPE *)); // Initialize pointers to NULL

    return new_column;
}

int insert_value(COLUMN *col, void *value) {
    if (col == NULL || value == NULL) {
        return 0; // Argument(s) invalide(s)
    }

    if (col->size == col->max_size) {
        int new_capacity = col->max_size + INITIAL_CAPACITY;
        COL_TYPE **new_data = (COL_TYPE **)realloc(col->data, new_capacity * sizeof(COL_TYPE *));
        if (new_data == NULL) {
            return 0; // Échec de la réallocation
        }
        col->data = new_data;
        col->max_size = new_capacity;
    }

    col->data[col->size] = (COL_TYPE *)malloc(sizeof(COL_TYPE));
    if (col->data[col->size] == NULL) {
        return 0; // Échec de l'allocation
    }

    switch (col->column_type) {
        case INT:
            col->data[col->size]->int_value = *((int *)value);
            break;
        case CHAR:
            col->data[col->size]->char_value = *((char *)value);
            break;
        case FLOAT:
            col->data[col->size]->float_value = *((float *)value);
            break;
        case DOUBLE:
            col->data[col->size]->double_value = *((double *)value);
            break;
        case STRING:
            col->data[col->size]->string_value = strdup((char *)value);
            if (col->data[col->size]->string_value == NULL) {
                free(col->data[col->size]);
                return 0;
            }
            break;
        default:
            free(col->data[col->size]);
            return 0;
    }

    col->size++;
    return 1;
}

void delete_column(COLUMN **col) {
    if (col == NULL || *col == NULL) {
        return;
    }

    for (unsigned int i = 0; i < (*col)->size; i++) {
        if ((*col)->data[i] != NULL) {
            if ((*col)->column_type == STRING) {
                free((*col)->data[i]->string_value);
            }
            free((*col)->data[i]);
        }
    }
    free((*col)->data);
    free((*col)->title);
    free(*col);
    *col = NULL;
}

void convert_value(COLUMN *col, unsigned long long int i, char *str, int size) {
    if (col == NULL || str == NULL || i >= col->size) {
        if (str != NULL) {
            str[0] = '\0';
        }
        return;
    }

    switch (col->column_type) {
        case INT:
            snprintf(str, size, "%d", col->data[i]->int_value);
            break;
        case CHAR:
            snprintf(str, size, "%c", col->data[i]->char_value);
            break;
        case FLOAT:
            snprintf(str, size, "%.2f", col->data[i]->float_value);
            break;
        case DOUBLE:
            snprintf(str, size, "%.2lf", col->data[i]->double_value);
            break;
        case STRING:
            snprintf(str, size, "%s", col->data[i]->string_value ? col->data[i]->string_value : "");
            break;
        default:
            str[0] = '\0'; // Pour les types non gérés ou pour ‘STRUCTURE’
            break;
    }
}

void print_col(COLUMN* col) {
    if (col == NULL) {
        printf("Column is NULL\n");
        return;
    }
    printf("Contents of column '%s':\n", col->title);
    for (unsigned int i = 0; i < col->size; i++) {
        char str[128]; // Augmentation de la taille pour une meilleure sécurité
        convert_value(col, i, str, sizeof(str));
        printf("[%u] %s\n", i, str);
    }
}

void convert_value_to_string(void* value, ENUM_TYPE type, char* str, int size) {
    if (value == NULL || str == NULL) {
        if (str != NULL) str[0] = '\0';
        return;
    }

    switch (type) {
        case INT:
            snprintf(str, size, "%d", *((int*)value));
            break;
        case CHAR:
            snprintf(str, size, "%c", *((char*)value));
            break;
        case FLOAT:
            snprintf(str, size, "%.2f", *((float*)value));
            break;
        case DOUBLE:
            snprintf(str, size, "%.2lf", *((double*)value));
            break;
        case STRING:
            snprintf(str, size, "%s", (char*)value);
            break;
        default:
            str[0] = '\0'; // Pour les types non gérés ou pour 'STRUCTURE'
            break;
    }
}

int count_occurrences(COLUMN* col, void* value) {
    if (col == NULL || value == NULL) {
        return 0;
    }

    int count = 0;
    char str_value[128], str_col_value[128];

    convert_value_to_string(value, col->column_type, str_value, sizeof(str_value));

    for (unsigned int i = 0; i < col->size; i++) {
        convert_value(col, i, str_col_value, sizeof(str_col_value));
        if (strcmp(str_col_value, str_value) == 0) {
            count++;
        }
    }

    return count;
}

void* get_value_at(COLUMN* col, unsigned long long int position) {
    if (col == NULL || position >= col->size) {
        return NULL;
    }

    return col->data[position];
}

int count_greater_than(COLUMN* col, void* value) {
    if (col == NULL || value == NULL) {
        return 0;
    }

    int count = 0;
    char str_value[128], str_col_value[128];

    convert_value_to_string(value, col->column_type, str_value, sizeof(str_value));

    for (unsigned int i = 0; i < col->size; i++) {
        convert_value(col, i, str_col_value, sizeof(str_col_value));
        if (strcmp(str_col_value, str_value) > 0) {
            count++;
        }
    }

    return count;
}

int count_less_than(COLUMN* col, void* value) {
    if (col == NULL || value == NULL) {
        return 0;
    }

    int count = 0;
    char str_value[128], str_col_value[128];

    convert_value_to_string(value, col->column_type, str_value, sizeof(str_value));

    for (unsigned int i = 0; i < col->size; i++) {
        convert_value(col, i, str_col_value, sizeof(str_col_value));
        if (strcmp(str_col_value, str_value) < 0) {
            count++;
        }
    }

    return count;
}

int count_equal_to (COLUMN* col, void* value) {
    return count_occurrences(col, value);
}

