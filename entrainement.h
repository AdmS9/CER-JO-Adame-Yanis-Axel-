#ifndef ENTRAINEMENT_H
#define ENTRAINEMENT_H

//définition des constantes 
#define MAX_ATHLETES 4                          
#define MAX_ENTRAINEMENT 7
#define MAX_LONGUEUR_NOM 20
#define MAX_LONGUEUR_DATE 20

//définition de la structure permettant de créer et gérer  des entrainements
typedef struct {
  char date[MAX_LONGUEUR_DATE]; //date de l'entrainement
  char type[MAX_LONGUEUR_NOM]; //type d'entraienemt
  float temps;                //temps réaliser 
  int position;              //position du coureur
} Entrainement;

//définition de la structure permettant de créer et gérer des athlètes
typedef struct {
  char nom[MAX_LONGUEUR_NOM];//nom de l'athlète
  Entrainement entrainements[MAX_ENTRAINEMENT];//tableau des entrainements de l'athlète
  int num_entrainements;//nombre d'entrainements de l'athlète
} Athlete;

//déclaration des fonctions nécessaires au fonctionnement du programme 
void ajouter_entrainement(char nom_athlete[], char date[], char type[], float temps, int position);//fonction permettant d'ajouter un entraînement à un athlète
void sauvegarder_entrainements(char nom_athlete[]);//fonction permettant de sauvegarder les entrainements d'un athlète dans un fichier txt correspondant à son nom
void historique_athlete(char nom_athlete[]);//fonction permettant d'afficher l'historique des entraînements d'un athlète
void statistiques_athlete(char nom_athlete[], char type_evenement[]);//fonction permettant d'afficher les statistiques d'un athlète pour un entrainement donné
void statisques_globales(char type_evenement[]);//fonction permettant d'afficher les statistiques globales pour un entrainement donné
void classement_athletes(char type_evenement[]);//fonction permettant d'afficher le classement des athlètes pour un entrainement donné
void progression_athlete(char nom_athlete[], char type_evenement[], char date1[], char date2[]);//fonction permettant d'afficher la progression d'un athlète pour un entrainement donné entre deux dates 
void charger_entrainements(char nom_athlete[]);//fonction permettant de charger les entrainements d'un athlète à partir de son nom 

#endif /*ENTRAINEMENT_H*/

