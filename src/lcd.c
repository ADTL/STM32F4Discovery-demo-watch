#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_spi.h"
#include "lcd.h"
#include "xprintf.h"
/* LCD init array */
const unsigned char initData[139]  =
{ 0xF4, 0x90, 0xB3, 0xA0, 0xD0,
0xF0, 0xE2, 0xD4, 0x70, 0x66, 0xB2, 0xBA, 0xA1, 0xA3, 0xAB, 0x94, 0x95,
0x95, 0x95, 0xF5, 0x90, 0xF1, 0x00, 0x10, 0x22, 0x30, 0x45, 0x50, 0x68,
0x70, 0x8A, 0x90, 0xAC, 0xB0, 0xCE, 0xD0, 0xF2, 0x0F, 0x10, 0x20, 0x30,
0x43, 0x50, 0x66, 0x70, 0x89, 0x90, 0xAB, 0xB0, 0xCD, 0xD0, 0xF3, 0x0E,
0x10, 0x2F, 0x30, 0x40, 0x50, 0x64, 0x70, 0x87, 0x90, 0xAA, 0xB0, 0xCB,
0xD0, 0xF4, 0x0D, 0x10, 0x2E, 0x30, 0x4F, 0x50, 0xF5, 0x91, 0xF1, 0x01,
0x11, 0x22, 0x31, 0x43, 0x51, 0x64, 0x71, 0x86, 0x91, 0xA8, 0xB1, 0xCB,
0xD1, 0xF2, 0x0F, 0x11, 0x21, 0x31, 0x42, 0x51, 0x63, 0x71, 0x85, 0x91,
0xA6, 0xB1, 0xC8, 0xD1, 0xF3, 0x0B, 0x11, 0x2F, 0x31, 0x41, 0x51, 0x62,
0x71, 0x83, 0x91, 0xA4, 0xB1, 0xC6, 0xD1, 0xF4, 0x08, 0x11, 0x2B, 0x31,
0x4F, 0x51, 0x80, 0x94, 0xF5, 0xA2, 0xF4, 0x60, 0xF0, 0x40, 0x50, 0xC0,
0xF4, 0x70 };
/* LCD character table */
unsigned char font5x7 [][5] = {
    
    { 0x00, 0x00, 0x00, 0x00, 0x00 },   // sp
    { 0x00, 0x00, 0x2f, 0x00, 0x00 },   // !
    { 0x00, 0x07, 0x00, 0x07, 0x00 },   // "
    { 0x14, 0x7f, 0x14, 0x7f, 0x14 },   // #
    { 0x24, 0x2a, 0x7f, 0x2a, 0x12 },   // $
    { 0x32, 0x34, 0x08, 0x16, 0x26 },   // %
    { 0x36, 0x49, 0x55, 0x22, 0x50 },   // &
    { 0x00, 0x05, 0x03, 0x00, 0x00 },   // '
    { 0x00, 0x1c, 0x22, 0x41, 0x00 },   // (
    { 0x00, 0x41, 0x22, 0x1c, 0x00 },   // )
    { 0x14, 0x08, 0x3E, 0x08, 0x14 },   // *
    { 0x08, 0x08, 0x3E, 0x08, 0x08 },   // +
    { 0x00, 0x00, 0x50, 0x30, 0x00 },   // ,
    { 0x10, 0x10, 0x10, 0x10, 0x10 },   // -
    { 0x00, 0x60, 0x60, 0x00, 0x00 },   // .
    { 0x20, 0x10, 0x08, 0x04, 0x02 },   // /
    { 0x3E, 0x51, 0x49, 0x45, 0x3E },   // 0
    { 0x00, 0x42, 0x7F, 0x40, 0x00 },   // 1
    { 0x42, 0x61, 0x51, 0x49, 0x46 },   // 2
    { 0x21, 0x41, 0x45, 0x4B, 0x31 },   // 3
    { 0x18, 0x14, 0x12, 0x7F, 0x10 },   // 4
    { 0x27, 0x45, 0x45, 0x45, 0x39 },   // 5
    { 0x3C, 0x4A, 0x49, 0x49, 0x30 },   // 6
    { 0x01, 0x71, 0x09, 0x05, 0x03 },   // 7
    { 0x36, 0x49, 0x49, 0x49, 0x36 },   // 8
    { 0x06, 0x49, 0x49, 0x29, 0x1E },   // 9
    { 0x00, 0x36, 0x36, 0x00, 0x00 },   // :
    { 0x00, 0x56, 0x36, 0x00, 0x00 },   // ;
    { 0x08, 0x14, 0x22, 0x41, 0x00 },   // <
    { 0x14, 0x14, 0x14, 0x14, 0x14 },   // =
    { 0x00, 0x41, 0x22, 0x14, 0x08 },   // >
    { 0x02, 0x01, 0x51, 0x09, 0x06 },   // ?
    { 0x32, 0x49, 0x59, 0x51, 0x3E },   // @
    { 0x7E, 0x11, 0x11, 0x11, 0x7E },   // A
    { 0x7F, 0x49, 0x49, 0x49, 0x36 },   // B
    { 0x3E, 0x41, 0x41, 0x41, 0x22 },   // C
    { 0x7F, 0x41, 0x41, 0x22, 0x1C },   // D
    { 0x7F, 0x49, 0x49, 0x49, 0x41 },   // E
    { 0x7F, 0x09, 0x09, 0x09, 0x01 },   // F
    { 0x3E, 0x41, 0x49, 0x49, 0x7A },   // G
    { 0x7F, 0x08, 0x08, 0x08, 0x7F },   // H
    { 0x00, 0x41, 0x7F, 0x41, 0x00 },   // I
    { 0x20, 0x40, 0x41, 0x3F, 0x01 },   // J
    { 0x7F, 0x08, 0x14, 0x22, 0x41 },   // K
    { 0x7F, 0x40, 0x40, 0x40, 0x40 },   // L
    { 0x7F, 0x02, 0x0C, 0x02, 0x7F },   // M
    { 0x7F, 0x04, 0x08, 0x10, 0x7F },   // N
    { 0x3E, 0x41, 0x41, 0x41, 0x3E },   // O
    { 0x7F, 0x09, 0x09, 0x09, 0x06 },   // P
    { 0x3E, 0x41, 0x51, 0x21, 0x5E },   // Q
    { 0x7F, 0x09, 0x19, 0x29, 0x46 },   // R
    { 0x46, 0x49, 0x49, 0x49, 0x31 },   // S
    { 0x01, 0x01, 0x7F, 0x01, 0x01 },   // T
    { 0x3F, 0x40, 0x40, 0x40, 0x3F },   // U
    { 0x1F, 0x20, 0x40, 0x20, 0x1F },   // V
    { 0x3F, 0x40, 0x38, 0x40, 0x3F },   // W
    { 0x63, 0x14, 0x08, 0x14, 0x63 },   // X
    { 0x07, 0x08, 0x70, 0x08, 0x07 },   // Y
    { 0x61, 0x51, 0x49, 0x45, 0x43 },   // Z
    { 0x00, 0x7F, 0x41, 0x41, 0x00 },   // [
    { 0x55, 0x2A, 0x55, 0x2A, 0x55 },   // 55
    { 0x00, 0x41, 0x41, 0x7F, 0x00 },   // ]
    { 0x04, 0x02, 0x01, 0x02, 0x04 },   // ^
    { 0x40, 0x40, 0x40, 0x40, 0x40 },   // _
    { 0x00, 0x01, 0x02, 0x04, 0x00 },   // '
    { 0x20, 0x54, 0x54, 0x54, 0x78 },   // a
    { 0x7F, 0x48, 0x44, 0x44, 0x38 },   // b
    { 0x38, 0x44, 0x44, 0x44, 0x20 },   // c
    { 0x38, 0x44, 0x44, 0x48, 0x7F },   // d
    { 0x38, 0x54, 0x54, 0x54, 0x18 },   // e
    { 0x08, 0x7E, 0x09, 0x01, 0x02 },   // f
    { 0x0C, 0x52, 0x52, 0x52, 0x3E },   // g
    { 0x7F, 0x08, 0x04, 0x04, 0x78 },   // h
    { 0x00, 0x44, 0x7D, 0x40, 0x00 },   // i
    { 0x20, 0x40, 0x44, 0x3D, 0x00 },   // j
    { 0x7F, 0x10, 0x28, 0x44, 0x00 },   // k
    { 0x00, 0x41, 0x7F, 0x40, 0x00 },   // l
    { 0x7C, 0x04, 0x18, 0x04, 0x78 },   // m
    { 0x7C, 0x08, 0x04, 0x04, 0x78 },   // n
    { 0x38, 0x44, 0x44, 0x44, 0x38 },   // o
    { 0x7C, 0x14, 0x14, 0x14, 0x08 },   // p
    { 0x08, 0x14, 0x14, 0x18, 0x7C },   // q
    { 0x7C, 0x08, 0x04, 0x04, 0x08 },   // r
    { 0x48, 0x54, 0x54, 0x54, 0x20 },   // s
    { 0x04, 0x3F, 0x44, 0x40, 0x20 },   // t
    { 0x3C, 0x40, 0x40, 0x20, 0x7C },   // u
    { 0x1C, 0x20, 0x40, 0x20, 0x1C },   // v
    { 0x3C, 0x40, 0x30, 0x40, 0x3C },   // w
    { 0x44, 0x28, 0x10, 0x28, 0x44 },   // x
    { 0x0C, 0x50, 0x50, 0x50, 0x3C },   // y
    { 0x44, 0x64, 0x54, 0x4C, 0x44 },   // z
};
/* Delay in ms */	
void _delay_ms(unsigned short delay) {
    volatile unsigned int counter = delay * 4000;
    while (counter--);
}
/* Send i/o data to LCD */
void lcd_send(unsigned char data) {
    /* Send byte through the SPI1 peripheral */
    LCD_SPI->DR = data;

    /* Wait to receive a byte */
    while (SPI_I2S_GetFlagStatus(LCD_SPI, SPI_I2S_FLAG_RXNE) == RESET);

    /* Return the byte read from the SPI bus */
    LCD_SPI->DR;
}
/* Change LCD contrast */
void lcd_contrast(unsigned char contrast) {
    LCD_RS_HI;
    LCD_SELECT;
    lcd_send(0xf4);
    lcd_send(0xb0 | (contrast >> 4));
    lcd_send(0xa0 | (contrast & 0x0f));
    LCD_DESEL;
}
/* Select draw window */
void lcd_window(unsigned char xstart, unsigned char ystart,
		unsigned char xend, unsigned char yend) {
    xstart <<= 1;
    xstart += 6;
    xend <<= 1;
    xend += 7;
    
    LCD_RS_HI;
    LCD_SELECT;
    lcd_send(0xf0);
    lcd_send(0x00 | (xstart & 0x0f));
    lcd_send(0x10 | (xstart >> 4));
    lcd_send(0x20 | (ystart & 0x0f));
    lcd_send(0x30 | (ystart >> 4));
    lcd_send(0xf5);
    lcd_send(0x00 | (xend & 0x0f));
    lcd_send(0x10 | (xend >> 4));
    lcd_send(0x20 | (yend & 0x0f));
    lcd_send(0x30 | (yend >> 4));
    LCD_DESEL;
    LCD_RS_LOW;
}
/* Select cursor position */
void lcd_cursor(unsigned char row, unsigned char col) {
    lcd_window(row, col, 100, 79);
}
/* Clear LCD */
void lcd_clear(unsigned short col) {
    unsigned short i;
    
    lcd_cursor(0, 0);
    LCD_RS_LOW;
    LCD_SELECT;
    for (i = 0; i < 8080; i++) {
	lcd_send(col >> 8);
	lcd_send(col & 0x00ff);
    }
    lcd_cursor(0, 0);
    LCD_DESEL;
}
/* Draw pixel */
void lcd_pixel(unsigned char x, unsigned char y, unsigned short color) {
    lcd_cursor(x, y);
    LCD_RS_LOW;
    LCD_SELECT;
    lcd_send((color & 0x0fff) >> 8);
    lcd_send(color & 0x00ff);
    LCD_DESEL;
    LCD_RS_HI;
}
/* Draw line */
void lcd_line(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2,
	      unsigned short color) {
    short dx, dy, stepx, stepy, fraction;
    
    dy = y2 - y1;
    dx = x2 - x1;
    
    if (dy < 0) {
	dy = -dy;
	stepy = -1;
    }
    else {
	stepy = 1;
    }
    
    if (dx < 0) {
	dx = -dx;
	stepx = -1;
    }
    else {
	stepx = 1;
    }
    
    dx <<= 1;
    dy <<= 1;
    
    lcd_pixel(x1, y1, color);
    
    if (dx > dy) {
	fraction = dy - (dx >> 1);
	while (x1 != x2) {
	    if (fraction >= 0) {
		y1 += stepy;
		fraction -= dx;
	    }
	    x1 += stepx;
	    fraction += dy;
	    
	    lcd_pixel(x1, y1, color);
	}
    }
    else {
	fraction = dx - (dy >> 1);
	while (y1 != y2) {
	    if (fraction >= 0) {
		x1 += stepx;
		fraction -= dy;
	    }
	    y1 += stepy;
	    fraction += dx;
	    
	    lcd_pixel(x1, y1, color);
	}
    }
}
/* Draw area */
void lcd_area(unsigned char x, unsigned char y, unsigned char height, unsigned char width,
	      unsigned short color) {
    short yy = y + height;
    for (; y < yy; y++) {
	lcd_line(x, x + width, y, y, color);
    }
}
/* Draw frame */
void lcd_frame(unsigned char x, unsigned char y, unsigned char height, unsigned char width,
	       unsigned char size, unsigned short color) {
    short x2 = x + width, y2 = y + height;
    unsigned short i;
    for (i = 1; i <= size; i++) {
	lcd_line(x, x, y, y2, color);
	lcd_line(x2, x2, y, y2, color);
	lcd_line(x, x2, y, y, color);
	lcd_line(x, x2, y2, y2, color);
	x++;
	y++;
	x2--;
	y2--;
    }
}
/* Draw image */
void lcd_image(unsigned char x, unsigned char y, unsigned char height, unsigned char width,
               const unsigned short *image)
{
    int i;
    lcd_window(x, y, x + width - 1, y + height -1);
    LCD_RS_LOW;
    LCD_SELECT;
    for (i = 0; i < height * width; i++) {
        lcd_send(image[i] >> 8);
        lcd_send(image[i] & 0x00ff);
    }
    lcd_cursor(0, 0);
    LCD_DESEL;
}
/* Draw char */
void lcd_char(char chr, unsigned char x, unsigned char y, unsigned short size,
	      unsigned short color_font, unsigned short color) {
    char buf;
    unsigned short i, j, l, k, xpoz, ypoz;
    xpoz = x;
    ypoz = y;
    if (size == 1) {
	for (i = 0; i < 5; i++) {
	    buf = font5x7[chr - 32][i];
	    j = 0;
	    while (j < 8) {
		if (buf & (1 << j)) {
		    lcd_pixel(xpoz + i, ypoz + j, color_font);
		    j++;
		}
		else if (color == GLASSY) {
		    j++;
		}
		else {
		    lcd_pixel(xpoz + i, ypoz + j, color);
		    j++;
		}
	    }
	}
    }
    else if (size == 2) {
	l = 0;
	for (i = 0; i < 5; i++) {
	    k = 0;
	    j = 0;
	    l += 2;
	    buf = font5x7[chr - 32][i];
	    while (j < 8) {
		if (buf & (1 << j)) {
		    lcd_pixel(xpoz + l, ypoz + k, color_font);
		    lcd_pixel(xpoz + l, ypoz + k + 1, color_font);
		    lcd_pixel(xpoz + l + 1, ypoz + k, color_font);
		    lcd_pixel(xpoz + l + 1, ypoz + k + 1, color_font);
		    k += 2;
		    j++;
		}
		else if (color == GLASSY) {
		    k += 2;
		    j++;
		}
		else {
		    lcd_pixel(xpoz + l, ypoz + k, color);
		    lcd_pixel(xpoz + l, ypoz + k + 1, color);
		    lcd_pixel(xpoz + l + 1, ypoz + k, color);
		    lcd_pixel(xpoz + l + 1, ypoz + k + 1, color);
		    k += 2;
		    j++;
		}
	    }
	}
    }
}
/* Draw string */
void lcd_string(char *str, unsigned char x, unsigned char y, unsigned short size,
		unsigned short color_font, unsigned short color) {
    while ((*str != 0) && (*str != 10)) {
	lcd_char(*str++, x, y, size, color_font, color);
	x += 6 * size;
	if (size == 1 && x > 80) {
	    y++;
	    x = 0;
	}
    }
}
/* Set interface speed */
static void spi_speed( enum speed_setting speed ) {
	unsigned int tmp;

	tmp = LCD_SPI->CR1;
	if ( speed == INTERFACE_SLOW ) {
		/* Set slow clock (100k-400k) */
		tmp = ( tmp | SPI_BAUDRATE_LOW );
	} else {
		/* Set fast clock (depends on the CSD) */
		tmp = ( tmp & ~SPI_BAUDRATE_LOW ) | SPI_BAUDRATE_HIGH;
	}
	LCD_SPI->CR1 = tmp;
}
/* Setup LCD interface */
static void lcd_spi_setup(void) {
    /* Configure ports */
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
    /* Enable GPIOB, SPI2 clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
    /* Setup AF functions for MOSI, SCK pins */
    GPIO_PinAFConfig(LCD_SPI_PORT, GPIO_PinSource13, GPIO_AF_SPI2);
    GPIO_PinAFConfig(LCD_SPI_PORT, GPIO_PinSource15, GPIO_AF_SPI2);
    /* Setup CLK, DATA pins */
    GPIO_InitStructure.GPIO_Pin = LCD_CLK | LCD_DATA;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_SPI_PORT, &GPIO_InitStructure);
    /* SPI configuration */
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BAUDRATE_LOW;
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(LCD_SPI, &SPI_InitStructure);

    SPI_CalculateCRC(LCD_SPI, DISABLE);
    
    /* Enable SPIx  */
    SPI_Cmd(LCD_SPI, ENABLE);
}
/* LCD Setup */
void lcd_setup(void) {
    /* Enable GPIOE */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    /* Configure port */
    GPIO_InitTypeDef GPIO_InitStructure;
    /* Setup RES, CS, RS pins */
    GPIO_InitStructure.GPIO_Pin = LCD_RES | LCD_CS | LCD_RS;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(LCD_PORT, &GPIO_InitStructure);
    /* Setup LCD SPI */
    lcd_spi_setup();
    /* Initing LCD */
    unsigned char j;
    LCD_DESEL;
    LCD_NORMAL;
    LCD_RS_LOW;
    LCD_RESET;
    _delay_ms(10);
    LCD_NORMAL;
    _delay_ms(10);
    LCD_RS_HI;
    LCD_SELECT;
    
    for (j = 0; j < 139; j++) {
	lcd_send(initData[j]);
    }
    _delay_ms(10);
    LCD_DESEL;
    _delay_ms(10);
    LCD_SELECT;
    
    lcd_send(0xf0);
    lcd_send(0x81);
    lcd_send(0xf4);
    lcd_send(0xb3);
    
    lcd_send(0xf0);
    lcd_send(0x06);
    lcd_send(0x10);
    lcd_send(0x20);
    lcd_send(0x30);
    lcd_send(0xf5);
    lcd_send(0x0f);
    lcd_send(0x1c);
    lcd_send(0x2f);
    lcd_send(0x34);
    LCD_DESEL;
    LCD_RS_LOW;
    
    spi_speed(INTERFACE_FAST);
}