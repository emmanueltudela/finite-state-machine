#include <stdio.h>
#include <stdlib.h>

#include "fstatem.h"

/* createMachine(alphabet, states, nbStates, initialStates, nbIStates, finalStates, nbFStates) =>
 *
 * alphabet -> alphabet on which the machine is made
 * states -> array of states in the machine
 * nbStates -> number of states in the machine
 * initialStates -> array of initialStates ids
 * nbIStates -> number of initialStates
 * finalStates -> array of finalStates ids
 * nbFStates -> number of finalStates
 *
 * Returns the machine constructed on the given alphabet with given states, initialStates and finalStates.
 *
 * initialStates and finalStates must be included in states.
 * initialStates, finalStates and states cannot be empty.
 */
Machine *createMachine(char *alphabet, State *states[], unsigned int nbStates, unsigned int *initialStates, unsigned int nbIStates, unsigned int *finalStates, unsigned int nbFStates) {
    if (states == NULL || nbStates == 0) {
        return NULL;
    }

    // initialStates and finalStates not empty
    if (nbIStates == 0 || nbFStates == 0) {
        return NULL;
    }
    // initialStates and finalStates included in states
    for (int i = 0; i < nbIStates; i++) {
        unsigned int initialState = initialStates[i];
        // initialState must be an int representing a state so
        //  over 0 and below nbStates
        if (initialState < 0 || initialState > nbStates)
            return NULL;
    }
    for (int i = 0; i < nbFStates; i++) {
        unsigned int finalState = finalStates[i];
        // finalState must be an int representing a state so
        //  over 0 and below nbStates
        if (finalState < 0 || finalState > nbStates)
            return NULL;
    }

    Machine *machine = malloc(sizeof(Machine));
    if (machine == NULL) {
        return NULL;
    }

    machine->states = states;
    machine->nbStates = nbStates;
    machine->initialStates = initialStates;
    machine->nbIStates = nbIStates;
    machine->finalStates = finalStates;
    machine->nbFStates = nbFStates;
    machine->alphabet = alphabet;
    return machine;
}

/* freeMachine(machine) =>
 *
 * machine -> machine to free
 *
 * Free the machine.
 */
void freeMachine(Machine *machine) {
    free(machine);
}

/* createStates(nbStates) =>
 *
 * nbStates -> number of states to return
 *
 * Returns an array with given number of states.
 */
State **createStates(int nbStates) {
    if (nbStates <= 0) {
        fprintf(stderr, "createStates => invalid argument, nbStates must be > 0\n");
        exit(EXIT_FAILURE);
    }

    State **states = malloc(nbStates * sizeof(State *));
    for (int i = 0; i < nbStates; i++) {
        states[i] = malloc(sizeof(State));
        states[i]->stateId = i;
        states[i]->edgesOut = NULL;
        states[i]->nbEdgesOut = 0;
    }

    return states;
}

/* freeStates(states, nbStates) =>
 *
 * states -> array of states to free
 * nbStates -> number of states to free
 *
 * Free every states and the array.
 */
void freeStates(State *states[], unsigned int nbStates) {
    for (int i = 0; i < nbStates; i++) {
        State *state = states[i];

        // Free every edges coming from this state
        unsigned int nbEdgesOut = state->nbEdgesOut;
        for (int j = 0; j < nbEdgesOut; j++) {
            free(state->edgesOut[j]);
        }

        free(state->edgesOut);
        free(state);
    }
    free(states);
}

/* connectStates(from, to, label) =>
 *
 * Creates an edge in fromState pointing towards toState with the given label.
 *
 * label must be included in given alphabet.
 */
int connectStates(State *states[], char *alphabet, unsigned int fromState, unsigned int toState, char label);

/* computeWord(machine, word) =>
 *
 * Returns wether or not word is accepted by the given machine.
 *
 * word must be made with characters from the alphabet used in machine.
 */
bool computeWord(Machine *machine, char *word);
