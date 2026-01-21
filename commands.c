#include <stdio.h>
#include "command.h"


struct Options c1Options[] = {
    {
        .no = 1,
        .parameter = "/fi",
        .description = "Specifies the types of processes to include in or exclude from the query."
    }
};

struct Options c2Options[] = {
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


struct Commands commandList[] = {
    {
        .no = 1, 
        .name = "tasklist",
        .description = "Displays a list of currently running processes on the local computer or on a remote computer. Tasklist replaces the tlist tool.",
        .syntax = "tasklist /fi", 
        .option = c1Options,
        .optionCount = sizeof(c1Options) / sizeof(c1Options[0])
    },
    {
        .no = 2,
        .name = "taskkill",
        .description = "Ends one or more tasks or processes. Processes can be ended by process ID or image name.",
        .syntax = "taskkill /pid <processID> /im <imageName>",
        .option = c2Options,
        .optionCount = sizeof(c2Options) / sizeof(c2Options[0])
    }
};

int commandCount = sizeof(commandList) / sizeof(commandList[0]);