
#include "cdataframe.h"
#include "column.h"

#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"

#include <stdio.h>
#include <stdlib.h>
#include "cdataframe.h"  // Assurez-vous que ce fichier contient les définitions de toutes les fonctions mentionnées
#include "function.h"
int main() {
    CDataframes* df = NULL;
    int running = 1, choice, index, value;
    char name[100];
    int* values;

    while (running) {
        printf("\n--- Système de Gestion de DataFrame ---\n");
        printf("1. Créer un DataFrame vide\n");
        printf("2. Remplir DataFrame avec saisie utilisateur\n");
        printf("3. Remplir DataFrame avec données fixes\n");
        printf("4. Afficher DataFrame\n");
        printf("5. Ajouter une ligne\n");
        printf("6. Supprimer une ligne\n");
        printf("7. Ajouter une colonne\n");
        printf("8. Supprimer une colonne\n");
        printf("9. Rechercher une valeur\n");
        printf("10. Accéder à une valeur\n");
        printf("11. Remplacer une valeur\n");
        printf("12. Renommer une colonne\n");
        printf("13. Afficher les noms des colonnes\n");
        printf("14. Afficher statistiques\n");
        printf("15. Quitter\n");
        printf("Choisissez une option : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Entrez le nombre de lignes : ");
                int rows;
                scanf("%d", &rows);
                printf("Entrez le nombre de colonnes : ");
                int cols;
                scanf("%d", &cols);
                df = creer_dataframe_vide(rows, cols);
                break;
            case 2:
                if (df) remplir_dataframe(df);
                else printf("Aucun DataFrame créé.\n");
                break;
            case 3:
                if (df) {
                    // Utiliser des valeurs prédéfinies pour la démonstration
                    int **fixedValues = malloc(df->rows * sizeof(int*));
                    for (int i = 0; i < df->rows; i++) {
                        fixedValues[i] = malloc(df->cols * sizeof(int));
                        for (int j = 0; j < df->cols; j++) {
                            fixedValues[i][j] = i * df->cols + j;  // Exemple de valeurs prédéfinies
                        }
                    }
                    remplir_dataframe_en_dur(df, fixedValues);
                }
                else printf("Aucun DataFrame créé.\n");
                break;
            case 4:
                if (df) afficher_dataframe(df);
                else printf("Aucun DataFrame à afficher.\n");
                break;
            case 5:
                if (df) {
                    values = malloc(df->cols * sizeof(int));
                    printf("Entrez les valeurs pour la nouvelle ligne :\n");
                    for (int i = 0; i < df->cols; i++) {
                        scanf("%d", &values[i]);
                    }
                    ajouter_ligne(df, values);
                    free(values);
                } else printf("Aucun DataFrame créé.\n");
                break;
            case 6:
                if (df && df->rows > 0) {
                    printf("Entrez l'indice de la ligne à supprimer : ");
                    scanf("%d", &index);
                    supprimer_ligne(df, index);
                } else printf("Aucune ligne à supprimer ou DataFrame non créé.\n");
                break;
            case 7:
                if (df) {
                    values = malloc(df->rows * sizeof(int));
                    printf("Entrez les valeurs pour la nouvelle colonne :\n");
                    for (int i = 0; i < df->rows; i++) {
                        scanf("%d", &values[i]);
                    }
                    ajouter_colonne(df, values);
                    free(values);
                } else printf("Aucun DataFrame créé.\n");
                break;
            case 8:
                if (df && df->cols > 0) {
                    printf("Entrez l'indice de la colonne à supprimer : ");
                    scanf("%d", &index);
                    supprimer_colonne(df, index);
                } else printf("Aucune colonne à supprimer ou DataFrame non créé.\n");
                break;
            case 9:
                if (df) {
                    printf("Entrez la valeur à rechercher : ");
                    scanf("%d", &value);
                    int found = verifier_valeur(df, value);
                    if (found) printf("Valeur trouvée.\n");
                    else printf("Valeur non trouvée.\n");
                } else printf("Aucun DataFrame créé.\n");
                break;
            case 10:
                if (df) {
                    printf("Entrez l’indice de ligne et de colonne : ");
                    int row, col;
                    scanf("%d %d", &row, &col);
                    int val = acceder_valeur(df, row, col);
                    if (val != -1) printf("Valeur à la position [%d][%d] : %d\n", row, col, val);
                    else printf("Position invalide.\n");
                } else printf("Aucun DataFrame créé.\n");
                break;
            case 11:
                if (df) {
                    printf("Entrez l’indice de ligne, colonne et la nouvelle valeur : ");
                    int row, col, newVal;
                    scanf("%d %d %d", &row, &col, &newVal);
                    remplacer_valeur(df, row, col, newVal);
                } else printf("Aucun DataFrame créé.\n");
                break;
            case 12:
                if (df && df->cols > 0) {
                    printf("Entrez l’indice de la colonne à renommer et le nouveau nom : ");
                    int colIdx;
                    char newName[100];
                    scanf("%d %99s", &colIdx, newName);
                    renommer_colonne(df, colIdx, newName);
                } else printf("Aucune colonne à renommer ou DataFrame non créé.\n");
                break;
            case 13:
                if (df) afficher_noms_colonnes(df);
                else printf("Aucun DataFrame créé.\n");
                break;
            case 14:
                if (df) {
                    printf("Nombre de lignes : %d\n", nombre_de_lignes(df));
                    printf("Nombre de colonnes : %d\n", nombre_de_colonnes(df));
                    printf("Entrez une valeur pour compter les occurrences : ");
                    scanf("%d", &value);
                    printf("Nombre de cellules égales à %d : %d\n", value, nombre_de_cellules_egales(df, value));
                    printf("Nombre de cellules inférieures à %d : %d\n", value, nombre_de_cellules_inferieures(df, value));
                    printf("Nombre de cellules supérieures à %d : %d\n", value, nombre_de_cellules_superieures(df, value));
                } else printf("Aucun DataFrame créé.\n");
                break;
            case 15:
                running = 0;
                if (df) free(df);  // Assurez-vous que cela libère correctement toutes les ressources allouées
                printf("Sortie…\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    }return 0;
}
