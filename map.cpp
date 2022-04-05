#include "map.h"

#include "globals.h"
#include "graphics.h"


/* Global Variables 
* NUMBUCKETS: Used within the Hash function
* 
*/


unsigned int NUMBUCKETS = 100;



/**
 * The Map structure. This holds a HashTable for all the MapItems, along with
 * values for the width and height of the Map.
 * In this file you need to define how the map will be structured. IE how will
 * you put values into the map, pull them from the map. Remember a "Map" variable
 * is a hashtable plus two ints (see below) 
 * You will have more than one map variable, one will be the main map with it's own hashtable.
 * Then you'll have a second map with another hashtable
 * You should store objects into the hashtable with different properties (spells
 * etc)
 */
struct Map {
    HashTable* items;
    int w, h;
};

/**
 * Storage area for the maps.
 * This is a global variable, but can only be access from this file because it
 * is static.
 */
 
 
 /*
 active_map is used as an Index of what map is currently be used during gameplay
 // give a more descriptive name for this map, after developing the map.
 */
//static Map map; //DELETE
static Map maps[6];  
static int active_map; 
static int key;


/**
 * The first step in HashTable access for the map is turning the two-dimensional
 * key information (x, y) into a one-dimensional unsigned integer.
 * This function should uniquely map (x,y) onto the space of unsigned integers.
 * Does this by:
 * n = Map's width
 *  0 1 2 3 4 5 6     . . .    (n - 1) |
 *  n  n+1 n+2  n+3   . . .   (2n - 1) |
 *  2n  2n+1 2n+2  2n+3  ...  (3n - 1) |
 *  3n               .......           |
 *  |                                  |
 *  |                                  | 
 */
static unsigned XY_KEY(int X, int Y) {
    /* By turnig the 2-D key information into a 1-D unsigned int,
    all horiznotal value x values are referenced to the left most edge, while 
    Y- values represent a traversal over (Y) number of horizontal Lines
    up until the desired line, were the count count of indicies within the display
    continues to incremenet after you move to the next line.
    */
    //pc.printf("Printing the XY_Key: %f\n", Y*(map.w) + X);
    return ( Y*( map_width() ) + X); 
}

/**
 * This is the hash function actually passed into createHashTable. It takes an
 * unsigned key (the output of XY_KEY) and turns it into a hash value (some
 * small non-negative integer).
 */
unsigned map_hash(unsigned key)
{
    /* Same function as what was used in the ht_tests.cpp 
    A simple hash function that maps a positive number to an integer between 0~(BUCKET_NUM-1).*/
    //pc.printf("Input key: %d    |    The Hash of the input Key: %d\n", key, key%NUMBUCKETS);
    return key % map_width();
}

void maps_init()
{
    pc.printf("====================================\nCalling maps_init()\n====================================\n");
    // TODO: Implement!    
    /*
    (1) Initializes the internal structures for all maps
    (2) allocate space for map withn items 
    (3) Initialize hash table, 
    */
    // Set width & height
    //------------------------------------------------------------
    //          Initializing  MAIN MAP
    //------------------------------------------------------------
    Map* map = get_active_map();
    HashTable* map_item = createHashTable(map_hash, NUMBUCKETS);
    map->items = map_item;
    // Default Sizing for the first map which is 50x50
    map->w = 50; 
    map->h = 50;
    //------------------------------------------------------------
    //          Initializing  LIMBO MAP
    //------------------------------------------------------------
    //pc.printf("Items:  %d  |  Map Width: %d  | Map Height: %d", map->items, map->w, map->h);
    map = set_active_map(1);
    map_item = createHashTable(map_hash, NUMBUCKETS);
    map->items = map_item;
    // Default Sizing for the first map which is 50x50
    map->w = 11; 
    map->h = 11;
    //------------------------------------------------------------
    //          Initializing  MARTA MAP
    //------------------------------------------------------------
    map = set_active_map(2);
    map_item = createHashTable(map_hash, NUMBUCKETS);
    map->items = map_item;
    // Default Sizing for the first map which is 50x50
    map->w = 21; 
    map->h = 5;
    //pc.printf("Items:  %d  |  Map Width: %d  | Map Height: %d", map->items, map->w, map->h);
    //------------------------------------------------------------
    //          Initializing  Poseidon MAP
    //------------------------------------------------------------
    map = set_active_map(3);
    map_item = createHashTable(map_hash, NUMBUCKETS);
    map->items = map_item;
    // Default Sizing for the first map which is 50x50
    map->w = 20; 
    map->h = 20;
    //pc.printf("Items:  %d  |  Map Width: %d  | Map Height: %d", map->items, map->w, map->h);
    //------------------------------------------------------------
    //          Initializing  OLYMPUS MAP
    //------------------------------------------------------------
    map = set_active_map(4);
    map_item = createHashTable(map_hash, NUMBUCKETS);
    map->items = map_item;
    // Default Sizing for the first map which is 50x50
    map->w = 14; 
    map->h = 14;
    //pc.printf("Items:  %d  |  Map Width: %d  | Map Height: %d", map->items, map->w, map->h);
    //------------------------------------------------------------
    //          Initializing  ATL (Pencil Building) MAP
    //------------------------------------------------------------
    map = set_active_map(5);
    map_item = createHashTable(map_hash, NUMBUCKETS);
    map->items = map_item;
    // Default Sizing for the first map which is 50x50
    map->w = 20; 
    map->h = 50;
    //pc.printf("Items:  %d  |  Map Width: %d  | Map Height: %d", map->items, map->w, map->h);
    pc.printf("====================================\n Completed MAP set ups in maps_init()\n====================================\n");
    /*
    map = set_active_map(6);
    map_item = createHashTable(map_hash, NUMBUCKETS);
    map->items = map_item;
    // Default Sizing for the first map which is 50x50
    map->w = 20; 
    map->h = 20;
    */
}

