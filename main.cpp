// Project includes
#include "globals.h"
#include "hardware.h"
#include "map.h"
#include "graphics.h"
#include "speech.h"

// Functions in this file
int get_action (GameInputs inputs);
int update_game (int action);
void draw_game (int init);
void init_main_map ();

// MOVEMENT Function prototypes
int go_right(int x, int y);
int go_left(int x, int y);
int go_up(int x, int y);
int go_down(int x, int y);

// USED within MAIN LOOP
int runTime_counter = 0;
int runTime_check = 0;
int check = 0;
int shift =0;
int leave_MAP0 =0;
int leave_MAP1 =0;
int leave_MAP2 =0;
int leave_MAP3 =0;
int TOP_lostSouls__move = 0;
int BOTTOM_lostSouls__move = 29;
int lostSouls__move = 1;
int direction = 1;
int LEFT_lostSouls__move = 1;
int RIGHT_lostSouls__move = 17;




// Main Loop
int main ();

// Initializing Structs in other header files
GameInputs reading_inputs;      // initializing input arg to get_action/ local GameInuputs struct that is modified in main()
int action;
int lives = 3;
int update = update_game(action);
int omni = false; // Enabling omni Presensce




//const char* testCase[2] = ["Sup Jean, my name is a Dimitrios, son of the Goddess Demeter and the God Appolo. I for one am the God of Art, Illusions, and Craftsanship.", "I've heard that your searching to solve the Mosiac of "];
char *meetNPC = "Sup Jean, my name is a Dimitrios, son of the Goddess Demeter and the God Appolo. I for one am the God of Art, Illusions, and Craftsanship.";
char *QuestIntructions1 = "I've heard that your searching to solve the Mosiac of ";
char *congratsLine = "Congradulations Basquiat, you have done well in compelting the task set before you. Now take this key and claim your prize!";
char *missionIncomplete = "You need to complete the Mission First";
char *RoomFlooded = "Oh NO Poseidon is here and your only way out is flooded.";
char *godButcher_retrieved = "God Butcher retrieved";
char *meetHERMES = "Hey Jean, my name is Hermes, I need you to retrieve my sword from the pesky muse. If you take the next stop on MARTA it will take you to the Pencil Building where there portal you can use to get to Olympus. Here are my shoes, to help you get to that portal in the CLOUDS.";
char *museSlain = "Muse Slain! Either keep the swoard or return home";
char *museHIT = "Hit muse ~ Muse lost health";
char *throwPotions = "Throw the potion into the river before entering the water   |  Press the 3rd button to Throw the potion      ";

char *lostHealth = "Health Lost (-1)";

//char meeting_NPC[2] = [meetNPC, QuestIntructions1];
//"I am a cook.", "love women all day ans for the rest of eternitry"


// Potion Related Speeches:
//----------------------------
char *wrongPotion = "Worng Potion, Try another.";
char *purplePotionRetrieved = "Purple Potion Retrieved!!!  :)";
char *orangePotionRetrieved = "Orange Potion Retrieved!!!  :)";



/**
 * The main game state. Must include Player locations and previous locations for
 * drawing to work properly. Other items can be added as needed.
 *
 * () Checkpoints_# : These varaibales serves as checks used to prevent repeated runs of the load_screen() function, espcially when the player has completed all the tasks expected from the current map they are on.
 *  ~ default value = 0 (set in the Main loop)
 */
struct {
    int x,y;    // Current locations
    int px, py; // Previous locations
    int has_key;
    // You can add other properties for the player here
    int mission_given_by_NPC; // DEFAULT: false ~ sinceyou haven't talked to the NPC when you first start the game -> value changes once talking to the NPC for the fisrt time
    int has_slain_beast;
    int ApollosCongrats;
    int has_godButcher;
    int has_treasure;
    int has_purplePotion;
    int has_orangePotion;
    int has_Hermes_shoes;
    int current_map;
    int prev_map;
    int mission_given_by_HERMES;    // Player struct 
    int health; // initialized as 3 and you are able to lose them once you are attacked
    int muse_health;
    int throwPotion;
    
    int prev_prev_map;
    int completed_tasked_in_current_map;
    //===============
    int checkpoint_1;
    int checkpoint_2;
    int checkpoint_3;
    int checkpoint_4;
    int checkpoint_5;
    int checkpoint_6;
    int checkpoint_7;
    int checkpoint_8;
    int checkpoint_9;
    int checkpoint_10;
    int checkpoint_11;
    
} Player;

/**
Initilaizing the Player Struct DEFAULT VALUES
---------------------------------------------
*/
/*
void throwPotions() 
{
    int x = Player.x
    int y = Player.y
    for(int i = 0; i<4; i++)
    {
        add_DPurplePotion(x+1, y-i);
        add_DOrangePotion(x, y-i);
        if(i) 
        {
            map_erase(get(x+1, y-i-1);
            map_erase(get(x, y-i-1);
        }
    }
    map_erase(get(x+1, y-i-1);
    map_erase(get(x, y-i-1);
}

*/

void muse_damage()
{
    if( get_north(Player.x, Player.y)->type == MUSE || 
        get_south(Player.x, Player.y)->type == MUSE || 
        get_east(Player.x, Player.y)->type == MUSE  || 
        get_west(Player.x, Player.y)->type == MUSE )
        {
            Player.health--;
            speech(lostHealth, lostHealth);
            if(Player.health == 0) 
            {
                lives--;
                Player.health = 3;
            }
            if (lives == 0) draw_game(3); 
        }
}



void retrieveGODBUTCHERR(int god_butch_X, int god_butch_Y)
{
    pc.printf("God Butcher Retrieved\n--------------------\n");
    pc.printf("god_butch_X:  %d   |      god_butch_Y:   %d  |\n",  god_butch_X, god_butch_Y);
    speech(godButcher_retrieved, godButcher_retrieved);
    map_erase(god_butch_X, god_butch_Y);
    Player.has_godButcher = 1;
    map_erase(7, 9);
    add_muse(12, 6);
    pc.printf("---------------------------\n");
}


void handle_trailingClouds()
{
    int x = Player.x;
    int y = Player.y;
    if (  !((get_here(x, y+1)->type) == ATL_OLYMPUS_PORTAL)  )  add_trailingCloud( x, y+1);
    pc.printf("\n=======================================\n");
    pc.printf("Trailing Cloud Locations: \n --------------------------\n");
    pc.printf("UP: %d\n", ( ( (get_here(x, y+2))->type ) == TRAILING_CLOUD) );
    pc.printf("LEFT: %d\n", ( ( (get_here(x, y+2))->type ) == TRAILING_CLOUD) );
    pc.printf("RIGHT: %d\n", ( ( (get_here(x+1, y+1))->type ) == TRAILING_CLOUD) );

    // Check Edge Cases Locations:  MapItem->type == TRAILING_CLOUD (x, y+2
    // ------------------------------
    // These are all cases where the function add_trailingCloud was called, then the player moved once more, in one of the following directions: UP (again), Right, or Left
    // UP : TRAILING_CLOUD block is loacted two blocks directly BELOW the Player.
    if( ( (get_here(x, y+2))->type ) == TRAILING_CLOUD  ) map_erase(x, y + 2);
    // LEFT (diagonal): TRAILING_CLOUD block is loacted 1 block directly BELOW and 1 block to the RIGHT of the Player.
    if( ( (get_here(x-1, y+1))->type ) == TRAILING_CLOUD  ) map_erase(x-1, y + 1);
    // RIGHT (diagonal): TRAILING_CLOUD block is loacted 1 block directly BELOW and 1 block to the Right of the Player.
    if( ( (get_here(x+1, y+1))->type ) == TRAILING_CLOUD  ) map_erase(x+1, y + 1);
    pc.printf("\n---------------------------------------\nAfter Clearing out the Trailing Cloud\n ---------------------------------------\n");
    pc.printf("UP: %d\n", ( ( (get_here(x, y+2))->type ) == TRAILING_CLOUD) );
    pc.printf("LEFT: %d\n", ( ( (get_here(x, y+2))->type ) == TRAILING_CLOUD) );
    pc.printf("RIGHT: %d\n", ( ( (get_here(x+1, y+1))->type ) == TRAILING_CLOUD) );
    pc.printf("\n=======================================\n");
}

