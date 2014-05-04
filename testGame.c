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


#define UNIMPORTANT_DICE_VALUE_FOR_TESTING 7
#define MIN_DICE_VALUE 2
#define MAX_DICE_VALUE 12
#define TURN_TESTING_ITERATIONS 1000
#define TERRA_NULLIS -1
#define NUM_INITIAL_CAMPUSES 2
#define INITIAL_NUMBER_OF_GO8s 0
#define INITIAL_NUMBER_OF_IP_PATENTS 0
#define INITIAL_NUMBER_OF_PUBLICATIONS 0

#define KPIPointsForCampus 10
#define KPIPointsForGO8 20
#define KPIPointsForARC 2
#define KPIPointsForPatentIP 10
#define KPIPointsForMostARCs 10
#define KPIPointsForMostPublications 10


// Setters
void testNewGame (void);
void testdisposeGame (void);
void testMakeAction (void);
void testThrowDice (void);

// Getters
void testGetDiscipline (void);
void testGetDiceValue (void);
void testGetWhoseTurn (void);
void testGetTurnNumber (void);
void testGetMostARCs (void);
void testGetMostPublications (void);
void testGetCampus (void);
void testGetARC (void);
void testGsLegalAction (void);
void testGetKPIpoints (void);
void testGetARCs (void);
void testGetGO8s (void);
void testGetCampuses (void);
void testGetIPs (void);
void testGetPublications (void);
void testGetStudents (void);
void testGetExchangeRate (void);


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


// .oO0-------------------------------------------------------0Oo. //
// ---------------------------- Setters -------------------------- //
// .oO0-------------------------------------------------------0Oo. //

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

   int diceScore = MIN_DICE_VALUE;

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
   a.actionCode = BUILD_CAMPUS;
   a.destination = "RL";

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


// .oO0-------------------------------------------------------0Oo. //
// ---------------------------- Getters -------------------------- //
// .oO0-------------------------------------------------------0Oo. //

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

   while (turnNumber <= TURN_TESTING_ITERATIONS) {
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


void testGetMostPublications (void) {
   // Test the get most publications function
   // Will use the makeAction function to do so
   // TODO (Hector/Matt) Check I haven't done anything 
   // stupid in this function because I copy pasted it 
   // from the previous one (I have checked)

   printf("Testing getMostPublications\n");

   // Create a new Game, values of stuff again isn't important

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Assert that the player with the most publications
   // starts off as no one

   assert (getMostPublications (g) == NO_ONE);

   // Advance the game from "Terra Nullis"

   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);

   // Initialise an action that adds an ARC and one that passes

   action obtainPublication;
   obtainPublication.actionCode = OBTAIN_PUBLICATION;

   action pass;
   pass.actionCode = PASS;

   // Add an ARC for player A (the player whose turn it currently is)
   // in a set position

   makeAction (g, obtainPublication);

   assert (getMostPublications (g) == UNI_A);

   // Advance the turn to UNI_B and give them an ARC
   // Then assert that UNI_A still has the title

   makeAction (g, pass);
   makeAction (g, obtainPublication);

   assert (getMostPublications (g) == UNI_A);

   // Give UNI_B another ARC
   // assert that now they have the title

   makeAction (g, obtainPublication);

   assert (getMostPublications (g) == UNI_B);

   // Cycle on to next player then test again, just to check

   makeAction (g, pass);

   assert (getMostPublications (g) == UNI_B);

   // End of tests! (? anything else Hector/Matt ?)

   disposeGame (g);

   printf("Passed!\n");
}