Map* get_map(int map_index)
{
    return &maps[map_index];
}

int get_map_index()
{
    return active_map;
}

Map* get_active_map()
{
    //******************************Change the following line***************************
    // There's only one map
    //pc.printf("Status: Current map being used is Map[%d]", active_map);
    //return &maps[active_map];
    //return &map;
    return &maps[active_map];
}

Map* set_active_map(int m)
{
    active_map = m;
    //pc.printf("***** ACTIVE_MAP CHANGED ******\n active_map = %d", active_map);
    //return &maps[active_map];
    //return &map;
    pc.printf("Active map is being set: %d\n", active_map);
    return &maps[active_map];
}


/*
'D', '0'
#define WALL    0 -> W
#define PLANT   1 -> P
#define GATE    2 -> G
#define PASSAGEWAY 3 -> 'D'
'T', 'B','C' , 'X'
#define TREASURE 7 -> 'T'
#define GOD_BUTCHER 8 -> 'B'
#define TRAILING_CLOUD 9 ->  'C'
#define COLORBLOCKS 10 -> 'X'
'N', 'M',   'H'  
// Characters
#define NPC 5 -> 'N'
#define MUSE 6 -> 'M'
#define HERMES 11 -> 'H'
#define LOSTSOUL 16 -> 'L'
'1', '2', '3', '4'
// Potions
#define DTPOTION 12 -> '1'
#define DBPOTION 13 -> '2'
#define DPPOTION 14 -> '3'
#define DOPOTION 15 -> '4'
'0'
'2', '3', '4' , '5'
// Portals 
#define HOME_PORTAL 4 -> '0'
#define MARTA_PORTAL 17 -> '2'
#define POSIEDON_PORTAL 18 -> '3'
#define LIMBO_OLYMPUS_PORTAL 19 -> '4'
#define ATL_OLYMPUS_PORTAL 20 -> '5'
#define MARTA_ATL 21 -> '6'

'D', '0', 'N', 'M', 'T', 'B','C' , 'X', 'H' ,'1', '2', '3', '4', 'L', '2', '3', '4' , '5'
*/

void print_map()
{
    // As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P', 'G', 'D', '0', 'N', 'M', 'T', 'B','C' , 'X', 'H' ,'1', '2', '3', '4', 'L', '2', '3', '4' , '5', '6', 'G'};
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    }
}

int map_width()
{
    Map *map = get_active_map();
    return map->w;
}

int map_height()
{
    Map *map = get_active_map();
    return map->h;
}

int map_area()
{   
    Map *map = get_active_map();
    return ( (map->w)*(map->h) );
}

/**=============================================================================
* ------------------    get_(Location of Items) Methods     -------------------
* =============================================================================
*/
/** General Format of these methods: 
*    (1)
*    (2)
*    (3)
*    return
*/

MapItem* get_north(int x, int y)
{       
    // Holds the current map in the gloabal map variable
    Map *map = get_active_map();
    /* Updates the value of key to a unique number that corresponds to the 
    point above the current provided (x, y) location*/
    key = XY_KEY(x, y-1);
    return (MapItem*) getItem(map->items,key);
    
}

MapItem* get_south(int x, int y)
{
    // Holds the current map in the gloabal map variable
    Map *map = get_active_map();
    /* Updates the value of key to a unique number that corresponds to the 
    point below the current provided (x, y) location*/
    key = XY_KEY(x, y+1);
    return (MapItem*) getItem(map->items,key);
}

MapItem* get_east(int x, int y)
{
   // Holds the current map in the gloabal map variable
    Map *map = get_active_map();
    /* Updates the value of key to a unique number that corresponds to the 
    rightward point of the current provided (x, y) location*/
    key = XY_KEY(x+1, y);
    return (MapItem*) getItem(map->items,key);
}

MapItem* get_west(int x, int y)
{
    // Holds the current map in the gloabal map variable
    Map *map = get_active_map();
    /* Updates the value of key to a unique number that corresponds to the 
    leftward point of the current provided (x, y) location*/
    key = XY_KEY(x-1, y);
    return (MapItem*) getItem(map->items,key);  
}
/* -------------------Use these below descriptions to provide information about
 the general operationn of the get_Somthing Methods which can be addreessed in the above Format Section*/

MapItem* get_here(int x, int y)
{
    // Holds the current map in the gloabal map variable
    Map *map = get_active_map();
    /* Updates the value of key to a unique number that corresponds to the 
    current provided (x, y) location*/
    key = XY_KEY(x, y);
    /*type-casts the returned "value" from getItem as a MapItem pointer. 
    Essentially just setting the "Value" pointer within a pointer within 
    a HashTableEntry to point to a Map Item struct, somewhere in memory*/
    return ((MapItem*) getItem(map->items,key));
}


// =============================================================================