/*
wrongPotion
purplePotionRetrieved
orangePotionRetrieved
Player.has_purplePotion
Player.has_orangePotion
Player.has_purplePotion = 0;
Player.has_orangePotion = 0;
*/

        
// Inputs will be (Player.px, Player.py) 
void handlePotions()
{
    if( get_north(Player.px, Player.py)->type ==  DTPOTION ||
        get_north(Player.px, Player.py)->type ==  DBPOTION  )
    {
        speech(wrongPotion, wrongPotion);
        // If the Purple Potion is Retrieved
    }   else if(get_here(Player.px, Player.py - 1)->type ==  DPPOTION) 
    {
        map_erase(Player.px, Player.py-1);
        add_desk(Player.px, Player.py-1);
        speech(purplePotionRetrieved, purplePotionRetrieved);
        pc.printf("Player.has_purplePotion Status: %d", Player.has_purplePotion);
        Player.has_purplePotion = 1;
        pc.printf("Player.has_purplePotion Status: %d", Player.has_purplePotion);
    }   else if(get_here(Player.px, Player.py - 1)->type ==  DOPOTION) 
    {
        map_erase(Player.px, Player.py-1);
        add_desk(Player.px, Player.py-1);
        speech(orangePotionRetrieved, orangePotionRetrieved);
        pc.printf("Player.has_orangePotion Status: %d", Player.has_orangePotion);
        Player.has_orangePotion = 1;
        pc.printf("Player.has_orangePotion Status: %d", Player.has_orangePotion);
    }
    
    
}

int local_wave_timer_START = 0;
int local_wave_timer = 0;
int row = 18;
//Start position of the Wave, (bottom left corner of the map ->  X = 1, Y = 18


void update_soulPosition()
{
    if( get_active_map() == get_map(1) )
    {
            //----------------------------------------------------------
            if(direction == 1) // move to the right (top initally)
            {
                add_lostSoul(lostSouls__move, 3);
                add_lostSoul(lostSouls__move, 7);
                add_lostSoul(3, lostSouls__move);
                add_lostSoul(7, lostSouls__move);
                if(lostSouls__move > 1)
                {
                     map_erase(lostSouls__move-1, 3);
                     map_erase(lostSouls__move-1, 7);
                     map_erase(3, lostSouls__move-1);
                     map_erase(7, lostSouls__move-1);
                     
                     //map_erase(lostSouls__move-1, 1);
                }
                lostSouls__move++;
            } else if (direction == 0)
                {
                    add_lostSoul(lostSouls__move, 3);
                    add_lostSoul(lostSouls__move, 7);
                    add_lostSoul(lostSouls__move, 7);
                    add_lostSoul(3, lostSouls__move);
                    add_lostSoul(7, lostSouls__move);
                    if(lostSouls__move != 9)
                    { 
                        map_erase(lostSouls__move+1, 3);
                        map_erase(lostSouls__move+1, 7);
                        map_erase(3, lostSouls__move+1);
                        map_erase(7, lostSouls__move+1);
                    }
                    lostSouls__move--;
                }
            //----------------------------------------------------------
            if (lostSouls__move == 9)
            {
                direction = 0;
                map_erase(9, 3);
                map_erase(9, 7);
                map_erase(3, 9);
                map_erase(7, 9);
            }
            if (lostSouls__move == 1)
            {
                direction = 1;
                map_erase(1, 3);
                map_erase(1, 7);
                map_erase(3, 1);
                map_erase(7, 1);
            }
       if(get_here(Player.x, Player.y)->type == LOSTSOUL)
       {
           Player.health--;
           speech(lostHealth, lostHealth);
           if(Player.health == 0)
           {
               lives--;
               Player.health = 3;
           }
       }
        
    }
    
    
}

//---------------------------------------------------------------------------------------


//---------------------------------------------------------------------------------------
//int trailingCLoud_X = Player.x;
//int trailingCLoud_Y = Player.y + 1;
/*==============================================================================
                                    Movement Fucntions
  ============================================================================*/
/* Go UP Function
---------------------
*/
int go_up(int x, int y) {
    MapItem* item = get_north(x,y);
    pc.printf("North Item ~ Profile:\n Type: %d | Walkable: %d | \nNULL Pointer: %d\n", item->type, item->walkable, NULL);
    if( (get_map_index() == 5) && !(Player.has_Hermes_shoes) )  return NULL;
    if((item->walkable) || omni) 
    {
        if(lives == 0)  return NULL;
        Player.y--;
        
        if( get_map_index() == 5) 
        {
            //trailingCLoud_X = Player.x;
            //trailingCLoud_Y = Player.y + 1;
            //add_trailingCloud(trailingCLoud_X, trailingCLoud_Y);
            //handle_trailingClouds();
            //if( (get_south( trailingCLoud_X,  trailingCLoud_Y))->type == TRAILING_CLOUD )  map_erase(remove_trailingCLoud_X,  remove_trailingCLoud_Y) ;              //= Player.x)
            
            
            //trailingCLoud_X = Player.x;
            //trailingCLoud_X = Player.y + 1;
        }
        
        
        //need a delete Trailing function  ~ adding this many trailing clouds should surely eat up eat/fragment alot of the memnory
        
        //draw_trailingClouds(x, y+1);
        return 1;
    }
    return 0;
}
/* Go Down Function
---------------------
*/
int go_down(int x, int y) {
    MapItem* item = get_south(x,y);
    pc.printf("South Item ~  Profile:\n Type: %d | Walkable: %d | \nNULL Pointer: %d\n", item->type, item->walkable, NULL);
    if((item->walkable) || omni) {
        if(lives == 0) {
            return NULL;
        }
        Player.y++;
        return 1;
    }
    return 0;
}
/* Go East Function
---------------------
*/
int go_east(int x, int y) {
    MapItem* item = get_east(x,y);
    pc.printf("EAST Item ~ Profile:\n Type: %d | Walkable: %d | \nNULL Pointer: %d\n", item->type, item->walkable, NULL);
    if((item->walkable) || omni) {
        if(lives == 0) {
            return NULL;
        }
        Player.x++;
        return 1;
    }
    return 0;
}
/* Go West Function
---------------------
*/
int go_west(int x, int y) {
    MapItem* item = get_west(x,y);
    pc.printf("WEST Item ~ Profile:\n Type: %d | Walkable: %d | \nNULL Pointer: %d\n", item->type, item->walkable, NULL);
    if((item->walkable) || omni) {
        if(lives == 0) {
            return NULL;
        }
        Player.x--;
        return 1;
    }
    return 0;
}


/*==============================================================================
                                    get_Action
  ============================================================================*/


/**
 * Given the game inputs, determine what kind of update needs to happen.
 * Possbile return values are defined below.
 */
