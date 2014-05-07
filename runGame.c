#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Game.h"

#define WIN_KPI 150

int main (int argc, char *argv[]) {
  Game g  = newGame(..);
  int currentPlayer = 0;
  
  While (getKPI (g, currentPlayer) < WIN_KPI) {
    diceValue = rollDice();
    throwDice(g, diceValue);
    action move = getMove();
    While (move.actionCode != PASS) {
      assert (isLegal (g, move) == TRUE);
      If(move.actionCode == START_SPINOFF) {
        diceValue = rollDice();
        Decide
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
    scanf ("Enter the destination path for the campus: %s", &move.destination);
  } else if (move.actionCode == 2) {
    scanf ("Enter the destination path for the GO8 campus: %s", &move.destination);
  } else if (move.actionCode == 3) {
    scanf ("Enter the destination path for the ARC: %s", &move.destination);
  }else if (move.actionCode == 7) {
    scanf ("Enter the student type to retrain: %d", &move.disciplineFrom);
  }
}
