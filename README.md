# C_CPP_RPG-Quest-Game_Academic-Project-

GT ECE 2035 (Programming for Hardware and Software Systems) Quest MMXXI FEATURE CHECKLIST

Student Name: ___Christopher Semali___

## Link to Youtube Video showcasing the Video-Game Demo: 
		
[YouTube Video of Gameplay](https://youtu.be/spUeAvs4yvg)

## Sprite 2D Graphics Designs

## BASIC GAME FUNCTIONALITY 

- [x]  Accelerometer moves the player

- [x]  Walls block character motion

- [x]  Omnipotent mode button walks through walls

- [x]  The first Map must be bigger than the screen (at least 50*50 tiles)

- [x]  Stairs/ladders/portals/the door go between the first and the second map. 

- [x]  More than 1 spell to choose from to fight the monster (you use the Godbuthcer (a sword) to kill the final Boss)

- [x]  Dialogue box presents when casting a spell 

- [x]  Quest works (key & door work)

- [x]  Display Game Over when quest complete

- [x]  Status bar shows player coordinates

- [x]  Speech bubbles used in the quest

- [x]  Art includes at least one sprite

---
## EXTRA FEATURES (choose up to 10):    	
* I made over 10 Advanced Features, which Prof. Wills checked off during office hours

- [x]  Add a start page 

- [ ]  Sound effects for interactions/background music 

- [x]  Different modes of locomotion (e.g., running, hopping, etc. ) They should be visually distinctive.
  * Trailing Clouds

- [x]  Animation for interactions with things on the map
  * Waves Flooding Poesidon's Room in the Third Map Present

- [ ]  In-game menu: 
* Save the game 
* Show status information 
* Configuration (Accelerometer direction, which button is which, etc.) 

- [x]  In-game inventory with useable items
  * Bottom Panel alongside the Lower Status bar

- [x]  Multiple lives and the possibility of loss:       
  * Health & stuff that hurts you. 
  * indicated with both the lower Status bar w/ Live: # and the Health bar to the right of "#" (the number of remaining lives the player has) 

- [x]  Mobile (walking) NPCs or monsters.
  * Lost Souls (x4) in Limbo map (World Between Worlds)

- [ ]  Save the game (persistent over power-off) 

- [ ]  Bigger objects in the map that blocks the character.
  * A very tall tree that hides the character. 
  * A feature you can walk behind/under such as a bridge. 

- [x]  Multiple enemies to defeat
  * Lost Souls and Muse, but the Muse is the main one, that needs to be defeated in order to complete the quest
  * User can complete the game without killing lost souls ( but they can deal damage to you whenever they pass through you)

- [ ]  Throwable combat items  
  * Animated dagger/spells 

- [x]  Turn-based combat menus 

- [ ]  Side profile for combat (think of Pokemon games combat sequences): will likely require the use of an SD card reader. 

---
## Other: (please describe)
- [x]  More than 5 sprites

- [x]  More than 5 maps

- [ ]  (5 Characters including, the main player, who are incorporated into the Storyline)
	* Cast: 
		* Player: Jean Micheal Basquiat (Player Icon is a low*resolution Pixel representation of the book cover of the 40th anniversary of the Taschen book which has a compilation of all his works
		* NPC 1: Dimitrios, God of Art, Craftsmanship, and Illusions
		* NPC 2: Lost Souls, in the Limbo map (Map with multiple portals)
		* NPC 3: Hermes, Messanger God 
		* NPC 4: Muse, didn't specify which of the 7


- [x]  Different GAME-OVER loading screens (One for if you lose all of your lives | The other for if you complete the Game and receive the Treasure ~ also has a 50x50 pixel Image drawn onto the screen)
	* 50x50 pixel Image of MF Doom, which is the Cover art on the album  Madvillany 
	* Image had to be manually converted from uint32_t (represented in hex) -> int (16-bit represented in hex) ~ also does not rely on using a char array, due to the number of different shades used.
	* In the future, I want to develop a Python script that does this conversion for me, saving time.

- [x] LOADING-SCREEN, which is queued when switching maps
	* (1) Contains an Animation with the loading ellipsis (and holds the loading screen display while (2) occurs)
	* (2) Backend of Loading Screen: Clears out all of the Map items within the previous map, then sets and Initializes the next map 
	* (3) Purpose of Development: to optimize the amount of allocated space being used within the game, 
		since previously it is not possible to initialize all maps simultaneously, due to the sheer number of MapItems present within each local map.
	* () It was my simpler alternative, to manually allocate memory within the 32 GB section of the mBed, which was mentioned by Daniel Cooper, in the ECE 2035 groupme,
		or having to employ the SD Card, and then within the SD card after use

- [ ] Multiple NPC's / Quests bestowed ~ (1) Dimitrios - overarching mission is to kill the muse (2) Hermes to retrieve God Butcher (a sword the Muse stole from him, however video does not show the return of the sword)

- [ ] There are other features that may or may not count as advanced but this is what I recall getting checked off, and is already around the 10 mark. 
