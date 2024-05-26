        #include <stdio.h>
        #include <stdlib.h>
        #include <string.h>
        #include "entrainement.h" //fichier d'en-tête pour les fonctions et structures
        #include "scanf.h"    //fichier d'en-tête pour la fonction better_scan

        int main() {
            char choix; //variable permettant de stocker le choix de l'utilisateur 

            do { //ouverture du menu en boucle jusqu'à ce que l'utilisateur quitte ou choisit une option invalide 
                //affichage du menu
                printf("Menu :\n");
                printf("1. Créer entraînement\n");
                printf("2. Historique\n");
                printf("3. Statistiques athlète\n");
                printf("4. Statistiques globales\n");
                printf("5. Classement\n");
                printf("6. Progression\n");
                printf("7. Quitter\n");
                printf("\nVotre choix : ");
                scanf(" %c", &choix); //sélection du choix de l'utilisateur
                while (getchar() != '\n') {} //nettoyage de la mémoire 

                switch (choix) {
                    case '1': {
                        //variables nécessaires à la création d'un entrainement
                        char nom_athlete[MAX_LONGUEUR_NOM];
                        char date[MAX_LONGUEUR_DATE];
                        char type[MAX_LONGUEUR_NOM];
                        float temps;
                        int position;
                        int entrainement_valide=0;
                        int nom_valide=0;
                        int temps_valide=0;
                        int position_valide=0;
                        
                        while(!nom_valide){//saisie du nom de l'athlète et validation si correct 
                            better_scan("Nom : ", nom_athlete, 's');
                            if(strcmp(nom_athlete,"")!=0){//condition permettant de vérifier que la saisie n'est pas vide 
                                nom_valide=1;
                            }
                            else{
                                printf("nom invalide il ne peut pas être vide\n");
                            }
                        }
                         
                        better_scan("Date (YYYY-MM-DD) :", date, 's');//saisie de la date
                        
                        while(!entrainement_valide){//saisie du type d'entrainement et validation si correct 
                            better_scan("Type  (100m,400m,5000m,marathon,relais) :", type, 's');
                            if(strcmp(type,"100m")==0||strcmp(type,"400m")==0||strcmp(type,"5000m")==0||strcmp(type,"marathon")==0||strcmp(type,"relais")==0){// condition permettant de valider le type d'entrainement 
                                entrainement_valide=1;
                                }
                            else{
                                printf("Entrainement invalide\n");
                                }
                        }
                        while(!temps_valide){//saisie du temps et validation si correct 
                            better_scan("Temps : ", &temps, 'f');
                            if(temps>0){//condition permettant de valider le temps 
                                temps_valide=1;
                            }
                            else{
                                printf("temps invalide \n");
                            }
                            
                            }
                        while(!position_valide){//saisie de la position et validation si correct 
                            better_scan("Position : ", &position, 'd');
                            if(position>0){//condition permettant de valider la position
                                position_valide=1;
                            }
                            else{
                                printf("position invalide \n");
                            }

                            }
                        
                        ajouter_entrainement(nom_athlete, date, type, temps, position);//appel de la fonction ajouter_entrainement permettant de créer un entrainement
                        sauvegarder_entrainements(nom_athlete);//appel de la fonction sauvegarder_entrainement permettant de sauvegarder les entrainements dans un fichier txt
                        break;//fin du cas 1
                    }

                    case '2': {
                        char nom_athlete[MAX_LONGUEUR_NOM];//variable nécessaire à la recherche d'un entrainement 
                        better_scan("Nom de l'athlète : ", nom_athlete, 's');// saisie du nom de l'athlète
                        historique_athlete(nom_athlete);//appel de la fonction historique_athlete permettant de rechercher les entrainements effectuer par un athlète
                        break;//fin du cas 2
                    }

                    case '3': {
                        //variables nécessaires à la recherche des statistiques d'un athlète
                        char nom_athlete[MAX_LONGUEUR_NOM];
                        char type[MAX_LONGUEUR_NOM];
                        int entrainement_valide=0;
                        better_scan("Nom de l'athlète : ", nom_athlete, 's');//saisie du nom de l'athlète
                        while(!entrainement_valide){//saisie du type d'entrainement et validation si correct 
                            better_scan("Type  (100m,400m,5000m,marathon,relais) :", type, 's');
                            if(strcmp(type,"100m")==0||strcmp(type,"400m")==0||strcmp(type,"5000m")==0||strcmp(type,"marathon")==0||strcmp(type,"relais")==0){// condition permettant de valider le type d'entrainement 
                                entrainement_valide=1;
                                }
                            else{
                                printf("Entrainement invalide\n");
                                }
                        }
                        statistiques_athlete(nom_athlete, type);//appel de la fonction statistiques_athlete permettant de rechercher les statistiques d'un athlète selon un entrainement donné 
                        break;//fin du cas 3
                    }

                    case '4': {
                        //variable nécéssaire à la recherche des statistiques gloables 
                        char type[MAX_LONGUEUR_NOM];
                        int entrainement_valide=0;
                        while(!entrainement_valide){//saisie du type d'entrainement et validation si correct 
                            better_scan("Type  (100m,400m,5000m,marathon,relais) :", type, 's');
                            if(strcmp(type,"100m")==0||strcmp(type,"400m")==0||strcmp(type,"5000m")==0||strcmp(type,"marathon")==0||strcmp(type,"relais")==0){// condition permettant de valider le type d'entrainement 
                                entrainement_valide=1;
                                }
                            else{
                                printf("Entrainement invalide\n");
                                }
                        }
                        statistiques_globales(type);//appel de la fonction statistiques_globales permettant de rechercher les statistiques globales d'un entrainement donné
                        break;//fin du cas 4
                    }

                    case '5': {
                        //variables nécéssaire à la classification des athlètes 
                        char type[MAX_LONGUEUR_NOM];
                        int entrainement_valide=0;
                        while(!entrainement_valide){//saisie du type d'entrainement et validation si correct 
                            better_scan("Type  (100m,400m,5000m,marathon,relais) :", type, 's');
                            if(strcmp(type,"100m")==0||strcmp(type,"400m")==0||strcmp(type,"5000m")==0||strcmp(type,"marathon")==0||strcmp(type,"relais")==0){// condition permettant de valider le type d'entrainement 
                                entrainement_valide=1;
                                }
                            else{
                                printf("Entrainement invalide\n");
                                }
                        }
                        classement_athletes(type);//appel de la fonction classement_athletes permettant de classer les athlètes selon leur temps sur un entrainement
                        break;//fin du cas 5
                    }

                    case '6': {
                        //variables nécessaire au calcul de la progression d'un athlète
                        char nom_athlete[MAX_LONGUEUR_NOM];
                        char type[MAX_LONGUEUR_NOM];
                        char date1[MAX_LONGUEUR_DATE];
                        char date2[MAX_LONGUEUR_DATE];
                        int entrainement_valide=0;
                        better_scan("Nom de l'athlète : ", nom_athlete, 's');
                        while(!entrainement_valide){//saisie du type d'entrainement et validation si correct 
                            better_scan("Type  (100m,400m,5000m,marathon,relais) :", type, 's');
                            if(strcmp(type,"100m")==0||strcmp(type,"400m")==0||strcmp(type,"5000m")==0||strcmp(type,"marathon")==0||strcmp(type,"relais")==0){// condition permettant de valider le type d'entrainement 
                                entrainement_valide=1;
                                }
                            else{
                                printf("Entrainement invalide\n");
                                }
                        }
                        better_scan("Date de début (YYYY-MM-DD) : ", date1, 's');//saisie de la date de début
                        better_scan("Date de fin (YYYY-MM-DD) : ", date2, 's');// saisie de la date de fin 
                        progression_athlete(nom_athlete, type, date1, date2);//appel de la fonction progression_athlete permettant de calculer l'écart de temps entre deux dates
                        break;//fin du cas 6
                    }

                    case '7':
                        printf("\nAu revoir !\n");
                        break;//arrêt du programme 

                    default:
                        printf("Choix invalide, veuillez réessayer.\n");
                        break;//fin du cas par défaut en cas de choix invalide 
                }
            } while (choix != '7');
        
            return 0;
        }
