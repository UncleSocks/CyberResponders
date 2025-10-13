#ifndef SCENARIO_H
#define SCENARIO_H

struct Incident {
    int caseNo;
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

extern struct Incident s1;
#endif