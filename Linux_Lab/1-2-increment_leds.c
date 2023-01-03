#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include "../address_map_arm.h"
//#include "../pushbutton_irq_handler/pushbutotn_irq_handler.c"

/* Prototypes for functions used to access physical memory addresses */
int open_physical (int);
void * map_physical (int, unsigned int, unsigned int);
void close_physical (int);
int unmap_physical (void *, unsigned int);

int stop = 0;

void sigint_handler_2(int sig_num) {
	signal(SIGINT, sigint_handler_2);
	stop = 0;
}

void sigint_handler(int sig_num){

	printf("\nCaught %d\n", sig_num);
	stop = 1;
	signal(SIGINT, sigint_handler_2);
	while (stop){
	
}
	signal(SIGINT, sigint_handler);
	fflush(stdout);

}

int our_pow (int a, int b) {
	int power = 1, i;
	for(i = 1; i  <= b; i++){

	power = power * a;

}return power;

}

/* This program increments the contents of the red LED parallel port */
int main(void)
{	
   int[10] decoded =  {0b011111, 0b0000110, 0b1011011, 0b1001111, 0b1100110, 0b1111101,  0b0000111, 0b1111111, 0b110111};
   for (int x=0; x<10; x++){
	printf("%d",decoded[x]);
	}
   volatile int * LEDR_ptr;   // virtual address pointer to red LEDs

   int fd = -1;               // used to open /dev/mem for access to physical addresses
   void *LW_virtual;          // used to map physical addresses for the light-weight bridge
    
   // Create virtual memory access to the FPGA light-weight bridge
   if ((fd = open_physical (fd)) == -1)
      return (-1);
   if ((LW_virtual = map_physical (fd, LW_BRIDGE_BASE, LW_BRIDGE_SPAN)) == NULL)
      return (-1);

   // Set virtual address pointer to I/O port
   LEDR_ptr = (unsigned int *) (LW_virtual + LEDR_BASE);
    
   signal(SIGINT, sigint_handler);
   while(stop == 0) {
   // Add 1 to the I/O register
   *LEDR_ptr = 0;

   //Continue addition?
   for(int i = 0; i < 10; i++)
	{
	

	*LEDR_ptr += our_pow(2, i);
	sleep(1);
	*LEDR_ptr = 0;

	}
for (int i = 9; i >= 0; i--){

	*LEDR_ptr += our_pow(2, i);
	sleep(1);
	*LEDR_ptr = 0;

}}
   unmap_physical (LW_virtual, LW_BRIDGE_SPAN);   // release the physical-memory mapping
   close_physical (fd);   // close /dev/mem
   return 0;
}

// Open /dev/mem, if not already done, to give access to physical addresses
int open_physical (int fd)
{
   if (fd == -1)
      if ((fd = open( "/dev/mem", (O_RDWR | O_SYNC))) == -1)
      {
         printf ("ERROR: could not open \"/dev/mem\"...\n");
         return (-1);
      }
   return fd;
}

// Close /dev/mem to give access to physical addresses
void close_physical (int fd)
{
   close (fd);
}

/*
 * Establish a virtual address mapping for the physical addresses starting at base, and
 * extending by span bytes.
 */
void* map_physical(int fd, unsigned int base, unsigned int span)
{
   void *virtual_base;

   // Get a mapping from physical addresses to virtual addresses
   virtual_base = mmap (NULL, span, (PROT_READ | PROT_WRITE), MAP_SHARED, fd, base);
   if (virtual_base == MAP_FAILED)
   {
      printf ("ERROR: mmap() failed...\n");
      close (fd);
      return (NULL);
   }
   return virtual_base;
}

/*
 * Close the previously-opened virtual address mapping
 */
int unmap_physical(void * virtual_base, unsigned int span)
{
   if (munmap (virtual_base, span) != 0)
   {
      printf ("ERROR: munmap() failed...\n");
      return (-1);
   }
   return 0;
}

