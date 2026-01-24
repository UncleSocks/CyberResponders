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
            "| unikey         | REG_SZ        | C:\\users\\wapols\\appdata\\local\\temp\\UniKeyTN.exe                     |\n"
            "| SecurityHealth | REG_EXPAND_SZ | %%windir%%\\system32\\SecurityHealthSystray.exe                       |\n"
            "| OneDrive       | REG_SZ        | ""C:\\Program Files\\Microsoft OneDrive\\OneDrive.exe"" /background       |\n"
            "========================================================================================================\n"
    }
};

struct Incident s2 = {
    .title = "\n\nCASE-IR-2: APT-COMPROMISED ENDPOINT RELATED TO THE FUNNYDREAM CAMPAIGN\n",
    .background = 
        "Meeps Security responded to a cyber incident that occurred to one of its clients based in the Philippines."
        "The initial findings provided by the client indicate that the attack is part of the FunnyDream campaign.\n\n"
        "Reports of this campaign indicates that the threat actor uses built-in Windows commands to collect system information,"
        "which are then exfiltrated using File Transfer Protocol (FTP). Additionally, it leverages the root directory"
        "of the Public user to stage its malware. The threat actor also abuses the Run registry key to maintain"
        "persistence in the infected machine.\n"
        "Tip: Use additional OSINT to better understand the campaign and threat actor.",
    .steps = s2Steps,
    .stepCount = sizeof(s2Steps) / sizeof(s2Steps[0])
};