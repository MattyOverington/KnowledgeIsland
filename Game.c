//
//  Game.c
//  The game abstract data type for Universities of Catan
//  Hector Morlet, Matthew Overington and Thomas Waring
//  3 May 2014
//


#define NUM_VERTICES 54
#define NUM_EDGES 72

#define EDGES_PER_VERTEX 3
#define REGIONS_PER_VERTEX 3 // not nescessarily, declare sea tiles as
                             // NULL pointers or something
#define VERTICES_PER_EDGE 2
#define VERTICES_PER_REGION 6

#define GO8_OFFSET 3

#define DEFAULT_EXCHANGE_RATE 3
#define EXCHAGE_RATE_WITH_CENTRE 2

#define KPIS_FOR_CAMPUS 10
#define KPIS_FOR_GO8 20
#define KPIS_FOR_ARC 2
#define KPIS_FOR_IP 10
#define KPIS_FOR_MOST_ARCS 10
#define KPIS_FOR_MOST_PUBLICATIONS 10

#define NUM_INITIAL_THD_STUDENTS 0
#define NUM_INITIAL_BPS_STUDENTS 3
#define NUM_INITIAL_BQN_STUDENTS 3
#define NUM_INITIAL_MJ_STUDENTS 1
#define NUM_INITIAL_MTV_STUDENTS 1
#define NUM_INITIAL_MMONEY_STUDENTS 1

// disciplines
#define STUDENT_THD 0
#define STUDENT_BPS 1
#define STUDENT_BQN 2
#define STUDENT_MJ  3
#define STUDENT_MTV 4
#define STUDENT_MMONEY 5

// Paths to retraining centres
#define PATH_TO_RETRAINING_CENTRE_BPS "RLRLRLRLRR"
#define PATH_TO_RETRAINING_CENTRE_BQN "LRLRLRRL"
#define PATH_TO_RETRAINING_CENTRE_MJ_ONE "RLRLRLLRLR"
#define PATH_TO_RETRAINING_CENTRE_MJ_TWO "RLRLRLLRLRR"
#define PATH_TO_RETRAINING_CENTRE_MTV "RR"
#define PATH_TO_RETRAINING_CENTRE_MMONEY_ONE "LR"
#define PATH_TO_RETRAINING_CENTRE_MMONEY_TWO "LRL"

#define NUM_INITIAL_CAMPUSES 2

#define NUM_PLAYERS 3

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "Game.h"


typedef struct _game {
   // Map things
   vertex vertices[NUM_VERTICES];
   edge edges[NUM_EDGES];
   region regions[NUM_REGIONS];

   // Players
   player players[NUM_PLAYERS];

   // Other useful things to store
   int turnNumber;
   int whoseTurn
   int playerWithMostARCs;
   int playerWithMostPublications;
} game;

typedef struct _vertex {
   // Adjacent things
   edge *adjacentEdges[EDGES_PER_VERTEX]; // Wez changed this to a list
                                          // of pointers to edges, 
                                          // likewise regions and in 
                                          // other structs
   region *adjacentRegions[REGIONS_PER_VERTEX];

   // Vertex attributes
   int vertexContent;
} vertex;

typedef struct _edge {
   // Adjacent things
   vertex *adjacentVertices[VERTICES_PER_EDGE];

   // Edge attributes
   int edgeContent;
} edge;

typedef struct _region {
   // Adjacent things
   vertex *adjacentVertices[VERTICES_PER_REGION];

   // Region attributes
   int studentType;
   int diceNumber;
} region;

typedef struct _player {
   // Player ID (relates to the #defines in the .h)
   int playerID; // isn't this just the index in the list of players

   // Player possessions
   int KPIs;
   int patents;
   int publications;
   int regularCampuses;
   int GO8Campuses;
   int ARCs;

   // Different types of student
   int THDs;
   int BPSs;
   int BQNs;
   int MJs;
   int MTVs;
   int MMONEYs;
} player;

