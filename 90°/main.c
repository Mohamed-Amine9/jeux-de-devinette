#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int meilleursScores[3] = {0, 0, 0}; // Initialiser les scores avec 0

void afficherIndication(int difference) {
    if (difference > 20) {
        printf("Vous êtes très loin.\n");
    } else if (difference > 10) {
        printf("Vous êtes loin.\n");
    } else if (difference > 5) {
        printf("Vous vous approchez.\n");
    } else {
        printf("Vous êtes très proche !\n");
    }
}

void afficherMeilleurScore(int niveau) {
    if (meilleursScores[niveau - 1] == 0) {
        printf("Pas de meilleur score pour ce niveau. À vous de le définir !\n");
    } else {
        printf("Meilleur score pour ce niveau : %d tentatives.\n", meilleursScores[niveau - 1]);
    }
}

void jouer(int plage, int tentativesMax) {
    int nombreMystere = rand() % plage + 1;
    int tentative = 0, nombreChoisi;

    printf("Bienvenue dans le jeu de devinette !\n");
    printf("Devinez le nombre mystere entre 1 et %d.\n", plage);

    do {
        printf("Entrez votre proposition : ");

        if (scanf("%d", &nombreChoisi) != 1) {
            printf("Veuillez entrer un entier valide.\n");
            while (getchar() != '\n');
            continue;
        }

        if (nombreChoisi < 1 || nombreChoisi > plage) {
            printf("Veuillez entrer un nombre entre 1 et %d.\n", plage);
            continue;
        }

        tentative++;

        if (nombreChoisi < nombreMystere) {
            printf("C'est plus grand ! ");
            afficherIndication(nombreMystere - nombreChoisi);
        } else if (nombreChoisi > nombreMystere) {
            printf("C'est plus petit ! ");
            afficherIndication(nombreChoisi - nombreMystere);
        } else {
            printf("Bravo, vous avez trouvé le nombre mystere en %d tentatives !\n", tentative);

            int indiceScore = (plage / 50) - 1; // Calculer l'indice du score
            if (meilleursScores[indiceScore] == 0 || tentative < meilleursScores[indiceScore]) {
                meilleursScores[indiceScore] = tentative;
                printf("Nouveau meilleur score pour ce niveau !\n");
            }

            if (tentative == 1) {
                printf("Incroyable ! Vous avez trouvé le nombre du premier coup !\n");
            } else if (tentative <= 5) {
                printf("Excellent ! Vous êtes vraiment doué.\n");
            } else if (tentative <= 10) {
                printf("Bien joué ! Vous avez fait un bon travail.\n");
            } else {
                printf("Pas mal. Vous avez trouvé le nombre.\n");
            }

            printf("Vous êtes un gagnant !\n");
            return; // Terminer le jeu car le joueur a gagné
        }

        if (tentative == tentativesMax) {
            printf("Désolé, vous avez dépassé le nombre maximal de tentatives.\n");
            printf("La réponse était %d. Vous avez perdu.\n", nombreMystere);
            return; // Terminer le jeu car le joueur a perdu
        }

    } while (nombreChoisi != nombreMystere);
}



int demanderRejouer() {
    char choix;
    printf("Voulez-vous rejouer ? (O/N) : ");
    scanf(" %c", &choix); // Notez l'espace avant %c pour ignorer les caractères de fin de ligne précédents
    return (toupper(choix) == 'O');
}
int choisirNiveau() {
    int niveau;
    printf("Choisissez votre niveau de difficulté :\n");
    printf("1. Facile (1-50)\n");
    printf("2. Intermédiaire (1-100)\n");
    printf("3. Difficile (1-200)\n");
    printf("Entrez le numéro du niveau : ");

    while (scanf("%d", &niveau) != 1 || (niveau < 1 || niveau > 3)) {
        printf("Veuillez entrer un numéro de niveau valide.\n");
        while (getchar() != '\n');
    }

    afficherMeilleurScore(niveau); // Afficher le meilleur score pour le niveau choisi
    return (niveau == 1) ? 50 : ((niveau == 2) ? 100 : 200);
}

int main() {
    srand(time(NULL)); // Initialiser le générateur de nombres aléatoires

    do {
        #ifdef _WIN32
        system("cls"); // Effacer l'écran sur Windows
        #else
        system("clear"); // Effacer l'écran sur Unix/Linux
        #endif

        int niveau = choisirNiveau();
        jouer(niveau, 10);
    } while (demanderRejouer());

    printf("Merci d'avoir joué !\n");
    return 0;
}