void map_erase(int x, int y)
{
    //pc.printf("small map erase function\n");
    //pc.printf("Inside map erase\n----------------------\n");
    Map *map = get_active_map();// &map[map_index]
    //pc.printf("line 1    |");
    key = XY_KEY(x, y);
    //pc.printf("         line 2\n");
    //pc.printf("bucket index: %d | XY_KEY: %d\n", map_hash(key), XY_KEY(x, y));
    //pc.printf("|  | \n", map_hash(key);
    //pc.printf("findItem: %d\n", findItem(map, key));
    //pc.printf("Active map: %d   |     get_map(__): %d  \n", get_active_map(), get_map(1) );
    //pc.printf("getItem: %d\n", getItem(map->items,key));
    //pc.printf("getItem->type: %d\n", getItem(map->items,key)->type);
    MapItem* map_item_exists = (MapItem*) getItem(map->items,key);
    //pc.printf("About to check if map item exists\n");
    if ( map_item_exists ) {
    /*IF MapItem pointer within the Hashtable Entry is NULL, then terminate the of the method
      IF NOT NULL (nonzero), the program runs the THEN BLOCK. */
        deleteItem(map->items,key);
        pc.printf("Item Deleted\n------------------------\n"); //provide more diagnostic check on deteleting item
        //but printing out the information that was released
    }
    //pc.printf("exit map erase\n");
}

void map_erase(int x, int y, int map_index)
{
    
    pc.printf("Inside map erase\n----------------------\n");
    Map *map = get_active_map();// &map[map_index]
    pc.printf("Active map: %d   |     gat_map(__): %d  \n", get_active_map(), get_map(1));
    pc.printf("line 1    |");
    key = XY_KEY(x, y);
    pc.printf("         line 2\n");
    pc.printf("bucket index: %d | XY_KEY: %d\n", map_hash(key), XY_KEY(x, y));
    //pc.printf("|  | \n", map_hash(key);
    //pc.printf("findItem: %d\n", findItem(map, key));
    
    pc.printf("getItem: %d\n", getItem(map->items,key) );
    MapItem* map_item_exists = (MapItem*) getItem(map->items,key);
    pc.printf("About to check if map item exists\n");
    if ( map_item_exists ) {
    /*IF MapItem pointer within the Hashtable Entry is NULL, then terminate the of the method
      IF NOT NULL (nonzero), the program runs the THEN BLOCK. */
        deleteItem(map->items,key);
        pc.printf("Item Deleted\n------------------------\n"); //provide more diagnostic check on deteleting item
        //but printing out the information that was released
    }
    pc.printf("exit map erase\n");
}

void full_map_erase(int map_index, int new_map)
{
    //Map *map = get_map(map_index);
    //destroyHashTable(map);
    pc.printf("Inside FULL MAP ERASE\n");
    Map *map = set_active_map(map_index);
    print_map();
    pc.printf("-----------------FULL MAP Erase Loop BEGIN-----------------\n");
    for(int y = 0; y < map_height(); y++)
    {
        for (int x = 0; x < map_width(); x++)
        {
            MapItem* item = get_here(x,y);
            if (item) 
            {
                //pc.printf("[X, Y] - [%d, %d]      |      Item->type:  %d  \n", x, y, item->type); //Portal->type: %d 
                //pc.printf("XY_KEY: %d    |  Bucket_Index (MAP Hash): %d\n",XY_KEY(x, y), map_hash(XY_KEY(x, y)));
                map_erase(x, y);
                //pc.printf("%c", lookup[item->type]);
            }
            //else pc.printf(" ");
        }
        //pc.printf("\r\n");
    }
    pc.printf("-----------------FULL MAP Erase Loop END-----------------\n");
    pc.printf("==================================\nPrinting Erased Map\n======================================\n");
    print_map();
    pc.printf("=======================================================================\n");
    map = set_active_map(new_map);
    
    /*
    // As you add more types, you'll need to add more items to this arra
// As you add more types, you'll need to add more items to this array.
    char lookup[] = {'W', 'P', 'G', 'D', '0', 'N', 'M', 'T', 'B','C' , 'X', 'H' ,'1', '2', '3', '4', 'L', '2', '3', '4' , '5', '6'};
    
    for(int y = 0; y < (map->h); y++)
    {
        for (int x = 0; x < (map->w); x++)
        {
            //map_erase(x, y);
            MapItem* item = ((MapItem*) getItem(map->items,XY_KEY(x, y)));
            if (item) pc.printf("%c", lookup[item->type]);
            else pc.printf(" ");
        }
        pc.printf("\r\n");
    } 
    
    
    //----------------------------------------------------------------------------------------------------------------------------------
    */
    /*
    char lookup[] = {'W', 'P', 'G', 'D', '0', 'N', 'M', 'T', 'B','C' , 'X', 'H' ,'1', '2', '3', '4', 'L', '2', '3', '4' , '5', '6'};
    //Map *map = set_active_map(1);
    Map *delete_map = get_map(map_index);
    //print_map();
    if( get_map(map_index) )
    {
        pc.printf("Correct, %d\n", get_map(map_index));
    }
    else
    {
        pc.printf("wrong\n");
    }
    pc.printf("-----------------FULL MAP Erase-----------------\n");
    for(int y = 1; y < delete_map->h; y++)
    {
        for (int x = 1; x < delete_map->w; x++)
        {
            
            //map_erase(x, y);
            MapItem* item = ((MapItem*) getItem(delete_map->items,XY_KEY(x, y)));
            if (item) 
            {
                //map_erase(x,y, 1); //pc.printf("%c", lookup[item->type]);
                
                //if (item)
                pc.printf("Map Item @ (X,Y) ~ (%d, %d)\n", x, y);
                pc.printf("XY_KEY FUNCTION \n_______________________\n (Y*( map_width() ) + X):");
                pc.printf("[ %d * ( %d )  + %d ] =  %d\n", y, (delete_map->w), x, ((y*(delete_map->w))+x) ) ;
                pc.printf("Bucket Index FUNCTION (map_hash)\n_______________________\n Bucket index: %d | XY_KEY: %d\n", ((y*(delete_map->w))+x)%(delete_map->w), ((y*(delete_map->w))+x) );
                pc.printf("MapItem->type: %d\n", item->type);
                pc.printf("%c", lookup[item->type]);
                //else pc.printf(" ");
            }
            //else pc.printf(" ");
        }
        pc.printf("\r\n");
    } 
    pc.printf("--------------------------------------------\nMAP ERASED\n--------------------------------------------\n");
    //print_map();
    //----------------
    set_active_map(0);
    print_map();
    */
    
}


