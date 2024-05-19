#ifndef FUNCTION_H
#define FUNCTION_H


typedef struct {
    int** data;
    int rows;
    int cols;
} CDataframe;


// Alimentation
CDataframe* creer_dataframe_vide(int rows, int cols);
void remplir_dataframe(CDataframe* df);
void remplir_dataframe_en_dur(CDataframe* df, int** values);

// Affichage
void afficher_dataframe(CDataframe* df);
void afficher_partie_lignes(CDataframe* df, int limit);
void afficher_partie_colonnes(CDataframe* df, int limit);

// Opérations usuelles
void ajouter_ligne(CDataframe* df, int* values);
void supprimer_ligne(CDataframe* df, int row_index);
void ajouter_colonne(CDataframe* df, int* values);
void supprimer_colonne(CDataframe* df, int col_index);
void renommer_colonne(CDataframe* df, int col_index, char* new_name);
int verifier_valeur(CDataframe* df, int value);
int acceder_valeur(CDataframe* df, int row, int col);
void remplacer_valeur(CDataframe* df, int row, int col, int value);
void afficher_noms_colonnes(CDataframe* df);

// Analyse et statistiques
int nombre_de_lignes(CDataframe* df);
int nombre_de_colonnes(CDataframe* df);
int nombre_de_cellules_egales(CDataframe* df, int x);
int nombre_de_cellules_inferieures(CDataframe* df, int x);
int nombre_de_cellules_superieures(CDataframe* df, int x);

#endif // FUNCTION_H


