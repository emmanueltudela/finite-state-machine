#ifndef __FSTATEM_H__
#define __FSTATEM_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "fstatem.h"

enum STATES_NAME {
    A_STATE,
    B_STATE,
    C_STATE,
    D_STATE,
    E_STATE,
    F_STATE,
    G_STATE,
    H_STATE,
    I_STATE,
    J_STATE,
    K_STATE,
    L_STATE,
    M_STATE,
    N_STATE,
    O_STATE,
    P_STATE,
    Q_STATE,
    R_STATE,
    S_STATE,
    T_STATE,
    U_STATE,
    V_STATE,
    W_STATE,
    X_STATE,
    Y_STATE,
    Z_STATE,
}

// Structs

typedef struct Edge {
    char label;
    SEdge from;
    SEdge to;
} *SEdge;

typedef struct State {
    unsigned int stateId;
    SEdge *edgesOut; 
} *SState;

typedef struct Machine {
    SState *states;
    unsigned int *initialStates;
    unsigned int *finalStates;
    char *alphabet;
} *SMachine;

// Functions

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
SMachine *createMachine(char *alphabet, SStates *states, unsigned int numberOfStates, unsigned int *initialStates, unsigned int nbIStates, unsigned int *finalStates, unsigned int nbFStates);

/* freeMachine(machine) =>
 *
 * machine -> machine to free
 *
 * Free the machine.
 */
void freeMachine(SMachine *machine);

/* createStates(nbStates) =>
 *
 * nbStates -> number of states to return
 *
 * Returns an array with given number of states.
 */
SState *createStates(int nbStates);

/* freeStates(states, nbStates) =>
 *
 * states -> array of states to free
 * nbStates -> number of states to free
 *
 * Free every states and the array.
 */
void freeStates(SState *states, unsigned int nbStates);

/* connectStates(from, to, label) =>
 *
 * Creates an edge in fromState pointing towards toState with the given label.
 *
 * label must be included in given alphabet.
 */
int connectStates(SState *states, char *alphabet, unsigned int fromState, unsigned int toState, char label);

/* computeWord(machine, word) =>
 *
 * Returns wether or not word is accepted by the given machine.
 *
 * word must be made with characters from the alphabet used in machine.
 */
bool computeWord(SMachine *machine, char *word);

#endif
