/*
 * display_task.c
 *
 * Created: 31-05-2017 14:48:27
 *  Author: T420s
 */ 

 #include "display_task.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


#include <avr/io.h>

// FreeRTOS Includes
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <queue.h>
#include <semphr.h>

#include "../board/board.h"
#include "../game/led_controll.h"
#include "../../structs.h"

static uint16_t * frame_buf;
static char * tictactoe_array;
SemaphoreHandle_t mutex_tictactoe;

void display_task(void *pvParameters)
{

	#if (configUSE_APPLICATION_TASK_TAG == 1)
	// Set task no to be used for tracing with R2R-Network
	vTaskSetApplicationTaskTag( NULL, ( void * ) 5 );
	#endif

	display_task_parameters_t *task_parameters = pvParameters;
	frame_buf = task_parameters->frame_buf;
	tictactoe_array = task_parameters->tictactoe_array;	
	mutex_tictactoe = task_parameters->mutex_tictactoe;	

	while(1)
	{	
		if( xSemaphoreTake( mutex_tictactoe, ( TickType_t ) 10 ) == pdTRUE )
		{
			display_tic_tac_toe(tictactoe_array, frame_buf);
			xSemaphoreGive( mutex_tictactoe );
		}		
		vTaskDelay(100);
	}
}