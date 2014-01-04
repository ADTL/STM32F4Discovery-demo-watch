#define LCD_PORT GPIOE
#define LCD_SPI_PORT GPIOB
#define LCD_SPI SPI2
#define LCD_CS GPIO_Pin_11
#define LCD_RES GPIO_Pin_10
#define LCD_RS GPIO_Pin_9
#define LCD_CLK GPIO_Pin_13
#define LCD_DATA GPIO_Pin_15

#define SPI_BAUDRATE_LOW SPI_BaudRatePrescaler_256
#define SPI_BAUDRATE_HIGH SPI_BaudRatePrescaler_4

#define LCD_SELECT LCD_PORT->ODR &= ~LCD_CS //GPIO_ResetBits(LCD_PORT, LCD_CS)
#define LCD_DESEL LCD_PORT->ODR |= LCD_CS //GPIO_SetBits(LCD_PORT, LCD_CS)

#define LCD_RESET LCD_PORT->ODR &= ~LCD_RES //GPIO_ResetBits(LCD_PORT, LCD_RES)
#define LCD_NORMAL LCD_PORT->ODR |= LCD_RES //GPIO_SetBits(LCD_PORT, LCD_RES)

#define LCD_RS_HI LCD_PORT->ODR |= LCD_RS //GPIO_SetBits(LCD_PORT, LCD_RS)
#define LCD_RS_LOW LCD_PORT->ODR &= ~LCD_RS//GPIO_ResetBits(LCD_PORT, LCD_RS)

#define LCD_CLK_HI LCD_SPI_PORT->ODR |= LCD_CLK //GPIO_SetBits(LCD_PORT, LCD_CLK)
#define LCD_CLK_LOW LCD_SPI_PORT->ODR &= ~LCD_CLK //GPIO_ResetBits(LCD_PORT, LCD_CLK)

#define LCD_DATA_HI LCD_SPI_PORT->ODR |= LCD_DATA //GPIO_SetBits(LCD_PORT, LCD_DATA)
#define LCD_DATA_LOW LCD_SPI_PORT->ODR &= ~LCD_DATA //GPIO_ResetBits(LCD_PORT, LCD_DATA)

/* Colors */
#define GLASSY 0xFFFF
#define WHITE 0xFFF
#define BLACK 0x000
#define RED 0xF00
#define GREEN 0x0F0
#define BLUE 0x00F
#define CYAN 0x0FF
#define MAGENTA 0xF0F
#define YELLOW 0xFF0
#define BROWN 0xB22
#define ORANGE 0xFA0
#define PINK 0xF9E
/* interface speed settings */
enum speed_setting { INTERFACE_SLOW, INTERFACE_FAST };
/* LCD Setup */
void lcd_setup(void);
/* Delay in ms */	
void _delay_ms(unsigned short delay);
/* Send i/o data to LCD */
void lcd_send(unsigned char data);
/* Change LCD contrast */
void lcd_contrast(unsigned char contrast);
/* Select draw window */
void lcd_window(unsigned char xstart, unsigned char ystart,
                unsigned char xend, unsigned char yend);
/* Select cursor position */
void lcd_cursor(unsigned char row, unsigned char col);
/* Clear LCD */
void lcd_clear(unsigned short col);
/* Draw pixel */
void lcd_pixel(unsigned char x, unsigned char y, unsigned short color);
/* Draw line */
void lcd_line(unsigned char x1, unsigned char x2, unsigned char y1, unsigned char y2,
	      unsigned short color);
/* Draw area */
void lcd_area(unsigned char x, unsigned char y, unsigned char height, unsigned char width,
	      unsigned short color);
/* Draw frame */
void lcd_frame(unsigned char x, unsigned char y, unsigned char height, unsigned char width,
	       unsigned char size, unsigned short color);
/* Draw image */
void lcd_image(unsigned char x, unsigned char y, unsigned char height, unsigned char width,
               const unsigned short *image);
/* Draw char */
void lcd_char(char chr, unsigned char x, unsigned char y, unsigned short size,
	      unsigned short color_font, unsigned short color);
/* Draw string */
void lcd_string(char *str, unsigned char x, unsigned char y, unsigned short size,
		unsigned short color_font, unsigned short color);