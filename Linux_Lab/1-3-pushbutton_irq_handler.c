#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/time.h>
//#include <stdio.h>
#include "../address_map_arm.h"
#include "../interrupt_ID.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Altera University Program");
MODULE_DESCRIPTION("DE1SoC Pushbutton Interrupt Handler");

void * LW_virtual;         // Lightweight bridge base address
volatile int *LEDR_ptr;    // virtual address for the LEDR port
volatile int *KEY_ptr;     // virtual address for the KEY port
volatile int *HEX3_HEX0_ptr;
int full_cycle = 1;
char seg7[10] =   {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
                   0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};


/*int our_pow (int a, int b) {
	
	int i;
	int power = 1;
	for (i = 1; i <= b; i++) {
	power = power * a;
	}
	return power;
}*/

irq_handler_t irq_handler(int irq, void *dev_id, struct pt_regs *regs) 
{
	*LEDR_ptr = *LEDR_ptr +1;
	*HEX3_HEX0_ptr = seg7[*(LEDR_ptr) % 10];
	/*if(*LEDR_ptr < 0x200 && full_cycle != 1){
		*LEDR_ptr = *LEDR_ptr << 1;
	}
	else{
		*LEDR_ptr = *LEDR_ptr >> 1;
		if(*LEDR_ptr == 0x1) 
			full_cycle = 1;
	}*/
	
	*(KEY_ptr + 3) = 0xF;
	

	/*int counter = 0;
 	while(counter < 7) {
	*LEDR_ptr = 0;
		int i = 0;
		while(i < 10){
		*LEDR_ptr = our_pow(2, i);
            //sleep(1);
            *LEDR_ptr = 0;
		i++;
		}

	counter++;	
	}*/
	return (irq_handler_t) IRQ_HANDLED;
}

/*{
   *LEDR_ptr = *LEDR_ptr + 1;
   // Clear the edgecapture register (clears current interrupt)
   *(KEY_ptr + 3) = 0xF;
	while(stop == 0) {
        LEDR_ptr = 0;
        for (int i = 0; i < 10; i++) {
            LEDR_ptr = our_pow(2, i);
            sleep(1);
            LEDR_ptr = 0;
                }
      		  }
 
    
   return (irq_handler_t) IRQ_HANDLED;
}*/




int stop = 0;
static int __init initialize_pushbutton_handler(void)
{
   int value;
	
	   // display 0
   // generate a virtual address for the FPGA lightweight bridge
   LW_virtual = ioremap_nocache (LW_BRIDGE_BASE, LW_BRIDGE_SPAN);
   LEDR_ptr = LW_virtual + LEDR_BASE;
	HEX3_HEX0_ptr = LW_virtual + HEX3_HEX0_BASE;	
   *LEDR_ptr = 0x000;
   *HEX3_HEX0_ptr = seg7[*LEDR_ptr];
	

	//*HEX3_HEX0_ptr = seg7[0];


   KEY_ptr = LW_virtual + KEY_BASE;    // init virtual address for KEY port
   // Clear the PIO edgecapture register (clear any pending interrupt)
   *(KEY_ptr + 3) = 0xF;
   // Enable IRQ generation for the 4 buttons
   *(KEY_ptr + 2) = 0xF; 



   // Register the interrupt handler.
   value = request_irq (KEYS_IRQ, (irq_handler_t) irq_handler, IRQF_SHARED, 
      "pushbutton_irq_handler", (void *) (irq_handler));
   return value;
}

static void __exit cleanup_pushbutton_handler(void)
{
   *LEDR_ptr = 0; // Turn off LEDs and de-register irq handler
	*HEX3_HEX0_ptr = 0;
	iounmap(LW_virtual);
   free_irq (KEYS_IRQ, (void*) irq_handler);

}

module_init(initialize_pushbutton_handler);
module_exit(cleanup_pushbutton_handler);

