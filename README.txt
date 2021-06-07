

- 1.01 -

The assignment for this version was to generate a dungeon with the following specs:
1. Size of 80x21
2. At least 5 rooms of min size 3x2
3. Paths leading to all the rooms i.e 1-(n-1)
4. Print the dungeon

 //Methods - only the important ones

make_rooms() -
this method has two helper placable() and place() to complete.
This method use the rand function to randomly pick the x,y and the width and height of the new room.
It runs through the dungeon[][] and places the room accordingly.

connect() -
this method connects each room to one another. 1 to n-1.
Uses a for loop to cycle through the rooms[][] array, where the room details are stored
then determines the path using the mid point of the room i.e x+height/2, y+width/2. It then cycles through
the dungeon[][] array and place the # iff dungeon[x][y] != '.'//room

main() -
sedding srand() here so we can use the rand() function.



- 1.02 -

This assignment asked us to implement a save and load routine. This was done using switches the user passed
when running the exec file. Example usage:
    1. .exec_name
    2. ./exec_name --load
    3. ./exec_name --save
    4. ./exec_name --load --save or --save --load
These switches can be repeated any amount of times and the order of the switches do not matter. It always loads
then saves or just the respective switched individually.

The path it loads and saves to is home/net-id/.rlg327/dungeon. Loading the dungeon will read the file and parse info
using the byte data that we were given in the assignment spec. Makes use of BigEndian, uint32_t and uint8_t.

//Methods - the new ones

load() -
Has no depedant methods. Uses the FILE system to open and read information with the "r" tag to open it in read mode.
Parses the information byte by byte and progressively places data in their respective fields. For a field varialbes,
it converts from BigEndian to an unsigned integer.

save()-
Has no depedant methods. Again uses the FILE systme to open and write information. If the file is not present in the
directory, it makes it. Converts all the dungeon data byte by byte and writes them to the file. In this case, it converts
from an unsigned integer to BigEndian format for a few varialbes. By defualt, the PC is places in the x,y co-ordinates of
the first room.


- 1.03 -

In the interest of saving time, I have chosen to use Professor Jeremey's code in order to save my self of change my code to
use structs.
This assignment asked us to implement Dijkstra's algorithm using a heap in order to calculate the distance from all points
to the PC. This will be used by both tunneling and non-tunneling monsters to move towards the PC.

//Methods - the new ones

dijsktra_non_tunnel() -
This method is used to calculate the distance to the PC if and only if (iff) the hardness of the the current map position
is either a room or a corridor (hardness 0).

dijkstra_tunnel() -
This method is used to calculate the distance from all position in the map to PC excluding the immutable wall.

Both methods pick the shortest paths.

- 1.04 -

Since I was not confident about splitting up my files, I decided to stick with my 1.03 code and modify that.
This week we were made to implement the PC and NPC characters and also run a discrete event simulator on the same.
The main method accepts a new switch called "--nummon *integer*". This allows the user to select the number of NPC
characters there are in the game.

//Methods - the new ones

generate_monsters() -
Generates the specified number of monsters and sets each attribute of the monster.

generate_move() -
Generate the next move based of the attributes of the NPC (monster) and also adds the monster to the heap
to run the game.

main() -
The main method got the biggest overhaul. This is now responsible for running the game based on the methods Jeremy
showed us in class (turn value based). This uses a priority queue and compares the turn value of each monster.

There are many more new methods but they are insignificant.


- 1.05 -

Uses Jeremy's code base. NOTE: There is a one second delay when pressing the ESC key when using monster_list().

//Methods - new only

input_move() - responsible for taking in input and do each of the functions. Uses the helper functions.

monster_list() - makes an array of all the monsters in the dungeon and prints them in a string with the
	       	 relative position to PC.

main() - Stops simulating the game and now uses ncurses to listen for input.


//imports

1. ncurses.h
2. curses.h //Just in case. Not actually used.


- 1.06 -

Uses Jeremey's code base for 1.05. Converted all code to c++ and implemented fog of war, a limited view field
for the player to make things more challenging. Also adds support abilities for the player. Those are:

  1. Targeted teleportation.
  2. Random teleportation.

NOTE: Usage!

 -- press g to enter Teleport Mode.
  ++ use navigation keys move targeter (*)
    >> use g to teleport to pointer
                or
  ++ use r to teleport to random (x,y) co-ordinates.


//Methods - most important

io_teleport_pc() - drives the input and also teleports pc.

io_display() - displays the limited FOV and also sets the pc_known array.


- 1.07 -

NOTE: The game does not run anymore. Just parsing the monster_desc.txt for this assignment.
NOTE: I'm lazy ¯\_(ツ)_/¯ Aren't we all??

Loads the monster_desc.txt from the home directory. It's inside the .rlg327 hidden folder.
Output is all the parsed text. For the dice class, I don't print output but it stores the values of base, dice, and sides.

//Methods - important ones only

parsemonsters() - parses the txt file using getline() and substr() and compare. Also does all the checks as per the assignment.

set_dice() - Inside the dice class. Splices the given string into substrings and uses atoi() to convert to int32_t and uint32_t

- 1.08 -

NOTE: Using Jeremy's code drop.

parses monster and object defenitions and loads them on to the map. No functionality for objects yet. Also displays everything in color!

//Methods - important only

gen_monsters() - Uses vectors and class monster_description to generate monsters. Works according to spec.

gen_object() - Uses vectors and class object_description to generate objects. Works according to spec.


- 1.09 -

NOTE: Compile using fedora 23, provided by prof. Jeremy.

This implements a proper combat system also with player inventories for equiped and uneqiped items.
Also implemented is Object and Monster inspection that shows the descriptions of those.

NOTE: includes one new .cpp file that is objectequip.cpp, contains all the new moethods except monster list.
That is implemented in io.cpp. Apart from that move.cpp has accomadated for the new combat mecs.

The PC picks up objects one by one from a stack leaving the next object in place. else it switches it to a dungeon
floor. You can drop multiple objects in the same place essentially stacking them. Wearing objects also Works
as per the specs. expunging and item makes sure it is not generated again. Listing inventories also Works.
You can also view the descriptions of monsters using L and inspect the description of items with I.



- 1.10-