/* **** Functions which change the game aka SETTERS **** */
// make a new game, given the disciplines produced by each
// region, and the value on the dice discs in each region.
// note: each array must be NUM_REGIONS long
// eg if you are using my sample game struct above this function
// would need to set the field currentTurn to -1.  (because the turn
// number is -1 at the start of the game)
// the ordering of the regions is column by column left to right,
// going from the top of each column to the bottom before moving 
// to the next column to the right.
//
// so to create the default game as shown on the badly drawn map:
//
/*
#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, 
                STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, 
                STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, 
                STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS }
#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}
*/
//
//   int disciplines[] = DEFAULT_DISCIPLINES;
//   int dice[] = DEFAULT_DICE;
//   Game g = newGame (disciplines, dice);

// PUT HERE ALL STUFF WE NEED TO BE CAREFUL OF IN newGame
                // Players and regions declared in list in correct order
Game newGame (int discipline[], int dice[]) {
   
   // Declare game
   game createdGame;
   Game pointerToGame;

   // Initialise the players
   numPlayersInitialised = 1;
   player players[NUM_UNIS];

   while (numPlayersInitialised <= NUM_UNIS) {
      player p;

      // Initialise player possessions
      p.playerID = numPlayersInitialised;

      p.KPIs = NUM_INITIAL_CAMPUSES * KPIS_FOR_CAMPUS;
      p.patents = 0;
      p.publications = 0;
      p.regularCampuses = NUM_INITIAL_CAMPUSES;
      p.GO8Campuses = 0;
      p.ARCs = 0;

      // Initialise player's students
      p.THDs = NUM_INITIAL_THD_STUDENTS;
      p.BPSs = NUM_INITIAL_BPS_STUDENTS;
      p.BQNs = NUM_INITIAL_BQN_STUDENTS;
      p.MJs = NUM_INITIAL_MJ_STUDENTS;
      p.MTVs = NUM_INITIAL_MTV_STUDENTS;
      p.MMONEYs = NUM_INITIAL_MMONEY_STUDENTS;

      // Put player into array
      players[numPlayersInitialised - 1] = p;

      numPlayersInitialised ++;
   }

   // Put array of players into game
   createdGame.players = players;

   
}
 
// free all the memory malloced for the game
void disposeGame (Game g) {

}
 
// make the specified action for the current player and update the 
// game state accordingly.  
// The function may assume that the action requested is legal.
// START_SPINOFF is not a legal action here
void makeAction (Game g, action a) {

}
 
// advance the game to the next turn, 
// assuming that the dice has just been rolled and produced diceScore
// the game starts in turn -1 (we call this state "Terra Nullis") and 
// moves to turn 0 as soon as the first dice is thrown. 
void throwDice (Game g, int diceScore) {

}
 
/* **** Functions which GET data about the game aka GETTERS **** */
 
// what type of students are produced by the specified region?
// regionID is the index of the region in the newGame arrays (above) 
// see discipline codes above
int getDiscipline (Game g, int regionID) {

}
 
// what dice value produces students in the specified region?
// 2..12
int getDiceValue (Game g, int regionID) {

}
 
// which university currently has the prestige award for the most ARCs?
// this is NO_ONE until the first arc is purchased after the game 
// has started.  
int getMostARCs (Game g) {
   // Get the value of the atribute that stores the player with
   // the most ARCs
   int playerWithMostARCs = g->playerWithMostARCs;

   // Return this value
   return playerWithMostARCs;
}
 
// which university currently has the prestige award for the most pubs?
// this is NO_ONE until the first publication is made.
int getMostPublications (Game g) {
   // Get the value of the atribute that stores the player with
   // the most publications
   int playerWithMostPublications = g->playerWithMostPublications;

   // Return this value
   return playerWithMostPublications;
}
 
// return the current turn number of the game -1,0,1, ..
int getTurnNumber (Game g) {
   // Get the value of the atribute that stores the turn number
   int turnNumber = g->turnNumber;

   // Return this value
   return turnNumber;
}
 