void add_wall(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_wall;
        //w1->walkable = false;
        w1->walkable = NULL;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
        //pc.printf("WALL: walkable? ~ %d\nKey: %d\n", w1->walkable, key);
        //pc.printf("I: %d  |  Length: %d  |", i, len);
    }
}



// Very similar Implementation as add_wall, with the excepetion of the type and DrawFunc
void add_passageWay(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
        {
            MapItem* p1 = (MapItem*) malloc(sizeof(MapItem));
            p1->type = PASSAGEWAY;
            p1->draw = draw_yellowBlock;
            //w1->walkable = false;
            p1->walkable = NULL;
            p1->data = NULL; 
            unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
            void* val = insertItem(get_active_map()->items, key, p1);
            if (val) free(val); // If something is already there, free it
            pc.printf("WALL: walkable? ~ %d\nKey: %d\n", p1->walkable, key);
        }
}


//Needs to be debugged
//----------This assumes thats you are deleting the passageway from the center of the gate-----------
//Change ^ gate so that it has a singular point where one can unlock the gate -> delete the passageway

void delete_passageWay ( int x, int y) { // insert Player.x, and Player.y for x and y when implementing thtis fucntion
    //Check to see if the above block is of type Passageway
    //if (get_north(x, y-1)->type == PASSAGEWAY) 
    //{
        //Free the Pointers
        //free(get_north(x, y -1)->draw);
        /*
        free(get_north(x, y - 1)->data);
        Free the Item itself
        free(get_north(x, y - 1));
        */
        map_erase(x, y);
        map_erase(x+1, y);
        map_erase(x+2, y);
        map_erase(x+3, y);
    //}
    
}

void add_mainGate() 
{
    // Vertical lines for the Walls of the gate
    add_wall(19, 1, VERTICAL, 7);
    add_wall(31, 1, VERTICAL, 7);
    // Horizontal lines for the Walls of the gate
    add_wall(19, 7, HORIZONTAL, 4);
    add_wall(27, 7, HORIZONTAL, 4);
    /*This MapItem is initally set to NOT be walkable, but has the ability of 
    being set as walkable by  the Player, when the player has a key*/
    //*******************UNCOMMENT THE LINE BELOW, AFTER TESTING THE DRAWING THE WALL OF THE GATE.
    add_passageWay(23, 7, HORIZONTAL, 4) ;
}



void add_plant(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_plant;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

void add_grass(int x, int y)
{
    MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
    w1->type = PLANT;
    w1->draw = draw_grass;
    w1->walkable = true;
    w1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), w1);
    if (val) free(val); // If something is already there, free it
}

// Tree will have the same Type as a plant
void add_tree(int x, int y)
{
    MapItem* tree1 = (MapItem*) malloc(sizeof(MapItem));
    tree1->type = PLANT;
    tree1->draw = draw_tree;
    tree1->walkable = true;
    tree1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), tree1);
    if (val) free(val); // If something is already there, free it
}
void add_limboTree(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* tree1 = (MapItem*) malloc(sizeof(MapItem));
        tree1->type = PLANT;
        tree1->draw = draw_limboTree;
        tree1->walkable = true;
        tree1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, tree1);
        if (val) free(val); // If something is already there, free it
        //pc.printf("WALL: walkable? ~ %d\nKey: %d\n", w1->walkable, key);
        //pc.printf("I: %d  |  Length: %d  |", i, len);
    }
}
void add_goldenTree(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* tree1 = (MapItem*) malloc(sizeof(MapItem));
        tree1->type = PLANT;
        tree1->draw = draw_goldenTree;
        tree1->walkable = true;
        tree1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, tree1);
        if (val) free(val); // If something is already there, free it
        //pc.printf("WALL: walkable? ~ %d\nKey: %d\n", w1->walkable, key);
        //pc.printf("I: %d  |  Length: %d  |", i, len);
    }
}

void add_trailingCloud(int x, int y) 
{
    MapItem* trailingCloud1 = (MapItem*) malloc(sizeof(MapItem));
    trailingCloud1->type = TRAILING_CLOUD;
    trailingCloud1->draw = draw_trailingClouds;
    trailingCloud1->walkable = true;
    trailingCloud1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), trailingCloud1);
    if (val) free(val); // If something is already there, free it
}

void delete_trailingCloud(int x, int y)
{
    map_erase(x, y);
    pc.printf("DELETE MUSE");
}
//=============================================================================
//                              LIMBO
//=============================================================================
void add_lostSoul(int x, int y)
{
    MapItem* lostSoul = (MapItem*) malloc(sizeof(MapItem));
    lostSoul->type = LOSTSOUL;
    lostSoul->draw = draw_lostSoul;
    lostSoul->walkable = NULL;
    lostSoul->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), lostSoul);if (val) free(val);
    pc.printf("Lost Soul Added\n");
     // If something is already there, free it
}


//=============================================================================
//-------------------- ADD Portal Function ------------------------------------
//=============================================================================

