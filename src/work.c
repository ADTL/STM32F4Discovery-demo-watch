/*-----------------------------------------------------------------------------
* Author: Boris Vinogradov(nis) : no111u3@gmail.com
* File: work.c
* Type: C code file
* Project: STM32F4D
* 2013
*-----------------------------------------------------------------------------*/
/* includes */
#include "stm32f4xx.h"
#include "lcd.h"
#include "rtc.h"
#include "glib.h"
#include "buttons.h"
#include "s_default.h"
#include "s_watch.h"
#include "xprintf.h"
#include "stm32f4xx_rtc.h"
/* main work function */
void work(void) {
    uint32_t ret = R_OK, event = E_NULL;
    gl_scr_settings curr_set = {
        &s_default,
        &s_default,
        &s_watch,
        &s_default
    };
    gl_scr_events events;
    /* buttons setup */
    buttons_setup();
    /* rtc setup */
    rtc_setup();
    /* lcd setup */
    lcd_setup();
    lcd_clear(BLACK);
    
    /* infinity loop */
    while (1) {
        curr_set.curr->create((p_gl_scr_settings)&curr_set);
        /* eventer loop */
        while ((ret = curr_set.curr->event(event, &events)) == R_OK) {
            /* get event */
            event = buttons_eventer(&events);
        }
        /* clear screen */
        curr_set.curr->destroy();
        /* clear events */
        events.buttons = 0;
        switch (ret) {
            case R_GO:
                gl_scr_go(&curr_set);
                break;
            case R_RETURN:
                gl_scr_return(&curr_set);
                break;
        }
    }
}