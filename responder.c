#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "scenario.h"

#define MAX_ARGS 10
#define MAX_LENGTH 256


void mainMenu() {
    char *menuPage = 
            "\n\n"
            "====================================================\n"
            "|   Meeps Security CyberResponder Console //////   |\n"
            "| ================================================ |\n"
            "|   1. Respond  <--------------------------------- |\n"
            "|   2. Commands  <-------------------------------- |\n"
            "|   3. Exit  <------------------------------------ |\n"
            "====================================================\n";

    printf("%s", menuPage);
    printf("Please select an option:\n");
    return;
}


void helpMenu() {

    char *helpPage = 
        "=================================================================\n"
        "| Command       | Description                                   |\n"
        "|===============================================================|\n"
        "| del           | Delete a file or folder.                      |\n"
        "| dir           | Enumerate a folder (directory).               |\n"
        "| mstsc         | Interactively connect to a remote desktop.    |\n"
        "| schtasks      | Manage scheduled tasks.                       |\n" 
        "| tasklist      | List the processes.                           |\n"
        "| taskkill      | Kill a process.                               |\n"
        "=================================================================\n";
    printf("%s", helpPage);
    return;
}


char *userInput(char *command, size_t size) {
    do {
        printf("> ");
        if (fgets(command, size, stdin) == NULL) {
            return command;
        }
        command[strcspn(command, "\n")] = 0;
    } while (strlen(command) == 0);
    return command;
}


void strToLower (char *str) {
    while (*str) {
        *str = tolower((unsigned char)*str);
        str++;
    }
}


char *trimStr(char *str) {
    char *endStr;

    while (isspace((unsigned char)*str)) {
        str++;
    }

    if (*str == '\0') {
        return str;
    }

    endStr = str + strlen(str) - 1;
    while (endStr > str && isspace((unsigned char)*endStr)) {
        endStr--;
    }
    *(endStr + 1) = '\0';

    return str;
}


int parseCmd(char *cmd, char *args[MAX_ARGS], char *command, char *options) {
    int argsCounter = 1;
    char *optionStart = strchr(cmd, '/');
    if(optionStart != NULL) {
        size_t cmdLen = optionStart - cmd;
        strncpy(command, cmd, cmdLen);
        command[cmdLen] = '\0';
        args[0] = command;
        strcpy(options, optionStart);
        char *pointer = options;
        char *pointerStart = options;

        while (*pointer) {
            if (*pointer == '/') {
                *pointer = '\0';
                if (*pointerStart != '\0') {
                    pointerStart = trimStr(pointerStart);
                    strToLower(pointerStart);
                    args[argsCounter++] = pointerStart;
                }
                pointerStart = pointer + 1; 
            }
            pointer++;
        }

        if (*pointerStart != '\0') {
            pointerStart = trimStr(pointerStart);
            strToLower(pointerStart);
            args[argsCounter++] = pointerStart;
        }
    } else {
        strcpy (command, cmd);
        strToLower(command);
        args[0] = command;
    }


    return argsCounter;
}


int compareCmd(char *cmd, char *ans) {
    char cmdCommand[MAX_LENGTH], ansCommand[MAX_LENGTH];
    char cmdOptions[MAX_LENGTH], ansOptions[MAX_LENGTH];
    char cmdBuffer[MAX_LENGTH], ansBuffer[MAX_LENGTH];
    char *cmdArgs[MAX_ARGS], *ansArgs[MAX_ARGS];

    strcpy(cmdBuffer, cmd);
    strcpy(ansBuffer, ans);

    int cmdCounter = parseCmd(cmdBuffer, cmdArgs, cmdCommand, cmdOptions);
    int ansCounter = parseCmd(ansBuffer, ansArgs, ansCommand, ansOptions);
    printf("%s - %s", cmdArgs[0], ansArgs[0]);
    if (cmdCounter == 0 || ansCounter == 0 || strcmp(cmdArgs[0], ansArgs[0]) != 0) {
        return 0;
    }

    int matchTrack[MAX_ARGS] = {0};
    for (int i = 1; i < ansCounter; i++) {
        int matched = 0;
        for (int j = 1; j < cmdCounter; j++) {
            if (!matchTrack[j] && strcmp(ansArgs[i], cmdArgs[j]) == 0){
                matchTrack[j] = 1;
                matched = 1;
                break;
            }
        }
        if (!matched) {
            return 0;
        }
    }

    return 1;
}


int processInput(char *command, size_t size, char *answer, int *life) {
    char *input = userInput(command, size);
    int checkAns = compareCmd(input, answer);

    while (checkAns == 0) {
        if (strcmp(input, "back") == 0) {
            return 0;
        } else if (strcmp(input, "help") == 0) {
            helpMenu();
        } else {
            (*life)--;
            printf("Wrong or unrecognized command. You have %d tries remaining\n", *life);
            if (*life <= 0) {
                printf("\nGame over. You have been compromised!");
                return 0;
            }
        }
        input = userInput(command, size);
        checkAns = compareCmd(input, answer);
    }

    return 1;
}


void scenarioViewer (struct Incident *incident) {
    int status;
    int life = 3;
    char command[200];
    char *answer;

    printf("%s\n", incident->title);
    printf("%s\n", incident->background);
    for (int step = 0; step < incident->stepCount; step++) {
        printf("%s", incident->steps[step].question);
        answer = incident->steps[step].answer;
        status = processInput(command, sizeof(command), answer, &life);
        if (status == 1) {
            printf("%s", incident->steps[step].terminalOut);
        } else {
            return;
        }
    }
    printf("\nRisk has been remediated.\n");
    printf("Returning to main menu...");
    return;
}


void displayCases () {
    printf("\n====================================== CASE LIST ======================================\n");
    for (int i = 0; i < caseList; i++) {
        printf("ID: %s - %s", list[i].caseId, list[i].caseTitle);
    }
    printf("\n=======================================================================================\n");
    return;
}


void caseSelector () {
    char selectedCase[32];
    displayCases ();
    printf("Select a case to respond:\n");
    userInput(selectedCase, sizeof(selectedCase));
    for (int i = 0; i < caseList; i++) {
        if (strcmp(selectedCase, list[i].caseId) == 0) {
            scenarioViewer(list[i].incidentPtr);
            return;
        }
    }

}


int main() {
    int running = 1;
    char menuSelected[MAX_LENGTH];
    mainMenu();
    while (running == 1) {
        userInput(menuSelected, sizeof(menuSelected));
        strToLower(menuSelected);
        if ((strcmp(menuSelected, "respond") == 0) || (strcmp(menuSelected, "1") == 0)) {
            caseSelector();
            mainMenu();
        } else if ((strcmp(menuSelected, "commands") == 0) || (strcmp(menuSelected, "2") == 0)) {
            printf("Go to command list page...");
            mainMenu();
        } else if ((strcmp(menuSelected, "exit") == 0) || (strcmp(menuSelected, "3") == 0)) {
            printf("Exiting...");
            running = 0;
        } else {
            printf("Invalid option selected. Please try again.\n");
        }
    }
    return 0;
}