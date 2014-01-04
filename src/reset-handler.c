/*-----------------------------------------------------------------------------
* Author: Boris Vinogradov(nis) : no111u3@gmail.com
* File: reset_hander.c
* Type: C code file
* Project: STM32F4D
* 2013
*-----------------------------------------------------------------------------*/
/* include headers */
#include "stm32f4xx.h"
#include "work.h"
/* extern vars */
extern uint32_t __text_end;
extern uint32_t __data_start;
extern uint32_t __data_end;
extern uint32_t __bss_start;
extern uint32_t __bss_end;
/* reset handler */
void reset_handler(void) {
    uint32_t * src;
    uint32_t * dest;
    
    src = &__text_end;
    dest = &__data_start;
    if (src != dest)
	while (dest < &__data_end)
	    *(dest++) = *(src++);
    
    dest = &__bss_start;
    while (dest < &__bss_end)
	*(dest++) = 0;
    /* call working code */
    work();
}
