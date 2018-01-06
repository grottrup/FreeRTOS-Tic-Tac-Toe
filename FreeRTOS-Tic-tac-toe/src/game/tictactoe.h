/*
 * tictactoe.h
 *
 * Created: 25-05-2017 14:01:48
 *  Author: T420s
 */ 

 #include <stdio.h>
 #include <stdint.h>

 /**
 * \brief when navigating you change which tic-tac-toe field is selected.
 * \param uint8_t direction indicates whether to navigate up, down, left or right
 * \param uint8_t selected_field is the field you current
 */
 uint8_t navigate(char direction,  uint8_t selected_field);

 /**
 * \brief insert a tic-tac-toe mark on the selected field if it is available.
 * \param char mark indicates the mark of the player. Player 1 will be using 'X' and Player 2 will be using 'O'.
 * \param uint8_t selected_field is the field which the mark will be inserted on
 * \param char* tictactoe_array holds all the fields and which marks that have been inserted where.
 * \param uint8_t available_fields how many fields are still available for inserting marks
 * \return state of the game. this indicates whether the game is ongoing (return 0), player 1 won (return 1), player 2 won (return 2) or a draw (return 3)
 */
 int insert_mark(char mark, uint8_t selected_field, char* tictactoe_array, uint8_t available_fields);