#define NO_ACTION 0
#define ACTION_BUTTON 1
#define MENU_BUTTON 2
#define GO_LEFT 3
#define GO_RIGHT 4
#define GO_UP 5
#define GO_DOWN 6
#define LOST_ALL_LIVES 7 // player dies
#define JUMPWORLDS 8
int get_action(GameInputs inputs)
{
    if (lives == 0){
        return LOST_ALL_LIVES;
    }
    if (inputs.ay >= 0.70 ){ //&& inputs.ay <= 0.40
        return GO_UP;
    }
    if (inputs.ay <= -0.70  ){ //&& inputs.ay > -0.40
        return GO_DOWN;
    }
    if (inputs.ax <= -0.40 ){ //&& inputs.ay > -0.70
        return GO_LEFT;
    }
    if (inputs.ax >= 0.40 ){ //&& inputs.ax <= 0.70
        return GO_RIGHT;
    }
    //---------------------------------
    //      ACTION BUTTON Controls
    //---------------------------------
    
    if ((inputs.b1) != 1)
    {
        //nested loop for the b1 (button closes to the accelerometer
        pc.printf("Current MAP Index: %d   |  Type @ Location: %d\n", get_map_index(), get_here(Player.px, Player.py));
        //--------------------------------------------------------------------------------------------------------------------------------
        // |    |   |   |   |   |   |   |   |    |   |   |   |   |   |   |  |    |   |   |   |   |   |   |  |    |   |   |   |   |   |   |
        //--------------------------------------------------------------------------------------------------------------------------------
        if (get_north(Player.px, Player.py)->type ==  DTPOTION ||
            get_north(Player.px, Player.py)->type ==  DBPOTION ||
            get_north(Player.px, Player.py)->type ==  DPPOTION ||
            get_north(Player.px, Player.py)->type ==  DOPOTION  )
        {
            handlePotions();
        }
        //--------------------------------------------------------------------------------------------------------------------------------
        // |    |   |   |   |   |   |   |   |    |   |   |   |   |   |   |  |    |   |   |   |   |   |   |  |    |   |   |   |   |   |   |
        //--------------------------------------------------------------------------------------------------------------------------------
        // =================== Switching MAPS ===========================
        //Toggle Maps (When on the PORTAL
        //----------------------------------
        if ( ( get_here(Player.px, Player.py)->type ) == HOME_PORTAL ||
             ( get_here(Player.px, Player.py)->type ) == MARTA_PORTAL ||
             ( get_here(Player.px, Player.py)->type ) == POSIEDON_PORTAL ||
             ( get_here(Player.px, Player.py)->type ) == LIMBO_OLYMPUS_PORTAL ||
             ( get_here(Player.px, Player.py)->type ) == ATL_OLYMPUS_PORTAL ||
             ( get_here(Player.px, Player.py)->type ) == MARTA_ATL)
        {
            pc.printf("Button 1 input: %d\n", inputs.b1);
            pc.printf("Enter Main Portal: %d\n", get_map_index());
            return JUMPWORLDS;
        }
        //--------------------------------------------------------------------------------------------------------------------------------
        // |    |   |   |   |   |   |   |   |    |   |   |   |   |   |   |  |    |   |   |   |   |   |   |  |    |   |   |   |   |   |   |
        //--------------------------------------------------------------------------------------------------------------------------------
        //Checks to see if the NPC is nearby the Player
        //===============================================
        //          Actions done while near the NPC
        //talking to the NPC
        if( get_north(Player.px, Player.py)->type == NPC  || 
            get_south(Player.px, Player.py)->type == NPC || 
            get_east(Player.px, Player.py)->type == NPC  || 
            get_west(Player.px, Player.py)->type == NPC )
            {
                
                /*First Encounter comunicating with the NPC
                ----------------------------------------------*/
                pc.printf("******************\nTalk to NPC\n******************\n");
                if (Player.mission_given_by_NPC == 0) 
                {
                    //long_speech(testCase, 2)  
                    speech(meetNPC, meetNPC); 
                    //Player.has_key = NULL;
                    Player.mission_given_by_NPC = 1;
                    Player.has_slain_beast = NULL;
                    //long_speech(meeting_NPC[], 2);
                }
            
                /** If the player has slain the NYMPH, and Re-Encounters the NPC (Dimitrios) then:
                 *  --------------------------------------
                 *  (1) NPC says Congrats on completing the Quest
                 *  (2) NPC gives you the key -> changes value of Player.has_key within Player struct
                            -   which in turn give you the ability to unlock the treasure behind the gate
                 *  (3) IF get_north() @ any point PASSAGEWAY MapItem && Player has a key in posseion, then call delete Key
                 *  (4) 
                 *  
                */    
                if (Player.mission_given_by_NPC && Player.has_slain_beast && !(Player.has_key)) 
                { 
                    speech(congratsLine, congratsLine);
                    Player.has_key = 1; // set to a nonzero value
                    //Player.ApollosCongrats = 1;
                }
    
            }
        //--------------------------------------------------------------------------------------------------------------------------------
        // |    |   |   |   |   |   |   |   |    |   |   |   |   |   |   |  |    |   |   |   |   |   |   |  |    |   |   |   |   |   |   |
        //--------------------------------------------------------------------------------------------------------------------------------
        if( get_east(Player.px, Player.py)->type == HERMES )   //only way you can directly interact HERMES [ALWAYS ON TO THE RIGHT OF THE PLAYER]
        {   
            pc.printf("******************\nTalk to HERMES\n******************\n");
            if (Player.mission_given_by_HERMES == 0) 
            {
                 //long_speech(testCase, 2)  
                speech(meetHERMES, meetHERMES); 
                //Player.has_key = NULL;
                Player.mission_given_by_HERMES = 1;
                Player.has_Hermes_shoes = 1;
                //long_speech(meeting_NPC[], 2);
            }
        }
        //--------------------------------------------------------------------------------------------------------------------------------
        // |    |   |   |   |   |   |   |   |    |   |   |   |   |   |   |  |    |   |   |   |   |   |   |  |    |   |   |   |   |   |   |
        //--------------------------------------------------------------------------------------------------------------------------------
        // If the Player has a key AND the above cell is of type PASSAGEWAY, then by clicking Button 1, the player would delete the Passageway
        if ((get_north( Player.px, Player.py )->type == PASSAGEWAY ) && (Player.has_key)) delete_passageWay(23, 7);
        /**
         *   After the player has completed the Quest, Recieved the Key, deleted the Passage way and Is now approaching the Treasure
         *   This IF-Block, switchs maps to the GAMEOVER Map once the player c
         */
        if ( (get_north( Player.px, Player.py )->type == TREASURE) ||
             (get_south( Player.px, Player.py )->type == TREASURE) ||
             (get_west( Player.px, Player.py )->type == TREASURE)  ||
             (get_east( Player.px, Player.py )->type == TREASURE)   ) 
        {
            if ( !(Player.has_key)) 
            {
                speech(missionIncomplete, missionIncomplete);
            } else 
                {
                    Player.has_treasure  = 1;
                    return JUMPWORLDS;
                }
        }
        if(get_map_index() == 4 )
        {
            if (get_north(Player.px, Player.py)->type ==  GOD_BUTCHER) retrieveGODBUTCHERR(Player.x, Player.y - 1 );
            if (get_south(Player.px, Player.py)->type ==  GOD_BUTCHER) retrieveGODBUTCHERR(Player.x, Player.y + 1 );
            if (get_east(Player.px, Player.py)->type ==  GOD_BUTCHER) retrieveGODBUTCHERR(Player.x + 1, Player.y);
            if (get_west(Player.px, Player.py)->type ==  GOD_BUTCHER) retrieveGODBUTCHERR(Player.x  - 1, Player.y);
        } 
    //End of the Button 1 Trgger IF-Block
    return NO_ACTION;  
    }    
    
    //--------------------------------------
    //      OMNIPOTENCE BUTTON Controls 
    //--------------------------------------
    if ((inputs.b2 != 1)) {
        pc.printf("-------------------\nStart ~ Omni Status: %d\n", omni);
        if(omni == false) {
            pc.printf("Button 2 pressed\nOmnipotence **ACTIVATED**\n");
            omni = true;
            pc.printf("-------------------\nEnd ~ Omni Status: %d\n", omni);
            return NO_ACTION;
        } else {
            pc.printf("Button 2 pressed\nOmnipotence **DEACTIVATED**\n");
            omni = false;   
            pc.printf("-------------------\nEnd ~ Omni Status: %d\n", omni);
            return NO_ACTION;
        }
    }
    //      Attack button
    //  ------------------------
    /*
    throwPotions
    */
    if ((inputs.b3 != 1)) 
    {   
        
            //----------------------------------------------------------------
            /*
            
            */
            //----------------------------------------------------------------
        
        //---------------------------------------
       //         Kill MUSE 
        //---------------------------------------
        if( get_north(Player.px, Player.py)->type == MUSE || 
            get_south(Player.px, Player.py)->type == MUSE || 
            get_east(Player.px, Player.py)->type == MUSE  || 
            get_west(Player.px, Player.py)->type == MUSE )
        {
        //-----------------------------------------
            if (Player.has_godButcher) 
            {
                Player.muse_health--;
                speech(museHIT,museHIT);
                if(Player.muse_health == 0) 
                {
                    speech(museSlain,museSlain);
                    delete_muse(12, 6);
                    Player.has_slain_beast = 1;
                }
            }
        }
        
        //End of the Button 3 Trgger IF-Block
        return NO_ACTION;
    }
        /*
    } else if (inputs.ay > 0.40) 
        return RUN_UP;
    } else if (inputs.ay < -0.40) 
        return RUN_DOWN;
    } else if (inputs.ax < -0.70)  
        return RUN_LEFT;
    } else if (inputs.ax >= 0.70) 
        return RUN_RIGHT;*/
    return NO_ACTION;
}