void testGetCampus (void) {
   // Test that adding a campus affects the result of getCampus
   // accordingly

   printf("Testing getCampus\n");

   // Create a new Game, values of stuff again isn't important

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Advance the game from "Terra Nullis"

   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);

   // Initialise some actions

   action addCampus;
   addCampus.actionCode = BUILD_CAMPUS;

   action addGO8;
   addGO8.actionCode = BUILD_GO8;

   action pass;
   pass.actionCode = PASS;

   // Assert that the starting campuses are where they should be

   path pathToVertex = "RLLLLL"; // A path back to the original vertex
   assert (getCampus (g, pathToVertex) == CAMPUS_A);

   pathToVertex = "RLRLRLRLRLL"; // A path to the other initial campus
                                // of player A
   assert (getCampus (g, pathToVertex) == CAMPUS_A);

   pathToVertex = "RRLRL"; // A path to one of the initial campuses
                          // of player B
   assert (getCampus (g, pathToVertex) == CAMPUS_B);

   pathToVertex = "LRLRLRRLRL"; // A path to the other initial campus
                               // of player B
   assert (getCampus (g, pathToVertex) == CAMPUS_B);

   pathToVertex = "LRLRL"; // A path to one of the initial campuses
                          // of player C
   assert (getCampus (g, pathToVertex) == CAMPUS_C);

   pathToVertex = "RRLRLLRLRL"; // A path to the other initial campus
                               // of player C
   assert (getCampus (g, pathToVertex) == CAMPUS_C);

   // Assert that empty vertexes are as they should be

   path paths[] = {"R", "RR", "RRL", "RRLR", "L", "LR", "LRR", "LRRR", 
                    "LRRRL", "LRRRLR", "LRRRLRL", "LRRRLRLR", 
                    "LRRRLRLRL", "LRL", "LRLR", "LRLRR", "LRLRRR", 
                    "LRLRRRL", "LRLRRRLR", "LRLRRRLRL", "LRLRRRLRLR", 
                    "LRLRRRLRLRL", "LRLRRRLRLRLR", "LRLRRRLRLRLRL", 
                    "LRLRLR", "LRLRLRR", "LRLRLRRR", "LRLRLRRRL", 
                    "LRLRLRRRLR", "LRLRLRRRLRL", "LRLRLRRRLRLR", 
                    "LRLRLRRRLRLRL", "LRLRLRRRLRLRLR", 
                    "LRLRLRRRLRLRLRL", "LRLRLRRRLRLRLRLL", "LRLRLRRL",
                    "LRLRLRRLR", "LRLRLRRLRL", "LRLRLRRLRLR", 
                    "LRLRLRRLRLRL", "LRLRLRRLRLRLR", "LRLRLRRLRLRLRL",
                    "LRLRLRRLRLRLRLR", "LRLRLRRLRLRLRLRL", "", "", "", ""};

   int i = 0;
   while(i < 48) {
      pathToVertex = paths[i];
      assert (getCampus (g, pathToVertex) == VACANT_VERTEX);
      i++;
   }

   // What is going on here?
   pathToVertex = "LRLRLRRLRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRLRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRLRLRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRLRLRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   // Assert that adding campuses and GO8's works with (and without) 
   // convoluted paths

   pathToVertex = "RL";
   addCampus.destination = pathToVertex;
   makeAction (g, addCampus);
   assert (getCampus (g, pathToVertex) == CAMPUS_A);

   pathToVertex = "LR";
   addGO8.destination = pathToVertex;
   makeAction (g, addGO8);
   assert (getCampus (g, pathToVertex) == GO8_A);

   makeAction (g, pass);

   pathToVertex = "RLLLLLLLRL";
   addCampus.destination = pathToVertex;
   makeAction (g, addCampus);
   assert (getCampus (g, pathToVertex) == CAMPUS_B);

   pathToVertex = "RLRLLLLLLLLLBLR";
   addGO8.destination = pathToVertex;
   makeAction (g, addGO8);
   assert (getCampus (g, pathToVertex) == GO8_B);

   makeAction (g, pass);

   pathToVertex = "LRLRRLBL";
   addCampus.destination = pathToVertex;
   makeAction (g, addCampus);
   assert (getCampus (g, pathToVertex) == CAMPUS_C);

   pathToVertex = "LRRLRL";
   addGO8.destination = pathToVertex;
   makeAction (g, addGO8);
   assert (getCampus (g, pathToVertex) == GO8_C);

   disposeGame (g);

   printf("Passed!\n");
}


