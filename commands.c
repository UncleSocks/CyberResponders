#include <stdio.h>
#include "command.h"


struct Options delOptions[] = {
    {
        .no = 1,
        .parameter = "<names>",
        .description = "Specifies a list of one or more files or directories."
    },
    {
        .no = 2,
        .parameter = "/s",
        .description = "	Deletes specified files from the current directory and all subdirectories."
    }
};

struct Options dirOptions[] = {
    {
        .no = 1,
        .parameter = "[<drive>:][<path>]",
        .description = "Specifies the drive and directory for which you want to see a listing."
    },
    {
        .no = 2,
        .parameter = "[<filename>]",
        .description = "Specifies a particular file or group of files for which you want to see a listing."
    }
};

struct Options mstscOptions[] = {
    {
        .no = 1,
        .parameter = "<connectionfile>",
        .description = "Specifies the name of an .rdp file for the connection."
    },
    {
        .no = 2,
        .parameter = "/v:<server>[:<port>]",
        .description = "Specifies the remote computer and, optionally, the port number to which you want to connect."
    },
    {
        .no = 3,
        .parameter = "/admin",
        .description = "Connects you to a session for administering the server."
    }
};

struct Options netstatOptions[] = {
    {
        .no = 1,
        .parameter = "/a",
        .description = "Displays all active TCP connections and the TCP and UDP ports on which the computer is listening."
    },
    {
        .no = 2,
        .parameter = "/n",
        .description = "Displays active TCP connections, however, addresses and port numbers are expressed numerically and no attempt is made to determine names."
    },
    {
        .no = 3,
        .parameter = "/o",
        .description = "Displays active TCP connections and includes the process ID (PID) for each connection."
    }
};

struct Options powershellOptions[] = {
    {
        .no = 1,
        .parameter = "/command",
        .description = "Specifies the powershell command to be executed."
    }
};

struct  Options regDeleteOptions[] = 
{
    {
        .no = 1,
        .parameter = "<keyname>",
        .description = "Specifies the full path of the subkey or entry to be deleted."
    },
    {
        .no = 2,
        .parameter = "/v <valuename>",
        .description = "Deletes a specific entry under the subkey. If no entry is specified, then all entries and subkeys under the subkey will be deleted."
    }
};

struct Options regQueryOptions[] = {
    {
        .no = 1,
        .parameter = "<keyname>",
        .description = "Specifies the full path of the subkey."
    },
    {
        .no = 2,
        .parameter = "/v <valuename>",
        .description = "Specifies the registry value name that is to be queried. If omitted, all value names for keyname are returned."
    }
};


struct Options rmdirOptions[] = {
    {
        .no = 1,
        .parameter = "[<drive>:]<path>",
        .description = "Specifies the location and the name of the directory that you want to delete. Path is required."
    },
    {
        .no = 2,
        .parameter = "/s",
        .description = "Deletes a directory tree (the specified directory and all its subdirectories, including all files)."
    }
};

struct Options schtasksOptions[] = {
    {
        .no = 1,
        .parameter = "/query",
        .description = "Query of all tasks on the system."
    },
    {
        .no = 2,
        .parameter = "/delete",
        .description = "Deletes a scheduled task."
    },
    {
        .no = 3,
        .parameter = "/tn {<taskname>}",
        .description = "Identifies the task to be deleted."
    }
};

struct Options taskkillOptions[] = {
    {
        .no = 1,
        .parameter = "/pid <processID",
        .description = "Specifies the process ID of the process to be terminated."
    },
    {
        .no = 2,
        .parameter = "/im <imageName>",
        .description = "Specifies the image name of the process to be terminated."
    }
};

struct Options tasklistOptions[] = {
    {
        .no = 1,
        .parameter = "/fi",
        .description = "Specifies the types of processes to include in or exclude from the query."
    }
};

struct Options tzutilOptions[] = {
    {
        .no = 1,
        .parameter = "/g",
        .description = "Displays the current time zone ID."
    }
};


