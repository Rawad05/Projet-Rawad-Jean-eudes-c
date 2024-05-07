// function.h

#ifndef FUNCTION_H
#define FUNCTION_H

typedef struct {
    int **data;   
    int rows;      
    int cols;      
} CDataframe;

// Function Prototypes
CDataframe create_empty_dataframe(int rows, int cols);
void fill_dataframe_from_input(CDataframe *df);
void print_dataframe(const CDataframe *df);
void print_dataframe_part(const CDataframe *df, int startRow, int endRow, int startCol, int endCol);
void add_row(CDataframe *df, int *row_values);
void delete_row(CDataframe *df, int row_index);
void add_column(CDataframe *df, int *col_values);
void delete_column(CDataframe *df, int col_index);
void rename_column(CDataframe *df, int col_index, char *new_name);
int search_value(const CDataframe *df, int value);
void set_value(CDataframe *df, int row, int col, int value);
int get_value(const CDataframe *df, int row, int col);
void print_column_names(const CDataframe *df);
void display_stats(const CDataframe *df);

#endif 