void testGetARC (void) {
   // Test that adding a campus affects the result of getARC
   // accordingly

   printf("Testing getARC\n");

   // Create a new Game, values of stuff again isn't important

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Advance the game from "Terra Nullis"

   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);

   // Initialise some actions

   action addARC;
   addARC.actionCode = OBTAIN_ARC;

   action pass;
   pass.actionCode = PASS;

   // TODO (if I can be bothered):
   //    Check whether vacant ARCs are all vacant

   // Assert that adding ARCs works with (and without) 
   // convoluted paths

   pathToVertex = "RL";
   addARC.destination = pathToVertex;
   makeAction (g, addARC);
   assert (getARC (g, pathToVertex) == ARC_A);

   pathToVertex = "LR";
   addARC.destination = pathToVertex;
   makeAction (g, addARC);
   assert (getARC (g, pathToVertex) == ARC_A);

   makeAction (g, pass);

   pathToVertex = "RLLLLLLLRL";
   addARC.destination = pathToVertex;
   makeAction (g, addARC);
   assert (getARC (g, pathToVertex) == ARC_B);

   pathToVertex = "RLRLLLLLLLLLBLR";
   addARC.destination = pathToVertex;
   makeAction (g, addARC);
   assert (getARC (g, pathToVertex) == ARC_B);

   makeAction (g, pass);

   pathToVertex = "LRLRRLBL";
   addARC.destination = pathToVertex;
   makeAction (g, addARC);
   assert (getARC (g, pathToVertex) == ARC_C);

   pathToVertex = "LRRLRL";
   addARC.destination = pathToVertex;
   makeAction (g, addARC);
   assert (getARC (g, pathToVertex) == ARC_C);

   // End of tests

   disposeGame (g);

   printf("Passed!\n");
}


