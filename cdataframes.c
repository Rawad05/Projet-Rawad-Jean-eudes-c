#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cdataframes.h"


#define INITIAL_SIZE 10



CDataframe* create_dataframe()
{
    CDataframe* df = (CDataframe*)malloc(sizeof(CDataframe));
    if (!df) {
        return NULL; // Échec de l'allocation
    }

    df->columns = (COLUMN**)malloc(INITIAL_SIZE * sizeof(COLUMN*));
    if (!df->columns) {
        free(df);
        return NULL; // Échec de l'allocation
    }

    df->size = 0;
    df->capacity = INITIAL_SIZE;

    return df;
}

int add_column_to_dataframe(CDataframe* df, COLUMN* col)
{
    if (!df || !col) {
        return 0; // Arguments invalides
    }

    if (df->size >= df->capacity) {
        int new_capacity = df->capacity * 2;
        COLUMN** new_columns = (COLUMN**)realloc(df->columns, new_capacity * sizeof(COLUMN*));

        if (!new_columns) {
            return 0; // Échec de la réallocation
        }

        df->columns = new_columns;
        df->capacity = new_capacity;
    }

    df->columns[df->size] = col;
    df->size++;

    return 1; // Succès
}

void fill_dataframe_from_user_input(CDataframe* df)
{
    if (!df) {
        return; // DataFrame non initialisé
    }

    int value;
    for (int i = 0; i < df->size; i++) {
        printf("Veuillez saisir une valeur pour la colonne '%s' : ", df->columns[i]->title);
        scanf("%d", &value);
        insert_value(df->columns[i], &value);
    }
}

void fill_dataframe_hardcoded(CDataframe* df)
{
    if (!df) {
        return; // DataFrame non initialisé
    }

    // Exemple : Remplir le CDataframe avec des valeurs prédéfinies
    int values[] = {10, 20, 30, 40, 50};

    for (int i = 0; i < df->size && i < sizeof(values)/sizeof(int); i++) {
        insert_value(df->columns[i], &values[i]);
    }
}


void print_dataframe(CDataframe* df)
{
    if (!df) {
        printf("CDataframe non initialisé\n");
        return;
    }

    printf("Nombre de colonnes : %d\n", df->size);
    printf("Contenu du CDataframe :\n");

    // Afficher les titres des colonnes
    for (int i = 0; i < df->size; i++) {
        printf("%s\t", df->columns[i]->title);
    }
    printf("\n");

    // Afficher les valeurs de chaque colonne
    for (int i = 0; i < df->size; i++) {
        for (int j = 0; j < df->columns[i]->size; j++) {
            printf("%d\t", df->columns[i]->data[j]);
        }
        printf("\n");
    }
}

void print_dataframe_rows(CDataframe* df, int limit)
{
    if (!df) {
        printf("CDataframe non initialisé\n");
        return;
    }

    // Afficher les titres des colonnes
    for (int i = 0; i < df->size; i++) {
        printf("%s\t", df->columns[i]->title);
    }
    printf("\n");

    // Afficher les valeurs de chaque colonne jusqu'à la limite spécifiée
    for (int j = 0; j < limit; j++) {
        for (int i = 0; i < df->size; i++) {
            if (j < df->columns[i]->size) {
                printf("%d\t", df->columns[i]->data[j]);
            } else {
                printf("\t"); // Afficher un espace si la colonne n'a pas de valeur à cet indice
            }
        }
        printf("\n");
    }
}

void print_dataframe_columns(CDataframe* df, int limit)
{
    if (!df) {
        printf("CDataframe non initialisé\n");
        return;
    }

    // Afficher les titres des colonnes jusqu'à la limite spécifiée
    for (int i = 0; i < df->size && i < limit; i++) {
        printf("%s\t", df->columns[i]->title);
    }
    printf("\n");

    // Afficher les valeurs de chaque colonne
    int max_rows = 0;
    for (int i = 0; i < df->size && i < limit; i++) {
        if (df->columns[i]->size > max_rows) {
            max_rows = df->columns[i]->size;
        }
    }

    for (int j = 0; j < max_rows; j++) {
        for (int i = 0; i < df->size && i < limit; i++) {
            if (j < df->columns[i]->size) {
                printf("%d\t", df->columns[i]->data[j]);
            } else {
                printf("\t"); // Afficher un espace si la colonne n'a pas de valeur à cet indice
            }
        }
        printf("\n");
    }
}


