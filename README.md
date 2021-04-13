# Tetris

## The project
Tetris (tetmatch) is a small tetris clone that is built for the raspberry pi.
It provides full controller support and allows more than one player to simultaneously play.
It gives each player the exact same pieces in the exact same order so that they may play a fair match againt each other.

## Dependencies
SFML (Simple Fast Multimedia Library):
	Used for graphical output as well as controller input
	Installation for Linux (Debian/Ubuntu):	```sudo apt-get install libsfml-dev```
	For other operating systems use the 'Getting Started' section of the officials [docs](https://www.sfml-dev.org/tutorials/2.5/).
	
The Diskopia font:
	I do not own this asset, it can be found [here](https://www.dafont.com/diskopia.font).
	Without this placed in the correct path the fonts won't load properly.
	The absolute path is used so find the definition of `DISKOPIAPATH` in `main.cpp` and `tetris.cpp` and change it to the path of your Diskopia font.
	
## Building the project
First you need to download the project:
	`git clone https://github.com/Arithmetic-Overflow/Tetris.git`

Next you need to run make twice, from the project directory run the following commands:
	`make`
	`cd tetrisexe`
	`make`
	
This will build two executables: both are needed for this program.

## Running the project
under the root directory of the project after building run `./tetmatch`
This will begin an instance of the game.

## Playing the game
In order to actually play this game you will need at least 1 controller.
The controls might vary across different input devices, but should be the equivalent of the following on DualShock3 controllers and xbox360 controllers:

#### Menu controls:
	A confirm selection
	B exit selection
	Left (d-pad) decrease selection
	Right (d-pad) increase selection
	Up (d-pad) change selection
	Down (d-pad) change selection
	
#### In-game controls:
	A clockwise rotation
	B anticlockwise rotation
	Left (d-pad) move your piece left
	Right (d-pad) move your piece right
	Down (d-pad) drop piece quickly
	
## Limitations
* There is currently no keyboard/mouse support.
* 'Kicks' (a feature present in tetris) are not implemented
* There is no communication between threads so instances of the game have no knowledge of each other's state
