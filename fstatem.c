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
 * initialStates and finalStates cannot be empty.
 */
Machine *createMachine(char *alphabet, State *states[], unsigned int numberOfStates, unsigned int *initialStates, unsigned int nbIStates, unsigned int *finalStates, unsigned int nbFStates);

/* freeMachine(machine) =>
 *
 * machine -> machine to free
 *
 * Free the machine.
 */
void freeMachine(Machine *machine);

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