struct Commands commandList[] = {
    {
        .name = "del",
        .description = "Deletes one or more files.",
        .syntax = "del [/s] <names>",
        .option = delOptions,
        .optionCount = sizeof(delOptions) / sizeof(delOptions[0])

    },
    {
        .name = "dir",
        .description = "Displays a list of a directory's files and subdirectories.",
        .syntax = "dir [<drive>:][<path>][<filename>]",
        .option = dirOptions,
        .optionCount = sizeof(dirOptions) / sizeof(dirOptions[0])
    },
    {
        .name = "ipconfig",
        .description = "Displays all current TCP/IP network configuration values and refreshes Dynamic Host Configuration Protocol (DHCP) and Domain Name System (DNS) settings.",
        .syntax = "ipconfig",
        .option = NULL,
        .optionCount = 0
    },
    {
        .name = "mstsc",
        .description = "Creates connections to Remote Desktop Session Host servers or other remote computers.",
        .syntax = "mstsc [<connectionfile] [/v:<server>[:<port>]] /admin",
        .option = mstscOptions,
        .optionCount = sizeof(mstscOptions) / sizeof(mstscOptions[0])
    },
    {
        .name = "netstat",
        .description = "Displays active TCP connections, ports on which the computer is listening, Ethernet statistics, the IP routing table, IPv4 statistics (for the IP, ICMP, TCP, and UDP protocols), and IPv6 statistics (for the IPv6, ICMPv6, TCP over IPv6, and UDP over IPv6 protocols).",
        .syntax = "netstat [/a] [/n] [/o]",
        .option = netstatOptions,
        .optionCount = sizeof(netstatOptions) / sizeof(netstatOptions[0])
    },
    {
        .name = "powershell",
        .description = "Windows PowerShell is a task-based command-line shell and scripting language designed especially for system administration.",
        .syntax = "powershell /command \"command\"",
        .option = powershellOptions,
        .optionCount = sizeof(powershellOptions) / sizeof(powershellOptions[0])
    },
    {
        .name = "reg delete",
        .description = "Deletes a subkey or entries from the registry.",
        .syntax = "reg delete <keyname> [/v valuename]",
        .option = regDeleteOptions,
        .optionCount = sizeof(regDeleteOptions) / sizeof(regDeleteOptions[0])
    },
    {
        .name = "reg query",
        .description = "Returns a list of the next tier of subkeys and entries that are located under a specified subkey in the registry.",
        .syntax = "reg query <keyname> [/v valuename]",
        .option = regQueryOptions,
        .optionCount = sizeof(regQueryOptions) / sizeof(regQueryOptions[0])
    },
    {
        .name = "rmdir",
        .description = "Deletes a directory.",
        .syntax = "rmdir [<drive>:]<path> [/s]",
        .option = rmdirOptions,
        .optionCount = sizeof(rmdirOptions) / sizeof(rmdirOptions[0])
    },
    {
        .name = "schtasks",
        .description = "Schedules commands and programs to run periodically or at a specific time, adds and removes tasks from the schedule, starts and stops tasks on demand, and displays and changes scheduled tasks.",
        .syntax = "schtasks [</query> | /delete [/tn {<taskname>}]]",
        .option = schtasksOptions,
        .optionCount = sizeof(schtasksOptions) / sizeof(schtasksOptions[0])
    },
    {
        .name = "systeminfo",
        .description = "Displays detailed configuration information about a computer and its operating system.",
        .syntax = "systeminfo",
        .option = NULL,
        .optionCount = 0
    },
    {
        .name = "taskkill",
        .description = "Ends one or more tasks or processes. Processes can be ended by process ID or image name.",
        .syntax = "taskkill [/pid <processID> | /im <imageName>]",
        .option = taskkillOptions,
        .optionCount = sizeof(taskkillOptions) / sizeof(taskkillOptions[0])
    },
    {
        .name = "tasklist",
        .description = "Displays a list of currently running processes on the local computer or on a remote computer.",
        .syntax = "tasklist /fi", 
        .option = tasklistOptions,
        .optionCount = sizeof(tasklistOptions) / sizeof(tasklistOptions[0])
    },
    {
        .name = "tzutil",
        .description = "Displays the Windows Time Zone utility.",
        .syntax = "tzutil [/g]",
        .option = tzutilOptions,
        .optionCount = sizeof(tzutilOptions) / sizeof(tzutilOptions[0])
    }
};

int commandCount = sizeof(commandList) / sizeof(commandList[0]);