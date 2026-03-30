#include <stdio.h>
#include "auth.h"

int main() {
    /* Prompt the user for login/register */
    int choice = 0;
    int running = 1;

    while (running) {
        choice = getAuthType();
        switch(choice) {
            case 1:
                printf("%d\n", loginUser());
                break;
            case 2:
                printf("%d\n", registerUser());
                break;
            case 3:
                running = 0;
                printf("Exiting program. Goodbye. \n");
                break;
        }

        printf("\n");
    }

    return 0;
}
