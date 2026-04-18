/*
    File: profile.c
    Author: Braian Halas, Dharm Barot
    Purpose: Implements functions for loading and saving persistent user profiles
    Date: 04/08/2026
*/

#include <stdio.h>
#include "profile.h"
#include "utils.h"

/* 
    Function: loadProfile
    Purpose: Loads the user profile from user_data.txt into the profile struct
    Arguments:
        profile - pointer to UserProfile to load data into
    Returns:
        void
*/

void loadProfile(UserProfile* profile, char* username) {
    FILE *f = fopen("user_data.txt","r");
    if (!f) return;

    char uname[MAX_NAME];
    int chips;
    int wins; 
    int losses;

    while(fscanf(f,"%s %d %d %d", uname, &chips, &wins, &losses) == 4) {
        if(equalStrings(uname, username) == 0) {
            copyString(profile->username, username);
            profile->total_chips = chips;
            profile->wins = wins;
            profile->losses = losses;
            break;
        }
    }

    fclose(f);
}

/* 
    Function: saveProfile
    Purpose: Appends the current profile data to user_data.txt
    Arguments:
        profile - pointer to UserProfile to save
    Returns:
        void
*/

void saveProfile(UserProfile *profile) {
    FILE *f = fopen("user_data.txt", "r");
    FILE *temp = fopen("user_data.tmp", "w");
    if (!temp) {
        perror("Cannot open temp file");
        if (f) fclose(f);
        return;
    }

    char uname[MAX_NAME];
    int chips, wins, losses;
    int found = 0;

    if (f) {
        while (fscanf(f, "%s %d %d %d", uname, &chips, &wins, &losses) == 4) {
            if (equalStrings(uname, profile->username) == 0) {
                // Update this user's data
                fprintf(temp, "%s %d %d %d\n", profile->username, profile->total_chips, profile->wins, profile->losses);
                found = 1;
            } else {
                // Copy other users unchanged
                fprintf(temp, "%s %d %d %d\n", uname, chips, wins, losses);
            }
        }
        fclose(f);
    }

    if (!found) {
        // User not in file yet → append new
        fprintf(temp, "%s %d %d %d\n", profile->username, profile->total_chips, profile->wins, profile->losses);
    }

    fclose(temp);

    // Replace original file with updated temp file
    if (remove("user_data.txt") != 0) {
        perror("Error deleting old data file");
        return;
    }

    if (rename("user_data.tmp", "user_data.txt") != 0) {
        perror("Error renaming temp file");
        return;
    }
}
