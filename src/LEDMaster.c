/* Created by Meng-huan Lee
 * 04/09/2018
 *
 *
 */

#include <cr_section_macros.h>
#include <NXP/crp.h>
#include "LPC17xx.h"                        /* LPC17xx definitions */
#include "ssp.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


/* Be careful with the port number and location number, because

some of the location may not exist in that port. */

#define PORT_NUM            0


uint8_t src_addr[SSP_BUFSIZE];
uint8_t dest_addr[SSP_BUFSIZE];


#define ST7735_TFTWIDTH 127
#define ST7735_TFTHEIGHT 159

#define ST7735_CASET 0x2A
#define ST7735_RASET 0x2B
#define ST7735_RAMWR 0x2C
#define ST7735_SLPOUT 0x11
#define ST7735_DISPON 0x29


void spiwrite(uint8_t c) {

	int pnum = 0;
	src_addr[0] = c;
	SSP_SSELToggle( pnum, 0 );
	SSPSend( pnum, (uint8_t *)src_addr, 1 );
	SSP_SSELToggle( pnum, 1 );
}

void writecommand(uint8_t c) {
	LPC_GPIO0->FIOCLR |= (0x1<<21);
	spiwrite(c);
}


void writedata(uint8_t c) {
	LPC_GPIO0->FIOSET |= (0x1<<21);
	spiwrite(c);
}


void writeword(uint16_t c) {
	uint8_t d;
	d = c >> 8;
	writedata(d);
	d = c & 0xFF;
	writedata(d);
}


void delay(int ms)

{
	int count = 24000;
	int i;
	for ( i = count*ms; i--; i > 0);
}


/*
 Main Function main()
*/
int main (void) {
	//Step1 set SPI to Master
	uint32_t pnum = PORT_NUM;
	pnum = 0 ;
	if ( pnum == 0 )
		SSP1Init();
	else
		puts("Port number is not correct");
	//Step: light LED
	//Set GPIO3[25] output

	LPC_GPIO3->FIODIR |= (0x1 << 25);
	LPC_GPIO3->FIOSET |= (0x1 << 25);

	SSPReceive(1,100,1);
	//turn on light
	LPC_GPIO3->FIOCLR |= (0x1 << 25);
	//delay 1000ms
	delay(1000);

	//turn off light
	LPC_GPIO3->FIOSET |= (0x1 << 25);



	return 0;
}


