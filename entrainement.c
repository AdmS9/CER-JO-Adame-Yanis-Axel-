// fichier d'en tête pour les fonctions
#include <stdio.h>
#include <stdlib.h> 
#include "entrainement.h"
#include <string.h>
//délcaration des athlètes et de leurs nombres au départ  
Athlete athletes[MAX_ATHLETES];
int num_athletes = 0;
//fonction permettant de sauvegarder les entrainements d'un athlète dans un fichier txt correspondant à son nom
void sauvegarder_entrainements(char nom_athlete[]){
    FILE *fichier;
    char nom_fichier[MAX_LONGUEUR_NOM + 4];
    sprintf(nom_fichier, "%s.txt", nom_athlete);//création du fichier avec le nom de l'athlète

    fichier=fopen(nom_fichier,"w");//ouverture du fichier en mode écriture
    if (fichier == NULL){//condition vérifiant la présence d'un fichier
        printf("Erreur lors de l'ouverture du fichier %s\n", nom_fichier);
        return;
    }

    
    int i;
    for(i=0; i < num_athletes; i++){//parcours des athlètes 
        if(strcmp(athletes[i].nom, nom_athlete)==0){//condition comparant le nom de l'athlète jusqu'à ce que le bon soit trouvé
            int j;
            for(j=0; j < athletes[i].num_entrainements; j++){//écriture des entrainements dans le fichier
            fprintf(fichier,"%s,%s,%.2f,%d\n",
                       athletes[i].entrainements[j].date, 
                       athletes[i].entrainements[j].type, 
                       athletes[i].entrainements[j].temps,
                       athletes[i].entrainements[j].position);
            }
        }
            break;//arrêt quand l'athlète est trouvé
    }
    fclose(fichier);// fermeture du fichier 
    }
    