int add_row_to_dataframe(CDataframe* df, int* values, int num_values)
{
    if (!df || num_values != df->size) {
        return 0; // Arguments invalides
    }

    for (int i = 0; i < num_values; i++) {
        insert_value(df->columns[i], &values[i]);
    }

    return 1; // Succès
}

int remove_row_from_dataframe(CDataframe* df, int index)
{
    if (!df || index < 0 || index >= df->columns[0]->size) {
        return 0; // Arguments invalides
    }

    for (int i = 0; i < df->size; i++) {
        // Déplacer les valeurs vers le bas pour remplir l'emplacement supprimé
        for (int j = index; j < df->columns[i]->size - 1; j++) {
            df->columns[i]->data[j] = df->columns[i]->data[j + 1];
        }
        df->columns[i]->size--; // Décrémenter la taille logique
    }

    return 1; // Succès
}

int remove_column_from_dataframe(CDataframe* df, int index)
{
    if (!df || index < 0 || index >= df->size) {
        return 0; // Arguments invalides
    }

    // Libérer la mémoire de la colonne supprimée
    delete_column(&(df->columns[index]));

    // Déplacer les pointeurs vers les colonnes suivantes
    for (int i = index; i < df->size - 1; i++) {
        df->columns[i] = df->columns[i + 1];
    }

    df->size--; // Décrémenter la taille

    return 1; // Succès
}

int rename_column(CDataframe* df, int index, char* new_title)
{
    if (!df || index < 0 || index >= df->size) {
        return 0; // Arguments invalides
    }

    free(df->columns[index]->title);
    df->columns[index]->title = strdup(new_title);

    return 1; // Succès
}

int search_value_in_dataframe(CDataframe* df, int value)
{
    if (!df) {
        return 0; // DataFrame non initialisé
    }

    for (int i = 0; i < df->size; i++) {
        for (int j = 0; j < df->columns[i]->size; j++) {
            if (df->columns[i]->data[j] == value) {
                return 1; // Valeur trouvée
            }
        }
    }

    return 0; // Valeur non trouvée
}

int access_replace_value(CDataframe* df, int row, int col, COL_TYPE *new_value)
{
    if (!df || row < 0 || col < 0 || row >= df->columns[0]->size || col >= df->size) {
        return 0; // Arguments invalides
    }

    df->columns[col]->data[row] = new_value;

    return 1; // Succès
}

void print_column_names(CDataframe* df)
{
    if (!df) {
        printf("CDataframe non initialisé\n");
        return;
    }

    printf("Noms des colonnes :\n");
    for (int i = 0; i < df->size; i++) {
        printf("%s\n", df->columns[i]->title);
    }
}

CDataframe* create_empty_dataframe() {
    CDataframe* df = create_dataframe();
    return df;
}

void fill_dataframe_from_user_input(CDataframe* df) {
    if (!df) {
        return; // DataFrame non initialisé
    }

    int value;
    for (int i = 0; i < df->size; i++) {
        printf("Veuillez saisir une valeur pour la colonne '%s' : ", df->columns[i]->title);
        scanf("%d", &value);
        insert_value(df->columns[i], &value);
    }

    void print_dataframe(CDataframe* df) {
    if (!df) {
        printf("CDataframe non initialisé\n");
        return;
    }

    printf("Nombre de colonnes : %d\n", df->size);
    printf("Contenu du CDataframe :\n");

    
    for (int i = 0; i < df->size; i++) {
        printf("%s\t", df->columns[i]->title);
    }
    printf("\n");

    
    for (int i = 0; i < df->size; i++) {
        for (int j = 0; j < df->columns[i]->size; j++) {
            printf("%d\t", df->columns[i]->data[j]);
        }
        printf("\n");
    }
}

void print_dataframe_rows(CDataframe* df, int limit) {
    if (!df) {
        printf("CDataframe non initialisé\n");
        return;
    }

    
    for (int i = 0; i < df->size; i++) {
        printf("%s\t", df->columns[i]->title);
    }
    printf("\n");

    
    for (int j = 0; j < limit; j++) {
        for (int i = 0; i < df->size; i++) {
            if (j < df->columns[i]->size) {
                printf("%d\t", df->columns[i]->data[j]);
            } else {
                printf("\t"); 
            }
        }
        printf("\n");
    }
}