void testIsLegalAction (void) {
   printf("Testing isLegalAction...\n");

   // --------------------------------------------
   // Init
   // --------------------------------------------

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Advance the game from "Terra Nullis" (it is now UNI_A's turn)
   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);

   // Initialising some actions
   action buildCampus;
   buildCampus.actionCode = BUILD_CAMPUS;

   action buildGO8;
   buildGO8.actionCode = BUILD_GO8;

   action obtainArc;
   obtainArc.actionCode = OBTAIN_ARC;

   action startSpinoff;
   startSpinoff.actionCode = START_SPINOFF;

   action obtainIPPatent;
   obtainIPPatent.actionCode = OBTAIN_IP_PATENT;

   action obtainPublication;
   obtainPublication.actionCode = OBTAIN_PUBLICATION;

   action retrainStudents;
   retrainStudents.actionCode = RETRAIN_STUDENTS;

   action pass;
   pass.actionCode = PASS;

   // --------------------------------------------
   // Planning bits
   // --------------------------------------------

   // Criteria for an action to be valid:
   // - It isn't currently Tera Nulius
   // - The action is valid to be made at this time
   // - The path is valid
   //    - The path does not lead off the island
   //    - It is of legal length
   //    - It has only legal direction characters in it

   // --------------------------------------------
   // Testing lack in resources to buy things
   // --------------------------------------------

   // - Doesn't have the students to pay for campus
   buildCampus.destination = "L";
   assert(isLegalAction(g, buildCampus) == FALSE);

   // - Doesn't have the students to pay for GO8
   // How??

   // - Has the right amount of students to start a spinoff
   assert(isLegalAction(startSpinoff) == FALSE);

   // - The university has the sufficient students to retrain people
   retrainStudents.disciplineFrom = STUDENT_MTV;
   retrainStudents.disciplineTo = STUDENT_BPS;
   assert(isLegalAction(retrainStudents) == FALSE);

   // -----------------------------------------------------
   // Iterating over turns to give players enough resources
   // -----------------------------------------------------

   int i = 0;
   while(i < TURN_TESTING_ITERATIONS) {
      makeAction(pass);
      throwDice(g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);
      i++;
   }

   // --------------------------------------------
   // Testing PASS
   // --------------------------------------------

   // Legals (passing is always legal)
   assert(isLegalAction(g, pass) == TRUE);

   // --------------------------------------------
   // Testing BUILD_CAMPUS
   // --------------------------------------------

   // Legals
   buildCampus.destination = "L";
   assert(isLegalAction(g, buildCampus) == TRUE);

   // Illegals

   // - The vertex isn't vacant

   // Making a campus to the left
   obtainArc.destination = "L";
   makeAction(g, obtainArc);
   buildCampus.destination = "L";
   makeAction(g, buildCampus);
   // Testing that trying to build in the same place is not allowed
   assert(isLegalAction(g, buildCampus) == FALSE);

   // - The path is incorrect

   //    - The path does not lead off the island
   buildCampus.destination = "BBBBBB";
   assert(isLegalAction(g, buildCampus) == FALSE);

   //    - It is of legal length
   buildCampus.destination = "RLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
                              LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
                              LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
                              LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL";
   assert(isLegalAction(g, buildCampus) == FALSE);

   //    - It has only legal direction characters in it
   buildCampus.destination = "XXXXXXXXXXX";
   assert(isLegalAction(g, buildCampus) == FALSE);

   // - The vertex isn't adjacent to one of the player's ARCs

   buildCampus.destination = "LRLRLRL";
   assert(isLegalAction(g, buildCampus) == FALSE);


   // --------------------------------------------
   // Testing BUILD_GO8
   // --------------------------------------------

   // Legals

   buildGO8.destination = "L";
   assert(isLegalAction(g, buildGO8) == TRUE);

   // Illegals

   // - There is no campus there

   obtainArc.destination = "R";
   makeAction(g, obtainArc);
   buildGO8.destination = "R";
   assert(isLegalAction(g, buildGO8) == FALSE);

   // - There are more than 7 GO8s

   // Making seven (more) GO8s
   char *GO8Paths[] = {"LR", "LRL", "LRLR", "LRLRL", 
                       "LRLRLR", "LRLRLRL", "LRLRLRLR", "LRLRLRLRL"};
   i = 0;
   while(i < 7) {
      obtainArc.destination = GO8Paths[i];
      buildCampus.destination = GO8Paths[i];
      buildGO8.destination = GO8Paths[i];
      makeAction(g, obtainArc);
      makeAction(g, buildCampus);
      makeAction(g, buildGO8);
      i++;
   }

   // Trying to make a ninth GO8
   obtainArc.destination = GO8Paths[7];
   buildCampus.destination = GO8Paths[7];
   buildGO8.destination = GO8Paths[7];
   makeAction(g, obtainArc);
   makeAction(g, buildCampus);
   assert(isLegalAction(g, buildGO8) == FALSE);

   // Making new game because there is too much crap on the old one
   disposeGame(g);
   Game g = newGame (disciplines, dice);
   i = 0;
   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);
   while(i < TURN_TESTING_ITERATIONS) {
      makeAction(pass);
      throwDice(g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);
      i++;
   }

   // --------------------------------------------
   // OBTAIN_ARC
   // --------------------------------------------

   // Legals
   obtainArc.destination = "L";
   assert(isLegalAction(g, obtainArc) == TRUE);

   // Illegals

   // - The edge isn't vacant

   obtainArc.destination = "L";
   makeAction(g, obtainArc);
   assert(isLegalAction(g, obtainArc) == FALSE);

   // - The path is incorrect

   //    - The path leads off the island
   obtainArc.destination = "BBBBBBBBBBB";
   assert(isLegalAction(g, obtainArc) == FALSE);

   //    - It isn't of legal length
   obtainArc.destination = "RLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
                            LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
                            LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL
                            LLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLLL";
   assert(isLegalAction(g, obtainArc) == FALSE);

   //    - It has illegal direction characters in it
   obtainArc.destination = "XXXXX";
   assert(isLegalAction(g, obtainArc) == FALSE);

   // - It is adjacent to a vertex which is adjacent to another
   //   edge owned by the same person

   obtainArc.destination = "LRL";
   assert(isLegalAction(g, obtainArc) == FALSE);

   // --------------------------------------------
   // START_SPINOFF
   // --------------------------------------------

   // Legals

   assert(isLegalAction(g, startSpinoff) == TRUE);

   // --------------------------------------------
   // OBTAIN_PUBLICATION
   // --------------------------------------------

   // Legals
   // ?whatdo?

   // Illegals
   // ?whatdo?

   // --------------------------------------------
   // OBTAIN_IP_PATENT
   // --------------------------------------------

   // Legals
   // ?whatdo?

   // Illegals
   // ?whatdo?

   // --------------------------------------------
   // RETRAIN_STUDENTS
   // --------------------------------------------

   // Legals

   retrainStudents.disciplineFrom = STUDENT_MTV;
   retrainStudents.disciplineTo = STUDENT_BPS;
   assert(isLegalAction(g, retrainStudents) == TRUE);

   // Illegals

   // - There aren't only legal discipline numbers (0, 1, 2, 3, 4, 5)

   retrainStudents.disciplineFrom = 4;
   retrainStudents.disciplineTo = 6;
   assert(isLegalAction(g, retrainStudents) == FALSE);

   retrainStudents.disciplineFrom = 6;
   retrainStudents.disciplineTo = 4;
   assert(isLegalAction(g, retrainStudents) == FALSE);

   retrainStudents.disciplineFrom = 6;
   retrainStudents.disciplineTo = 7;
   assert(isLegalAction(g, retrainStudents) == FALSE);

   // - Wrong discipline convertions

   retrainStudents.disciplineFrom = STUDENT_THD;
   retrainStudents.disciplineTo = STUDENT_MMONEY;
   assert(isLegalAction(g, retrainStudents) == FALSE);

   // - Converting to the same thing

   retrainStudents.disciplineFrom = STUDENT_MMONEY;
   retrainStudents.disciplineTo = STUDENT_MMONEY;
   assert(isLegalAction(g, retrainStudents) == FALSE);

   // Done (I really am not sure -- will need aditions as we go along)
   disposeGame(g);

   printf("Passed!\n");
}


