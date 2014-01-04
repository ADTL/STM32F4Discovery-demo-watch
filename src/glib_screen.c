#include "glib.h"
/* Go to next screen */
void gl_scr_go(gl_scr_settings * settings)
{
    p_gl_screen current;
    current = settings->curr;
    settings->curr = settings->next;
    settings->prev = current;
}
/* Return to previous screen */
void gl_scr_return(gl_scr_settings * settings)
{
    p_gl_screen current;
    current = settings->curr;
    settings->curr = settings->prev;
    settings->prev = current;
}