#include "function.h"
#include <stdio.h>
#include <stdlib.h>

CDataframe create_empty_dataframe(int rows, int cols) {
    CDataframe df;
    df.rows = rows;
    df.cols = cols;
    df.data = (int**) malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        df.data[i] = (int*) calloc(cols, sizeof(int));
    }
    return df;
}

void fill_dataframe_from_input(CDataframe *df) {
    printf("Enter the data for the dataframe:\n");
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            scanf("%d", &df->data[i][j]);
        }
    }
}

void print_dataframe(const CDataframe *df) {
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            printf("%d ", df->data[i][j]);
        }
        printf("\n");
    }
}


void display_stats(const CDataframe *df) {
    // Example function to display stats
    printf("Number of rows: %d\n", df->rows);
    printf("Number of columns: %d\n", df->cols);
}