//===========================================================================================================================================================================================================
//------------------------------------------------------------------------------Initializing Display Screens-------------------------------------------------------------------------------------------------
//===========================================================================================================================================================================================================
/*==============================================================================
                            Start Page
         ( Provideds the essential information about the game )
  ==============================================================================*/
void init_START_map()
{
    uLCD.filled_rectangle(0,0,255,255,BLACK);
    uLCD.text_width(1);
    uLCD.text_height(1);
    uLCD.color(GREEN);
    uLCD.textbackground_color(BLACK);
    uLCD.locate(4,0);
    uLCD.printf("Welcome to");
    uLCD.locate(6,1);
    uLCD.printf("NEW DAWN");
    uLCD.locate(0,5);
    uLCD.printf("To Begin you Quest");
    uLCD.locate(3,6);
    uLCD.printf("Meet Meech "); 
    pc.printf("----------------Start Screen ON-----------------------\n");
    wait(10);
    
}
/*=============================================================================
                                GAME OVER SCREEN
=============================================================================*/

void init_GAMEOVER_map()
{
    uLCD.filled_rectangle(0,0,255,255,BLACK);
    uLCD.text_width(1);
    uLCD.text_height(1);
    uLCD.color(GREEN);
    uLCD.textbackground_color(BLACK);
    if(lives == 0)
    {
        uLCD.locate(2,7);
        uLCD.printf("You Died!!!!!");
        uLCD.locate(2, 9);
        uLCD.printf("Click Mbed");
        uLCD.locate(2, 10);
        uLCD.printf("Reset Button");
        print_map();
        wait(10000000000);
        
    } else {
            uLCD.locate(0,7);
            uLCD.printf("You WIN!!!!!");
            uLCD.locate(2, 9);
            // Drawing the cover of Madvillany
            draw_basq(39, 39);
            wait(2);
            
            uLCD.printf("Click Mbed");
            uLCD.locate(5, 10);
            uLCD.printf("Reset Button");
            print_map();
            wait(10000000000);
            }
        
}
int loading_dot_count = 0;

/*=============================================================================
                 LOADING SCREEN (Loading MAP screen)
=============================================================================*/

void init_LOADING_SCREEN_map()
{
    //Map *map = set_active_map(6);
    pc.printf("Inside init_LOADING_SCREEN_map() Printting uLCD commands\n----------------------------------------------------\n");
    pc.printf("Player.completed_tasked_in_current_map: ----- %d\n", Player.completed_tasked_in_current_map);
    uLCD.filled_rectangle(0,0,255,255,BLACK);
    uLCD.text_width(1);
    uLCD.text_height(1);
    uLCD.color(GREEN);
    uLCD.textbackground_color(BLACK);
    uLCD.locate(3,7);
    uLCD.printf("LOADING MAP\n");
    for(int ellipses = 0; ellipses < 3; ellipses++) 
    { 
        uLCD.locate(7,8);
        uLCD.printf(".");
        wait(0.33);
        uLCD.locate(7,8);
        uLCD.printf("..");
        wait(0.33);
        uLCD.locate(7,8);
        uLCD.printf("...");
        wait(0.33);
        uLCD.locate(7,8);
        uLCD.printf("....");
        wait(0.33);
        uLCD.locate(7,8);
        uLCD.printf(".....");
        wait(0.33);
        uLCD.locate(7,8);
        uLCD.printf("           ");
        wait(0.33);
    }
    
    
    
    Player.completed_tasked_in_current_map = 1;
    pc.printf("Player.completed_tasked_in_current_map:    %d\n", Player.completed_tasked_in_current_map);
    print_map();
    wait(1);
    pc.printf("EXITING init_LOADING_SCREEN_map() ----- Printting uLCD commands\n");
}



void limbo_portal_coordinates_display()
{
    uLCD.filled_rectangle(0,0,255,255,BLACK);
    uLCD.text_width(1);
    uLCD.text_height(1);
    uLCD.color(GREEN);
    uLCD.textbackground_color(BLACK);
    uLCD.locate(0,0);
    uLCD.printf("Coordinates System: (X, Y)");
    uLCD.locate(3,3);
    uLCD.printf("Home: (X, Y)");
    
    uLCD.locate(3,0);
    uLCD.printf("Home: (X, Y)");
}


//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                                                                   Initializing Maps + MapItems
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Initialize the main world map. Add walls around the edges, interior chambers,
 * and plants in the background so you can see motion. Note: using the similar
 * procedure you can init the secondary map(s).
 */
/*=============================================================================
                            Main MAP  ~ [MAP Index: 0]
 =============================================================================*/