// return the player id of the player whose turn it is 
// the result of this function is NO_ONE during Terra Nullis
int getWhoseTurn (Game g) {
   // Get the value of the atribute that stores whose turn it is
   int whoseTurn = g->whoseTurn;

   // Return this value
   return whoseTurn;
}
 
// return the contents of the given vertex (ie campus code or 
// VACANT_VERTEX)
int getCampus(Game g, path pathToVertex) {

}
 
// the contents of the given edge (ie ARC code or vacent ARC)
int getARC(Game g, path pathToEdge) {

}
 
// returns TRUE if it is legal for the current
// player to make the specified action, FALSE otherwise.
//
// "legal" means everything is legal: 
//   * that the action code is a valid action code which is legal to 
//     be made at this time
//   * that any path is well formed and legal ie consisting only of 
//     the legal direction characters and of a legal length, 
//     and which does not leave the island into the sea at any stage.
//   * that disciplines mentioned in any retraining actions are valid 
//     discipline numbers, and that the university has sufficient
//     students of the correct type to perform the retraining
//
// eg when placing a campus consider such things as: 
//   * is the path a well formed legal path 
//   * does it lead to a vacent vertex?
//   * under the rules of the game are they allowed to place a 
//     campus at that vertex?  (eg is it adjacent to one of their ARCs?)
//   * does the player have the 4 specific students required to pay for 
//     that campus?
// It is not legal to make any action during Terra Nullis ie 
// before the game has started.
// It is not legal for a player to make the moves OBTAIN_PUBLICATION 
// or OBTAIN_IP_PATENT (they can make the move START_SPINOFF)
// you can assume that any pths passed in are NULL terminated strings.
int isLegalAction (Game g, action a) {

}
 
// --- get data about a specified player ---
 
// return the number of KPI points the specified player currently has
int getKPIpoints (Game g, int player) {

   // Get the player struct for the specified player
   player p = g->players[player];

   // Get that player's KPI points
   int kpiPoints = p.KPIs;

   // Return this value
   return kpiPoints;
}
 
// return the number of ARC grants the specified player currently has
int getARCs (Game g, int player) {

   // Get the player struct for the specified player
   player p = g->players[player];

   // Get that player's number of ARCs
   int ARCs = p.ARCs;

   // Return this value
   return ARCs;
}
 
// return the number of GO8 campuses the specified player currently has
int getGO8s (Game g, int player) {

   // Get the player struct for the specified player
   player p = g->players[player];

   // Get that player's number of GO8's
   int GO8Campuses = p.GO8Campuses;

   // Return this value
   return GO8Campuses;
}
 
// return the number of normal Campuses the specified player 
// currently has
int getCampuses (Game g, int player) {

   // Get the player struct for the specified player
   player p = g->players[player];

   // Get that player's number of campuses
   int campuses = p.regularCampuses;

   // Return this value
   return campuses;
}
 
// return the number of IP Patents the specified player currently has
int getIPs (Game g, int player) {

   // Get the player struct for the specified player
   player p = g->players[player];

   // Get that player's number of IPs
   int IPs = p.patents;

   // Return this value
   return IPs;
}
 
// return the number of Publications the specified player currently has
int getPublications (Game g, int player) {

   // Get the player struct for the specified player
   player p = g->players[player];

   // Get that player's number of publications
   int publications = p.publications;

   // Return this value
   return publications;
}
 
// return the number of students of the specified discipline type 
// the specified player currently has
int getStudents (Game g, int player, int discipline) {

   // Get the player struct for the specified player
   player p = g->players[player];

   // Figure out what discipline is being asked for and get the result
   int numberStudents;

   if (discipline == STUDENT_THD) {
      numberStudents = p.THDs;
   }

   if (discipline == STUDENT_BPS) {
      numberStudents = p.BPSs;
   }

   if (discipline == STUDENT_BQN) {
      numberStudents = p.BQNs;
   }

   if (discipline == STUDENT_MJ) {
      numberStudents = p.MJs;
   }

   if (discipline == STUDENT_MTV) {
      numberStudents = p.MTVs;
   }

   if (discipline == STUDENT_MMONEY) {
      numberStudents = p.MMONEYs;
   }

   // Return this value
   return numberStudents;
}
 
