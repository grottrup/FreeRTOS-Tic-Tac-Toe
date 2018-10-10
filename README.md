% Tic-tac-toe Console Game

# Introduction

Project's goal is to deliver a complete functional tic-tac-toe game based on a Game Console
which will be connected with a PC and they will be able to play a game session between
each other. The PC should be able receive and print out statistics from the GC
which will contain the winner for the current game session.
Following chapters include all technical aspects of analysis, design and implementation.
Tic-tac-toe (also known as Xs and Os) is a paper-and-pencil game for two players, X and
O, who take turns marking the spaces in a 3×3 grid. The player who succeeds in placing
three of their marks in a horizontal, vertical, or diagonal row wins the game.
The game console user will be 'Player 1' and the PC user will be 'Player 2'.

# Analysis

## Plan for collecting data for the setup of requirements and testing
### Requirements
The costumer (the project supervisors) has already given well defined
requirements. Therefore what is left is to define the game of the desired behavior for
that.

### Physical specifications
Investigation of the Game Console this includes:

* Display specifications, the limitations it causes and how to control it
* COM ports. At what rate can it be communicated between the Game Console
and the computer? Any limitations due to this?
* Joystick specifications, the limitations it causes and how to control it

This can be investigated by use of datasheets for the Game Console

### Real time operating systems for embedded devices
* Investigate the API for FreeRTOS
* Determine which kind of scheduling to use for the system

### Resource protection and process communication
* Investigate mutexes and semephores
* Communication protocols Determine the protocol of handling communication and data
loss

### Error detection
* Compare different types of error detection and select the most appropriate

### Testing
* Investigate CppUTest
* Determine the requirements and functionalities. Write rules for the system.
* Test whether the system forfills these rules. Either by TDD or black box testing.

## Requirements
The following list of requirement have been set up according the given requirements for
the project as well as what should be expected for a tic-tac-toe game such as the one
described in the introduction.

### Priotised functional requirements
1. The Game Console LED display must show where the players inserted their marks.
2. It must be possible to choose where to insert a mark.
3. A winner must be selected when a player has 3 marks vertically, horizontally or diagonally.
4. After a completed game session, the players should have an option to start a new game.
5. The result of a game session must be shown on the PC application.
6. Only one player at a time may be able to insert tictac-toe marks. Meaning the game must be
turn based.
7. The result of the game must be a draw if there are no fields without marks left and if there is no
winner.
8. It should possible to see which field the current player has selected on the PC application.

### Environment requirement
* Context of use
  * Player 2 should be able to interact with game using the keyboard of a PC.
  * Player 1 should be able to interact with the game with a joystick.
* Technologies
  * All game logic must be in the software running on the Game Console.
  * The software for the system should be written using C-programming. The system must
have a PC application.
  * The Game Console and the PC must connect through a Serial USB cable.

### Usability and other non-functional requirements
This is meant to be a prototype for demonstration of the achievement of the restriction of the temporal
requirements. The marketbility of the product is irrelevant for the scope of the project. However, it is
possible to imagine this product being a prototype for a cheap game console. In this case the target
group would be hobbyists and children.

* The tic-tac-toe game must consist of a 3x3 fields.
* The marks of Player 1 and Player 2 should be distinct.
* It should ta ke 0.25 seconds from a player pressing the button to insert a tic-tac-toe mark to it b
eing updated inside the game logic. This means that it is okay that it will take a bit longer
before the action is displayed, but there should from pressing the joystick button till updating
the data regarding the what is stored about the tic-tac-toe marks take less than 0.25 seconds.
* The light of the LEDs of the Dot-Matrix display should appear stable to the human eye.

### Delimitations
* The system will not allow the players to undo placed marks.
* The system will not have an option to select who will have the first turn. The player on the
Game Console (Player 1) will always have the first turn.

# Design
## Tasks
The planned behaviour of the system was analysed and processed it was divided into two groups: 
* The tasks, tagged with (HRT) are hard real time, meaning their deadlines can never be
 missed. 
* Those with the (SRT) tag are soft real time – missing their deadlines is deemed notimportant.

### GC Tasks
* Joystick: The Game Console must regularly handle input from the Joystick.(HRT)
* GC communication: The Game Console must regularly receive messages from the PC.
The Game Console must also occasionally update the PC application with
information of selected fields and results of the tic-tac-toe game.(HRT)
* Logic: The Game Console must act on input and received messages within a short
time interval. The purpose is to update the state of the tic-tac-toe game. (HRT)
* Display: The Game Console must be able change what the LEDs should display, per
updates of the state of the game, within a short time interval. (SRT) 

### PC Tasks
* PC communication: Send and receive information through the connection to the
Game Console. (HRT)
* Keyboard: Receive input from the PC keyboard. (HRT)
* View: Show information on the PC screen. (SRT)

---

Clean writing the rest of the report...

Ideally I would like to convert this to LaTex
