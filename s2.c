#include <stdio.h>
#include "scenario.h"


struct Playbook s2Steps [] = {
    {
        .stepNo = 1,
        .question = "Before performing the remediation steps, collect system information of the infected Windows machine, such as its hostname and OS version, for the case notes.\n",
        .command = "systeminfo",
        .arguments = {NULL},
        .terminalOut = 
            "Host Name:             WIN-END-PH10\n"
            "OS Name:               Microsoft Windows 10 Professional\n"
            "OS Manufacturer:       Microsoft Corporation\n"
            "OS Configuration:      Standalone Workstation\n"
            "Product ID:            00311-394826-95962-BBEM\n"
            "Original Install Date: 12/31/2021, 6:51:32 AM\n"
            "System Boot Time:      1/24/2026, 8:41:44 AM\n"
            "System Manufacturer:   Dell Technologies\n"
            "System Model:          Precision 5550\n"
            "System Type:           x64-based PC\n"
    },
    {
        .stepNo = 2,
        .question = "It is important to establish a proper timeline of events when respoding to an incident. Verify the configured timezone of the infected machine.\n",
        .command = "tzutil",
        .arguments = {"g", NULL},
        .terminalOut = "Singapore Standard Time\n"
    },
    {
        .stepNo = 3,
        .question = "After identifying basic system information, determine the IPv4 address of the machine.\n",
        .command = "ipconfig",
        .arguments = {NULL},
        .terminalOut = 
            "Wireless LAN adapter Wi-Fi:\n"
            "\tIPv4 Address . . . . . . . . . .  : 192.168.23.202\n"
            "\tSubnet Mask . . . . . . . . . . . : 255.255.255.0\n"
            "\tDefault Gateway . . . . . . . . . : 192.168.23.254\n\n"
            "Ethernet adapter Bluetooth Network Connection:\n"
            "\tMedia State . . . . . . . . . . . : Media disconnected\n"
            "\tConnection-specified DNS Suffix . :\n"
    },
    {
        .stepNo = 4,
        .question = "Enumerate the active network connections of the machine and note the malicious PID that is associated with data exfiltration.\n",
        .command = "netstat",
        .arguments = {"o", NULL},
        .terminalOut = 
            "Active Connections\n"
            "==================================================================================\n"
            "| Proto | Local Address          | Foreign Address        | State       | PID    |\n"
            "==================================================================================\n"
            "| TCP   | 127.0.0.1:51794        | WIN-END-PH10:51801     | ESTABLISHED | 8996   |\n"
            "| TCP   | 127.0.0.1:51795        | WIN-END-PH10:51800     | ESTABLISHED | 8996   |\n"
            "| TCP   | 127.0.0.1:51800        | WIN-END-PH10:51795     | ESTABLISHED | 15688  |\n"
            "| TCP   | 127.0.0.1:51801        | WIN-END-PH10:51794     | ESTABLISHED | 15688  |\n"
            "| TCP   | 192.168.23.202:52454   | 20.189.173.4:443       | ESTABLISHED | 11600  |\n"
            "| TCP   | 192.168.23.202:52455   | edge-dgw-03-mnl3:443   | ESTABLISHED | 11600  |\n"
            "| TCP   | 192.168.23.202:52456   | 160.16.200.77:21       | ESTABLISHED | 19356  |\n"
            "| TCP   | 192.168.23.202:52457   | 216.239.34.157:443     | TIME_WAIT   | 0      |\n"
            "==================================================================================\n"
    },
    {
        .stepNo = 5,
        .question = "After identifying the malicious process, kill it using its process ID (PID).\n",
        .command = "taskkill",
        .arguments = {"pid 19356", NULL},
        .terminalOut = "Process ccf32:19356 successfully killed.\n"
    },
    {
        .stepNo = 6,
        .question = "To ensure that re-infection will not occur, the persistence mechanism of the threat actor needs to be determined.\n",
        .command = "reg query hklm\\software\\microsoft\\windows\\currentversion\\run",
        .arguments = {NULL},
        .terminalOut = 
            "HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\n"
            "========================================================================================================\n"
            "| Name           | Type          | Data                                                                |\n"
            "========================================================================================================\n"
            "| (Default)      | REG_SZ        | (value not set)                                                     |\n"
            "| unikey         | REG_SZ        | C:\\users\\public\\UniKeyTN.exe                                        |\n"
            "| SecurityHealth | REG_EXPAND_SZ | %%windir%%\\system32\\SecurityHealthSystray.exe                       |\n"
            "| OneDrive       | REG_SZ        | ""C:\\Program Files\\Microsoft OneDrive\\OneDrive.exe"" /background        |\n"
            "========================================================================================================\n"
    },
    {
        .stepNo = 7,
        .question = "Delete the malicious Run registry value to remove the threat actor's persistence in the machine.\n",
        .command = "reg delete hklm\\software\\microsoft\\windows\\currentversion\\run",
        .arguments = {"v unikey", NULL},
        .terminalOut = "The operation completed successful.\n"
    },
    {
        .stepNo = 8,
        .question = "Enumerate the Public user's root directory to identify other malicious files staged by the threat actor.\n",
        .command = "dir c:\\users\\public",
        .arguments = {NULL},
        .terminalOut = 
            "Directory of C:\\Users\\Public\n"
            "=======================================================================\n"
            "| Date Modified        | Type    | Size      | Name                   |\n"
            "=======================================================================\n"
            "| 03/16/2026 1:00 PM   | <DIR>   |           | .                      |\n"
            "| 03/16/2026 1:00 PM   | <DIR>   |           | ..                     |\n"
            "| 03/16/2026 1:47 PM   | <DIR>   |           | Public Documents       |\n"
            "| 03/16/2026 1:47 PM   | <DIR>   |           | Public Downloads       |\n"
            "| 03/16/2026 1:47 PM   | <DIR>   |           | Public Music           |\n"
            "| 03/16/2026 1:47 PM   | <DIR>   |           | Public Pictures        |\n"
            "| 03/16/2026 1:47 PM   | <DIR>   |           | Public Videos          |\n"
            "| 03/16/2026 1:47 PM   | <DIR>   |           | Roaming                |\n"
            "| 03/26/2026 2:18 AM   |         | 160,389   | ccf32.exe              |\n"
            "| 03/26/2026 2:19 AM   |         | 115,652   | UniKeyTN.exe           |\n"
            "| 03/26/2026 2:19 AM   |         | 167,102   | filepak.exe            |\n"
            "| 03/26/2026 2:19 AM   |         | 43,062    | y54947.exe             |\n"
            "| 03/26/2026 2:19 AM   |         | 44,773    | M93732.exe             |\n"
            "| 03/26/2026 2:19 AM   |         | 44,893    | x4984.exe              |\n"
            "| 03/26/2026 2:23 AM   |         | 8,192     | NTUSER.dat             |\n"
            "=======================================================================\n"
    },
    {
        .stepNo = 9,
        .question = "Compute the SHA256 file hash of ccf32.exe to enable the client to add it to their list of IOCs.\nNote: This is the CMD console and use the absolute file path.\n",
        .command = "powershell",
        .arguments = {"command \"get-filehash c:\\users\\public\\ccf32.exe\"", NULL},
        .terminalOut = 
            "=================================================================================================================\n"
            "| Algorithm  | Hash                                                             | Path                          |\n"
            "=================================================================================================================\n"
            "| SHA256     | 1cd8b6f1e2d49e6605f5ae695ea126eee8c82264a9644758126a4c30662ce9d5 | C:\\Users\\Public\\ccf32.exe     |\n"
            "=================================================================================================================\n"
    },
    {
        .stepNo = 10,
        .question = "As part of the eradication step, delete all EXE files in Public user's directory.",
        .command = "del *.exe",
        .arguments = {NULL},
        .terminalOut = "The operation completed successful.\n"
    }
};

struct Incident s2 = {
    .title = "\n\nCASE-IR-2: APT-COMPROMISED ENDPOINT RELATED TO THE FUNNYDREAM CAMPAIGN\n",
    .background = 
        "Meeps Security responded to a cyber incident that occurred to one of its clients based in the Philippines."
        "The initial findings provided by the client indicate that the attack is part of the FunnyDream campaign.\n\n"
        "Reports of this campaign indicates that the threat actor uses built-in Windows commands to collect system information,\n"
        "which are then exfiltrated using File Transfer Protocol (FTP). Additionally, it leverages the root directory\n"
        "of the Public user to stage its malware. The threat actor also abuses the Run registry key to maintain\n"
        "persistence in the infected machine.\n"
        "Tip: Use additional OSINT to better understand the campaign and threat actor.",
    .steps = s2Steps,
    .stepCount = sizeof(s2Steps) / sizeof(s2Steps[0])
};