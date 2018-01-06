/*
* tictactoe.c
*
* Created: 25-05-2017 15:23:00
*  Author: T420s
*/
#include <stdint.h>
#include <stdbool.h>
#include "tictactoe.h"

//------------------------------------------------

static uint8_t goUp(uint8_t selected_field)
{
	if (selected_field > 2) 
	{
		selected_field -= 3;
	}
	return selected_field;
}

static uint8_t goDown(uint8_t selected_field)
{
	if (selected_field <= 5) 
	{
		selected_field += 3;
	}
	return selected_field;
}

static uint8_t goLeft(uint8_t selected_field)
{
	if (selected_field % 3 != 0) 
	{
		selected_field--;
	}
	return selected_field;
}

static uint8_t goRight(uint8_t selected_field)
{
	if ((selected_field - 2) % 3 != 0)
	{
		selected_field++;
	}
	return selected_field;
}

uint8_t navigate(char direction, uint8_t selected_field)
{
	switch(direction)
	{
		case 'U':
			selected_field = goUp(selected_field);
			break;
		case 'R':
			selected_field = goRight(selected_field);
			break;
		case 'D':
			selected_field = goDown(selected_field);
			break;
		case 'L':
			selected_field = goLeft(selected_field);
			break;
		default:
		break;
	}
	return selected_field;
}

//------------------------------------------------

static bool has_won(char mark, char* fields)
{
	
	//diagonal
	if ((fields[0] == mark && fields[4] == mark && fields[8] == mark)||
	(fields[2] == mark && fields[4] == mark && fields[6] == mark)||
	//vertical
	(fields[0] == mark && fields[1] == mark && fields[2] == mark)||
	(fields[3] == mark && fields[4] == mark && fields[5] == mark)||
	(fields[6] == mark && fields[7] == mark && fields[8] == mark)||
	//horizontal
	(fields[0] == mark && fields[3] == mark && fields[6] == mark)||
	(fields[1] == mark && fields[4] == mark && fields[7] == mark)||
	(fields[2] == mark && fields[5] == mark && fields[8] == mark))
	return true;
	//else
	return false;
	
}

static bool draw(uint8_t available_fields)
{
	available_fields--;
	if(available_fields == 0)
	{
		return true;
	}
	return false;
}

int insert_mark(char mark, uint8_t selected_field, char* tictactoe_array, uint8_t available_fields)
{		
	if (tictactoe_array[selected_field] != 'X' || tictactoe_array[selected_field] != 'O')
	{
		tictactoe_array[selected_field] = mark;
		//mark placed, check if end of game
		if (has_won(mark, tictactoe_array))
		{
			//player is winner
			if(mark == 'X')
			{
				return 1;
			}
			else if (mark == 'O')
			{
				return 2;
			}
		}
		else if(draw(available_fields))
		{
			return 3;
		}
	}
	return 0;
}