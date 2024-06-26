#ifndef CDATAFRAMES_H
#define CDATAFRAMES_H

#include "column.h" // Assurez-vous que columns.h est protégé par des include guards

typedef struct {
    COLUMN** columns;
    int size;
    int capacity;
} CDataframe;

CDataframe* create_dataframe();
int add_column_to_dataframe(CDataframe* df, COLUMN* col);
void fill_dataframe_from_user_input(CDataframe* df);
void fill_dataframe_hardcoded(CDataframe* df);
void print_dataframe(CDataframe* df);
void delete_dataframe(CDataframe* df);


void print_dataframe_rows(CDataframe* df, int limit);

void print_dataframe_columns(CDataframe* df, int limit);

int add_row_to_dataframe(CDataframe* df, int* values, int num_values);

int remove_row_from_dataframe(CDataframe* df, int index);

int remove_column_from_dataframe(CDataframe* df, int index);

int rename_column(CDataframe* df, int index, char* new_title);

int search_value_in_dataframe(CDataframe* df, int value);

int access_replace_value(CDataframe* df, int row, int col, COL_TYPE *new_value);

void print_column_names(CDataframe* df);

void delete_dataframe(CDataframe* df);

#endif // CDATAFRAMES_H




