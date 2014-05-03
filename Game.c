//
//  Game.c
//  The game abstract data type for Universities of Catan
//  Hector Morlet, Matthew Overington and Thomas Waring
//  3 May 2014
//


#define NUM_VERTICES
#define NUM_EDGES
#define NUM_REGIONS

#define EDGES_PER_VERTEX 3
#define REGIONS_PER_VERTEX 3
#define VERTICES_PER_EDGE 
#define VERTICES_PER_REGION

#define NUM_PLAYERS 3


typedef struct _game {
   // Map things
   vertex vertices[NUM_VERTICES];
   edge edges[NUM_EDGES];
   region regions[NUM_REGIONS];

   // Players
   player players[NUM_PLAYERS];
} game;

typedef struct _vertex {
   // Adjacent things
   edge adjacentEdges[EDGES_PER_VERTEX];
   region adjacentRegions[REGIONS_PER_VERTEX];

   // Vertex attributes
   int owner;
   int vertexContent;
} vertex;

typedef struct _edge {
   // Adjacent things
   vertex adjacentVertices[VERTICES_PER_EDGE];

   // Edge attributes
   int edgeContent;
} edge;

typedef struct _region {
   // Adjacent things
   vertex adjacentVertices[VERTICES_PER_REGION];

   // Region attributes
   int studentType;
   int diceNumber;
} region;

typedef struct _player {
   // Player ID (relates to the #defines in the .h)
   int playerID;

   // Player possessions
   int KPIs;
   int patents;
   int papers;
   int regularCampuses; // Is there any point in having these if each
   int GO8campuses;     // individual vertex and edge will be storing
   int ARCs;            // it's owner and if it is a GO8?
   // It could make a few functions faster and
   // easier.

   // Different types of student
   int THDs;
   int BPSs;
   int BQNs;
   int MJs;
   int MTVs;
   int MMONEYs;
} player;