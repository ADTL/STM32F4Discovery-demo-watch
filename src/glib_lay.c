#include "glib.h"

/* Drawing element and subtree */
void gl_lay_drawing(gl_lay_elem * elem)
{
    gl_lay_elem *current = elem;
    
    while (1) {
        if (current->draw != 0)
            (current->draw)();
        if (current->child != 0) {
            gl_lay_drawing((gl_lay_elem *)current->child);
        }
        if (current->next != 0)
            current = (gl_lay_elem *)current->next;
        else
            break;
    }
}
/* Drawing once element */
void gl_lay_drawing_once(gl_lay_elem * elem)
{
    if (elem->draw != 0)
        (elem->draw)();
    if (elem->child != 0)
        gl_lay_drawing((gl_lay_elem *)elem->child);
}
