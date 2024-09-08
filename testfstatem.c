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
        unsigned int alphabetSize = 2;

        State **states = createStates(5);
        if (states == NULL)
            return EXIT_FAILURE;

        unsigned int initialStates[] = {A_STATE};
        unsigned int finalStates[] = {A_STATE};
        Machine *machine = createMachine(alphabet, alphabetSize, states, 5, initialStates, 1, finalStates, 1);
        // Should work
        if (machine == NULL)
            return EXIT_FAILURE;

        if (machine == NULL)
            return EXIT_FAILURE;
        else if (machine->states != states)
            return EXIT_FAILURE;
        else if (machine->initialStates != initialStates)
            return EXIT_FAILURE;
        else if (machine->nbIStates != 1)
            return EXIT_FAILURE;
        else if (machine->finalStates != finalStates)
            return EXIT_FAILURE;
        else if (machine->alphabet != alphabet)
            return EXIT_FAILURE;
        else if (machine->alphabetSize != alphabetSize)
            return EXIT_FAILURE;

        freeMachine(machine);

        // initialStates isn't inside states
        unsigned int is1[] = {Z_STATE};
        unsigned int fs1[] = {A_STATE};
        machine = createMachine(alphabet, alphabetSize, states, 5, is1, 1, fs1, 1);
        if (machine != NULL)
            return EXIT_FAILURE;

        freeMachine(machine);

        // finalStates isn't inside states
        unsigned int is2[] = {A_STATE};
        unsigned int fs2[] = {Z_STATE};
        machine = createMachine(alphabet, alphabetSize, states, 5, is2, 1, fs2, 1);
        if (machine != NULL)
            return EXIT_FAILURE;

        freeMachine(machine);

        // states is empty
        unsigned int is3[] = {A_STATE};
        unsigned int fs3[] = {A_STATE};
        machine = createMachine(alphabet, alphabetSize, NULL, 5, is3, 1, fs3, 1);
        if (machine != NULL)
            return EXIT_FAILURE;

        freeMachine(machine);

        // initialStates is empty
        unsigned int is4[] = {};
        unsigned int fs4[] = {A_STATE};
        machine = createMachine(alphabet, alphabetSize, states, 5, is4, 0, fs4, 1);
        if (machine != NULL)
            return EXIT_FAILURE;

        freeMachine(machine);

        // finalStates is empty
        unsigned int is5[] = {};
        unsigned int fs5[] = {A_STATE};
        machine = createMachine(alphabet, alphabetSize, states, 5, is5, 1, fs5, 0);
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
        Machine *machine = createMachine(alphabet, 2, states, 5, initialStates, 1, finalStates, 1);

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
        Machine *machine = createMachine(alphabet, 2, states, 5, initialStates, 1, finalStates, 1);
        // Should work
        if (machine == NULL)
            return EXIT_FAILURE;

        // No error, should work, error if not
        int res = connectStates(states, 5, alphabet, 2, A_STATE, A_STATE, 'a'); 
        if (res == -1) {
            fprintf(stderr, "Working case\n");
            return EXIT_FAILURE;
        }

        // Check that the connexion is there
        if (states[A_STATE]->edgesOut[0]->to != states[A_STATE] ||
            states[A_STATE]->edgesOut[0]->label != 'a' ||
            states[A_STATE]->nbEdgesOut != 1) {
            fprintf(stderr, "Invalid copy to new edge\n");
            return EXIT_FAILURE;
        }
        
        // Error, Z_STATE isn't in the states list
        res = connectStates(states, 5, alphabet, 2, A_STATE, Z_STATE, 'a');
        if (res != -1) {
            fprintf(stderr, "Connexion is going to invalid State\n");
            return EXIT_FAILURE;
        }

        // Error, 'z' isn't in the given alphabet
        res = connectStates(states, 5, alphabet, 2, A_STATE, C_STATE, 'z');
        if (res != -1) {
            fprintf(stderr, "label isn't in the alphabet");
            return EXIT_FAILURE;
        }
        
        freeMachine(machine);
        freeStates(states, 5);
        return EXIT_SUCCESS;
    } else if (strcmp(testName, "computeWord") == 0) {
        char alphabet[] = {'a', 'b', 'c'};

        State **states = createStates(2);
        if (states == NULL)
            return EXIT_FAILURE;

        unsigned int initialStates[] = {A_STATE};
        unsigned int finalStates[] = {B_STATE};
        Machine *machine = createMachine(alphabet, 3, states, 2, initialStates, 1, finalStates, 1);
        // Should work
        if (machine == NULL)
            return EXIT_FAILURE;
        return EXIT_FAILURE;

        // Connect the final state machine
        int res = connectStates(states, 2, alphabet, 3, A_STATE, B_STATE, 'b');
        if (res == -1)
            return EXIT_FAILURE;

        res = connectStates(states, 2, alphabet, 3, B_STATE, B_STATE, 'a');
        if (res == -1)
            return EXIT_FAILURE;

        res = connectStates(states, 2, alphabet, 3, B_STATE, A_STATE, 'c');
        if (res == -1)
            return EXIT_FAILURE;

        // Test accepted words
        bool acc = computeWord(machine, "b");
        if (!acc)
            return EXIT_FAILURE;
        acc = computeWord(machine, "ba");
        if (!acc)
            return EXIT_FAILURE;
        acc = computeWord(machine, "baa");
        if (!acc)
            return EXIT_FAILURE;
        acc = computeWord(machine, "baacba");
        if (!acc)
            return EXIT_FAILURE;

        // Test refused word
        acc = computeWord(machine, "a");
        if (acc)
            return EXIT_FAILURE;
        acc = computeWord(machine, "bac");
        if (acc)
            return EXIT_FAILURE;

        freeMachine(machine);
        freeStates(states, 2);
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}
