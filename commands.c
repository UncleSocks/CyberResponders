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


struct Commands commandList[] = {
    {
        .no = 1,
        .name = "del",
        .description = "Deletes one or more files.",
        .syntax = "del [/s] <names>",
        .option = delOptions,
        .optionCount = sizeof(delOptions) / sizeof(delOptions[0])

    },
    {
        .no = 2,
        .name = "dir",
        .description = "Displays a list of a directory's files and subdirectories.",
        .syntax = "dir [<drive>:][<path>][<filename>]",
        .option = dirOptions,
        .optionCount = sizeof(dirOptions) / sizeof(dirOptions[0])
    },
    {
        .no = 3,
        .name = "mstsc",
        .description = "Creates connections to Remote Desktop Session Host servers or other remote computers.",
        .syntax = "mstsc [<connectionfile] [/v:<server>[:<port>]] /admin",
        .option = mstscOptions,
        .optionCount = sizeof(mstscOptions) / sizeof(mstscOptions[0])
    },
    {
        .no = 4,
        .name = "rmdir",
        .description = "Deletes a directory.",
        .syntax = "rmdir [<drive>:]<path> [/s]",
        .option = rmdirOptions,
        .optionCount = sizeof(rmdirOptions) / sizeof(rmdirOptions[0])
    },
    {
        .no = 5,
        .name = "schtasks",
        .description = "Schedules commands and programs to run periodically or at a specific time, adds and removes tasks from the schedule, starts and stops tasks on demand, and displays and changes scheduled tasks.",
        .syntax = "schtasks [</query> | /delete [/tn {<taskname>}]]",
        .option = schtasksOptions,
        .optionCount = sizeof(schtasksOptions) / sizeof(schtasksOptions[0])
    },
    {
        .no = 1,
        .name = "taskkill",
        .description = "Ends one or more tasks or processes. Processes can be ended by process ID or image name.",
        .syntax = "taskkill [/pid <processID> | /im <imageName>]",
        .option = taskkillOptions,
        .optionCount = sizeof(taskkillOptions) / sizeof(taskkillOptions[0])
    },
    {
        .no = 2, 
        .name = "tasklist",
        .description = "Displays a list of currently running processes on the local computer or on a remote computer.",
        .syntax = "tasklist /fi", 
        .option = tasklistOptions,
        .optionCount = sizeof(tasklistOptions) / sizeof(tasklistOptions[0])
    }
};

int commandCount = sizeof(commandList) / sizeof(commandList[0]);