#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "auth.h"
#include "home.h"
#include "profile.h"

int main() {

    srand(time(NULL));

    /* Prompt the user for login/register */
    int choice = 0;
    int running = 1;
    int nextAction = 0;
    char username[MAX_NAME];
    UserProfile user;

    while (running) {
        choice = getAuthType();
        switch(choice) {
            case 1:
                nextAction = loginUser(username);
                loadProfile(&user, username);
                if (nextAction == 1) {
                    nextAction = getHomeScreen(&user);
                    if (nextAction == 3) {
                        running = 0;
                        printf("Exiting program. Goodbye. \n");
                        break;
                    }
                }
                break;
            case 2:
                registerUser();
                break;
            case 3:
                running = 0;
                printf("Exiting program. Goodbye. \n");
                break;
        }

        printf("\n");
    }

    return EXIT_SUCCESS;
}
