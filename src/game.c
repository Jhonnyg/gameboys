#include <gb/gb.h>
#include <stdio.h>

/* game includes */
#include "../include/sprites.h"

void main()
{
	/* martin timell tells the time */
	int frame = 0;

	/* pre-draw setup code */
    DISPLAY_ON;
  	enable_interrupts(); 

  	while(1) 
  	{
  		/* wait for vertical blank, guess it's a complete screen redraw sync */
  		wait_vbl_done();

  		
  		frame++;
  	}
}