void testGetKPIpoints (void) {
   printf("Testing getKPIpoints\n");

   // Create a new Game, values of stuff again isn't important

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Advance the game from "Terra Nullis"

   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);

   // Initialise some actions

   action addCampus;
   addCampus.actionCode = BUILD_CAMPUS;

   action addGO8;
   addGO8.actionCode = BUILD_GO8;

   action obtainArc;
   obtainArc.actionCode = OBTAIN_ARC;

   action obtainIPPatent;
   obtainIPPatent.actionCode = OBTAIN_IP_PATENT;

   action obtainPublication;
   obtainPublication.actionCode = OBTAIN_PUBLICATION;

   action pass;
   pass.actionCode = PASS;

   // Assert KPI points are correct at the start of the game
   // The only KPI points Unis start with are the ones for
   // their two initial ordinary campuses

   int uniAKPIs = NUM_INITIAL_CAMPUSES * KPIPointsForCampus;
   int uniBKPIs = NUM_INITIAL_CAMPUSES * KPIPointsForCampus;
   int uniCKPIs = NUM_INITIAL_CAMPUSES * KPIPointsForCampus;

   assert (getKPIpoints (g, UNI_A) == uniAKPIs);
   assert (getKPIpoints (g, UNI_B) == uniBKPIs);
   assert (getKPIpoints (g, UNI_C) == uniCKPIs);

   // Assert adding campuses affects the KPI points correctly
   // (for every uni)

   addCampus.destination = "R";
   makeAction (g, addCampus);
   uniAKPIs += KPIPointsForCampus;
   assert (getKPIpoints (g, UNI_A) == uniAKPIs);
   makeAction (g, pass);

   addCampus.destination = "L";
   makeAction (g, addCampus);
   uniBKPIs += KPIPointsForCampus;
   assert (getKPIpoints (g, UNI_B) == uniBKPIs);
   makeAction (g, pass);

   addCampus.destination = "LR";
   makeAction (g, addCampus);
   uniCKPIs += KPIPointsForCampus;
   assert (getKPIpoints (g, UNI_C) == uniCKPIs);
   makeAction (g, pass);

   // Assert turning one of a Uni's (any Uni's) original campuses 
   // into a GO8 affects KPIs accordingly

   addGO8.destination = "RLLLLL";
   makeAction (g, addGO8);
   uniAKPIs += KPIPointsForGO8;
   uniAKPIs -= KPIPointsForCampus;
   assert (getKPIpoints (g, UNI_A) == uniAKPIs);
   makeAction (g, pass);

   addGO8.destination = "RRLRL";
   makeAction (g, addGO8);
   uniBKPIs += KPIPointsForGO8;
   uniBKPIs -= KPIPointsForCampus;
   assert (getKPIpoints (g, UNI_B) == uniBKPIs);
   makeAction (g, pass);

   addGO8.destination = "LRLRL";
   makeAction (g, addGO8);
   uniCKPIs += KPIPointsForGO8;
   uniCKPIs -= KPIPointsForCampus;
   assert (getKPIpoints (g, UNI_C) == uniCKPIs);
   makeAction (g, pass);

   // Assert that adding ARCs affects KPIs accordingly for every Uni
   // Including prestige awards: getting and losing

   addARC.destination = "R";
   makeAction (g, addARC);
   uniAKPIs += KPIPointsForARC;
   uniAKPIs += KPIPointsForMostARCs;
   assert (getKPIpoints (g, UNI_A) == uniAKPIs);
   makeAction (g, pass);

   addARC.destination = "L";
   makeAction (g, addARC);
   uniBKPIs += KPIPointsForARC;
   assert (getKPIpoints (g, UNI_B) == uniBKPIs);
   makeAction (g, pass);

   addARC.destination = "LR";
   makeAction (g, addARC);
   uniCKPIs += KPIPointsForARC;
   assert (getKPIpoints (g, UNI_C) == uniCKPIs);

   addARC.destination = "LRL";
   makeAction (g, addARC);
   uniCKPIs += KPIPointsForARC;
   uniCKPIs += KPIPointsForMostARCs;
   uniAKPIs -= KPIPointsForMostARCs;
   assert (getKPIpoints (g, UNI_C) == uniCKPIs);
   assert (getKPIpoints (g, UNI_A) == uniAKPIs);
   makeAction (g, pass);

   // Assert that obtaining IP Patents affects KPIs accordingly

   makeAction (g, obtainIPPatent);
   uniAKPIs += KPIPointsForPatentIP;
   assert (getKPIpoints (g, UNI_A) == uniAKPIs);
   makeAction (g, pass);

   makeAction (g, obtainIPPatent);
   uniBKPIs += KPIPointsForPatentIP;
   assert (getKPIpoints (g, UNI_B) == uniBKPIs);
   makeAction (g, pass);

   makeAction (g, obtainIPPatent);
   uniCKPIs += KPIPointsForPatentIP;
   assert (getKPIpoints (g, UNI_C) == uniCKPIs);
   makeAction (g, pass);

   // Assert that obtaining publications affects KPIs accordingly 
   // for every Uni Including prestige awards: getting and losing

   makeAction (g, obtainPublication);
   uniAKPIs += KPIPointsForMostPublications;
   assert (getKPIpoints (g, UNI_A) == uniAKPIs);
   makeAction (g, pass);

   makeAction (g, obtainPublication);
   assert (getKPIpoints (g, UNI_B) == uniBKPIs);
   makeAction (g, pass);

   makeAction (g, obtainPublication);
   assert (getKPIpoints (g, UNI_C) == uniCKPIs);

   makeAction (g, obtainPublication);
   uniCKPIs += KPIPointsForMostPublications;
   uniAKPIs -= KPIPointsForMostPublications;
   assert (getKPIpoints (g, UNI_C) == uniCKPIs);
   assert (getKPIpoints (g, UNI_A) == uniAKPIs);
   makeAction (g, pass);

   // End of these tests!

   disposeGame (g);

   printf("Passed!\n");
}


