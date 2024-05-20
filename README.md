Partie 1: cdataframes

-Compilation:

1. Prérequis : Assurez-vous que GCC  est installé sur votre système. Vous pouvez l’installer via le gestionnaire de paquets de votre système d’exploitation 

2.	Création d’un fichier d’en-tête : Si le programme fait référence à un fichier d’en-tête "cdataframes.h", assurez-vous que ce fichier est présent dans le même répertoire que cdataframes.c. Le fichier d’en-tête doit contenir les déclarations des structures et des fonctions utilisées dans cdataframes.c.

3.	Compilation : Ouvrez un terminal dans le dossier contenant vos fichiers source. Compilez le fichier source avec la commande suivante :
   gcc -o cdataframes cdataframes.c

-utilisation:

Pour utiliser le programme, vous aurez besoin  des fonctions disponibles dans cdataframes.c:
	•	Créer un dataframe : Utilisez la fonction create_dataframe() pour initialiser un nouveau dataframe.
	•	Ajouter une colonne : La fonction add_column_to_dataframe(CDataframe* df, COLUMN* col) permet d’ajouter une colonne à votre dataframe. Vous devrez créer et configurer une colonne avant de l’ajouter.
	•	Manipulation des données :  le programme contient des fonctions pour manipuler ou afficher les données, ces fonctions seront également utilisées.

 -exemple de code:
 
 Voici un exemple simplifié d’utilisation de ces fonctions dans un programme principal :
 
 #include "cdataframes.h"

int main() {
    CDataframe* my_df = create_dataframe();
    if (my_df == NULL) {
        printf("Erreur de création du dataframe.\n");
        return 1;
    }

    // Supposons que vous avez une fonction pour créer une colonne
    COLUMN* new_column = create_column("Nom de la colonne", DATA_TYPE);
    if (add_column_to_dataframe(my_df, new_column)) {
        printf("Colonne ajoutée avec succès.\n");
    } else {
        printf("Échec de l'ajout de la colonne.\n");
    }

    // Ajoutez d'autres manipulations ici

    // N'oubliez pas de libérer les ressources allouées
    free_dataframe(my_df);
    return 0;
}

partie 2: columns

-compilation:
1.	Prérequis : Assurez-vous que GCC est installé sur votre machine.
2.	Fichier d’en-tête : Vérifiez que vous avez un fichier d’en-tête columns.h dans le même répertoire que columns.c. Ce fichier doit contenir les déclarations pour les structures et les fonctions utilisées.
3.	Compiler le fichier :
gcc -o columns columns.c

-utilisation:
1.	create_columns :
	 •	Description : Crée une colonne avec un titre et un type spécifié.
	 •	Paramètres :
	        •	type : Type de données de la colonne (doit être défini dans l’énumération ENUM_TYPE).
        	•	title : Titre de la colonne.
        	•	Retour : Pointeur vers la nouvelle colonne ou NULL en cas d’échec.
	2.	insert_value :
	•	Description : Insère une valeur dans une colonne.
	•	Paramètres :
	        •	col : Pointeur vers la colonne où insérer la valeur.
	        •	value : Pointeur vers la valeur à insérer.
	        •	Retour : 1 si succès, 0 si échec.

-exemple de code:
Voici comment vous pourriez utiliser les fonctions dans un programme en C :
#include "columns.h"

int main() {
    COLUMN* my_column = create_columns(INT_TYPE, "Age");
    if (my_column == NULL) {
        printf("Erreur de création de la colonne.\n");
        return 1;
    }

    int age = 25;
    if (insert_value(my_column, &age)) {
        printf("Valeur ajoutée avec succès.\n");
    } else {
        printf("Échec de l'ajout de la valeur.\n");
    }

    // Ajouter d'autres opérations ici

    free_column(my_column);
    return 0;
}


partie 3: functions

 Alimentation

1. creer_dataframe_vide
   - Crée et initialise un `CDataframe` vide avec un nombre de lignes et de colonnes spécifié.

2. remplir_dataframe
   - Remplit le `CDataframe` avec des valeurs saisies par l'utilisateur.

3. remplir_dataframe_en_dur
   - Remplit le `CDataframe` avec des valeurs prédéfinies.

 Affichage

4. afficher_dataframe
   - Affiche toutes les valeurs du `CDataframe`.

5. afficher_partie_lignes
   - Affiche un nombre limité de lignes du `CDataframe`.

6. afficher_partie_colonnes
   - Affiche un nombre limité de colonnes du `CDataframe`.

 Opérations usuelles

7. ajouter_ligne
   - Ajoute une nouvelle ligne avec des valeurs fournies au `CDataframe`.

8. supprimer_ligne
   - Supprime une ligne du `CDataframe` à l'index spécifié.

9. ajouter_colonne
   - Ajoute une nouvelle colonne avec des valeurs fournies au `CDataframe`.

10. supprimer_colonne
    - Supprime une colonne du `CDataframe` à l'index spécifié.

11. renommer_colonne
    - Renomme une colonne du `CDataframe` (non implémenté).

12. verifier_valeur
    - Vérifie l'existence d'une valeur dans le `CDataframe`.

13. acceder_valeur
    - Accède à la valeur d'une cellule spécifique dans le `CDataframe`.

14. remplacer_valeur
    - Remplace la valeur d'une cellule spécifique dans le `CDataframe`.

15. afficher_noms_colonnes
    - Affiche les noms des colonnes du `CDataframe` (non implémenté).

Analyse et statistiques

16. nombre_de_lignes
    - Retourne le nombre de lignes du `CDataframe`.

17. nombre_de_colonnes
    - Retourne le nombre de colonnes du `CDataframe`.

18. nombre_de_cellules_egales
    - Compte le nombre de cellules égales à une valeur donnée dans le `CDataframe`.

19. nombre_de_cellules_inferieures
    - Compte le nombre de cellules inférieures à une valeur donnée dans le `CDataframe`.

20. nombre_de_cellules_superieures
    - Compte le nombre de cellules supérieures à une valeur donnée dans le `CDataframe`.

