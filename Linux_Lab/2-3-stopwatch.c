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

void *LW_virtual;         // Lightweight bridge base address

char seg7[10] =   {0b00111111, 0b00000110, 0b01011011, 0b01001111, 0b01100110,
                   0b01101101, 0b01111101, 0b00000111, 0b01111111, 0b01101111};

volatile int *LEDR_ptr;    // virtual address for the LEDR port
volatile int *KEY_ptr;     // virtual address for the KEY port
volatile int *TIMER_ptr;    // virtual address for the TIMER port
volatile int *HEX3_HEX0_ptr;
volatile int *HEX5_HEX4_ptr;
volatile int *SW_ptr;
int time_in ;   // holds time in centiseconds.
int set_ms; // centisecond set value
int set_s; // second set value
int set_m; // minute set value

irq_handler_t irq_handler(int irq, void *dev_id, struct pt_regs *regs)
{
    // interrupt is from timer
    if(irq == 72) {
        *TIMER_ptr = 0b0;
        *(TIMER_ptr + 1) = 0b101;
        time_in--; // decrement remaining time
        if (time_in <= 0) time_in = 360000; // if 0 is reached, wrap around

        int time_mins = 0; // holds time in minutes.

        // holds time in seconds.
        int time_secc = time_in / 100;
        time_secc = time_secc % 60;

        // extracts minutes, if no minutes are left => 0
        if (time_in / 6000 > 0)
            time_mins = time_in / 6000;


        int time_mins_ones = time_mins % 10; // ones digit of mins
        int time_mins_tens = time_mins / 10; // tens digit of mins
        // print on 7-seg 4,5
        *HEX5_HEX4_ptr = seg7[time_mins_ones];
        *HEX5_HEX4_ptr += seg7[time_mins_tens] << 8;


        int time_sec_ones = time_secc % 10; // ones digit of seconds
        int time_sec_tens = time_secc / 10; // tens digit of seconds
        // print on 7-seg 3,2
        *HEX3_HEX0_ptr = seg7[time_sec_ones];
        *HEX3_HEX0_ptr += seg7[time_sec_tens] << 8;
        *HEX3_HEX0_ptr = *HEX3_HEX0_ptr << 16;


        *(TIMER_ptr + 5) = 0b0;

        int time_low = time_in % 100; // centisecond extraction
        int time_low_ones = time_low % 10; // ones digit of centiseconds
        int time_low_tens = time_low / 10; // tens digit of centiseconds
        // print on 7-seg 1, 0
        *HEX3_HEX0_ptr += seg7[time_low_ones];
        *HEX3_HEX0_ptr += seg7[time_low_tens] << 8;

        *(KEY_ptr + 3) = 0xF; // clear edgecaptures


    }

    else {

        switch(*(KEY_ptr + 3)){
            // stops if first key is pressed.
            case 0b0001:


                if (*(TIMER_ptr + 1) % 2 == 1) *(TIMER_ptr + 1) = 0b1000; // stop timer if interrupt is enabled
                else *(TIMER_ptr + 1) = 0b0101; // if interrupt is not enabled, continues the timer.

                int time_mins = 0; // holds time in minutes.

                // holds time in seconds.
                int time_secc = time_in / 100;
                time_secc = time_secc % 60;

                // extracts minutes, if no minutes are left => 0
                if (time_in / 6000 > 0)
                    time_mins = time_in / 6000;


                int time_mins_ones = time_mins % 10; // ones digit of mins
                int time_mins_tens = time_mins / 10; // tens digit of mins
                // print on 7-seg 4,5
                *HEX5_HEX4_ptr = seg7[time_mins_ones];
                *HEX5_HEX4_ptr += seg7[time_mins_tens] << 8;


                int time_sec_ones = time_secc % 10; // ones digit of seconds
                int time_sec_tens = time_secc / 10; // tens digit of seconds
                // print on 7-seg 3,2
                *HEX3_HEX0_ptr = seg7[time_sec_ones];
                *HEX3_HEX0_ptr += seg7[time_sec_tens] << 8;
                *HEX3_HEX0_ptr = *HEX3_HEX0_ptr << 16;


                *(TIMER_ptr + 5) = 0b0;

                int time_low = time_in % 100; // centisecond extraction
                int time_low_ones = time_low % 10; // ones digit of centiseconds
                int time_low_tens = time_low / 10; // tens digit of centiseconds
                // print on 7-seg 1, 0
                *HEX3_HEX0_ptr += seg7[time_low_ones];
                *HEX3_HEX0_ptr += seg7[time_low_tens] << 8;

                *(KEY_ptr + 3) = 0xF; // clear edgecaptures

                break;
            
            // set the centiseconds from switches if second key is pressed
            case 0b0010:
                set_ms = *SW_ptr;
                time_in = set_m + set_s + set_ms;
                *(KEY_ptr + 3) = 0xF;
                break;

            // set the seconds if third key is pressewd
            case 0b0100:
                set_s = *SW_ptr * 100;
                time_in = set_m + set_s + set_ms;
                *(KEY_ptr + 3) = 0xF;
                break;

            // set minutes if fourth key is pressed
            case 0b1000:
                set_m = *SW_ptr * 6000;
                time_in = set_m + set_s + set_ms;
                *(KEY_ptr + 3) = 0xF;
                break;

            // won't do anything on default
            default:
                *(KEY_ptr + 3) = 0xF;
                break;

        }

    }

	return (irq_handler_t) IRQ_HANDLED;
}

