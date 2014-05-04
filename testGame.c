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


#define UNIMPORTANT_DICE_VALUE_FOR_TESTING 7; // wtf
#define MIN_DICE_VALUE 2;
#define MAX_DICE_VALUE 12;
#define TURN_TESTING_ITERATIONS 1000;//ARBITRARILY_LARGE_NUMBER_TO_TEST_TURNS_UP_TO 1000;
#define TERRA_NULLIS -1;


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

   assert (getMostPublications(g) == NO_ONE);

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


void testGetCampus(void) {
   printf("Testing _...\n");

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

   pathToVertex = "R";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "RR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "RRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "RRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "L";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRRR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRRRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRRRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRRRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRRRLRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRRRLRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRRR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRRRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRRRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRRRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRRRLRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRRRLRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRRRLRLRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRRRLRLRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRRLRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRRLRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRRLRLRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRRLRLRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRRLRLRLRLL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRLRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRLRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRLRLRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRLRLRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRLRLRLRLR";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

   pathToVertex = "LRLRLRRLRLRLRLRL";
   assert (getCampus (g, pathToVertex) == VACANT_VERTEX);

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


void testGetARC(void) {
   printf("Testing getARC...\n");

   printf("Passed!\n");
}


void testIsLegalAction(void) {
   printf("Testing isLegalAction...\n");

   // Valid action codes:
   // PASS
   // BUILD_CAMPUS
   // BUILD_GO8
   // OBTAIN_ARC
   // START_SPINOFF
   // OBTAIN_PUBLICATION
   // OBTAIN_IP_PATENT
   // RETRAIN_STUDENTS

   // Criteria for an action to be valid:
   // - It isn't currently Tera Nulius
   // - The action is valid to be made at this time
   // - The path is valid
   //    - The path does not lead off the island
   //    - It is of legal length
   //    - It has only legal direction characters in it
   // PASS
   

   // BUILD_CAMPUS
   //  - The vertex is vacant
   //  - The path is correct
   //  - Is the vertex adjacent to one of the player's ARCs
   //  - Does the university have the correct students to pay


   // BUILD_GO8
   //  - There is already a campuss here
   //  - Has the students to pay
   //  - There are less than 8 GO8s
   // OBTAIN_ARC
   //  - The edge is vacant
   //  - The path is correct
   //  - It is adjacent to a vertex which is adjacent to another
   //    edge owned by the same person
   // START_SPINOFF
   //  - Has the right amount of students
   //  - Has the right type of students
   // OBTAIN_PUBLICATION
   // OBTAIN_IP_PATENT
   // RETRAIN_STUDENTS
   //  - There are only legal discipline numbers
   //     - 0, 1, 2, 3, 4, 5
   //  - The university has the sufficient amount and type of
   //    students to retrain these people

   printf("Passed!\n");
}


void testGetKPIpoints(void) {
   printf("Testing getKPIpoints...\n");

   printf("Passed!\n");
}


void testGetARCs(void) {
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


void testGetGO8s(void) {
   printf("Testing getGO8s...\n");

   printf("Passed!\n");
}


void testGetCampuses(void) {
   printf("Testing getCampuses...\n");

   printf("Passed!\n");
}


void testGetIPs(void) {
   printf("Testing getIPs...\n");

   printf("Passed!\n");
}


void testGetPublications(void) {
   printf("Testing getPublications...\n");

   printf("Passed!\n");
}


void testGetStudents(void) {
   printf("Testing getStudents...\n");

   printf("Passed!\n");
}


void testGetExchangeRate(void) {
   printf("Testing getExchangeRate...\n");

   printf("Passed!\n");
}