/*
Draw Functions: 
----------------
void draw_homePortal(int u, int v);
void draw_martaPortal(int u, int v);
void draw_posiedonPortal(int u, int v);
void draw_LIMBO_OLYMPUS_PORTAL(int u, int v);
void draw_ATL_OLYMPUS_PORTAL(int u, int v);


void add_homePortal(int x, int y);
void add_martaPortal(int x, int y);
void add_posiedonPortal(int x, int y);
void add_LIMBO_OLYMPUS_PORTAL(int x, int y);
void add_ATL_OLYMPUS_PORTAL(int x, int y);

*/


void add_homePortal(int x, int y)
{
    MapItem* p1 = (MapItem*) malloc(sizeof(MapItem));
    p1->type = HOME_PORTAL;
    p1->draw = draw_homePortal;
    p1->walkable = true;
    p1->data = NULL;
    //portal->tx = x;
    //portal->ty = y;
    //portal->tm = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), p1);
    if (val) free(val); // If something is already there, free it
    pc.printf("Portal added ~ [X, Y] - [%d, %d]\nPortal->type: %d \n", x, y, p1->type);
    pc.printf("XY_KEY: %d    |  Bucket_Index (MAP Hash): %d\n",XY_KEY(x, y), map_hash(XY_KEY(x, y)));
}

void add_martaPortal(int x, int y)
{
    MapItem* p1 = (MapItem*) malloc(sizeof(MapItem));
    p1->type = MARTA_PORTAL;
    p1->draw = draw_martaPortal;
    p1->walkable = true;
    p1->data = NULL;
    //portal->tx = x;
    //portal->ty = y;
    //portal->tm = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), p1);
    if (val) free(val); // If something is already there, free it
    pc.printf("Portal added ~ [X, Y] - [%d, %d]\nPortal->type: %d \n", x, y, p1->type);
    pc.printf("XY_KEY: %d    |  Bucket_Index (MAP Hash): %d\n",XY_KEY(x, y), map_hash(XY_KEY(x, y)));
}
void add_posiedonPortal(int x, int y)
{
    MapItem* p1 = (MapItem*) malloc(sizeof(MapItem));
    p1->type = POSIEDON_PORTAL;
    p1->draw = draw_posiedonPortal;
    p1->walkable = true;
    p1->data = NULL;
    //portal->tx = x;
    //portal->ty = y;
    //portal->tm = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), p1);
    if (val) free(val); // If something is already there, free it
    pc.printf("Portal added ~ [X, Y] - [%d, %d]\nPortal->type: %d \n", x, y, p1->type);
    pc.printf("XY_KEY: %d    |  Bucket_Index (MAP Hash): %d\n",XY_KEY(x, y), map_hash(XY_KEY(x, y)));
}
void add_LIMBO_OLYMPUS_PORTAL(int x, int y)
{
    MapItem* p1 = (MapItem*) malloc(sizeof(MapItem));
    p1->type = LIMBO_OLYMPUS_PORTAL;
    p1->draw = draw_LIMBO_OLYMPUS_PORTAL;
    p1->walkable = true;
    p1->data = NULL;
    //portal->tx = x;
    //portal->ty = y;
    //portal->tm = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), p1);
    if (val) free(val); // If something is already there, free it
    pc.printf("Portal added ~ [X, Y] - [%d, %d]\nPortal->type: %d \n", x, y, p1->type);
    pc.printf("XY_KEY: %d    |  Bucket_Index (MAP Hash): %d\n",XY_KEY(x, y), map_hash(XY_KEY(x, y)));
}
void add_ATL_OLYMPUS_PORTAL(int x, int y)
{
    MapItem* p1 = (MapItem*) malloc(sizeof(MapItem));
    p1->type = ATL_OLYMPUS_PORTAL;
    p1->draw = draw_ATL_OLYMPUS_PORTAL;
    p1->walkable = true;
    p1->data = NULL;
    //portal->tx = x;
    //portal->ty = y;
    //portal->tm = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), p1);
    if (val) free(val); // If something is already there, free it
    pc.printf("Portal added ~ [X, Y] - [%d, %d]\nPortal->type: %d \n", x, y, p1->type);
    pc.printf("XY_KEY: %d    |  Bucket_Index (MAP Hash): %d\n",XY_KEY(x, y), map_hash(XY_KEY(x, y)));
}

void add_MARTA_ATL(int x, int y)
{
    MapItem* p1 = (MapItem*) malloc(sizeof(MapItem));
    p1->type = MARTA_ATL;
    p1->draw = draw_posiedonPortal;;
    p1->walkable = true;
    p1->data = NULL;
    //portal->tx = x;
    //portal->ty = y;
    //portal->tm = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), p1);
    if (val) free(val); // If something is already there, free it
    pc.printf("Portal added ~ [X, Y] - [%d, %d]\nPortal->type: %d \n", x, y, p1->type);
    pc.printf("XY_KEY: %d    |  Bucket_Index (MAP Hash): %d\n",XY_KEY(x, y), map_hash(XY_KEY(x, y)));
}



//=============================================================================
//---------------------------------------------------------------------------
//                               Posideon's Room
//--------------------------------------------------------------------------- 
//=============================================================================

// Potions 
//--------------------------------------
void add_DTealPotion(int x, int y)
{
    MapItem* potion = (MapItem*) malloc(sizeof(MapItem));
    potion->type = DTPOTION;
    potion->draw = draw_DTealPotion;
    potion->walkable = NULL;
    potion->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), potion);
    if (val) free(val); // If something is already there, free it
}

void add_DBluePotion(int x, int y)
{
    MapItem* potion = (MapItem*) malloc(sizeof(MapItem));
    potion->type = DBPOTION;
    potion->draw = draw_DBluePotion;
    potion->walkable = NULL;
    potion->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), potion);
    if (val) free(val); // If something is already there, free it
}