//fonction permettant de charger les entrainements d'un athlète à partir d'un fichier txt correspondant à son nom
void charger_entrainements(char nom_athlete[]) {
    FILE *fichier;
    char nom_fichier[MAX_LONGUEUR_NOM + 4];
    sprintf(nom_fichier, "%s.txt", nom_athlete);

    fichier = fopen(nom_fichier, "r");//ouverture du fichier en mode lecture
    if (fichier == NULL) {
        printf("Aucun fichier trouvé pour %s\n", nom_athlete);
        return;
    }

    Athlete nouvel_athlete;
    strcpy(nouvel_athlete.nom, nom_athlete);
    nouvel_athlete.num_entrainements = 0;
    //lecture des entrainements du fichier 
    while (fscanf(fichier, "%s %s %f %d", 
                  nouvel_athlete.entrainements[nouvel_athlete.num_entrainements].date, 
                  nouvel_athlete.entrainements[nouvel_athlete.num_entrainements].type, 
                  &nouvel_athlete.entrainements[nouvel_athlete.num_entrainements].temps, 
                  &nouvel_athlete.entrainements[nouvel_athlete.num_entrainements].position) == 4) {
        nouvel_athlete.num_entrainements++;
    }

    athletes[num_athletes++] = nouvel_athlete;
    fclose(fichier);
}
//fonction permettant d'ajouter un entraînement à un athlète
void ajouter_entrainement(char nom_athlete[], char date[], char type[], float temps, int position) {
    int i;
    for (i = 0; i < num_athletes; i++) {//parcours des athlètes
        if (strcmp(athletes[i].nom, nom_athlete) == 0) {//condition comparant le nom de l'athlète jusqu'à ce que le bon soit trouvé
            if (strcmp(type, "relais") == 0 && athletes[i].num_entrainements > 0) {//condition vérifiant que le type d'entrainement est un relais et qu'il n'a pas déjà fait un entrainement de relais ce jour ci 
                printf("Un seul entraînement en relais par jour est autorisé.\n");
                return;
            }
            //crée un nouvel entrainement et l'ajoute à l'athlète
            Entrainement nouvel_entrainement;
            strcpy(nouvel_entrainement.date, date);
            strcpy(nouvel_entrainement.type, type);
            nouvel_entrainement.temps = temps;
            nouvel_entrainement.position = position;
            athletes[i].entrainements[athletes[i].num_entrainements++] = nouvel_entrainement;//ajoute l'entrinement à la liste d'entrainement de l'athlète
            sauvegarder_entrainements(nom_athlete);//appel de la foncction sauvegarder_entrainement pour sauvegarder les entrainements de l'athlète dans le fichier txt correspondant
            printf("Entraînement ajouté avec succès pour %s.\n", nom_athlete);
            return;
        }
    }
    //si l'athlète n'est pas trouvé, on vérifie que le nombre d'athlètes n'est pas atteint
    if (num_athletes >= MAX_ATHLETES) {
        printf("Limite d'athlètes atteinte.\n");
        return;
    }
    //crée un nouvel athlète et l'ajoute à la liste d'athlètes si il n'a pas été trouvé dans la liste 
    strcpy(athletes[num_athletes].nom, nom_athlete);
    Entrainement nouvel_entrainement;
    strcpy(nouvel_entrainement.date, date);
    strcpy(nouvel_entrainement.type, type);
    nouvel_entrainement.temps = temps;
    nouvel_entrainement.position = position;
    athletes[num_athletes].entrainements[athletes[num_athletes].num_entrainements++] = nouvel_entrainement;
    sauvegarder_entrainements(nom_athlete);
    num_athletes++;
    printf("Nouvel athlète ajouté : %s.\n", nom_athlete);
}
//fonction permettant d'afficher l'historique des entraînements d'un athlète
void historique_athlete(char nom_athlete[]) {
    int i;
    for (i = 0; i < num_athletes; i++) { //parcours des athlètes
        if (strcmp(athletes[i].nom, nom_athlete) == 0) {//condition vérifiant que le nom de l'athlète est trouvé
            printf("Historique des entraînements pour %s :\n", nom_athlete);
            int j;
            for (j = 0; j < athletes[i].num_entrainements; j++) {//parcours des entrainements de l'athlète
                //affiche les entrainements de l'athlète
                printf("Date: %s, Type: %s, Temps: %.2f", 
                       athletes[i].entrainements[j].date, 
                       athletes[i].entrainements[j].type, 
                       athletes[i].entrainements[j].temps);
                if (strcmp(athletes[i].entrainements[j].type, "relais") == 0) {//condition vérifiant que le type d'entrainement est un relais
                    printf(", Position: %d\n", athletes[i].entrainements[j].position);//affiche la position du coureur
                } else {
                    printf("\n");
                }
            }
            return;
        }
    }
   printf("Athlète introuvable : %s.\n", nom_athlete);//affiche un message d'erreur si l'athlète n'est pas trouvé
}
//fonction permettant d'afficher les statistiques d'un athlète pour un entrainement donné 
void statistiques_athlete(char nom_athlete[], char type_evenement[]) {
              int i, count = 0;
              float temps_total = 0, meilleur_temps = 2, 
              pire_temps = -1;
              for (i = 0; i < num_athletes; i++) { //parcours des athlètes
                  if (strcmp(athletes[i].nom, nom_athlete) == 0) {//condition vérifiant que le nom de l'athlète est trouvé
                      int j;
                      for (j = 0; j < athletes[i].num_entrainements; j++) {//parcours des entrainements de l'athlète
                          if (strcmp(athletes[i].entrainements[j].type, type_evenement) == 0) {//condition vérifiant que le type d'entrainement est le même que celui donné
                              count++;
                              temps_total += athletes[i].entrainements[j].temps;//ajoute le temps de l'entrainement à la somme des temps
                              if (athletes[i].entrainements[j].temps < meilleur_temps) {//condition vérifiant que le temps de l'entrainement est le meilleur
                                  meilleur_temps = athletes[i].entrainements[j].temps;//met à jour le meilleur temps
                              }
                              if (athletes[i].entrainements[j].temps > pire_temps) {//condition vérifiant que le temps de l'entrainement est le pire
                                  pire_temps = athletes[i].entrainements[j].temps;//met à jour le pire temps
          }
        }
      }
    }
  }
    if (count > 0) {//condition vérifiant que l'athlète a fait au moins un entrainement et affiche ses statistiques
      printf("Statistiques pour %s - %s:\n", nom_athlete, type_evenement);
      printf("Nombre d'entraînements: %d\n", count);
      printf("Temps moyen: %.2f\n", temps_total / count);
      printf("Meilleur temps: %.2f\n", meilleur_temps);
      printf("Pire temps: %.2f\n", pire_temps);
    } else {//affiche un message d'erreur si l'athlète n'a pas fait d'entrainement 
      printf("Aucun entraînement trouvé pour %s - %s.\n", nom_athlete, type_evenement);
  }
}
//fonction permettant d'afficher les statistiques globales pour un entrainement donné
          void statistiques_globales(char type_evenement[]) {
            int count = 0;
            float temps_total = 0, meilleur_temps = 2, pire_temps = -1;
            int i, j;
            for (i = 0; i < num_athletes; i++) {//parcours des athlètes
                for (j = 0; j < athletes[i].num_entrainements; j++) {//parcours des entrainements de chaque athlète
                    if (strcmp(athletes[i].entrainements[j].type, type_evenement) == 0) {//condition vérifiant que le type d'entrainement est le même que celui donné
                        count++;
                        temps_total += athletes[i].entrainements[j].temps;//ajoute le temps de l'entrainement à la somme des temps
                        if (athletes[i].entrainements[j].temps < meilleur_temps) {//condition vérifiant que le temps de l'entrainement est le meilleur
                            meilleur_temps = athletes[i].entrainements[j].temps;//met à jour le meilleur temps
                        }
                        if (athletes[i].entrainements[j].temps > pire_temps) {//condition vérifiant que le temps de l'entrainement est le pire
                            pire_temps = athletes[i].entrainements[j].temps;//met à jour le pire temps
        }
      }
    }
  }
    if (count > 0) {//affiche les statistiques globales de l'entrainement 
      printf("Statistiques pour l'événement %s:\n", type_evenement);
      printf("Nombre total d'entraînements: %d\n", count);
      printf("Temps moyen: %.2f\n", temps_total / count);
      printf("Meilleur temps: %.2f\n", meilleur_temps);
      printf("Pire temps: %.2f\n", pire_temps);
    } else {
      printf("Aucun entraînement trouvé pour l'événement %s.\n", type_evenement);//affiche un message d'erreur si aucun entrainement n'a été trouvé
  }
}
//fonction permettant d'afficher le classement des athlètes pour un entrainement donné
 void classement_athletes(char type_evenement[]) {
 float temps[MAX_ATHLETES];
 int i, j;
 for (i = 0; i < num_athletes; i++) {//parcours des athlètes
   temps[i] = 0;
   int count = 0;
    for (j = 0; j < athletes[i].num_entrainements; j++) {//parcours des entrainements de chaque athlète
    if (strcmp(athletes[i].entrainements[j].type, type_evenement) == 0) {//condition vérifiant que le type d'entrainement est le même que celui donné
      temps[i] += athletes[i].entrainements[j].temps;//ajoute le temps de l'entrainement à la somme des temps
      count++;
  }
}
    if (count > 0) {
                temps[i] /= count;//calcul la moyenne des temps 
            } else {
                temps[i] = -1;
    }
    }
        //tri à bulle des temps dans l'ordre croissant 
        for (i = 0; i < num_athletes - 1; i++) {
          for (j = 0; j < num_athletes - i - 1; j++) {
              if (temps[j] > temps[j + 1]) {
                  float temp = temps[j];
                  temps[j] = temps[j + 1];
                  temps[j + 1] = temp;
                  Athlete temp_athlete = athletes[j];
                  athletes[j] = athletes[j + 1];
                  athletes[j + 1] = temp_athlete;

      }
    }
  }
      printf("Meilleurs athlètes pour l'événement %s:\n", type_evenement);
       for (i = 0; i < num_athletes && i < 3 && temps[i] != -1; i++) {
        printf("%d. %s - Temps moyen: %.2f\n", i + 1, athletes[i].nom, temps[i]);
 }
}
        //fonction permettant d'afficher la progression d'un athlète pour un entrainement entre deux dates
       void progression_athlete(char nom_athlete[], char type_evenement[], char date1[], char date2[]) {
       float temps1 = -1, temps2 = -1;
       int i, j;
        for (i = 0; i < num_athletes; i++) {//parcours des athlètes
          if (strcmp(athletes[i].nom, nom_athlete) == 0) {//condition vérifiant que le nom de l'athlète est trouvé
           for (j = 0; j < athletes[i].num_entrainements; j++) {//parcours des entrainements de l'athlète
            if (strcmp(athletes[i].entrainements[j].type, type_evenement) == 0) {//condition vérifiant que le type d'entrainement est le même que celui donné
              if (strcmp(athletes[i].entrainements[j].date, date1) == 0) {
               temps1 = athletes[i].entrainements[j].temps;
              } else if (strcmp(athletes[i].entrainements[j].date, date2) == 0) {
                temps2 = athletes[i].entrainements[j].temps;
                 }
              }
            }
          }
        }
      if (temps1 != -1 && (strcmp(type_evenement, "relais") != 0 || temps2 != -1)) {
    printf("Progression de %s pour l'événement %s entre %s et %s:\n", nom_athlete, type_evenement, date1, date2);//affichage de la progression de l'athlète entre les deux dates
    printf("Ancien temps: %.2f\n", temps1);
    printf("Nouveau temps: %.2f\n", temps2);
    printf("Différence de temps: %.2f\n", temps1 - temps2);//affichage et calcul de la différence de temps entre les deux dates
  } 
  else {
    printf("Impossible de trouver les temps pour %s pour l'événement %s entre %s et %s.\n", nom_athlete, type_evenement, date1, date2);
    }//affiche un message d'erreur si les temps ne sont pas trouvés
}
