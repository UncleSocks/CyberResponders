#include <stdio.h>
#include "scenario.h"


struct Cases list[] = {
    {
        .caseId = "1",
        .caseTitle = "UNKNOWN MALWARE INFECTION ON A WORKSTATION",
        .incidentPtr = &s1
    }
};

int caseList = sizeof(list) / sizeof(list[0]);