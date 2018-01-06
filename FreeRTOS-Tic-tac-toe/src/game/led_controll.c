/*
 * led_controll.c
 *
 * Created: 31-05-2017 16:33:16
 *  Author: T420s
 */ 

  #include <stdint.h>
  #define FIELDS 9
  #define FRAME_BUF_SIZE 14

 
 
 static void display_mark(char mark, uint16_t field, uint16_t * frame_buf)
 {
	 uint8_t col1;
	 uint8_t col2;
	 uint8_t col3;

	 switch(field)
	 {
		 case 0:
		 case 3:
		 case 6:
		 col1 = 0;
		 col2 = 1;
		 col3 = 2;
		 break;
		 case 1:
		 case 4:
		 case 7:
		 col1 = 5;
		 col2 = 6;
		 col3 = 7;
		 break;
		 case 2:
		 case 5:
		 case 8:
		 col1 = 10;
		 col2 = 11;
		 col3 = 12;
		 break;
		 default:
		 break;
	 }
	 

	 if(mark == 'X')
	 {
		 switch(field)
		 {
			 case 0:
			 case 1:
			 case 2:
			 frame_buf[col2] += 3;
			 break;
			 case 3:
			 case 4:
			 case 5:
			 frame_buf[col2] += 48;
			 break;
			 case 6:
			 case 7:
			 case 8:
			 frame_buf[col2] += 768;
			 break;
			 default:
			 break;
		 }
	 }

	 if(mark == 'O')
	 {
		 switch(field)
		 {
			 case 0:
			 case 1:
			 case 2:
			 frame_buf[col1] += 2;
			 frame_buf[col2] += 2;
			 frame_buf[col3] += 2;
			 break;
			 case 3:
			 case 4:
			 case 5:
			 frame_buf[col1] += 32;
			 frame_buf[col2] += 32;
			 frame_buf[col3] += 32;
			 break;
			 case 6:
			 case 7:
			 case 8:
			 frame_buf[col1] += 512;
			 frame_buf[col2] += 512;
			 frame_buf[col3] += 512;
			 break;
			 default:
			 break;
		 }
	 }
 } 

static void clear_buf(uint16_t * frame_buf)
{
	for(uint8_t i = 0; i < FRAME_BUF_SIZE; i++)
	{
		frame_buf[i] = 0;
	}
}


void display_tic_tac_toe(char * tictactoe_array, uint16_t * frame_buf)
 {
	clear_buf(frame_buf);
	for(uint8_t i = 0; i < FIELDS; i++)
	{
		display_mark(tictactoe_array[i], i, frame_buf);
	}
 }
 