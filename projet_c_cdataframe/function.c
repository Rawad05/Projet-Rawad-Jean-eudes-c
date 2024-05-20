#include <stdio.h>
#include <stdlib.h>
#include "function.h"

// Alimentation
CDataframes* creer_dataframe_vide(int rows, int cols) {
    CDataframes* df = (CDataframes*)malloc(sizeof(CDataframes));
    df->data = (int*)malloc(rows * sizeof(int));
    for (int i = 0; i < rows; i++) {
        df->data[i] = (int*)malloc(cols * sizeof(int));
    }
    df->rows = rows;
    df->cols = cols;
    return df;
}

void remplir_dataframe(CDataframes* df) {
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            printf("Enter value for cell [%d][%d]: ", i, j);
            scanf("%d", &(df->data[i][j]));
        }
    }
}

void remplir_dataframe_en_dur(CDataframes* df, int** values) {
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            df->data[i][j] = values[i][j];
        }
    }
}

// Affichage
void afficher_dataframe(CDataframes* df) {
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            printf("%d ", df->data[i][j]);
        }
        printf("\n");
    }
}

void afficher_partie_lignes(CDataframes* df, int limit) {
    for (int i = 0; i < limit && i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            printf("%d ", df->data[i][j]);
        }
        printf("\n");
    }
}

void afficher_partie_colonnes(CDataframes* df, int limit) {
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < limit && j < df->cols; j++) {
            printf("%d ", df->data[i][j]);
        }
        printf("\n");
    }
}

// Opérations usuelles
void ajouter_ligne(CDataframes* df, int* values) {
    df->rows++;
    df->data = (int*)realloc(df->data, df->rows * sizeof(int));
    df->data[df->rows - 1] = (int*)malloc(df->cols * sizeof(int));
    for (int i = 0; i < df->cols; i++) {
        df->data[df->rows - 1][i] = values[i];
    }
}

void supprimer_ligne(CDataframes* df, int row_index) {
    if (row_index < 0 || row_index >= df->rows) return;
    free(df->data[row_index]);
    for (int i = row_index; i < df->rows - 1; i++) {
        df->data[i] = df->data[i + 1];
    }
    df->rows--;
    df->data = (int*)realloc(df->data, df->rows * sizeof(int));
}

void ajouter_colonne(CDataframes* df, int* values) {
    for (int i = 0; i < df->rows; i++) {
        df->data[i] = (int*)realloc(df->data[i], (df->cols + 1) * sizeof(int));
        df->data[i][df->cols] = values[i];
    }
    df->cols++;
}

void supprimer_colonne(CDataframes* df, int col_index) {
    if (col_index < 0 || col_index >= df->cols) return;
    for (int i = 0; i < df->rows; i++) {
        for (int j = col_index; j < df->cols - 1; j++) {
            df->data[i][j] = df->data[i][j + 1];
        }
        df->data[i] = (int*)realloc(df->data[i], (df->cols - 1) * sizeof(int));
    }
    df->cols--;
}

void renommer_colonne(CDataframes* df, int col_index, char* new_name) {}

int verifier_valeur(CDataframes* df, int value) {
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            if (df->data[i][j] == value) return 1;
        }
    }
    return 0;
}

int acceder_valeur(CDataframes* df, int row, int col) {
    if (row >= 0 && row < df->rows && col >= 0 && col < df->cols) {
        return df->data[row][col];
    }
    return -1; // Error value
}

void remplacer_valeur(CDataframes* df, int row, int col, int value) {
    if (row >= 0 && row < df->rows && col >= 0 && col < df->cols) {
        df->data[row][col] = value;
    }
}

void afficher_noms_colonnes(CDataframes* df) {
    // This function would be more relevant if column names were stored
    // As is, it doesn't make sense with an integer array.
}

// Analyse et statistiques
int nombre_de_lignes(CDataframes* df) {
    return df->rows;
}

int nombre_de_colonnes(CDataframes* df) {
    return df->cols;
}

int nombre_de_cellules_egales(CDataframes* df, int x) {
    int count = 0;
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            if (df->data[i][j] == x) count++;
        }
    }
    return count;
}

int nombre_de_cellules_inferieures(CDataframes* df, int x) {
    int count = 0;
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            if (df->data[i][j] < x) count++;
        }
    }
    return count;
}

int nombre_de_cellules_superieures(CDataframes* df, int x) {
    int count = 0;
    for (int i = 0; i < df->rows; i++) {
        for (int j = 0; j < df->cols; j++) {
            if (df->data[i][j] > x) count++;
        }
    }
    return count;
}
