#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "scenario.h"
#include "command.h"

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
            "|                                                  |\n"
            "|                                                  |\n"
            "| By: @unclesocks                             v0.1 |\n"
            "====================================================\n";

    printf("%s", menuPage);
    printf("Please select an option:\n");
    return;
}


void helpMenu() {

    char *helpPage = 
        "============================================================================\n"
        "| Command       | Description                                              |\n"
        "============================================================================\n"
        "| del           | Delete a file.                                           |\n"
        "| dir           | Enumerate a folder (directory).                          |\n"
        "| ipconfig      | Displays network configuration                           |\n"
        "| mstsc         | Interactively connect to a remote desktop.               |\n"
        "| netstat       | Displays active TCP connections and ports.               |\n"
        "| powershell    | A task-based command-line shell and scripting language.  |\n"
        "| reg delete    | Deletes an entry from the registry.                      |\n"
        "| reg query     | Returns a list of subkeys and entries.                   |\n"
        "| rmdir         | Delete a folder (directory).                             |\n"
        "| schtasks      | Manage scheduled tasks.                                  |\n"
        "| systeminfo    | Displays computer configuration information.             |\n" 
        "| tasklist      | List the processes.                                      |\n"
        "| taskkill      | Kill a process.                                          |\n"
        "| tzutil        | Displays the Windows Time Zone utility.                  |\n"
        "============================================================================\n";
    printf("%s", helpPage);
    return;
}