void add_DPurplePotion(int x, int y)
{
    MapItem* potion = (MapItem*) malloc(sizeof(MapItem));
    potion->type = DPPOTION;
    potion->draw = draw_DPurplePotion;
    potion->walkable = NULL;
    potion->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), potion);
    if (val) free(val); // If something is already there, free it
}

void add_DOrangePotion(int x, int y)
{
    MapItem* potion = (MapItem*) malloc(sizeof(MapItem));
    potion->type = DOPOTION;
    potion->draw = draw_DOrangePotion;
    potion->walkable = NULL;
    potion->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), potion);
    if (val) free(val); // If something is already there, free it
}

//----------------------------------------------------------------------



//----------------------------------------------------------------------

void add_water(int x, int y, int dir, int len)
{
    
    for(int i = 0; i < len; i++)
    {
        //pc.printf("Water: [X, Y] ~ %d, %d\n", x, y);
        MapItem* water = (MapItem*) malloc(sizeof(MapItem));
        water->type = COLORBLOCKS;
        water->draw = draw_water;
        water->walkable = true;
        water->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        //pc.printf("Key: %d\n", key);
        void* val = insertItem(get_active_map()->items, key, water);
        if (val) free(val); // If something is already there, free it
        //if()
    }
}


void add_desk(int x, int y)
{
    MapItem* desk = (MapItem*) malloc(sizeof(MapItem));
    desk->type = COLORBLOCKS;
    desk->draw = draw_desk;
    desk->walkable = true;
    desk->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), desk);
    if (val) free(val); // If something is already there, free it
}

void add_bedsheets(int x, int y)
{
    MapItem* bedsheets = (MapItem*) malloc(sizeof(MapItem));
    bedsheets->type = COLORBLOCKS;
    bedsheets->draw = draw_redSheets;
    bedsheets->walkable = 1;
    bedsheets->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), bedsheets);
    if (val) free(val); // If something is already there, free it
}
void add_pillow(int x, int y)
{
    MapItem* pillows = (MapItem*) malloc(sizeof(MapItem));
    pillows->type = COLORBLOCKS;
    pillows->draw = draw_WHITE;
    pillows->walkable = false;
    pillows->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), pillows);
    if (val) free(val); // If something is already there, free it
}


// This function takes in the TOP-LEFT MOST corner of the Bed set up
void add_bed(int x, int y)
{
    for(int i = 0; i<5; i++)
    {
        // Adding pillow MapItems along the the top row of the bed (length: 5)
        add_pillow((x + i), y);
        // Nested For loop: Creates a square area illistrating Poseidon's Bed
        //- The Inner loop creates 5 Bedsheets MapItems vertically, creating a line of Bedsheets
        for(int j = 0; j<5; j++)
        {
            add_bedsheets(x +i, (y + j + 1));
        }
    }
}

void add_nightStand(int x, int y)
{
    add_DTealPotion(x, y);
    add_DBluePotion(x+1, y);
    add_DPurplePotion(x+2, y);
    add_DOrangePotion(x+3, y);
    add_desk(x+4, y);

} 

//-----------------------------------------------------------------------
 // Handling functions:
 //--------------------









//=============================================================================
//-------------------- Marta Background  ------------------------------------
//=============================================================================
/*
Functions Used: 
----------------


draw_trainTopSection
void add_trainTopSection(int x, int y)

draw_trainMidSection
void add_trainMidSection(int x, int y)

draw_trainBottomSection
void add_trainBottomSection(int x, int y)

void add_TrainCar(int x, int y)
*/

void add_trainTopSection(int x, int y)
{
    MapItem* trainTopSection = (MapItem*) malloc(sizeof(MapItem));
    trainTopSection->type = COLORBLOCKS;
    trainTopSection->draw = draw_nothing;
    trainTopSection->walkable = false;
    trainTopSection->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), trainTopSection);
    if (val) free(val); // If something is already there, free it
}


void add_trainMidSection(int x, int y)
{
    MapItem* trainMidSection = (MapItem*) malloc(sizeof(MapItem));
    trainMidSection->type = COLORBLOCKS;
    trainMidSection->draw = draw_trainMidSection;
    trainMidSection->walkable = true;
    trainMidSection->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), trainMidSection);
    if (val) free(val); // If something is already there, free it
}

void add_trainBottomSection(int x, int y)
{
    MapItem* trainBottomSection = (MapItem*) malloc(sizeof(MapItem));
    trainBottomSection->type = COLORBLOCKS;
    trainBottomSection->draw = draw_trainBottomSection;
    trainBottomSection->walkable = true;
    trainBottomSection->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), trainBottomSection);
    if (val) free(val); // If something is already there, free it
}

unsigned int LENGTH_OF_MARTA = 20; 

void add_TrainCar(int x, int y)
{
    for(int i = 0; i<LENGTH_OF_MARTA; i++)
    {
        if(i==12)
        {
            continue;
        }
        add_trainTopSection((x+i), y);
        add_trainMidSection((x+i), y+1);
        add_trainBottomSection((x+i), y+2);
    }
}


//------------------------------------------------------------------------------


//=============================================================================
//-------------------- ATL Background  ------------------------------------
//=============================================================================

/*
Functions: 
--------------

void add_cloudPiece(int x, int y, int dir, int len)
void add_cloud(int x, int y);
*/

