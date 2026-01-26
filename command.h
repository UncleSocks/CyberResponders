#ifndef COMMAND_H
#define COMMAND_H

struct Commands {
    char *name;
    char *description;
    char *syntax;
    struct Options *option;
    int optionCount;
};

struct Options {
    int no;
    char *parameter;
    char *description;
};

extern struct Commands commandList[];
extern int commandCount;


#endif