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
        if (states == NULL)
            return EXIT_FAILURE;

        freeStates(states, 10);
        return EXIT_SUCCESS;
    } else if (strcmp(testName, "createStates") == 0) {
        State **states = createStates(5);

        // Should work
        if (states == NULL)
            return EXIT_FAILURE;

        // Check that everything is in place
        for (int i = 0; i < 5; i++) {
            State *state = states[i];
            if (state == NULL) {
                return EXIT_FAILURE;
            }
            if (state->stateId != i) {
                return EXIT_FAILURE;
            }
            if (state->nbEdgesOut != 0 || state->edgesOut != NULL) {
                return EXIT_FAILURE;
            }
        }

        freeStates(states, 5);
        return EXIT_SUCCESS;
    } else if (strcmp(testName, "createMachine") == 0) {
        char alphabet[] = {'a', 'b'};

        State **states = createStates(5);
        if (states == NULL)
            return EXIT_FAILURE;

        unsigned int initialStates[] = {A_STATE};
        unsigned int finalStates[] = {A_STATE};
        Machine *machine = createMachine(alphabet, states, 5, initialStates, 1, finalStates, 1);
        // Should work
        if (machine == NULL)
            return EXIT_FAILURE;

        if (machine == NULL) {
            return EXIT_FAILURE;
        } else if (machine->states != states) {
            return EXIT_FAILURE;
        } else if (machine->initialStates != initialStates) {
            return EXIT_FAILURE;
        } else if (machine->nbIStates != 1) {
            return EXIT_FAILURE;
        } else if (machine->finalStates != finalStates) {
            return EXIT_FAILURE;
        } else if (machine->alphabet != alphabet) {
            return EXIT_FAILURE;
        }

        freeMachine(machine);

        // initialStates isn't inside states
        unsigned int is1[] = {Z_STATE};
        unsigned int fs1[] = {A_STATE};
        machine = createMachine(alphabet, states, 5, is1, 1, fs1, 1);
        if (machine != NULL)
            return EXIT_FAILURE;

        freeMachine(machine);

        // finalStates isn't inside states
        unsigned int is2[] = {A_STATE};
        unsigned int fs2[] = {Z_STATE};
        machine = createMachine(alphabet, states, 5, is2, 1, fs2, 1);
        if (machine != NULL)
            return EXIT_FAILURE;

        freeMachine(machine);

        // states is empty
        unsigned int is3[] = {A_STATE};
        unsigned int fs3[] = {A_STATE};
        machine = createMachine(alphabet, NULL, 5, is3, 1, fs3, 1);
        if (machine != NULL)
            return EXIT_FAILURE;

        freeMachine(machine);

        // initialStates is empty
        unsigned int is4[] = {};
        unsigned int fs4[] = {A_STATE};
        machine = createMachine(alphabet, states, 5, is4, 0, fs4, 1);
        if (machine != NULL)
            return EXIT_FAILURE;

        freeMachine(machine);

        // finalStates is empty
        unsigned int is5[] = {};
        unsigned int fs5[] = {A_STATE};
        machine = createMachine(alphabet, states, 5, is5, 1, fs5, 0);
        if (machine != NULL)
            return EXIT_FAILURE;

        freeMachine(machine);
        freeStates(states, 5);
        return EXIT_SUCCESS;
    } else if (strcmp(testName, "freeMachine") == 0) {
        char alphabet[] = {'a', 'b'};

        State **states = createStates(5);
        if (states == NULL)
            return EXIT_FAILURE;

        unsigned int initialStates[] = {A_STATE};
        unsigned int finalStates[] = {A_STATE};
        Machine *machine = createMachine(alphabet, states, 5, initialStates, 1, finalStates, 1);

        freeMachine(machine);
        freeStates(states, 5);
        return EXIT_SUCCESS;
    } else if (strcmp(testName, "connectStates") == 0) {
        char alphabet[] = {'a', 'b'};

        State **states = createStates(5);
        if (states == NULL)
            return EXIT_FAILURE;

        unsigned int initialStates[] = {A_STATE};
        unsigned int finalStates[] = {A_STATE};
        Machine *machine = createMachine(alphabet, states, 5, initialStates, 1, finalStates, 1);

        // No error, should work, error if not
        int res = connectStates(states, alphabet, A_STATE, A_STATE, 'a'); 
        if (res == -1)
            return EXIT_FAILURE;

        // Check that the connexion is there
        if (states[A_STATE]->edgesOut[0]->to != states[B_STATE])
            return EXIT_FAILURE;
        if (states[A_STATE]->edgesOut[0]->label != 'a')
            return EXIT_FAILURE;
        if (states[A_STATE]->nbEdgesOut != 1)
            return EXIT_FAILURE;
        
        // Error, Z_STATE isn't in the states list
        res = connectStates(states, alphabet, A_STATE, Z_STATE, 'a');
        if (res != -1)
            return EXIT_FAILURE;

        // Error, 'z' isn't in the given alphabet
        res = connectStates(states, alphabet, A_STATE, C_STATE, 'z');
        if (res != -1)
            return EXIT_FAILURE;
        
        freeMachine(machine);
        freeStates(states, 5);
        return EXIT_FAILURE;
    } else if (strcmp(testName, "computeWord") == 0) {
        return EXIT_FAILURE;
    }

    return EXIT_FAILURE;
}
