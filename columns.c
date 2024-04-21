#include "columns.h"

COLUMN *create_columns(ENUM_TYPE type, char *title) {
    // Allocation mémoire pour la colonne
    COLUMN *new_column = (COLUMN *)malloc(sizeof(COLUMN));
    if (new_column == NULL) {
        return NULL; // Échec de l'allocation
    }

    // Initialisation des attributs de la colonne
    new_column->title = strdup(title); // Duplication du titre
    new_column->size = 0;
    new_column->max_size = 0;
    new_column->column_type = type;
    new_column->data = NULL;  // Initialisation du tableau de données à NULL
    new_column->index = NULL; // Initialisation du tableau d'indices à NULL

    return new_column;
}


int insert_value(COLUMN *col, void *value) {
    // Vérifier si la colonne est valide
    if (col == NULL) {
        return 0;
    }

    // Vérifier si la taille logique a atteint la taille maximale
    if (col->size == col->max_size) {
        // Réallouer la mémoire pour augmenter la taille physique
        COL_TYPE **new_data = (COL_TYPE **)realloc(col->data, (col->max_size + 256) * sizeof(COL_TYPE *));
        if (new_data == NULL) {
            return 0; // Échec de la réallocation
        }
        col->data = new_data;
        col->max_size += 256; // Mettre à jour la taille physique
    }

    // Allouer de l'espace pour la nouvelle valeur
    switch (col->column_type) {
        case INT:
            col->data[col->size] = (COL_TYPE *)malloc(sizeof(int));
            *((int *)col->data[col->size]) = *((int *)value);
            break;
        case CHAR:
            col->data[col->size] = (COL_TYPE *)malloc(sizeof(char));
            *((char *)col->data[col->size]) = *((char *)value);
            break;
            // Ajoutez d'autres cas selon les types nécessaires (UINT, FLOAT, DOUBLE, STRING, STRUCTURE)
        default:
            col->data[col->size] = NULL; // Cas par défaut
            break;
    }

    col->size++; // Mettre à jour la taille logique

    return 1; // Succès de l'insertion
}


void delete_column(COLUMN **col) {
    // Vérifier si la colonne est valide
    if (col == NULL || *col == NULL) {
        return;
    }

    // Libérer l'espace de chaque valeur dans le tableau de données
    for (unsigned int i = 0; i < (*col)->size; i++) {
        free((*col)->data[i]);
    }

    // Libérer le tableau de données
    free((*col)->data);

    // Libérer le tableau d'indices
    free((*col)->index);

    // Libérer le titre de la colonne
    free((*col)->title);

    // Libérer la structure de la colonne
    free(*col);

    // Définir le pointeur sur NULL pour éviter les problèmes de double libération
    *col = NULL;
}


void convert_value(COLUMN *col, unsigned long long int i, char *str, int size) {
    // Vérifier si la colonne est valide
    if (col == NULL || i >= col->size) {
        str[0] = '\0'; // Chaîne vide
        return;
    }

    // Convertir la valeur en chaîne de caractères en fonction du type de la colonne
    switch (col->column_type) {
        case INT:
            snprintf(str, size, "%d", col->data[i]->int_value);
            break;
        case CHAR:
            snprintf(str, size, "%c", col->data[i]->char_value);
            break;
        case FLOAT:
            snprintf(str, size, "%.2f", col->data[i]->float_value); // Affichage avec deux décimales
            break;
        case DOUBLE:
            snprintf(str, size, "%.2lf", col->data[i]->double_value); // Affichage avec deux décimales
            break;
        case STRING:
            snprintf(str, size, "%s", col->data[i]->string_value);
            break;
        case STRUCTURE:
            // À définir la manière de convertir une structure en chaîne de caractères
            snprintf(str, size, "Structure"); // Placeholder
            break;
        default:
            str[0] = '\0'; // Chaîne vide
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
        char str[50]; // Taille de la chaîne suffisamment grande pour contenir les valeurs converties
        convert_value(col, i, str, sizeof(str));
        printf("[%u] %s\n", i, str);
    }
}


int count_occurrences(COLUMN* col, void* value) {
    int count = 0;
    char str[50]; // Taille de la chaîne suffisamment grande pour contenir les valeurs converties

    for (unsigned int i = 0; i < col->size; i++) {
        convert_value(col, i, str, sizeof(str));

        // Comparer la chaîne convertie avec la chaîne de la valeur à rechercher
        if (strcmp(str, (char*)value) == 0) {
            count++;
        }
    }

    return count;
}

// Fonction pour retourner la valeur présente à la position x
void* get_value_at(COLUMN* col, unsigned long long int position) {
    if (position >= col->size) {
        return NULL; // Position hors limites
    }

    return col->data[position];
}

// Fonction pour retourner le nombre de valeurs supérieures à x
int count_greater_than(COLUMN* col, void* value) {
    int count = 0;
    char str[50]; // Taille de la chaîne suffisamment grande pour contenir les valeurs converties

    for (unsigned int i = 0; i < col->size; i++) {
        convert_value(col, i, str, sizeof(str));

        // Comparer la chaîne convertie avec la chaîne de la valeur à comparer
        if (strcmp(str, (char*)value) > 0) {
            count++;
        }
    }

    return count;
}

// Fonction pour retourner le nombre de valeurs inférieures à x
int count_less_than(COLUMN* col, void* value) {
    int count = 0;
    char str[50]; // Taille de la chaîne suffisamment grande pour contenir les valeurs converties

    for (unsigned int i = 0; i < col->size; i++) {
        convert_value(col, i, str, sizeof(str));

        // Comparer la chaîne convertie avec la chaîne de la valeur à comparer
        if (strcmp(str, (char*)value) < 0) {
            count++;
        }
    }

    return count;
}

// Fonction pour retourner le nombre de valeurs égales à x
int count_equal_to (COLUMN* col, void* value) {
    int count = 0;
    char str[50]; // Taille de la chaîne suffisamment grande pour contenir les valeurs converties

    for (unsigned int i = 0; i < col->size; i++) {
        convert_value(col, i, str, sizeof(str));

        // Comparer la chaîne convertie avec la chaîne de la valeur à comparer
        if (strcmp(str, (char*)value) == 0) {
            count++;
        }
    }

    return count;
}

