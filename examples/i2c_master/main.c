#include <nrf.h>
#include <stdint.h>
#include <stdio.h>
#include "ssd1306.h"

#define DEVICE_ADDRESS (0x3c)
#define PIN_SCL        (27)
#define PIN_SDA        (26)
#define PIN 13UL

void i2c_write(uint8_t addr, uint8_t data)
{
  uint8_t tx_buf[2];

  NRF_TWIM0->SHORTS = TWIM_SHORTS_LASTTX_STOP_Msk;

  tx_buf[0] = addr;
  tx_buf[1] = data;
  NRF_TWIM0->TXD.MAXCNT = sizeof(tx_buf);
  NRF_TWIM0->TXD.PTR = (uint32_t)&tx_buf[0];

  NRF_TWIM0->EVENTS_STOPPED = 0;
  NRF_TWIM0->TASKS_STARTTX = 1;
  while (NRF_TWIM0->EVENTS_STOPPED == 0);
}

uint8_t i2c_read(uint8_t addr)
{
  uint8_t tx_buf[1];
  uint8_t rx_buf[1];
  NRF_TWIM0->SHORTS = TWIM_SHORTS_LASTTX_STARTRX_Msk | TWIM_SHORTS_LASTRX_STOP_Msk;

  tx_buf[0] = addr;
  NRF_TWIM0->TXD.MAXCNT = sizeof(tx_buf);
  NRF_TWIM0->TXD.PTR = (uint32_t)&tx_buf[0];

  NRF_TWIM0->RXD.MAXCNT = 1;
  NRF_TWIM0->RXD.PTR = (uint32_t)&rx_buf[0];

  NRF_TWIM0->EVENTS_STOPPED = 0;
  NRF_TWIM0->TASKS_STARTTX = 1;
  while (NRF_TWIM0->EVENTS_STOPPED == 0);

  return rx_buf[0];
}

void oledClear(){
	int pp=0;
	i2c_write(0x0, 0x21);
	i2c_write(0x0, 0);
	i2c_write(0x0, 127);
	i2c_write(0x0, 0x22);
	i2c_write(0x0, 0);
	i2c_write(0x0, 7);

	for(pp=0; pp<=1023; pp++){
		i2c_write(0x40, 0x00);
	}
}

void oledFF(){
	int pp=0;
	i2c_write(0x0, 0x21);
	i2c_write(0x0, 0);
	i2c_write(0x0, 127);
	i2c_write(0x0, 0x22);
	i2c_write(0x0, 0);
	i2c_write(0x0, 7);

	for(pp=0; pp<=1023; pp++){
		i2c_write(0x40, 0xaa);
	}
}

int main(void)
{
    uint32_t volatile tmo;
	
	char time[16];
	int hh,mm,ss;
    
    tmo = 1000000;
    while (tmo--);
	
	NRF_P0->PIN_CNF[PIN] = (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos) |
												(GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos);
	
	NRF_P0->OUT = GPIO_OUT_PIN13_High << GPIO_OUT_PIN13_Pos;
	NRF_P0->OUT &= ~GPIO_OUT_PIN13_Msk;
	
  NRF_TWIM0->PSEL.SCL = PIN_SCL;
  NRF_TWIM0->PSEL.SDA = PIN_SDA;

  NRF_TWIM0->ADDRESS = DEVICE_ADDRESS;
  NRF_TWIM0->FREQUENCY = TWIM_FREQUENCY_FREQUENCY_K400 << TWIM_FREQUENCY_FREQUENCY_Pos;
  NRF_TWIM0->SHORTS = 0;

  NRF_TWIM0->ENABLE = TWIM_ENABLE_ENABLE_Enabled << TWIM_ENABLE_ENABLE_Pos;

 i2c_write(0x0, 0xAE);
 i2c_write(0x0, 0xD5);
 i2c_write(0x0, 0x80);
 i2c_write(0x0, 0xD3);
 i2c_write(0x0, 0x0);
 i2c_write(0x0, 0x40);
 i2c_write(0x0, 0x8D);
 i2c_write(0x0, 0x14);
 i2c_write(0x0, 0x20);
 i2c_write(0x0, 0x00);
 i2c_write(0x0, 0xA1);
 i2c_write(0x0, 0xC8);
 i2c_write(0x0, 0xDA);
 i2c_write(0x0, 0x12);
 i2c_write(0x0, 0x81);
 i2c_write(0x0, 0xCF);
 i2c_write(0x0, 0xD9);
 i2c_write(0x0, 0xF1);
 i2c_write(0x0, 0xDB);
 i2c_write(0x0, 0x40);
 i2c_write(0x0, 0xA4);
 i2c_write(0x0, 0xA6);
 i2c_write(0x0, 0xAF);
 oledClear();
//oledFF();


hh=23;
mm=58;
ss=58;
  while (1)
  {
		LCD_Goto(0,0);
		sprintf((char*)&time, "%02i:%02i:%02i", hh, mm, ss);
		LCD_Printf((char*)&time);
    tmo = 6400000;
    while (tmo--);
		ss++;
		if(ss==60) {ss=0; mm++;}
		if(mm==60) {mm=0; hh++;}
		if(hh==24) hh=0;
  }
}
