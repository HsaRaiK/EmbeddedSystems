#include <linux/unistd.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <linux/time.h>
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



// enters when pushbutton key is pressed
irq_handler_t irq_handler(int irq, void *dev_id, struct pt_regs *regs) 
{
	*LEDR_ptr = *LEDR_ptr +1; // increment the led bits by 1
	*HEX3_HEX0_ptr = seg7[*(LEDR_ptr) % 10]; // print led values into HEX display (max 0-9)

	*(KEY_ptr + 3) = 0xF; // reset the edgecapture
	

	return (irq_handler_t) IRQ_HANDLED;
}




int stop = 0;
static int __init initialize_pushbutton_handler(void)
{
   int value;
	
   // generate a virtual address for the FPGA lightweight bridge
   LW_virtual = ioremap_nocache (LW_BRIDGE_BASE, LW_BRIDGE_SPAN);
   LEDR_ptr = LW_virtual + LEDR_BASE;

	HEX3_HEX0_ptr = LW_virtual + HEX3_HEX0_BASE; // init virtual address for first 4 HEX ports.	
   *LEDR_ptr = 0x000; // sets leds to 0
   *HEX3_HEX0_ptr = seg7[*LEDR_ptr]; // print initial LED value
	


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

