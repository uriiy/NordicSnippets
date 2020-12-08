#ifndef __SSD1306_H
#define __SSD1306_H

#include <nrf.h>
#include <stdint.h>
#include <stdio.h>

//extern static const uint8_t LCD_Buffer[][22];
extern uint8_t LCD_X,LCD_Y;
#define SSD1306_I2C_ADDRESS									0x78
#define SSD1306_I2C_SPEED               	100000//300000

// gpio LCD
#define SSD1306_I2C                         I2C1
#define SSD1306_I2C_CLK                  	RCC_APB1Periph_I2C1
#define SSD1306_I2C_SCL_PIN                 GPIO_Pin_6                 
#define SSD1306_I2C_SCL_GPIO_PORT           GPIOB                       
#define SSD1306_I2C_SCL_GPIO_CLK            RCC_APB2Periph_GPIOB
#define SSD1306_I2C_SDA_PIN                 GPIO_Pin_7                  
#define SSD1306_I2C_SDA_GPIO_PORT           GPIOB                       
#define SSD1306_I2C_SDA_GPIO_CLK            RCC_APB2Periph_GPIOB
#define SSD1306_I2C_DR                      ((uint32_t)0x40005410)

// size 
#define SSD1306_LCDWIDTH                  	128
#define SSD1306_LCDHEIGHT                 	64
#define SSD1306_DEFAULT_SPACE				5
// Commands
#define SSD1306_SETCONTRAST 0x81
#define SSD1306_DISPLAYALLON_RESUME 0xA4
#define SSD1306_DISPLAYALLON 0xA5
#define SSD1306_NORMALDISPLAY 0xA6
#define SSD1306_INVERTDISPLAY 0xA7
#define SSD1306_DISPLAYOFF 0xAE
#define SSD1306_DISPLAYON 0xAF

#define SSD1306_SETDISPLAYOFFSET 0xD3
#define SSD1306_SETCOMPINS 0xDA

#define SSD1306_SETVCOMDETECT 0xDB

#define SSD1306_SETDISPLAYCLOCKDIV 0xD5
#define SSD1306_SETPRECHARGE 0xD9

#define SSD1306_SETMULTIPLEX 0xA8

#define SSD1306_SETLOWCOLUMN 0x00
#define SSD1306_SETHIGHCOLUMN 0x10

#define SSD1306_SETSTARTLINE 0x40

#define SSD1306_MEMORYMODE 0x20
#define SSD1306_COLUMNADDR 0x21
#define SSD1306_PAGEADDR   0x22

#define SSD1306_COMSCANINC 0xC0
#define SSD1306_COMSCANDEC 0xC8

#define SSD1306_SEGREMAP 0xA0

#define SSD1306_CHARGEPUMP 0x8D

#define SSD1306_EXTERNALVCC 0x1
#define SSD1306_SWITCHCAPVCC 0x2

// Scrolling #defines
#define SSD1306_ACTIVATE_SCROLL 0x2F
#define SSD1306_DEACTIVATE_SCROLL 0x2E
#define SSD1306_SET_VERTICAL_SCROLL_AREA 0xA3
#define SSD1306_RIGHT_HORIZONTAL_SCROLL 0x26
#define SSD1306_LEFT_HORIZONTAL_SCROLL 0x27
#define SSD1306_VERTICAL_AND_RIGHT_HORIZONTAL_SCROLL 0x29
#define SSD1306_VERTICAL_AND_LEFT_HORIZONTAL_SCROLL 0x2A

#define COMAND		0x00
#define DATA		0x40

void LCD_init(void);
void LCD_Commmand(uint8_t ControByte, uint8_t DataByte);
void LCD_Goto(uint8_t x, uint8_t y);
void LCD_Print(char c);
void LCD_Printf(char* buf);
void LCD_Clear(void);
void LCD_draw8x8(uint8_t * buffer, uint8_t x, uint8_t y);
void LCD_DrawImage(uint8_t * buf);
void LCD_WakeUp(void);
void hhh(void);
extern void i2c_write(uint8_t addr, uint8_t data);

#endif