char *userInput(char *answer, size_t size) {
    do {
        printf("> ");
        if (fgets(answer, size, stdin) == NULL) {
            return answer;
        }
        answer[strcspn(answer, "\n")] = 0;
    } while (strlen(answer) == 0);
    return answer;
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

int getNumArgs(char *args[]) {
    int count = 0;
    while (count < 32 && args[count] != NULL) {
        count++;
    }
    return count;
}


int parseCmd(char *cmd, char *args[MAX_ARGS], char *command, char *options) {
    int argsCounter = 1;
    char *optionStart = strchr(cmd, '/');


    if(optionStart != NULL) {
        size_t cmdLen = optionStart - cmd;
        strncpy(command, cmd, cmdLen);
        command[cmdLen] = '\0';
        char *trimmedCmd = trimStr(command);
        memmove(command, trimmedCmd, strlen(trimmedCmd) + 1);
        strToLower(command);
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


int compareCmd(char *cmd, char *command, char *arguments[], int argsCount) {
    char cmdCommand[MAX_LENGTH];
    char cmdOptions[MAX_LENGTH];
    char cmdBuffer[MAX_LENGTH];
    char *cmdArgs[MAX_ARGS];

    strcpy(cmdBuffer, cmd);

    int cmdCounter = parseCmd(cmdBuffer, cmdArgs, cmdCommand, cmdOptions);

    if (cmdCounter == 0 || strcmp(cmdArgs[0], command) != 0) {
        return 0;
    }
    if (argsCount!=0 && cmdCounter != 1) {
        int matchTrack[MAX_ARGS] = {0};
        for (int i = 1; i < cmdCounter; i++) {
            int matched = 0;
            for (int j = 0; j < argsCount; j++) {
                if (!matchTrack[j] && strcmp(cmdArgs[i], arguments[j]) == 0){
                    matchTrack[j] = 1;
                    matched = 1;
                    break;
                }
            }
            if (!matched) {
                return 0;
            }
        }

        for (int j=0; j<argsCount; j++) {
            if (!matchTrack[j]) {
                return 0;
            }
        }

    } else if (argsCount==0 && cmdCounter==1 && strcmp(cmdArgs[0], command) == 0) {
        ;
    } else {
        return 0;
    }

    return 1;
}


void processHelp(char *arg, struct Commands *comm, int count) {
    for (int command = 0; command < count; command++) {
        if (strcmp(comm[command].name, arg) == 0) {
            printf("%-12s   %s\n", comm[command].name, comm[command].description);
            printf("%-12s   %s\n", "SYNTAX:", comm[command].syntax);
            printf("OPTIONS:\n");

            for (int option = 0; option < comm[command].optionCount; option++) {
                printf(" %-12s   %s\n",comm[command].option[option].parameter, comm[command].option[option].description);
            }
            printf("\n\n");

        }
    }
}


int processInput(char *answer, size_t size, char *command, char *arguments[], int argsCount, int *life) {
    char *input = userInput(answer, size);
    int checkAns = compareCmd(input, command, arguments, argsCount);

    while (checkAns == 0) {
        char *space = strchr(input, ' ');
        char *cmd = input;
        char *args = NULL;

        if (space) {
            *space = '\0';
            args = space + 1;
        }

        char *trimmedCmd = trimStr(cmd);
        memmove(cmd, trimmedCmd, strlen(trimmedCmd) + 1);
        strToLower(cmd);

        if (strcmp(cmd, "back") == 0 && args == NULL) {
            return 0;
        } else if (strcmp(cmd, "help") == 0 && args == NULL) {
            helpMenu();
        } else if (strncmp(cmd, "help", 4) == 0 && args != NULL) {
            char *trimmedArgs = trimStr(args);
            memmove(args, trimmedArgs, strlen(trimmedArgs) + 1);
            strToLower(args);
            processHelp(args, commandList, commandCount);
        } else {
            (*life)--;
            printf("Wrong or unrecognized command. You have %d tries remaining\n", *life);
            if (*life <= 0) {
                printf("\nGame over. You have been compromised!");
                return 0;
            }
        }
        input = userInput(answer, size);
        checkAns = compareCmd(input, command, arguments, argsCount);
    }

    return 1;
}


void scenarioViewer (struct Incident *incident) {
    int status;
    int life = 5;
    int argsCount;
    char answer[200];
    char *command;
    char **arguments;

    printf("%s\n", incident->title);
    printf("%s\n", incident->background);
    for (int step = 0; step < incident->stepCount; step++) {
        printf("\n%d. %s", incident->steps[step].stepNo, incident->steps[step].question);
        command = incident->steps[step].command;
        if (incident->steps[step].arguments != NULL) {
            arguments = incident->steps[step].arguments;
            argsCount = getNumArgs(arguments);
        }
        status = processInput(answer, sizeof(answer), command, arguments, argsCount, &life);
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


char commandViewer (struct Commands *comm, int count) {

    printf("\n");
    printf("%-12s   %s\n\n", "COMMAND", "DESCRIPTION");

    for (int command = 0; command < count; command++) {
        printf("%-12s   %s\n", comm[command].name, comm[command].description);
        printf("%-12s   %s\n", "SYNTAX:", comm[command].syntax);
        printf("OPTIONS:\n");

        for (int option = 0; option < comm[command].optionCount; option++) {
            printf(" %-12s   %s\n",comm[command].option[option].parameter, comm[command].option[option].description);
        }
        printf("\n\n");

    }
}


void displayCases () {
    printf("\n====================================== CASE LIST ======================================\n");
    for (int i = 0; i < caseList; i++) {
        printf("ID: %d - %s\n", list[i].caseId, list[i].caseTitle);
    }
    printf("=======================================================================================\n");
    return;
}


void caseSelector () {
    char selectedCase[32];
    int selectedCaseId;
    int index;
    displayCases ();
    printf("Select a case ID to respond:\n");
    userInput(selectedCase, sizeof(selectedCase));
    selectedCaseId = atoi(selectedCase);
    index = selectedCaseId - 1;

    while (!(index >= 0 && index < caseList)) {
        if (strcmp(selectedCase, "back") == 0 ){
            return;
        }
        printf("Case ID not found. Please try again.\n");
        userInput(selectedCase, sizeof(selectedCase));
        selectedCaseId = atoi(selectedCase);
        index = selectedCaseId - 1;
    } 

    scenarioViewer(list[index].incidentPtr);
    
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
            commandViewer(commandList, commandCount);
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