void testGetARCs (void) {
   printf("Testing getARCs...\n");

   // Create a new Game, values of stuff again isn't important
   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
             STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
             STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
             STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
             STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame(disciplines, dice);

   // Assert that all players start off with no ARCs
   assert (getARCs(g, UNI_A) == 0);
   assert (getARCs(g, UNI_B) == 0);
   assert (getARCs(g, UNI_C) == 0);

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
   makeAction(g, addARC);

   // Test it's number of ARCs is 1
   assert(getARCs(g, UNI_A) == 1);

   // End player A's turn
   makeAction (g, pass);

   // Add two ARCs for player B
   makeAction (g, addARC);
   addARC.destination = "L";
   makeAction (g, addARC);

   // Test it's number of ARCs is 2
   assert (getARCs(g, UNI_B) == 2);

   // End player B's turn
   makeAction (g, pass);

   // Advance the turn to UNI_C and give them an ARC
   makeAction (g, addARC);

   // Test it's number of ARCs is 1
   assert (getARCs(g, UNI_C) == 1);

   // End of tests! (? anything else Wezza/Matt ?)
   disposeGame (g);

   printf("Passed!\n");
}


void testGetCampuses (void) {
   // Test the getCampuses function

   printf("Testing getCampuses\n");

   // Create a new Game, values of stuff again isn't important

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS, STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Advance the game from "Terra Nullis"

   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);

   // Initialise some actions

   action getCampus;
   getCampus.actionCode = BUILD_CAMPUS;

   action pass;
   pass.actionCode = PASS;

   // Assert all Unis start off with two campuses

   int numUniACampuses = NUM_INITIAL_CAMPUSES;
   int numUniBCampuses = NUM_INITIAL_CAMPUSES;
   int numUniCCampuses = NUM_INITIAL_CAMPUSES;

   assert (getCampuses (g, UNI_A) == numUniACampuses);
   assert (getCampuses (g, UNI_B) == numUniBCampuses);
   assert (getCampuses (g, UNI_C) == numUniCCampuses);

   // Assert adding campuses affects the 
   // result of the function correctly

   addCampus.destination = "R";
   makeAction (g, addCampus);
   numUniACampuses += 1;
   assert (getCampus (g, UNI_A) == numUniACampuses);
   makeAction (g, pass);

   addCampus.destination = "L";
   makeAction (g, addCampus);
   numUniBCampuses += 1;
   assert (getCampus (g, UNI_B) == numUniBCampuses);
   makeAction (g, pass);

   addCampus.destination = "LR";
   makeAction (g, addCampus);
   numUniCCampuses += 1;
   assert (getCampus (g, UNI_C) == numUniCCampuses);
   makeAction (g, pass);

   // Assert changing a campus into a GO8 reduces the apparent
   // number of campuses accordingly

   addGO8.destination = "RLLLLL";
   makeAction (g, addGO8);
   numUniACampuses -= 1;
   assert (getKPIpoints (g, UNI_A) == numUniACampuses);
   makeAction (g, pass);

   addGO8.destination = "RRLRL";
   makeAction (g, addGO8);
   numUniBCampuses -= 1;
   assert (getKPIpoints (g, UNI_B) == numUniBCampuses);
   makeAction (g, pass);

   addGO8.destination = "LRLRL";
   makeAction (g, addGO8);
   numUniCCampuses -= 1;
   assert (getKPIpoints (g, UNI_C) == numUniCCampuses);
   makeAction (g, pass);

   // End of tests!

   disposeGame (g);

   printf("Passed!\n");
}