int stop = 0;
static int __init initialize_pushbutton_handler(void)
{
   int value;

   // generate a virtual address for the FPGA lightweight bridge
   LW_virtual = ioremap_nocache (LW_BRIDGE_BASE, LW_BRIDGE_SPAN);

   TIMER_ptr = TIMER_BASE + LW_virtual;

   // set timer to count down from 100th of a second
   *(TIMER_ptr + 2) = 0b0100001001000000; 
   *(TIMER_ptr + 3) = 0b1111; 
   *(TIMER_ptr + 1) = 0b000;

    time_in = 360000; // remaining time is initially 60 minutes
    SW_ptr = SW_BASE + LW_virtual;
    // initialize set values
    set_ms = 0;
    set_s = 0;
    set_m = 0;


    // this horrendousnes sets the display values to 0.
   HEX3_HEX0_ptr = HEX3_HEX0_BASE + LW_virtual;
   *HEX3_HEX0_ptr = seg7[0];
   *HEX3_HEX0_ptr = *HEX3_HEX0_ptr << 8;
   *HEX3_HEX0_ptr += seg7[0];
   *HEX3_HEX0_ptr = *HEX3_HEX0_ptr << 8;
   *HEX3_HEX0_ptr += seg7[0];
   *HEX3_HEX0_ptr = *HEX3_HEX0_ptr << 8;
   *HEX3_HEX0_ptr += seg7[0];

   HEX5_HEX4_ptr = HEX5_HEX4_BASE + LW_virtual;
   *HEX5_HEX4_ptr = seg7[0];
   *HEX5_HEX4_ptr = *HEX5_HEX4_ptr << 8;
   *HEX5_HEX4_ptr += seg7[0];

   LEDR_ptr = LW_virtual + LEDR_BASE;
   *LEDR_ptr = 0x200;

   KEY_ptr = LW_virtual + KEY_BASE;    // init virtual address for KEY port
   // Clear the PIO edgecapture register (clear any pending interrupt)
   *(KEY_ptr + 3) = 0xF;
   // Enable IRQ generation for the 4 buttons
   *(KEY_ptr + 2) = 0xF;

   // Register the interrupt handler.
   value = request_irq (KEYS_IRQ, (irq_handler_t) irq_handler, IRQF_SHARED,
	"pushbutton_irq_handler", (void *) (irq_handler));

	value = request_irq (INTERVAL_TIMER_IRQi, (irq_handler_t) irq_handler, IRQF_SHARED,
	"timer_irq_handler", (void *) (irq_handler));
   return value;
}

static void __exit cleanup_pushbutton_handler(void)
{
   *LEDR_ptr = 0; // Turn off LEDs and de-register irq handler
	iounmap(LW_virtual);
   free_irq (INTERVAL_TIMER_IRQi ,(void*) irq_handler);
   free_irq (KEYS_IRQ ,(void*) irq_handler);
   *HEX3_HEX0_ptr = 0;
   *HEX5_HEX4_ptr = 0;

}

module_init(initialize_pushbutton_handler);
module_exit(cleanup_pushbutton_handler);

