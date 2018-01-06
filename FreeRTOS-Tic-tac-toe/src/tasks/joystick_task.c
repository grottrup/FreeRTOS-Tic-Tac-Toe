/*
* joystick_task.c
*
* Created: 30-05-2017 19:21:26
*  Author: T420s
*/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <avr/io.h>

// FreeRTOS Includes
#include <FreeRTOS.h>
#include <task.h>
#include <timers.h>
#include <queue.h>
#include <semphr.h>

#include "../board/board.h"
#include "../../structs.h"

#define NON_BLOCKING 0
#define JOYSTICK_BUFFER_SIZE 13

static QueueHandle_t * queue;

void joystick_task(void *pvParameters)
{
	task_parameters_t *task_parameters = pvParameters;
	queue = task_parameters->queue;

	#if (configUSE_APPLICATION_TASK_TAG == 1)
	// Set task no to be used for tracing with R2R-Network
	vTaskSetApplicationTaskTag( NULL, ( void * ) 3 );
	#endif
	
	// BaseType_t result = 0;
	// uint8_t byte; //this

	//uint8_t selected_field = 0;
	
	//mini state machine
		
	while(1)
	{
		uint8_t key = 0;
		if(uxQueueSpacesAvailable(queue) > 0)
		{
			if (!(PINC & 0b01000000)) //up
			{
				key = 'U';
			}

			if (!(PINC & 0b00000001)) //down
			{

				key = 'D';
			}

			if (!(PINC & 0b00000010)) //right
			{
				key = 'R';
			}

			if (!(PINC & 0b10000000)) //left
			{
				key = 'L';
			}

			if (!(PIND & 0b00001000)) //push
			{
				key = 'E';
			}

			if(key != 0)
			{
				input_t * joystick_input = pvPortMalloc(sizeof(input_t));
				joystick_input->key = key;
				input_t ** queue_pointer = &joystick_input;
				xQueueSend(queue, &queue_pointer, NON_BLOCKING); // testing whether there is room for sending more
			}
		}
		vTaskDelay(50);
	}
}