// return how many students of discipline type disciplineFrom
// the specified player would need to retrain in order to get one 
// student of discipline type disciplineTo.  This will depend 
// on what retraining centers, if any, they have a campus at.
int getExchangeRate (Game g, int player, 
                     int disciplineFrom, int disciplineTo) {

   // Check that you aren't trying to retrain THDs
   assert (disciplineFrom != STUDENT_THD);

   int exchangeRate;
   int campusAtRetrainingCentre;
   int campusAtRetrainingCentreTwo;

   // Check whether the player has a retraining centre for the
   // pertinent discipline
   if (disciplineFrom == STUDENT_BPS) {
      campusAtRetrainingCentre = 
            getCampus (g, PATH_TO_RETRAINING_CENTRE_BPS);

      if (campusAtRetrainingCentre == player
            || campusAtRetrainingCentre == player + GO8_OFFSET) {
         exchangeRate = EXCHAGE_RATE_WITH_CENTRE;
      } else {
         exchangeRate = DEFAULT_EXCHANGE_RATE;
      }

   } else if (disciplineFrom == STUDENT_BQN) {
      campusAtRetrainingCentre = 
            getCampus (g, PATH_TO_RETRAINING_CENTRE_BQN);

      if (campusAtRetrainingCentre == player
            || campusAtRetrainingCentre == player + GO8_OFFSET) {
         exchangeRate = EXCHAGE_RATE_WITH_CENTRE;
      } else {
         exchangeRate = DEFAULT_EXCHANGE_RATE;
      }
      
   } else if (disciplineFrom == STUDENT_MJ) {
      campusAtRetrainingCentre = 
            getCampus (g, PATH_TO_RETRAINING_CENTRE_MJ_ONE);
      campusAtRetrainingCentreTwo = 
            getCampus (g, PATH_TO_RETRAINING_CENTRE_MJ_TWO);

      if (campusAtRetrainingCentre == player
            || campusAtRetrainingCentre == player + GO8_OFFSET
            || campusAtRetrainingCentreTwo == player
            || campusAtRetrainingCentreTwo == player + GO8_OFFSET) {
         exchangeRate = EXCHAGE_RATE_WITH_CENTRE;
      } else {
         exchangeRate = DEFAULT_EXCHANGE_RATE;
      }
      
      
   } else if (disciplineFrom == STUDENT_MTV) {
      campusAtRetrainingCentre = 
            getCampus (g, PATH_TO_RETRAINING_CENTRE_MTV);

      if (campusAtRetrainingCentre == player
            || campusAtRetrainingCentre == player + GO8_OFFSET) {
         exchangeRate = EXCHAGE_RATE_WITH_CENTRE;
      } else {
         exchangeRate = DEFAULT_EXCHANGE_RATE;
      }
      
   } else if (disciplineFrom == STUDENT_MMONEY) {
      campusAtRetrainingCentre = 
            getCampus (g, PATH_TO_RETRAINING_CENTRE_MMONEY_ONE);
      campusAtRetrainingCentreTwo = 
            getCampus (g, PATH_TO_RETRAINING_CENTRE_MMONEY_TWO);

      if (campusAtRetrainingCentre == player
            || campusAtRetrainingCentre == player + GO8_OFFSET
            || campusAtRetrainingCentreTwo == player
            || campusAtRetrainingCentreTwo == player + GO8_OFFSET) {
         exchangeRate = EXCHAGE_RATE_WITH_CENTRE;
      } else {
         exchangeRate = DEFAULT_EXCHANGE_RATE;
      }
      
   } 

   // Return the calculated exchange rate
   return exchangeRate;
}















