#include <nrf.h>
#include <stdint.h>

#define PIN_GPIO  (13UL)
#define t 5000000

//static const uint32_t buf = 0xffffffff;
	uint8_t flag;
	uint32_t data;

static void nvmc_wait_until_ready(void)
{
	while (NRF_NVMC->READY != NVMC_READY_READY_Ready)
	{
		// Wait until NVMC is done with its current operation.
	}
	return;
}

int main(void)
{
	const uint32_t add_buf = 0x00020000;
	uint32_t add = (uint32_t)add_buf;
		data = 0x32323232;
		flag = 0;
	
  // Configure GPIO pin as output with standard drive strength.
  NRF_GPIO->PIN_CNF[PIN_GPIO] = (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos) |
                                (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos) |
                                (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_INPUT_Pos) |
                                (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos) |
                                (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);
  
  
  // Toggle GPIO ON/OFF.
  while (1)
  {
	      uint32_t volatile tmo;
	  
	switch(flag){
		case 1:
			nvmc_wait_until_ready();
			NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Een;
			NRF_NVMC->ERASEPAGE = add;
			nvmc_wait_until_ready();
			NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
			flag = 0;
			break;
		case 2:
			nvmc_wait_until_ready();
			NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
			*((uint32_t *)add) = data;
			nvmc_wait_until_ready(); add += 4;
			*((uint32_t *)add) = data;
			nvmc_wait_until_ready();
			NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;
			flag = 0;
			break;
	}
    
    tmo = t;
    while (tmo--);
    NRF_GPIO->OUTSET = (1UL << PIN_GPIO);    
    
    tmo = t;
    while (tmo--);
    NRF_GPIO->OUTCLR = (1UL << PIN_GPIO);  
  }
}