void init_main_map()
{
    //init_START_map();
    
    Map* map = set_active_map(0);
    // "Random" Trees
    for(int i = map_width() + 3; i < map_area(); i += 39)
    {
        //add_plant(i % map_width(), i / map_width());
        add_tree(i % map_width(), i / map_width());
    }
    pc.printf("plants\r\n");
    /*Bounds to the Map
    ----------------------*/
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    add_wall(0,              0,              VERTICAL,   map_height());
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    
    add_mainGate();
    
    // Trees around the NPC and Portal
    for(int j = 15; j<22; j++)
    {
         // Vertical tree Boundaries
         add_tree(15, j);
         add_tree(21, j);
         // Horizontal tree Boundaries
         add_tree(j, 15);
         add_tree(j, 21);
    }
    add_homePortal(19, 18);
    //add_wall(int x, int y, int dir, int len)
    add_npc(17, 18);
    add_treasure(25,3);       // placed within the center of the closed off gates
    pc.printf("Printing MAIN MAP  ~ [MAP Index: 0]\n");
    pc.printf("======================================================\n");
    print_map();
}  

/*==============================================================================
               World Between Worlds (LIMBO) ~ MAP Index: 1
                            (area of lost souls)
==============================================================================*/
void init_LIMBO_map()
{
    // "Random" plants
    Map* map = set_active_map(1);
    /*
    for(int i = map_width() + 3; i < map_area(); i += 39)
    {
        add_plant(i % map_width(), i / map_width());
    }
    pc.printf("plants\r\n");
    */
    /*Bounds to the Map
    ----------------------*/
    pc.printf("Adding walls!\r\n");
    add_limboTree(0,              0,              HORIZONTAL, map_width());
    add_limboTree(0,              map_height()-1, HORIZONTAL, map_width());
    add_limboTree(0,              0,              VERTICAL,   map_height());
    add_limboTree(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    //---------------------------------------
    //       Corners relative to the Portals  
    //---------------------------------------
    add_limboTree(2, 2, HORIZONTAL, 1);
    add_limboTree(8, 8, HORIZONTAL, 1);
    add_limboTree(2, 8, HORIZONTAL, 1);
    add_limboTree(8, 2, HORIZONTAL, 1);
    //------------------
    add_homePortal(5, 2);
    //------------------
    add_martaPortal(8, 5);
    // Posiedon's Portal Color: dark teal ~ blue-green) -> right of the center
    //------------------
    add_posiedonPortal(2, 5);
    //------------------
    add_LIMBO_OLYMPUS_PORTAL(5, 8);
    //ATL-Olympus Portal Color: Orange
    //add_ATL_OLYMPUS_PORTAL(int x, int y);
    //------------------------------------------ 
    pc.printf("Printing World Between Worlds (LIMBO) ~ MAP Index: 1\n");
    pc.printf("======================================================\n");
    print_map();
}

/*==============================================================================
                            MARTA ~ MAP Index: 2
                        ( Map where you meet Hermes )
  ==============================================================================*/
void init_MARTA_map()
{
    // "Random" plants
    Map* map = set_active_map(2);
    
    /*Restricitve Bounds to the Map
    ----------------------*/
    
    pc.printf("Adding walls!\r\n");
    add_pavement(0,              0,              HORIZONTAL, map_width());
    add_pavement(0,              map_height()-1, HORIZONTAL, map_width());
    add_pavement(0,              0,              VERTICAL,   map_height());
    add_pavement(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    
    //add_mainGate();
    // MARTA-LIMBO's Portal Color: Dark green Brown)
    add_TrainCar(1, 1);
    add_martaPortal(1, 3);
    add_MARTA_ATL(13, 3);
    add_Hermes(20, 3);
    pc.printf("Printing MARTA ~ MAP Index: 2\n");
    pc.printf("===========================================\n");
    print_map();
}

/*==============================================================================
                        Poseidon's Bedroom ~ MAP Index: 3
                ( Map where the Player retireves the viels of poision )
  ==============================================================================*/
void init_POSEIDON_BEDROOM_map()
{
    // Initializing HashTable for POSEIDON_BEDROOM_map ~ MAP Index: 3
    Map* map = set_active_map(3);
    
    /*Restricitve Bounds to the Map
    ----------------------*/
    pc.printf("Adding walls!\r\n");
    add_wall(0,              0,              HORIZONTAL, map_width());
    pc.printf("Wall 1 Complete\n---------------------\n");
    add_wall(0,              map_height()-1, HORIZONTAL, map_width());
    pc.printf("Wall 2 Complete\n---------------------\n");
    add_wall(0,              0,              VERTICAL,   map_height());
    pc.printf("Wall 3 Complete\n---------------------\n");
    add_wall(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Wall 4 Complete\n---------------------\n");
    pc.printf("Walls done!\r\n");
    
    // Posiedon's Portal Color: dark teal ~ blue-green)
    add_posiedonPortal(18, 3);
    //adding items within Posiedon's Room
    add_nightStand(1,1); 
    add_bed(7, 1);
    
    pc.printf("Printing Poseidon's Bedroom ~ MAP Index: 3\n");
    pc.printf("===========================================\n");
    print_map();
}

/*==============================================================================
                            Olympus ~ MAP Index: 4
                        ( Map where the Player Kills one )
  ==============================================================================*/
void init_OLYMPUS_map()
{
    // "Random" plants
    Map* map = set_active_map(4);
    /*  Golden Tree Walls
    ------------------------*/
    pc.printf("Adding walls!\r\n");
    add_goldenTree(0,              0,              HORIZONTAL, map_width());
    add_goldenTree(0,              map_height()-1, HORIZONTAL, map_width());
    add_goldenTree(0,              0,              VERTICAL,   map_height());
    add_goldenTree(map_width()-1,  0,              VERTICAL,   map_height());
    pc.printf("Walls done!\r\n");
    //-------------------------------------------------------------------------
    // Adding the River 
    //--------------------
    add_water((map_width()-7), 8, HORIZONTAL, 6 );
    add_water((map_width()-7), 9, HORIZONTAL, 6 );
    add_water((map_width()-7), 10, HORIZONTAL, 6 );
    //-------------------------------------------------------------------------
    // Add MUSE, God butcher
    add_muse(7, 9);
    add_godButcher (10, 6);
    add_LIMBO_OLYMPUS_PORTAL( 5 , 3);
    print_map();
}
/*==============================================================================
                            ATL ~ MAP Index: 5
                        
  ==============================================================================*/
void init_ATL_map()
{
    // "Random" plants
    Map* map = set_active_map(5);
    add_cloud(0, 0);
    //add_triangularGrid(10, 10);
    add_PencilBuilding(4,20);
    add_pavement( 0, map_height() , HORIZONTAL, map_width() );
    //  Add portals for MARTA -> ATL and ATL -> OLYMPUS :
    //  -------------------------------------------------
    add_MARTA_ATL( (map_width() - 1) , (map_height() - 1) );
    add_ATL_OLYMPUS_PORTAL(3, 5);
    add_desk(12,7);
    print_map();
}
//===========================================================================================================================================================================================================
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//===========================================================================================================================================================================================================
/** Load Screen Fucntion:
 *------------------------
 *Description 
 *@param    int release_map_index   ~ map that Player is exiting from and will have ALL the MapItems within it, freed
 *@param    int loading_map_index   ~ map will be set active and have the 
 *
 * Reoccuring comment: |  release_map_index:  _  |   loading_map_index:   _  |
 */

//  |  release_map_index:    |   loading_map_index:      |
int update_delay = 0;
void load_screen(int release_map_index, int loading_map_index)          
{
    //Load Screen then preform all the above mentioned functions
    pc.printf("Screen is loading .....\n");
    init_LOADING_SCREEN_map();
    pc.printf("About to Draw_Game\n");
    //draw_game(FULL_DRAW); // ----------------------------------  
    pc.printf("Draw_Game-------\n");
    /* The following conditional checks to see 
    (1) If you are currently on the map you want to release, which is NOT ALLOWED
    (2) Ensuring that Player is on the Current map index equals the desired loading screen
    (3) result: increments a variable that sets off Leaving the first map.
    */
    pc.printf("Begin Conditional within load_screen()  \n");
    pc.printf("get_active_map(): %d\n",(get_active_map()));
    pc.printf("get_map(release_map_index): %d\n",get_map(release_map_index));
    pc.printf("Condtional 1: %d\n", (get_active_map()) != get_map(release_map_index));
    pc.printf("Condtional 2: %d\n", (Player.completed_tasked_in_current_map) );
    if( (get_active_map()) != get_map(release_map_index) && (Player.completed_tasked_in_current_map) )
    {
        //Should change this to load the map of the next map while waiting for
        // -------------------if( (get_active_map()) == get_map(loading_map_index) ) leave_MAP++;
        pc.printf("runTime_check: %d", runTime_check);
        pc.printf("update_delay: %d", update_delay);
        runTime_check = runTime_counter; 
        pc.printf("Line: 1\n");
        if( runTime_check != 0 )
        {
            pc.printf("update_delay: %d", update_delay);
            update_delay++;
        }
        pc.printf("runTime_check: %d", runTime_check);
        pc.printf("update_delay: %d", update_delay);
        pc.printf("Line: 2\n");
        if(update_delay == 1) // 
        {
            // Update completed task in previous map
            Player.completed_tasked_in_current_map = 0;
            //(1)
            pc.printf("Attemptin to clear MAP: %d\n", get_map(0));
            full_map_erase(release_map_index, loading_map_index);
            ///leave_MAP = 0;
            if( (loading_map_index == 0) && get_map_index() == 0) init_main_map();
            if( (loading_map_index == 1) && get_map_index() == 1) init_LIMBO_map();
            if( (loading_map_index == 2) && get_map_index() == 2) init_MARTA_map();
            if( (loading_map_index == 3) && get_map_index() == 3) init_POSEIDON_BEDROOM_map();
            if( (loading_map_index == 4) && get_map_index() == 4) init_OLYMPUS_map();
            if( (loading_map_index == 5) && get_map_index() == 5) init_ATL_map();
            //draw_game(FULL_DRAW);
            update_delay = 0;
            Player.prev_map = Player.current_map;
            Player.current_map = get_map_index();
            //(2)
            pc.printf("Player.current_map: %d\n", get_map_index());
        }
        init_LOADING_SCREEN_map();
    }   
    pc.printf("End Condtioinal within load_screen() \n");

}




//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
/**
 * Update the game state based on the user action. For example, if the user
 * requests GO_UP, then this function should determine if that is possible by
 * consulting the map, and update the Player position accordingly.
 * 
 * Return values are defined below. FULL_DRAW indicates that for this frame,
 * draw_game should not optimize drawing and should draw every tile, even if
 * the player has not moved.
 */
#define NO_RESULT 0
#define NONE 1
#define FULL_DRAW 2
#define GAME_OVER 3
int update_game(int action)
{
    // Save player previous location before updating
    Player.px = Player.x;
    Player.py = Player.y;
    int prev_prev_X = Player.px;
    int prev_prev_Y = Player.py;

    // Do different things based on the each action.
    // You can define functions like "go_up()" that get called for each case.
    switch(action)
    {
        case GO_UP: 
            if(go_up(Player.x, Player.py)){
                //if(hermes condition satified) add_trailingClouds();
                //pc.printf("Player Location: X~ %d, Y~ %d", Player.x, Player.y);
                //draw_trailingClouds(Player.x, Player.y+1);
                //if add_trailingCloud(trailingCLoud_X, trailingCLoud_Y);
                //handle_trailingClouds();
                return FULL_DRAW;
            } 
            else break;
        case GO_DOWN:
            if(go_down(Player.px, Player.py)){
                return FULL_DRAW;
            } 
            else break;
        case GO_LEFT:
            if(go_west(Player.px, Player.py)){
                return FULL_DRAW;
            } 
            else break;          
        case GO_RIGHT: 
            if(go_east(Player.px, Player.py)){
                return FULL_DRAW;
            } 
            else break;
        case JUMPWORLDS:
            /*  
            */
            if (Player.has_treasure) {
                //set_active_map(2);
                Player.x = Player.y = 8;
                return GAME_OVER;
            }
            
            /*  Using the Shared portal between MAP 0 and MAP 1,
            *   to jump between the two worlds
            *   ------------------------------------------------*/
            if ( (get_here(Player.px, Player.py)->type) == HOME_PORTAL)
            {
                if(get_map_index() == 0)
                { // change get_active_map() == 0
                    // Initialize game state
                    //init_LIMBO_map();
                    set_active_map(1);
                    load_screen(0, 1);  //-------------|  release_map_index:  0  |   loading_map_index:   1   |
                    Player.x = 5;
                    Player.y = 2;
                    return FULL_DRAW;
                }   else if(get_map_index() == 1)
                    { // change get_active_map() == 1
                        //init_main_map();
                        set_active_map(0);
                        load_screen(1, 0);     //-------------|  release_map_index:  1  |   loading_map_index:   0   |
                        Player.x = 19;
                        Player.y = 18;
                        return FULL_DRAW;
                    }
            }
            
            // Traveling between LIMBO and MARTA
            //------------------------------------
            else if ( (get_here(Player.px, Player.py)->type) == MARTA_PORTAL)
            {
                if(get_map_index() == 1)
                { // change get_active_map() == 0
                    // Initialize game state
                    //init_MARTA_map();
                    set_active_map(2);
                    load_screen(1, 2);      //-------------|  release_map_index:  1  |   loading_map_index:   2   |
                    Player.x = 1;
                    Player.y = 3;
                    return FULL_DRAW;
                }   else if(get_map_index() == 2)
                    { // change get_active_map() == 1
                        //init_LIMBO_map();
                        set_active_map(1);
                        load_screen(2, 1);      //-------------|  release_map_index:   2 |   loading_map_index:   1   |
                        Player.x = 8;
                        Player.y = 5;
                        return FULL_DRAW;
                    }
            }
            
            // Traveling between LIMBO and Posedion's bedroom
            //------------------------------------------------
            else if ( (get_here(Player.px, Player.py)->type) == POSIEDON_PORTAL)
            {
                if(get_map_index() == 1)
                { // change get_active_map() == 0
                    // Initialize game state
                    //init_POSEIDON_BEDROOM_map();
                    set_active_map(3);
                    load_screen(1, 3);          //-------------|  release_map_index:  1  |   loading_map_index:   3   |
                    Player.x = 18;
                    Player.y = 3;
                    return FULL_DRAW;
                }   else if(get_map_index() == 3)
                    { // change get_active_map() == 1
                        //init_LIMBO_map();
                        set_active_map(1);
                        load_screen(3,1);       //-------------|  release_map_index:  3  |   loading_map_index:   1   |
                        Player.x = 2;
                        Player.y = 5;
                        return FULL_DRAW;
                    }
            }
            // Traveling between OLYMPUS->LIMBO
            //------------------------------------------------
            else if ( (get_here(Player.px, Player.py)->type) == LIMBO_OLYMPUS_PORTAL)
            {
                if(get_map_index() == 4)
                { // change get_active_map() == 0
                    // Initialize game state
                    set_active_map(1);
                    load_screen(4, 1);      //-------------|  release_map_index:  5  |   loading_map_index:   4   |
                    Player.x = 5;
                    Player.y = 8;
                    return FULL_DRAW;
                }   
                /*
                else if(get_map_index() == 4)
                    { // change get_active_map() == 1
                        set_active_map(1);
                        load_screen(4, 1);      //-------------|  release_map_index:  4  |   loading_map_index:   1   |
                        Player.x = 5;
                        Player.y = 8;
                        return FULL_DRAW;
                    }
                    */
            }
            // Traveling between ATL->OLYMPUS & OLYMPUS->ATL
            //------------------------------------------------
            else if ( (get_here(Player.px, Player.py)->type) == ATL_OLYMPUS_PORTAL)
            {
                if(get_map_index() == 5)
                { // change get_active_map() == 0
                    // Initialize game state
                    set_active_map(4);
                    load_screen(5, 4);      //-------------|  release_map_index:  5 |   loading_map_index:   4   |
                    Player.x = 1;
                    Player.y = 4;
                    return FULL_DRAW;
                }   else if(get_map_index() == 4)
                    { // change get_active_map() == 1
                        set_active_map(5);
                        load_screen(4, 5);      //-------------|  release_map_index:  4  |   loading_map_index:   5   |
                        Player.x = 1;
                        Player.y = 1;
                        return FULL_DRAW;
                    }
            }
            // Traveling between MARTA->ATL and ATL->MARTA
            //------------------------------------------------
            else if ( (get_here(Player.px, Player.py)->type) == MARTA_ATL)
            {
                pc.printf("------@ marta train car--------");
                if(get_map_index() == 2)
                { // change get_active_map() == 0
                    // Initialize game state
                    set_active_map(5);
                    load_screen(2, 5);      //-------------|  release_map_index:  2  |   loading_map_index:   5   |
                    Player.x = map_width()-1;
                    Player.y = map_height()-1;
                    return FULL_DRAW;
                }   else if(get_map_index() == 5)
                    { // change get_active_map() == 1
                        set_active_map(2);
                        Player.x = 13;
                        Player.y = 3;
                        return FULL_DRAW;
                    }
                    
            }
            else break;                
        case ACTION_BUTTON:
            if(lives) {
                return NULL;
                //return FULL_DRAW;
            }
            else break;
        case MENU_BUTTON: 
            if(lives) {
                return NULL;
            }
            else break;
        default:
            break;
    }
    return NO_RESULT;
}





//=================================================================================================================================================================================================================

/**
 * Entry point for frame drawing. This should be called once per iteration of
 * the game loop. This draws all tiles on the screen, followed by the status 
 * bars. Unless init is nonzero, this function will optimize drawing by only 
 * drawing tiles that have changed from the previous frame.
 */
 
void draw_game(int init)
{
    if(init == 3) 
    {
        init_GAMEOVER_map();
    }
    
    
    
    
    // Draw game border first
    if(init) draw_border();
    
    // Iterate over all visible map tiles
    for (int i = -5; i <= 5; i++) // Iterate over columns of tiles
    {
        for (int j = -4; j <= 4; j++) // Iterate over one column of tiles
        {
            // Here, we have a given (i,j)
            
            // Compute the current map (x,y) of this tile
            int x = i + Player.x;
            int y = j + Player.y;
            
            // Compute the previous map (px, py) of this tile
            int px = i + Player.px;
            int py = j + Player.py;
                        
            // Compute u,v coordinates for drawing
            int u = (i+5)*11 + 3;
            int v = (j+4)*11 + 15;
            
            // Figure out what to draw
            DrawFunc draw = NULL;
            if (init && i == 0 && j == 0) // Only draw the player on init
            {
               /* if(player_in_Elevator)
                {
                    uLCD.filled_rectangle(u, v, u+11, v+11, DYELLOW;
                    continue;
                }
                */
                draw_player(u, v, Player.has_key);
                
                continue;
            }
            else if (x >= 0 && y >= 0 && x < map_width() && y < map_height()) // Current (i,j) in the map
            {
                MapItem* curr_item = get_here(x, y);
                MapItem* prev_item = get_here(px, py);
                if (init || curr_item != prev_item) // Only draw if they're different
                {
                    if (curr_item) // There's something here! Draw it
                    {
                        draw = curr_item->draw;
                        //if(curr_item->draw == draw_water) pc.printf("Water is being Drawn----------------------[U, V]:  [%d, %d]\n", u, v);
                    }
                    else // There used to be something, but now there isn't
                    {
                        draw = draw_nothing;
                        if(get_map_index() == 5) draw = draw_lightBlue;
                        if(get_map_index() == 4) draw = draw_grass;
                    }
                }
            }
            else if (init) // If doing a full draw, but we're out of bounds, draw the walls.
            {
                draw = draw_wall;
            }

            // Actually draw the tile
            if (draw) draw(u, v);
        }
    }
    /*
    if(get_map_index() == 1)
    {
        draw_water(3,92);
        draw_water(14,92);
        draw_water(25,92);
        draw_water(36,92);
        draw_water(47,92);
        draw_water(58,92);
    }
    */
    // Draw status bars    
    draw_upper_status(Player.x, Player.y, get_map_index());
    draw_lower_status(lives);
    if(Player.has_godButcher)  draw_godButcher(107, 119);
    if(Player.has_purplePotion) draw_DPurplePotion(70, 119);
    if(Player.has_orangePotion) draw_DOrangePotion(83, 119);
    if(Player.has_Hermes_shoes) draw_hermes(95, 119);
    
    
    // Health Bar
    if(Player.health  == 3) draw_fullHealth(58, 119);
    if(Player.health  == 2) draw_twoThirds_Health(58, 119);
    if(Player.health  == 1) draw_oneThird_Health(58, 119);
    
    
    
    // if player
    // 
}
/*
void Elevator()
{
    // Place this if statement ouside of the function, when calling it duing read inputs in Update game
    if(Player.has_elevator_key)
    {
        //Center of the bottom of the building (get dimesions) -
        
        Player.x = Player.x - 3 // Displaces the X-Position of the Player to the center of the screen
        //Player.y = Player.y -> Y-Coordinante doesn't change
        // Condition: Loop continues as long as the block above Player is not of type GRID
        while( (( get_north(Player.x, Player.y) )->type) != GRID )
        {
            // Incrementally shifts up the Player's Y-Coordinate in relation to the screen -> (up the Center of the Pencil Building)
            Player.y--;
        }
    }
}
*/

void Flood_Poseidons_Room()
{
    //Map *map = get_active_map();
    if (local_wave_timer_START == 0) local_wave_timer_START = runTime_counter;
    if ((local_wave_timer_START%2) != 0) local_wave_timer_START++;
    if (local_wave_timer == 0) local_wave_timer = local_wave_timer_START;
    //for(int i = 0; i<map_height()-5; i++)
    // max runTime of this function will be 60 seconds
    pc.printf("local_wave_timer_START:  %d  | local_wave_timer:  %d\n", local_wave_timer_START, local_wave_timer);
    local_wave_timer++;                                     // Local Timer is synced with the runTime of the while loop in Main
    if( ((local_wave_timer % 6) == 0) && (row > 3) )
    {
        pc.printf("Adding Water Row: (%d, %d)\n-------------------------------------------\n", 1, row);
        pc.printf("\n-------------------------------------------\n");
        //add_water((1), (row), HORIZONTAL, 1 );
        add_water((1), (row), HORIZONTAL, (map_width()-2) ); // Adds waves to each row from the BOTTOM of the MAP -> UP
        pc.printf("Adding water: (%d, %d)\n", 1, row);
        if(row <=14 )  // only have to check 1 block in order ti know that an entire row will be fillled with the same type of block - > WATER Block
        {
            for(int x = 1; x<(map_width()-1); x++)
            {
                map_erase(x, row + 4);
                //print_map();
            }
        }
        row--;     
    }   else if(row == 3)
        {
            speech(RoomFlooded, RoomFlooded);
            lives--;
            set_active_map(1);
            Player.x = Player.y = 5;
            load_screen(3, 1);
            pc.printf("----------\n--------------\n------------\n------------\n-----------\n-------------\n");
            pc.printf("     Diagnostic Check: \n------------------------\n");
            pc.printf("Lives: %d\n");
            Player.has_purplePotion = 0;
            Player.has_orangePotion = 0;
            pc.printf(" Player.has  --- Purple Potion: %d\n", Player.has_purplePotion);
            pc.printf(" Player.has  --- Purple Potion: %d\n", Player.has_orangePotion);
            pc.printf("----------\n--------------\n------------\n------------\n-----------\n-------------\n");
            //draw_game(FULL_DRAW);
            row = 18;
            if (lives == 0) draw_game(GAME_OVER); // ~ Essentially the same as draw_game(GAME_OVER) -> issue: GAME_OVER isn't #defined till later in th ecod

        }
    /*                                          // Translates to shifting the row up by 1 for the next itteration
    if (row == map_height()-5))
    {
        // lose a life and sent back to LIMBO which re-initalizes the map
        set_active_map(1);
        Player.has_purplePotion = 0;
        Player.has_orangePotion = 0;
        draw_game(FULL_DRAW);
        init_POSEIDON_BEDROOM_map();
        //Player.has
        //break;      
    }
    while(local_wave_timer<(local_wave_timer_START + 60))       //
    {
        
    }-----------------------------------------------------------------------------------------------------------------------------------------------------------------
    */
}


int map_switch1 = 0;

/*


*/


/*
int runTime_counter = 0;
int runTime_check = 0;
int check = 0;
int shift =0;
int leave_MAP0 =0;
int leave_MAP1 =0;
int leave_MAP2 =0;
int leave_MAP3 =0;
int TOP_lostSouls__move = 0;
int BOTTOM_lostSouls__move = 29;
int lostSouls__move = 1;
int direction = 1;
int LEFT_lostSouls__move = 1;
int RIGHT_lostSouls__move = 17;
*/

/*==============================================================================
 *------------------------------------------------------------------------------
 *                              MAIN Function
 *------------------------------------------------------------------------------
  ==============================================================================*/
/**
 * Program entry point! This is where it all begins.
 * This function orchestrates all the parts of the game. Most of your
 * implementation should be elsewhere - this holds the game loop, and should
 * read like a road map for the rest of the code.
 */
int main()
{
    // First things first: initialize hardware
    ASSERT_P(hardware_init() == ERROR_NONE, "Hardware init failed!");
    //uLCD.filled_rectangle(64, 64, 74, 74, RED); //DELETE OR COMMENT THIS LINE
    //-------------------------------------------------------
    // Keep track of how long it takes to complete the game
    //-------------------------------------------------------
    //Timer runTime; runTime.start();
    
    
    /* Initial Debugging Setup
    while(1) {
        pc.printf("This is a Serial Port test!\r\n");
        wait(1);
    }*/
    
    //<------ DELETE THIS LINE
    pc.printf("Initialize the maps\n");
    // Initialize the maps
    //----------------------
    maps_init();
    init_START_map();
    init_main_map();
    //init_LIMBO_map();
    //init_POSEIDON_BEDROOM_map();
    //init_MARTA_map();
    //init_ATL_map();
    /*
    
    char* extraSpace = 0x2007C000;
    my_item* items = (my_item*)extraSpace;
    items[1] = 
    my_item* items2 = (my_item*)(extraSpace + sizeof(my_item) * 1000);
    
    init_POSEIDON_BEDROOM_map();
    init_OLYMPUS_map();
    init_ATL_map();
    
    */
    pc.printf("==========================Initialize game state===============================\n");
    // Initialize game state
    set_active_map(0);
    /* Initilizing the Player Struct Variables
    --------------------------------------------*/
    Player.has_key = 0;
    Player.mission_given_by_NPC = 0;
    Player.has_slain_beast = 0;
    Player.ApollosCongrats = 0;
    
    Player.has_treasure = 0;
    // Displayed on the Lower Status Bar once complete
    Player.has_purplePotion = 0;
    Player.has_orangePotion = 0;
    // MAP 5 ~ feature
    
    Player.mission_given_by_HERMES = 0;
    Player.has_Hermes_shoes = 0;
    Player.has_godButcher = 0;
    Player.health = 3;
    Player.muse_health = 3;
    Player.throwPotion = 0;
    // Initializing players location on the map
    Player.x = Player.y = 15;
    //--------------------------------------
    lostSouls__move = 1;
    direction = 1;
    Player.current_map = get_map_index();
    //============================
    // Initilaizing Checkpoints
    //============================
    Player.checkpoint_1 = 0;
    Player.checkpoint_2 = 0;
    Player.checkpoint_3 = 0;
    Player.checkpoint_4 = 0;
    Player.checkpoint_5 = 0;
    Player.checkpoint_6 = 0;
    Player.checkpoint_7 = 0;
    Player.checkpoint_8 = 0;
    Player.checkpoint_9 = 0;
    Player.checkpoint_10 = 0;
    Player.checkpoint_11 = 0;    
    //=============================
        
    pc.printf("Initial drawing\n");
    // Initial drawing3
    draw_game(FULL_DRAW);
    pc.printf("Main game loop\n----------------------\n");
    // Main game loop
    while(1)
    {
        //W
        if( get_active_map() == get_map(1) ) update_soulPosition();
        if(get_map_index() == 3) Flood_Poseidons_Room();
        if( (get_map_index() == 5) && (Player.has_Hermes_shoes) )  handle_trailingClouds();
        if (lives == 0) draw_game(GAME_OVER); 
        if( (get_map_index() == 5) ) muse_damage();
        /*
        if( (get_south(Player.px, Player.py)->type == COLORBLOCKS) && (get_map_index() == 4) && !(Player.throwPotion) )   
        {
            speech(throwPotions,throwPotions);   // The waves are the only Color blocks in the 4th map in Olympus
            Player.throwPotion = 1;
        }
        */
        
        pc.printf("Run Time: %d\n", runTime_counter);
        runTime_counter++;
        
        // Timer to measure game update speed
        Timer t; t.start();
        Timer dementor_movements; dementor_movements.start();
        // Actually do the game update:
        // 1. Read inputs
        //pc.printf("about to read inputs\n");        
        reading_inputs = read_inputs();
        //pc.printf("read inputs\n");        
        // 2. Determine action (get_action)    
        action =  get_action(reading_inputs); 
        // 3. Update game (update_game)
        update = update_game(action); 
        // 3b. Check for game over
        // 4. Draw frame (draw_game)
        draw_game(update);
        // -----UNCOMMENT THIS  LATER ----->  
        draw_game(true);
        
        // 5. Frame delay
        t.stop();
        dementor_movements.stop();
        int dt = t.read_ms();
        int walkdt = t.read_ms();
        
        
        
        if (dt < 100) wait_ms(100 - dt);
        //pc.printf("Completed loop\n----------------------\n");
    }
  //DELETE THIS LINE  -----> 
}
