#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Game.h"

#define WIN_KPI 150

#define DICE_LOWERBOUND_START_SPINOFF 0
#define DICE_UPPERBOUND_START_SPINOFF 2
#define DICE_VAL_FOR_IP 0

int main (int argc, char *argv[]) {
  Game g  = newGame(..);
  int currentPlayer = 0;
  
  while (getKPI (g, currentPlayer) < WIN_KPI) {
    diceValue = rollDice();
    throwDice(g, diceValue);
    action move = getMove();
    while (move.actionCode != PASS) {
      assert (isLegalAction (g, move) == TRUE);
      if (move.actionCode == START_SPINOFF) {
        diceValue = rollDice(DICE_LOWERBOUND_START_SPINOFF,
                              DICE_UPPERBOUND_START_SPINOFF);
        if (diceValue == DICE_VAL_FOR_IP) {
          
        }
      }
    makeAction(g, move);
    }
    currentPlayer = nextPlayer(currentPlayer);
  }
}

action getMove () {
  // Initialise the action
  action move;
  
  // Get the actionCode
  scanf ("Enter the action code: %d", &move.actionCode);
  
  // Get extra information if necessary
  if (move.actionCode == 1) {
    printf ("Enter the destination path for the campus: ");
    scanf ("%s", move.destination);
  } else if (move.actionCode == 2) {
    printf ("Enter the destination path for the GO8 campus: ");
    scanf ("%s", move.destination);
  } else if (move.actionCode == 3) {
    printf ("Enter the destination path for the ARC: ");
    scanf ("%s", move.destination);
  }else if (move.actionCode == 7) {
    printf ("Enter the student type to retrain: ");
    scanf ("%d", move.disciplineFrom);
    printf ("Enter the student type to retrain to: ");
    scanf ("%d", &move.desciplineTo);
  }
}

// Get a user inputted dice value
// Limits are inclusive
int getDiceValueTwixt (int lowerbound, int upperbound) {
  int val;
  printf ("Enter a value between %d and %d", lowerbound, upperbound);
  scanf ("%d", &val);
}