void testGetGO8s (void) {
   // Test the getGO8s function

   printf("Testing getGO8s\n");

   // Create a new Game, values of stuff again isn't important

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS, STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Advance the game from "Terra Nullis"

   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);

   // Initialise some actions

   action addGO8;
   addGO8.actionCode = BUILD_GO8;

   action pass;
   pass.actionCode = PASS;

   // Assert all Unis start off with no GO8s

   int numUniAGO8s = INITIAL_NUMBER_OF_GO8s;
   int numUniBGO8s = INITIAL_NUMBER_OF_GO8s;
   int numUniCGO8s = INITIAL_NUMBER_OF_GO8s;

   assert (getGO8s (g, UNI_A) == numUniAGO8s);
   assert (getGO8s (g, UNI_B) == numUniBGO8s);
   assert (getGO8s (g, UNI_C) == numUniCGO8s);

   // Assert transforming an initial campus into a GO8 changes the
   // result of this function accordingly

   addGO8.destination = "RLLLLL";
   makeAction (g, addGO8);
   numUniAGO8 += 1;
   assert (getGO8s (g, UNI_A) == numUniAGO8);
   makeAction (g, pass);

   addGO8.destination = "RRLRL";
   makeAction (g, addGO8);
   numUniBGO8 += 1;
   assert (getGO8s (g, UNI_B) == numUniBGO8);
   makeAction (g, pass);

   addGO8.destination = "LRLRL";
   makeAction (g, addGO8);
   numUniCGO8 += 1;
   assert (getGO8s (g, UNI_C) == numUniCGO8);
   makeAction (g, pass);

   // End of tests!

   disposeGame (g);

   printf("Passed!\n");
}


