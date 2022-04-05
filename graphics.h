#ifndef GRAPHICS_H
#define GRAPHICS_H


/**
 * Draws the player. This depends on the player state, so it is not a DrawFunc.
 */
void draw_player(int u, int v, int key);

/**
 * Takes a string image and draws it to the screen. The string is 121 characters
 * long, and represents an 11x11 tile in row-major ordering (across, then down,
 * like a regular multi-dimensional array). The available colors are:
 *      R = Red
 *      Y = Yellow
 *      G = Green
 *      D = Brown ("dirt")
 *      5 = Light grey (50%)
 *      3 = Dark grey (30%)
 *      Any other character is black
 * More colors can be easily added by following the pattern already given.
 */
void draw_img(int u, int v, const char* img);


void draw_basq(int u, int v);


void draw_fullHealth(int u, int v);
void draw_twoThirds_Health(int u, int v);
void draw_oneThird_Health(int u, int v);
    
    


/**
 * DrawFunc functions. 
 * These can be used as the MapItem draw functions.
 */

void draw_nothing(int u, int v);
void draw_wall(int u, int v);
void draw_plant(int u, int v);

/*Addtional Sprites:
---------------------*/
void draw_lostSoul(int u, int v);

void draw_pavement(int u, int v);


//--------------------------------

void draw_redSheets(int u, int v);
void draw_WHITE(int u, int v);
void draw_desk(int u, int v);
void draw_water(int u, int v);
void draw_DTealPotion(int u, int v);
void draw_DBluePotion(int u, int v);
void draw_DPurplePotion(int u, int v);
void draw_DOrangePotion(int u, int v);


//--------------------------------


//--------------------------------


void draw_trainMidSection(int u, int v);
void draw_trainBottomSection(int u, int v);


//--------------------------------

void draw_trailingClouds(int u, int v);

void draw_grass(int u, int v);

void draw_tree(int u, int v);
void draw_limboTree(int u, int v);
void draw_goldenTree(int u, int v);

//-------------------------------
//      Portals
//-------------------------------

void draw_homePortal(int u, int v);
void draw_martaPortal(int u, int v);
void draw_posiedonPortal(int u, int v);
void draw_LIMBO_OLYMPUS_PORTAL(int u, int v);
void draw_ATL_OLYMPUS_PORTAL(int u, int v);
//------------------------------------------


//=======================================================================
//                    Pencil Building
//=======================================================================
void draw_brown(int u, int v);
void draw_darkblueBlock(int u, int v);
void draw_yellowBlock(int u, int v);
void draw_darkYELLOW(int u, int v);
void draw_lightBlue(int u, int v);
//---------------------------------------


void draw_leftGrid(int u, int v);
void draw_centerGrid(int u, int v);
void draw_rightGrid(int u, int v);
void draw_gridTip(int u, int v);




void draw_npc(int u, int v);

void draw_muses(int u, int v);

void draw_hermes(int u, int v);

void draw_grass(int u, int v);

void draw_treasure(int u, int v);

void draw_godButcher (int u, int v); 

/**
 * Draw the upper status bar.
 */
void draw_upper_status(int x, int y, int map_index);

/**
 * Draw the lower status bar.
 */ 
void draw_lower_status(int lives);

/**
 * Draw the border for the map.
 */
void draw_border();


#endif // GRAPHICS_H