#ifndef MAP_H
#define MAP_H

#include "hash_table.h"

/**
 * A structure to represent the map. The implementation is private.
 */
struct Map;

// A function pointer type for drawing MapItems.
// All tiles are 11x11 blocks.
// u,v is the top left corner pixel of the block
typedef void (*DrawFunc)(int u, int v);

/**
 * The data for elements in the map. Each item in the map HashTable is a
 * MapItem.
 */
typedef struct {
    /**
     * Indicates the "type" of the MapItem: WALL, DOOR, PLANT, etc. This is
     * useful for determining how to interact with the object when updating the
     * game state.
     */
    int type;
    
    /**
     * A function pointer to the drawing function for this item. Used by draw_game.
     */
    DrawFunc draw;
    
    /**
     * If zero, this item should block character motion.
     */
    int walkable;
    
    /**
     * Arbitrary extra data for the MapItem. Could be useful for keeping up with
     * special information, like where a set of stairs should take the player.
     * 
     * Iterpretation of this can depend on the type of the MapItem. For example,
     * a WALL probably doesn't need to use this (it can be NULL), where an NPC
     * might use it to store game state (have I given the player the key yet?).
     */
    void* data;
} MapItem;

typedef struct {
    int tm;
    int tx, ty;
} StairsData;

//get_north()






// MapItem types
// Define more of these!
#define WALL    0
#define PLANT   1
#define GATE    2
#define PASSAGEWAY 3

#define TREASURE 7
#define GOD_BUTCHER 8
#define TRAILING_CLOUD 9
#define COLORBLOCKS 10

// Characters
#define NPC 5
#define MUSE 6
#define HERMES 11
#define LOSTSOUL 16

// Potions
#define DTPOTION 12
#define DBPOTION 13
#define DPPOTION 14
#define DOPOTION 15


// Portals 
#define HOME_PORTAL 4
#define MARTA_PORTAL 17
#define POSIEDON_PORTAL 18
#define LIMBO_OLYMPUS_PORTAL 19
#define ATL_OLYMPUS_PORTAL 20
#define MARTA_ATL 21

// Pencil Builing Triangular Grid
#define GRID 22




/**
 * Initializes the internal structures for all maps. This does not populate
 * the map with items, but allocates space for them, initializes the hash tables, 
 * and sets the width and height.
 */
void maps_init();

/**
*returns an integer value of stored stoered within the active_map variable(which is declared in map.cpp)
*
*/
int get_map_index();

/**
 * Returns a pointer to the active map.
 */
Map* get_active_map();

/**
 * Sets the active map to map m, where m is the index of the map to activate.
 * Returns a pointer to the new active map.
 */
Map* set_active_map(int m);

/**
 * Returns the map m, regardless of whether it is the active map. This function
 * does not change the active map.
 */
Map* get_map(int m);

/**
 * Print the active map to the serial console.
 */
void print_map();

// Access
/**
 * Returns the width of the active map.
 */
int map_width();

/**
 * Returns the heigh of the active map.
 */
int map_height();

/**
 * Returns the total number of cells in the active map.
 */
int map_area();

/**
 * Returns the MapItem immediately above the given location.
 */
MapItem* get_north(int x, int y);

/**
 * Returns the MapItem immediately below the given location.
 */
MapItem* get_south(int x, int y);

/**
 * Returns the MapItem immediately to the right of the given location.
 */
MapItem* get_east(int x, int y);

/**
 * Returns the MapItem immediately to the left of  the given location.
 */
MapItem* get_west(int x, int y);

/**
 * Returns the MapItem at the given location.
 */
MapItem* get_here(int x, int y);

// Directions, for using the modification functions
#define HORIZONTAL  0
#define VERTICAL    1

/**
 * If there is a MapItem at (x,y), remove it from the map.
 */
void map_erase(int x, int y);
void map_erase(int x, int y, int map_index);


Map* get_map(int map_index);
void full_map_erase(int map_index, int new_map);



/**
 * Add WALL items in a line of length len beginning at (x,y).
 * If dir == HORIZONTAL, the line is in the direction of increasing x.
 * If dir == VERTICAL, the line is in the direction of increasing y.
 *
 * If there are already items in the map that collide with this line, they are
 * erased.
 */
