#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fstatem.h"

void usage(char *execName) {
    printf("%s usage =>\n", execName);
    printf("%s -h : Displays this text\n", execName);
    printf("%s [test_name] : Execute the given test and end execution with test restult\n", execName);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage(argv[0]);
        exit(EXIT_FAILURE);
    }

    char *testName = argv[1];

    if (strcmp(testName, "freeStates") == 0) {
        State **states = createStates(10);
        freeStates(states, 10);
        
        return EXIT_SUCCESS;
    } else if (strcmp(testName, "createStates") == 0) {
        // TO DO
    }

    return EXIT_FAILURE;
}
