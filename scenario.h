#ifndef SCENARIO_H
#define SCENARIO_H

struct Incident {
    char *title;
    char *background;
    struct Playbook *steps;
    int stepCount;
};

struct Playbook {
    char *question;
    char *answer;
    char *terminalOut;
};

struct Cases {
    char *caseId;
    char *caseTitle;
    struct Incident *incidentPtr;
};


extern struct Cases list[];
extern int caseList;

extern struct Incident s1;

#endif