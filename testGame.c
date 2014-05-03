// testGame.c
// Tests the functions implemented in Game.c
// Group Brown Sugar
// Hector Morlet, Matty Overington and Thomas Waring
// Commenced on Saturday the 3rd of May

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>

#include "Game.h"

#define UNIMPORTANT_DICE_VALUE_FOR_TESTING 7;
#define MIN_DICE_VALUE 2;
#define MAX_DICE_VALUE 12;
#define ARBITRARILY_LARGE_NUMBER_TO_TEST_TURNS_UP_TO 1000;
#define TERRA_NULLIS -1;

void testNewGame (void);
void testMakeAction (void);
void testThrowDice (void);
void testGetDiscipline (void);
void testGetDiceValue (void);
void testGetWhoseTurn (void);
void testGetTurnNumber (void);
void testGetMostARCs (void);

int main(int argc, char *argv[]) {

   testNewGame ();
   testMakeAction ();
   testThrowDice ();
   testGetDiscipline ();
   testGetDiceValue ();
   testGetWhoseTurn ();
   testGetTurnNumber ();

   return EXIT_SUCCESS;;
}

void testNewGame (void) {
   // All this does is check the program doesn't crash when
   // making a new game.
   // The actual creation and parameters will be checked in the
   // getter functions.
   // Also tests for lack of crashing on disposal

   printf("Testing newGame\n");

   // Create a game

   Game g;

   // The values from the "badly drawn map"
   // They aren't really important, just needed
   // to parse into the function

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   disposeGame (g);

   printf("Passed!\n");
}

void testThrowDice (void) {
   // As above, test to see that throwing the dice doesn't result in
   // the game crashing.

   printf("Testing throwDice\n");

   // Create a game

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Loop over all possible dice scores and throw the dice for
   // that score

   diceScore = MIN_DICE_VALUE;

   while (diceScore <= MAX_DICE_VALUE) {
      throwDice (g, diceScore);
   }

   printf("Passed!\n");
}

void testMakeAction (void) {
   // Again all this does is check the program doesn't crash
   // Whether the action worked will be tested in other functions

   printf("Testing makeAction\n");

   // Create a game

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Throw the dice once to get the game out of "Terra Nullis"

   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);

   // Test making a campus

   action a;
   path destination;
   destination = "RL";
   a.actionCode = BUILD_CAMPUS;
   a.destination = destination;

   makeAction (g, a);

   // Test building a GO8

   a.actionCode = BUILD_GO8;

   makeAction (g, a);

   // Test obtaining an ARC grant

   a.actionCode = OBTAIN_ARC;

   makeAction (g, a);

   // Test obtaining a publication

   a.actionCode = OBTAIN_PUBLICATION;

   makeAction (g, a);

   // Test obtaining an IP patent

   a.actionCode = OBTAIN_IP_PATENT;

   makeAction (g, a);

   // Test retraining students
   // TODO check this doesn't just crash due to negative students

   a.actionCode = RETRAIN_STUDENTS;
   a.disciplineFrom = STUDENT_BPS;
   a.disciplineTo = STUDENT_MJ;

   makeAction (g, a);

   // Dispose the game

   disposeGame (g);

   printf("Passed!\n");
}

void testGetDiscipline (void) {
   // Tests that getDiscipline returns the correct discipline

   printf("Testing getDiscipline\n");

   // Create a new game with the values from the "badly drawn map"

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   int regionID = 0;

   // Loops over all the regions checking they were assigned
   // the correct discipline value

   while (regionID < NUM_REGIONS) {
      assert (getDiscipline (g, regionID) == disciplines [regionID]);
      regionID ++;
   }

   disposeGame (g);

   printf("Passed!\n");
}

void testGetDiceValue (void) {
   // Tests that getDiceValue returns the correct discipline

   printf("Testing getDiceValue\n");

   // Create a new game with the values from the "badly drawn map"

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Loops over all the regions checking they were assigned
   // the correct dice value

   int regionID = 0;

   while (regionID < NUM_REGIONS) {
      assert (getDiceValue (g, regionID) == dice [regionID]);
      regionID ++;
   }

   disposeGame (g);

   printf("Passed!\n");
}

void testGetWhoseTurn (void) {
   // Test that rolling the dice and passing
   // advances the value of getWhoseTurn correctly

   printf("Testing getWhoseTurn\n");

   // Create a new Game, values of stuff isn't important

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Initialise an action that merely passes

   action pass;
   pass.actionCode = PASS;

   // Run Tests

   assert (getWhoseTurn (g) == NO_ONE);

   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);

   assert (getWhoseTurn (g) == UNI_A);

   makeAction (g, pass);

   assert (getWhoseTurn (g) == UNI_B);

   makeAction (g, pass);

   assert (getWhoseTurn (g) == UNI_C);

   makeAction (g, pass);

   assert (getWhoseTurn (g) == UNI_A);

   disposeGame (g);

   printf("Passed!\n");
}

void testGetTurnNumber (void) {
   // Test that taking three turns advances the turn number correctly

   printf("Testing getTurnNumber\n");

   // Create a new Game, values of stuff isn't important

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Initialise an action that merely passes

   action pass;
   pass.actionCode = PASS;

   // Run Tests

   int turnNumber = TERRA_NULLIS;

   while (turnNumber <= ARBITRARILY_LARGE_NUMBER_TO_TEST_TURNS_UP_TO) {
      assert (getTurnNumber (g) == turnNumber);

      // Make three turns, one for each player
      makeAction (g, pass);
      makeAction (g, pass);
      makeAction (g, pass);

      turnNumber ++;
   }

   printf("Passed!\n");
}

void testGetMostARCs (void) {
   // Test the get most ARCs function
   // Will use the makeAction function to do so

   printf("Testing getMostARCs\n");

   // Create a new Game, values of stuff again isn't important

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Assert that the player with the most ARCs starts off as no one

   assert (getMostARCs (g) == NO_ONE);

   // Advance the game from "Terra Nullis"

   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);

   // Initialise an action that adds an ARC and one that passes

   action addARC;
   addARC.actionCode = OBTAIN_ARC;

   action pass;
   pass.actionCode = PASS;

   // Add an ARC for player A (the player whose turn it currently is)
   // in a set position

   addARC.destination = "R";
   makeAction (g, addARC);

   assert (getMostARCs (g) == UNI_A);

   // Advance the turn to UNI_B and give them an ARC
   // Then assert that UNI_A still has the title

   makeAction (g, pass);
   makeAction (g, addARC);

   assert (getMostARCs (g) == UNI_A);

   // Give UNI_B another ARC
   // assert that now they have the title

   addARC.destination = "L";
   makeAction (g, addARC);

   assert (getMostARCs (g) == UNI_B);

   // End of tests! (? anything else Hector/Matt ?)

   disposeGame (g);

   printf("Passed!\n");
}











