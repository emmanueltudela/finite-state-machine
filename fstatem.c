#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fstatem.h"

/* createMachine(alphabet, alphabetSize, states, nbStates, initialStates, nbIStates, finalStates, nbFStates) =>
 *
 * alphabet -> alphabet on which the machine is made
 * alphabetSize -> number of chars in alphabet
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
Machine *createMachine(char *alphabet, unsigned int alphabetSize, State *states[], unsigned int nbStates, unsigned int *initialStates, unsigned int nbIStates, unsigned int *finalStates, unsigned int nbFStates) {
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
    machine->alphabetSize = alphabetSize;
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
    if (states == NULL) {
        return NULL;
    }

    for (int i = 0; i < nbStates; i++) {
        states[i] = malloc(sizeof(State));
        if (states[i] == NULL) {
            free(states);
            return NULL;
        }
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

/* connectStates(states, nbStates, alphabet, alphabetSize, fromState, toState, label) =>
 *
 * states -> collection of states
 * nbStates -> number of states in states
 * alphabet -> alphabet on which the machine is built
 * alphabetSize -> number of chars in alphabet
 * fromState -> id of the state where the connexion is coming
 * toState -> id of the state where the connexion is going
 * label -> label of the connexion
 *
 * Creates an edge in fromState pointing towards toState with the given label.
 *
 * label must be included in given alphabet.
 */
int connectStates(State *states[], unsigned int nbStates, char alphabet[], unsigned int alphabetSize, unsigned int fromState, unsigned int toState, char label) {
    if (states == NULL) {
        return -1;
    }

    // Check that the label is in alphabet
    for (int i = 0; i < alphabetSize; i++) {
        if (alphabet[i] == label) {
            break;
        }
        if (i == alphabetSize - 1) {
            return -1;
        }
    }

    // Check that fromState and toState are in the states collection
    // Since fromState and toState are integers representing the location in states
    // they must be greater than 0 and below the max nbStates
    if (fromState < 0 || fromState >= nbStates || toState < 0 || toState >= nbStates) {
        return -1;
    }

    State *stateFrom = states[fromState];
    State *stateTo = states[toState];

    // Expend the array of edgesOut in stateFrom by one and copy the last array
    size_t newNbEdgesOut = stateFrom->nbEdgesOut + 1;
    Edge **newEdgesOut = malloc(newNbEdgesOut * sizeof(Edge *));
    // Failed malloc
    if (newEdgesOut == NULL)
        return -1;
    memcpy(newEdgesOut, stateFrom->edgesOut, stateFrom->nbEdgesOut * sizeof(Edge *));

    // Free unupdated array
    free(stateFrom->edgesOut);

    // Reassign the new edgesOut array
    stateFrom->edgesOut = newEdgesOut;

    // Append a new Edge
    unsigned int lastIndex = newNbEdgesOut - 1;
    stateFrom->nbEdgesOut += 1;
    stateFrom->edgesOut[lastIndex] = malloc(sizeof(Edge));
    stateFrom->edgesOut[lastIndex]->to = stateTo;
    stateFrom->edgesOut[lastIndex]->label = label;
    return 1;
}

/* computeWordAux(machine, currentState, word) =>
 *
 * machine -> machine which the word will go through
 * currentState -> current state id the word is in
 * word -> word part remaining to be processed
 *
 * Returns whether or not the remaining word part can go through the machine from it's current state.
 */
bool computeWordAux(Machine *machine, unsigned int currentState, char *word) {
    if (machine == NULL || word == NULL)
        return false;

    if (*word == '\0') {
        // Check that the word is in finalState
        for (int i = 0; i < machine->nbFStates; i++) {
            if (currentState == machine->finalStates[i])
                return true;
        }
    }

    // Check if there is a next state corresponding to the first char of our word
    // if not the word can't be processed if yes then continue exploring.
    State *state = machine->states[currentState];
    Edge **edgesOut = state->edgesOut;
    for (int i = 0; i < state->nbEdgesOut; i++) {
        Edge *edge = edgesOut[i];
        if (edge->label == *word) {
            if (computeWordAux(machine, edge->to->stateId, ++word))
                return true;
        }
    }

    return false;
}

/* computeWord(machine, word) =>
 *
 * Returns wether or not word is accepted by the given machine.
 */
bool computeWord(Machine *machine, char *word) {
    if (machine == NULL || word == NULL)
        return false;

    // Find initialState
    unsigned int *initialStates = machine->initialStates;
    for (int i = 0; i < machine->nbIStates; i++) {
        State *initialState = machine->states[initialStates[i]];
        Edge **edgesOut = initialState->edgesOut;
        for (int i = 0; i < initialState->nbEdgesOut; i++) {
            Edge *edge = edgesOut[i];
            if (edge->label == *word) {
                if (computeWordAux(machine, edge->to->stateId, ++word))
                    return true;
            }
        }
    }

    return false;
}
