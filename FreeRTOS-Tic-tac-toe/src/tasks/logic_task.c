/*
* logic_task.c
*
* Created: 30-05-2017 20:31:11
*  Author: T420s
*/

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
#include "../game/tictactoe.h"
#include "../../structs.h"

#define NON_BLOCKING 0
#define LOGIC_BUFFER_SIZE 4
#define  FIELDS

static QueueHandle_t * joystick_input_queue;
static char * tictactoe_array;
SemaphoreHandle_t mutex_tictactoe;

static uint8_t selected_field = 0;
static uint8_t available_fields = 9;

void logic_task(void *pvParameters)
{
	#if (configUSE_APPLICATION_TASK_TAG == 1)
	// Set task no to be used for tracing with R2R-Network
	vTaskSetApplicationTaskTag( NULL, ( void * ) 4 );
	#endif

	logic_task_parameters_t *task_parameters = pvParameters;
	joystick_input_queue = task_parameters->joystick_input_queue;
	tictactoe_array = task_parameters->tictactoe_array;
	mutex_tictactoe = task_parameters->mutex_tictactoe;
	void * queue_pointer = NULL; //this

	while(1)
	{			
			if(xQueueReceive(joystick_input_queue, &queue_pointer, NON_BLOCKING))
			{
				input_t ** pointer_pointer = queue_pointer;
				input_t * joystick_input = *pointer_pointer;
				char buffer[LOGIC_BUFFER_SIZE];

				if(joystick_input->key == 'E')
				{
					if( xSemaphoreTake( mutex_tictactoe, ( TickType_t ) 10 ) == pdTRUE )
					{
						insert_mark('X', selected_field, tictactoe_array,available_fields);
					xSemaphoreGive( mutex_tictactoe );
					}
				}
				else
				{
					selected_field = navigate(joystick_input->key, selected_field);
				}
				vPortFree(joystick_input);
			}
		vTaskDelay(150);

	}
}