void add_cloudPiece(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* cloudPiece1 = (MapItem*) malloc(sizeof(MapItem));
        cloudPiece1->type = COLORBLOCKS;
        cloudPiece1->draw = draw_WHITE;
        //cloudPiece1->walkable = false;
        cloudPiece1->walkable = NULL;
        cloudPiece1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, cloudPiece1);
        if (val) free(val); // If something is already there, free it
        pc.printf("cloudPiece: walkable? ~ %d\nKey: %d\n", cloudPiece1->walkable, key);
    }
}


// Covers an 11x11 cell area
//--------------------------
void add_cloud(int x, int y)
{
    /* 
    1st Cloud segments
    =======
    ====
    */
    
    add_cloudPiece(x, y, HORIZONTAL,6);
    add_cloudPiece(x, y+1, HORIZONTAL,4);
    
    /* 2nd Cloud segments
                    =====
                     ====
    */
    
    add_cloudPiece(x+10, y, HORIZONTAL,5);
    add_cloudPiece(x+10, y+1, HORIZONTAL,4);
    
    /* 3rd Cloud segments
          =====
        =========   
       ==========
      ==========
        =========
      
    */
    
    add_cloudPiece(x+4, y + 5, HORIZONTAL,5);
    add_cloudPiece(x+2, y + 6, HORIZONTAL,8);
    add_cloudPiece(x+1, y + 7, HORIZONTAL,9);
    add_cloudPiece(x, y + 8, HORIZONTAL,9);
    add_cloudPiece(x+2, y + 9, HORIZONTAL,7);
    
    // Cloud segment to the right of these other clouds and will will have the key for the elevator
    add_cloudPiece(x+13, y + 7, HORIZONTAL,4);
    add_cloudPiece(x+12, y + 8, HORIZONTAL,3);
    
}

//------------------------------------------------------------------------------
//                            Pencil Building 
//------------------------------------------------------------------------------                            

/*
Functions used
----------------
[graphic.h]
void draw_brown(int u, int v); ~ implemented
void draw_darkblueBlock(int u, int v); ~ implemented
void draw_yellowBlock(int u, int v); ~ implemented
 
intatioanted
void draw_leftGrid(int u, int v);~  implemented
void draw_centerGrid(int u, int v);~  implemented
void draw_rightGrid(int u, int v);~  implemented
void draw_gridTip(int u, int v);~  implemented

[map.h]
void add_brownBlock(int x, int y, int dir, int len); ~  implemented
void add_darkblueBlock(int x, int y) ~ implemented
void add_yellowBlock(int x, int y); ~ implemented

void add_leftGrid(int x, int y); ~ implemented
void add_centerGrid(int x, int y); ~ implemented
void add_rightGrid(int x, int y); ~ implemented
void add_gridTip(int x, int y); ~ implemented

void add_pencilTIp(int x, int y) ~ implemented
void add_triangularGrid(int x, int y) ~ implemented


implemented| !!!!!!  STILL NEEDS to be tested!!!!!!!!
-----------------------------------
void add_buildingBlock(int x, int y)
void add_PencilBuilding(int x, int y)



*/



void add_brownBlock(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* brownBlock = (MapItem*) malloc(sizeof(MapItem));
        brownBlock->type = COLORBLOCKS;
        brownBlock->draw = draw_brown;
        //brownBlock->walkable = false;
        brownBlock->walkable = NULL;
        brownBlock->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, brownBlock);
        if (val) free(val); // If something is already there, free it
        pc.printf("cloudPiece: walkable? ~ %d\nKey: %d\n", brownBlock->walkable, key);
    } 
}

void add_darkblueBlock(int x, int y)
{
    MapItem* darkblueBlock = (MapItem*) malloc(sizeof(MapItem));
    darkblueBlock->type = COLORBLOCKS;
    darkblueBlock->draw = draw_darkblueBlock;
    darkblueBlock->walkable = false;
    darkblueBlock->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), darkblueBlock);
    if (val) free(val); // If something is already there, free it
}

void add_yellowBlock(int x, int y)
{
    MapItem* yellowBlock = (MapItem*) malloc(sizeof(MapItem));
    yellowBlock->type = COLORBLOCKS;
    yellowBlock->draw = draw_yellowBlock;
    yellowBlock->walkable = false;
    yellowBlock->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), yellowBlock);
    if (val) free(val); // If something is already there, free it
}

//------------------------------------------------------------------------------
/*                          Tip of the Pencil Building
 *------------------------------------------------------------------------------
 * Input X, Y coordinates correspond to the block being placed athe the bottom of the Tip (so leave room @ the top)
 * just a column of yellow block ~ LENGTH: 5
 */
void add_pencilTIp(int x, int y)
{
    add_yellowBlock(x, y);
    add_yellowBlock(x, y-1);
    add_yellowBlock(x, y-2);
    add_yellowBlock(x, y-3);
}

//-------------------------------------------------------------------------------
void add_leftGrid(int x, int y)
{
    MapItem* leftGrid = (MapItem*) malloc(sizeof(MapItem));
    leftGrid->type = COLORBLOCKS;
    leftGrid->draw = draw_leftGrid;
    leftGrid->walkable = false;
    leftGrid->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), leftGrid);
    if (val) free(val); // If something is already there, free it
}
    
