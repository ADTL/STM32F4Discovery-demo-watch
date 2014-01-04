#pragma once
/*
 * Graphic lib
 */
#include <stdint.h>
/*
 * Layout
 */
/* prototype of element */
struct gl_lay_elem;
typedef struct gl_lay_elem * p_gl_lay_elem;
/* GLIB layout element */
typedef struct {
    void (*draw)(void); /* Drawing method for current element */
    p_gl_lay_elem next; /* next element on leaf */
    p_gl_lay_elem child; /* first child of this node */
} gl_lay_elem;

/* Drawing element and subtree */
void gl_lay_drawing(gl_lay_elem * elem);
/* Drawing once element */
void gl_lay_drawing_once(gl_lay_elem * elem);
/*
 * Screen
 */

enum ret_values {
    R_OK,
    R_RETURN,
    R_GO
};

enum event_state {
    E_NULL,
    E_BUTTONS,
    E_UPDATE,
    E_TIMER
};

struct gl_scr_events;
typedef struct gl_scr_events * p_gl_scr_events;

struct gl_screen;
typedef struct gl_screen * p_gl_screen;

struct gl_scr_settings;
typedef struct gl_scr_settings * p_gl_scr_settings;
/* GLIB screen events */
typedef struct {
    uint32_t buttons;
} gl_scr_events;
/* GLIB screen element */
typedef struct {
    p_gl_lay_elem root;         /* root of layout */
    void (*create)(p_gl_scr_settings); /* create callback */
    void (*destroy)(void);      /* destroy callback */
    int (*event)(uint32_t, p_gl_scr_events);        /* events loopback */
} gl_screen;
/* GLIB screen settings */
typedef struct {
    gl_screen *curr;
    gl_screen *prev;
    gl_screen *next;
    gl_screen *def;
} gl_scr_settings;
/* Go to next screen */
void gl_scr_go(gl_scr_settings * settings);
/* Return to previous screen */
void gl_scr_return(gl_scr_settings * settings);