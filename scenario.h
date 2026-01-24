#ifndef SCENARIO_H
#define SCENARIO_H

struct Incident {
    char *title;
    char *background;
    struct Playbook *steps;
    int stepCount;
};

struct Playbook {
    int stepNo;
    char *question;
    char *command;
    char *arguments[32];
    char *terminalOut;
};

struct Cases {
    int caseId;
    char *caseTitle;
    struct Incident *incidentPtr;
};


extern struct Cases list[];
extern int caseList;

extern struct Incident s1;
extern struct Incident s2;

#endif