void add_centerGrid(int x, int y)
{
    MapItem* centerGrid = (MapItem*) malloc(sizeof(MapItem));
    centerGrid->type = COLORBLOCKS;
    centerGrid->draw = draw_centerGrid;
    centerGrid->walkable = false;
    centerGrid->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), centerGrid);
    if (val) free(val); // If something is already there, free it
}
void add_rightGrid(int x, int y)
{
    MapItem* rightGrid = (MapItem*) malloc(sizeof(MapItem));
    rightGrid->type = COLORBLOCKS;
    rightGrid->draw = draw_rightGrid;
    rightGrid->walkable = false;
    rightGrid->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), rightGrid);
    if (val) free(val); // If something is already there, free it
}
void add_gridTip(int x, int y)
{
    MapItem* gridTip = (MapItem*) malloc(sizeof(MapItem));
    gridTip->type = COLORBLOCKS;
    gridTip->draw = draw_gridTip;
    gridTip->walkable = false;
    gridTip->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), gridTip);
    if (val) free(val); // If something is already there, free it
}

//-------------------------------------------------------------------------------

void add_triangularGrid(int x, int y)
{
    // Coordinates: (X, Y) ~ Starts from the bottom up
    // Tip->2nd->1st->Bottom 
    
    // Bottom Row
    add_leftGrid(x, y);
    add_leftGrid(x+2, y);
    add_rightGrid(x+4, y);
    add_rightGrid(x+6, y);
    //1st Row 
    add_leftGrid(x+1, y-1);
    add_centerGrid(x+3, y-1);
    add_rightGrid(x+5, y-1);
    //2nd Row 
    add_leftGrid(x+2, y-2);
    add_rightGrid(x+4, y-2);
    //Tip
    add_gridTip(x+3, y-3);
    
}

void add_buildingBlock(int x, int y)
{
    pc.printf("Bottom of Building Block: Y ~ %d\n", y+2);
    // Coordinates X | Y represent the Top Left corner of the building block
    add_brownBlock(x, y, HORIZONTAL, 7);
    add_brownBlock(x, y+2, HORIZONTAL, 7);
    
    add_brownBlock(x, y+1, HORIZONTAL, 1);
    add_brownBlock(x+2, y+1, HORIZONTAL, 1);
    add_brownBlock(x+4, y+1, HORIZONTAL, 1);
    add_brownBlock(x+6, y+1, HORIZONTAL, 1);
    
    //------ Windows -------
    add_darkblueBlock(x+1, y+1);
    add_darkblueBlock(x+3, y+1);
    add_darkblueBlock(x+5, y+1);    
}



void add_pavement(int x, int y, int dir, int len)
{
    for(int i = 0; i < len; i++)
    {
        MapItem* w1 = (MapItem*) malloc(sizeof(MapItem));
        w1->type = WALL;
        w1->draw = draw_pavement;
        //w1->walkable = false;
        w1->walkable = NULL;
        w1->data = NULL;
        unsigned key = (dir == HORIZONTAL) ? XY_KEY(x+i, y) : XY_KEY(x, y+i);
        void* val = insertItem(get_active_map()->items, key, w1);
        if (val) free(val); // If something is already there, free it
        //pc.printf("WALL: walkable? ~ %d\nKey: %d\n", w1->walkable, key);
        //pc.printf("I: %d  |  Length: %d  |", i, len);
    }
}


void add_PencilBuilding(int x, int y)
{
    //int base_offset = 9; // ---------------------------------Change once planned out better
    // COMMENT: Center of the building (x, y + 3)
    
    // Pencil building: Tip
    //---------------------
    add_pencilTIp(x+3, y-5);                //Tip must be offset in order to align with the center of the building, hence why the input is (x+3)
    
    // -----------------
    add_triangularGrid(x, y-1);
    
    // Triangular Grid Structure 
    //----------------------------
    //~ between the tip and the Buildings base
    //add_triangularGrid(***, ***);
    
    // Series of Building BLocks used to depict 
    //-------------------------------------------
    for(int i = 0; i<10; i++)
    {
        add_buildingBlock(x , y + (3*i) );          //            y + (3*i)+ base_offset
    }
}




//==============================================
//----------------- ADD NPC --------------------
//==============================================
void add_npc(int x, int y)
{
    MapItem* npc = (MapItem*) malloc(sizeof(MapItem));
    npc->type = NPC;
    npc->draw = draw_npc;
    npc->walkable = false;
    npc->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), npc);
    if (val) free(val); // If something is already there, free it
}

void add_Hermes(int x, int y)
{
    MapItem* hermes = (MapItem*) malloc(sizeof(MapItem));
    hermes->type = HERMES;
    hermes->draw = draw_npc;
    hermes->walkable = false;
    hermes->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), hermes);
    if (val) free(val); // If something is already there, free it
}
void add_muse(int x, int y)
{
    MapItem* muse = (MapItem*) malloc(sizeof(MapItem));
    muse->type = MUSE;
    muse->draw = draw_muses;
    muse->walkable = false;
    muse->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), muse);
    if (val) free(val); // If something is already there, free it
}
void delete_muse(int x, int y)
{
    map_erase(x, y);
    pc.printf("DELETE MUSE");
}



void add_treasure(int x, int y)
{
    MapItem* t1 = (MapItem*) malloc(sizeof(MapItem));
        t1->type = TREASURE;
        t1->draw = draw_treasure;
        t1->walkable = false;
        t1->data = NULL;
        void* val = insertItem(get_active_map()->items, XY_KEY(x, y), t1);
        if (val) free(val); // If something is already there, free it
}

void add_godButcher (int x, int y) 
{
    MapItem* godButcher1 = (MapItem*) malloc(sizeof(MapItem));
    godButcher1->type = GOD_BUTCHER;
    godButcher1->draw = draw_godButcher;
    godButcher1->walkable = false;
    godButcher1->data = NULL;
    void* val = insertItem(get_active_map()->items, XY_KEY(x, y), godButcher1);
    if (val) free(val); // If something is already there, free it
}