void testGetIPs (void) {
   // Test the getIPs function

   printf("Testing getIPs\n");

   // Create a new Game, values of stuff again isn't important

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS, STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Advance the game from "Terra Nullis"

   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);

   // Initialise some actions

   action obtainIPPatent;
   obtainIPPatent.actionCode = OBTAIN_IP_PATENT;

   action pass;
   pass.actionCode = PASS;

   // Assert all Unis start off with no IPs

   int numUniAIPs = INITIAL_NUMBER_OF_IP_PATENTS;
   int numUniBIPs = INITIAL_NUMBER_OF_IP_PATENTS;
   int numUniCIPs = INITIAL_NUMBER_OF_IP_PATENTS;

   assert (getIPs (g, UNI_A) == numUniAIPs);
   assert (getIPs (g, UNI_B) == numUniBIPs);
   assert (getIPs (g, UNI_C) == numUniCIPs);

   // Assert obtaining an IP affects the result of the function
   // accordingly

   makeAction (g, obtainIPPatent);
   numUniAIPs += 1;
   assert (getIPs (g, UNI_A) == numUniAIPs);
   makeAction (g, pass);

   makeAction (g, obtainIPPatent);
   numUniBIPs += 1;
   assert (getIPs (g, UNI_B) == numUniBIPs);
   makeAction (g, pass);

   makeAction (g, obtainIPPatent);
   numUniCIPs += 1;
   assert (getIPs (g, UNI_C) == numUniCIPs);
   makeAction (g, pass);

   // End of tests!

   disposeGame (g);

   printf("Passed!\n");
}


void testGetPublications (void) {
   // Test the getPublications function

   printf("Testing getPublications\n");

   // Create a new Game, values of stuff again isn't important

   Game g;

   int disciplines[] = {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS, STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS};
   int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};

   g = newGame (disciplines, dice);

   // Advance the game from "Terra Nullis"

   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);

   // Initialise some actions

   action obtainPublication;
   obtainPublication.actionCode = OBTAIN_PUBLICATION;

   action pass;
   pass.actionCode = PASS;

   // Assert all Unis start off with no Publications

   int numUniAPublications = INITIAL_NUMBER_OF_PUBLICATIONS;
   int numUniBPublications = INITIAL_NUMBER_OF_PUBLICATIONS;
   int numUniCPublications = INITIAL_NUMBER_OF_PUBLICATIONS;

   assert (getPublications (g, UNI_A) == numUniAPublications);
   assert (getPublications (g, UNI_B) == numUniBPublications);
   assert (getPublications (g, UNI_C) == numUniCPublications);

   // Assert obtaining a publication affects the result of the function
   // accordingly

   makeAction (g, obtainPublication);
   numUniAPublications += 1;
   assert (getPublications (g, UNI_A) == numUniAPublications);
   makeAction (g, pass);

   makeAction (g, obtainPublication);
   numUniBPublications += 1;
   assert (getPublications (g, UNI_B) == numUniBPublications);
   makeAction (g, pass);

   makeAction (g, obtainPublication);
   numUniCPublications += 1;
   assert (getPublications (g, UNI_C) == numUniCPublications);
   makeAction (g, pass);

   // End of tests!

   disposeGame (g);

   printf("Passed!\n");
}


void testGetStudents (void) {
   printf("Testing getStudents\n");

   // Create a new Game, values of stuff again isn't important

   Game g;

   int disciplines[] = {STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_MJ, STUDENT_MJ, STUDENT_MJ, 
                STUDENT_MJ, STUDENT_MJ, STUDENT_MJ, STUDENT_MJ};
   int dice[] = {1,2,3,4,5,6,7,8,9,10,11,12,1,2,3,4,5,6,7};

   g = newGame (disciplines, dice);

   // Advance the game from "Terra Nullis"

   throwDice (g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);

   // Initialising some actions

   action pass;
   pass.actionCode = PASS;

   // Giving the all the players (as a whole) an MTV student per 
   // iteration

   int i = 0;
   while (i < 10) {
      throwDice(g, UNIMPORTANT_DICE_VALUE_FOR_TESTING);
      makeAction(pass);
      i++;
   }

   // Asserting that they have 10 STUDENT_MTV's
   assert(getStudents(g, UNI_A, STUDENT_MTV) +
          getStudents(g, UNI_B, STUDENT_MTV) +
          getStudents(g, UNI_C, STUDENT_MTV)) == 10);

   // End of tests!

   disposeGame(g);

   printf("Passed!\n");
}


void testGetExchangeRate (void) {

}









