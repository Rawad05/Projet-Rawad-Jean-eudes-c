#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "columns.c"
#include "cdataframes.h"



int main() {
    // Créer une colonne pour les entiers
    COLUMN *int_column = create_columns(INT, "Int Column");
    if (int_column == NULL) {
        printf("Erreur lors de la création de la colonne d'entiers\n");
        return 1;
    }

    // Insérer quelques valeurs dans la colonne d'entiers
    int values[] = {10, 20, 30, 40, 50};
    for (int i = 0; i < sizeof(values)/sizeof(values[0]); i++) {
        insert_value(int_column, &values[i]);
    }

    // Afficher la colonne d'entiers
    print_col(int_column);

    // Compter les occurrences d'une valeur spécifique dans la colonne d'entiers
    int count = count_occurrences(int_column, "30");
    printf("Occurrences of '30': %d\n", count);

    // Créer une colonne pour les chaînes de caractères
    COLUMN *string_column = create_columns(STRING, "String Column");
    if (string_column == NULL) {
        printf("Erreur lors de la création de la colonne de chaînes de caractères\n");
        delete_column(&int_column);
        return 1;
    }

    // Insérer quelques valeurs dans la colonne de chaînes de caractères
    char *strings[] = {"apple", "banana", "cherry"};
    for (int i = 0; i < sizeof(strings)/sizeof(strings[0]); i++) {
        insert_value(string_column, strings[i]);
    }

    // Afficher la colonne de chaînes de caractères
    print_col(string_column);

    // Libérer la mémoire allouée
    delete_column(&int_column);
    delete_column(&string_column);

    return 0;
}


int main() {
    // Création du dataframe
    CDataframe* df = create_dataframe();
    if (!df) {
        printf("Erreur lors de la création du CDataframe\n");
        return 1;
    }

    // Création des colonnes
    COLUMN* col1 = (COLUMN*)malloc(sizeof(COLUMN));
    col1->title = strdup("Colonne1");
    col1->data = (int*)malloc(5 * sizeof(int));
    col1->data[0] = (COL_TYPE *) 10;
    col1->data[1] = (COL_TYPE *) 20;
    col1->data[2] = (COL_TYPE *) 30;
    col1->data[3] = (COL_TYPE *) 40;
    col1->data[4] = (COL_TYPE *) 50;
    col1->size = 5;

    COLUMN* col2 = (COLUMN*)malloc(sizeof(COLUMN));
    col2->title = strdup("Colonne2");
    col2->data = (int*)malloc(5 * sizeof(int));
    col2->data[0] = (COL_TYPE *) 1;
    col2->data[1] = (COL_TYPE *) 2;
    col2->data[2] = (COL_TYPE *) 3;
    col2->data[3] = (COL_TYPE *) 4;
    col2->data[4] = (COL_TYPE *) 5;
    col2->size = 5;

    // Ajout des colonnes au dataframe
    add_column_to_dataframe(df, col1);
    add_column_to_dataframe(df, col2);

    // Remplissage du dataframe avec des valeurs prédéfinies
    fill_dataframe_hardcoded(df);

    // Affichage des noms des colonnes
    print_column_names(df);

    // Affichage du dataframe
    print_dataframe(df);

    // Libération de la mémoire
    for (int i = 0; i < df->size; i++) {
        free(df->columns[i]->title);
        free(df->columns[i]->data);
        free(df->columns[i]);
    }
    free(df->columns);
    free(df);

        // Création d'une instance de CDataframe
    CDataframe* df = create_dataframe();
    if (!df) {
        printf("Erreur lors de la création du CDataframe\n");
        return 1;
    }

    // Ajout de colonnes à la structure
    COLUMN* col1 = create_columns(INT, "Column1");
    COLUMN* col2 = create_columns(INT, "Column2");

    if (!add_column_to_dataframe(df, col1)) {
        printf("Erreur lors de l'ajout de la colonne 1\n");
        return 1;
    }

    if (!add_column_to_dataframe(df, col2)) {
        printf("Erreur lors de l'ajout de la colonne 2\n");
        return 1;
    }

    // Ajout de lignes de valeurs à la structure
    int values1[] = {1, 2, 3, 4, 5};
    int values2[] = {6, 7, 8, 9, 10};

    if (!add_row_to_dataframe(df, values1, sizeof(values1)/sizeof(values1[0]))) {
        printf("Erreur lors de l'ajout de la ligne de valeurs 1\n");
        return 1;
    }

    if (!add_row_to_dataframe(df, values2, sizeof(values2)/sizeof(values2[0]))) {
        printf("Erreur lors de l'ajout de la ligne de valeurs 2\n");
        return 1;
    }

    // Affichage du contenu de la structure
    printf("Contenu du CDataframe :\n");
    print_dataframe(df);

    // Libération de la mémoire
    for (int i = 0; i < df->size; i++) {
        free(df->columns[i]->title);
        free(df->columns[i]->data);
        free(df->columns[i]);
    }
    free(df->columns);
    free(df);

    return 0;
}
