/*-----------------------------------------------------------------------------
* Author: Boris Vinogradov(nis) : no111u3@gmail.com
* File: buttons.h
* Type: C header file
* Project: f4examples/05-timers/02-ccr-in-comp-mode
* 2012
*-----------------------------------------------------------------------------*/
#include "glib.h"

#define B_CLICK (unsigned char)'C' /* state if button pressed */
#define B_RELEASE (unsigned char)'R' /* state if button released */
#define B_SHORT_CLICK 1 /* couter value for short click */

#define BUT_PORT GPIOA

enum ButtonTypes { B_LGHT, B_SET, B_UP, B_DWN, B_SU, B_MOD };

#define E_B_LGHT (1 << B_LGHT)
#define E_B_SET (1 << B_SET)
#define E_B_UP (1 << B_UP)
#define E_B_DWN (1 << B_DWN)
#define E_B_SU (1 << B_SU)
#define E_B_MOD (1 << B_MOD)

typedef struct {
    unsigned char counter[6];
    unsigned char state[6];
} ButtonsState;

/* extern buttons structure */
extern volatile ButtonsState button_state;
/* Buttons setup */
void buttons_setup(void);
/* Button eventer */
int buttons_eventer(gl_scr_events * events);