#ifndef FUNCTION_H
#define FUNCTION_H


typedef struct {
    int** data;
    int rows;
    int cols;
} CDataframes;


// Alimentation
CDataframes* creer_dataframe_vide(int rows, int cols);
void remplir_dataframe(CDataframes* df);
void remplir_dataframe_en_dur(CDataframes* df, int** values);

// Affichage
void afficher_dataframe(CDataframes* df);
void afficher_partie_lignes(CDataframes* df, int limit);
void afficher_partie_colonnes(CDataframes* df, int limit);

// Opérations usuelles
void ajouter_ligne(CDataframes* df, int* values);
void supprimer_ligne(CDataframes* df, int row_index);
void ajouter_colonne(CDataframes* df, int* values);
void supprimer_colonne(CDataframes* df, int col_index);
void renommer_colonne(CDataframes* df, int col_index, char* new_name);
int verifier_valeur(CDataframes* df, int value);
int acceder_valeur(CDataframes* df, int row, int col);
void remplacer_valeur(CDataframes* df, int row, int col, int value);
void afficher_noms_colonnes(CDataframes* df);

// Analyse et statistiques
int nombre_de_lignes(CDataframes* df);
int nombre_de_colonnes(CDataframes* df);
int nombre_de_cellules_egales(CDataframes* df, int x);
int nombre_de_cellules_inferieures(CDataframes* df, int x);
int nombre_de_cellules_superieures(CDataframes* df, int x);

#endif // FUNCTION_H


