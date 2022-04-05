#include "speech.h"
//#include "graphics.h"
#include "globals.h"
#include "hardware.h"

GameInputs inputs;
Timer speechTimer;
const char* line_ptr;
int toggle = 0;
/**
 * Draw the speech bubble background.
 * Use this file to draw speech bubbles, look at the uLCD libraries for printing
 * text to the uLCD (see graphics.cpp note for link)
 */
static void draw_speech_bubble();

/**
 * Erase the speech bubble.
 */
static void erase_speech_bubble();

/**
 * Draw a single line of the speech bubble.
 * @param line The text to display
 * @param which If TOP, the first line; if BOTTOM, the second line.
 */
#define TOP    0 // Lines will be printed onto uLCD.locate(1,12)
#define BOTTOM 1 // Lines will be printed onto uLCD.locate(1,13)

static void draw_speech_line(const char* line, int which);

/**
 * Delay until it is time to scroll.
 */
static void speech_bubble_wait();





void draw_speech_bubble()
{
    uLCD.filled_rectangle(0, 113 , 128, 93, BLACK);
    uLCD.filled_rectangle(0,    93, 128,  94, 0x8282ff); 
    uLCD.filled_rectangle(0,   113, 128, 112, 0x8282ff); 
    uLCD.filled_rectangle(0,    113,   1, 93, 0x8282ff);
    uLCD.filled_rectangle(128,  113, 126, 93, 0x8282ff);   
}

void erase_speech_bubble()
{
    uLCD.filled_rectangle(0,    93, 128,  94, BLACK); 
    uLCD.filled_rectangle(0,   113, 128, 112, BLACK); 
    uLCD.filled_rectangle(0,    113,   1, 93, BLACK);
    uLCD.filled_rectangle(128,  113, 126, 93, BLACK);
}

void draw_speech_line(const char* line, int which)
{
    uLCD.text_bold(TEXTBOLD);
    uLCD.textbackground_color(0xAAA3AB);
    uLCD.color(WHITE);
    const char* space = " ";
    int len = strlen(line);
    int charIndex = 0;
    // While the line pointer still points to a Chracter wihtin the String ~ (Array of Characters)
    while (*line)
    {
        // Draw the box border at the bottom of the screen, which 
        //encloses the area where the charcters will be printed
        // DELETE since this is already being called in both speech and draw_speech_bubble();
        if( which == TOP ){
            uLCD.locate(1,12);
            charIndex = 0;
        } 
        while(charIndex<17 && *line) {
            if (charIndex == 0) {
                uLCD.text_bold(TEXTBOLD);
                if (*line == *space) {
                    charIndex++;
                    line++;
                    continue;
                }
            }
            uLCD.printf("%c", *line);
            wait_ms(50);
            // Increment the bottom charcter index of the Array of 17 Characters ~ String
            charIndex++;
            // 
            line++;
        }
        if ( which == TOP){ // which == BOTTOM
            uLCD.locate(1,13);
            charIndex = 0;
             //speech_bubble_wait();
        }
        while(charIndex<17 && *line) {
            if (charIndex == 0) {
                uLCD.text_bold(TEXTBOLD);
                if (*line == *space) {
                    charIndex++;
                    line++;
                    continue;
                }
            }
            uLCD.printf("%c", *line);
            //wait_ms(50);
            // Increment the bottom charcter index of the Array of 17 Characters ~ String
            charIndex++;
            // 
            line++;
        }
        // -----------------keep in speech_bubble wait-------------------
        speech_bubble_wait();
    }
    
    
}

void speech_bubble_wait()
{  
    speechTimer.start();
    int timePass;

    do {
        // wait until ~1.5 seconds pass before being able to remove
        inputs = read_inputs();
        timePass = speechTimer.read_ms();
        
        
        wait_ms(200);   // wait 200 ms = 0.2s
        // Toggle is intially set = 0, t
        toggle = !toggle; 
        /* 
        CONDITIONAL: sets up the flashing Black and Red, circle in the 
        lower right corner of the speech text box.
        [ Red Circle ]-> toggle = 1
        -------------
        ~ indicating not ready to recieve input 
        [ Black Circle ]-> toggle = 0 
        ---------------
        ~ indicating ready to recieve an input after a sufficient time,
        to queue the next lines within the charc Array (sentence);
        */
        if (toggle) {
            uLCD.filled_circle(120,121,4,RED);
        } else {
            uLCD.filled_circle(120,121,4,BLACK);
        }
        inputs = read_inputs();
    } while(inputs.b1 || !(timePass > 300 && !inputs.b1));      // 
    // After sufficient Time has passed then just display a [ Black circle ]
    // {----Player is ready to continue with the rest of the game-----}
    uLCD.filled_circle(120,121,4,BLACK);
    return;
}
#define DPURPLE 0x6C426E // dark purple: P
#define VDGRAY 0x78807A  // very dark gray: 5
void speech(const char* line1, const char* line2)
{
    draw_speech_bubble();
    draw_speech_line(line1, TOP);
    //draw_speech_line(line2, BOTTOM);
    //speech_bubble_wait();
    erase_speech_bubble();
    uLCD.filled_circle(120,121,3, GREEN);
}

void long_speech(const char* lines[], int n)
{
    int num_lines;
    int count = 0;
    draw_speech_bubble();
    // MAIN LOOP
    //===============================================
    for(num_lines = 0; num_lines < n; num_lines++) {
        line_ptr = lines[num_lines];
        while(*line_ptr){
            draw_speech_line(line_ptr, TOP);
            draw_speech_line(line_ptr, BOTTOM);
            speech_bubble_wait();
        }
    }
    uLCD.filled_circle(120,121,3, GREEN);
}