void add_wall(int x, int y, int dir, int len);

/**
 * Add a PLANT item at (x,y). If there is already a MapItem at (x,y), erase it
 * before adding the plant.
 */
void add_plant(int x, int y);

//----------------------------------------------------
void add_tree(int x, int y);
void add_limboTree(int x, int y, int dir, int len);
void add_goldenTree(int x, int y, int dir, int len);

void add_grass(int x, int y);
void add_trailingCloud(int x, int y);

//-----------------------------------------------------
/** This Description applies to Two seperate fuctions that are apart of one another
 * Gate Format: 12x8 grid of cells 
 * Add GATE items in a line of length len beginning at (x,y).
 * ----------------------------------------------------------
 * These lines are simply just WALLs
 * 2 Vertical Lines ~ length :  7 cells
 * 2 Horiontal lines ~ length : 4 cels
 * Add Passage Way item in the a line length len beginning at (x,y).
 * -----------------------------------------------------------------
 * This line is a deletable Wall with a Different Color (~indicative of a Gate)
 * 1 Horizontal Line ~ length: 4 cells
 *      - this portion will be deletable once the Player recieves a key            
 * +-----------------------------+
 * |         |    =    |         |
 * |         |         |         |
 * |         +---   ---+         |
 * |                             |
 * |                             |
 * |                             |
 * +-----------------------------+
 * If there are already items in the map that collide with this line, they are
 * erased.
 */
void add_mainGate();
void add_passageWay(int x, int y, int dir, int len);
void delete_passageWay (int x, int y);
void delete_muse(int x, int y);
//---------------------------------------------------------------------------------------





//********************************* EDIT *************************
//--------------------------------
//              Portals
//--------------------------------
/**Brief 
* This Method will place within the map a 2x2 region for where the main player,
* can jump into a different world, eventually will be multiple worlds
* 
* @param x ~ represenests the x-coordinate of the top-left corner of the 21x1 area
* @param y ~ represenests the y-coordinate of the top-left corner of the 2x2 area 
* 
*/
void add_homePortal(int x, int y);
void add_martaPortal(int x, int y);
void add_posiedonPortal(int x, int y);
void add_LIMBO_OLYMPUS_PORTAL(int x, int y);
void add_ATL_OLYMPUS_PORTAL(int x, int y);
void add_MARTA_ATL(int x, int y);

//-------------------------------------------------------------
void add_npc(int x, int y);
void add_muse(int x, int y);
void add_godKiller(int x, int y);
void add_treasure(int x, int y);
void add_godButcher (int x, int y);
//-------------------------------------------------------------

//  LIMBO
//----------
void add_lostSoul(int x, int y);



//-------------------------------------------------------------

// Posiedon's Room
//----------------------

void add_water(int x, int y, int dir, int len);
void add_desk(int x, int y);
void add_bedsheets(int x, int y);
void add_pillow(int x, int y);
void add_bed(int x, int y);
void add_nightStand(int x, int y);

void add_DTealPotion(int x, int y);
void add_DBluePotion(int x, int y);
void add_DPurplePotion(int x, int y);
void add_DOrangePotion(int x, int y);
//-------------------------------------------------------------
// MARTA
//----------------------

void add_trainTopSection(int x, int y);

void add_trainMidSection(int x, int y);

void add_trainBottomSection(int x, int y);

void add_TrainCar(int x, int y);


void add_Hermes(int x, int y);

//-------------------------------------------------------------
// Pencil Building/ATL
//----------------------

void add_pavement(int x, int y, int dir, int len);
void add_cloudPiece(int x, int y, int dir, int len);
void add_cloud(int x, int y);

void add_brownBlock(int x, int y, int dir, int len);
void add_darkblueBlock(int x, int y);
void add_yellowBlock(int x, int y);


void add_pencilTIp(int x, int y);
void add_triangularGrid(int x, int y);
void add_buildingBlock(int x, int y);
void add_PencilBuilding(int x, int y);

/*Trinagular Grid (located towards the top of the pencil builidng 
~ between the tip and the main builidng structure.
*/
void add_leftGrid(int x, int y);
void add_centerGrid(int x, int y);
void add_rightGrid(int x, int y);
void add_gridTip(int x, int y);




#endif //MAP_H