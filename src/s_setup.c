#include "lcd.h"
#include "glib.h"
#include "buttons.h" 
#include "s_setup.h"
#include "s_watch.h"
#include "s_clock_set.h"
#include "s_date_set.h"

gl_lay_elem root_e, menu;
gl_scr_settings * l_settings;

char s_setup_menu[][10] = { "CLOCK", "DATE" };
char menu_index = 0;

void s_setup_create(gl_scr_settings * settings);
void s_setup_destroy(void);
int s_setup_event(uint32_t event, gl_scr_events * events);

gl_screen s_setup = {
    (p_gl_lay_elem)&root_e,
    s_setup_create,
    s_setup_destroy,
    s_setup_event
};

void s_setup_root_draw(void)
{
    lcd_area(24, 0, 9, 30, BLUE);
    lcd_string("SETUP", 25, 1, 1, WHITE, BLUE);
}

void s_setup_menu_draw(void)
{
    int i;
    int16_t font, back;
    
    for (i = 0; i < 2; i++) {
        if (menu_index == i) {
            font = BLACK;
            back = WHITE;
        }
        else {
            font = WHITE;
            back = BLACK;
        }
        lcd_area(24, 19 + i * 9, 9, 30, back);
        lcd_string(s_setup_menu[i], 25, 20 + i * 9, 1, font, back);
    }
}

void s_setup_create(gl_scr_settings * settings)
{
    l_settings = settings;
    root_e.draw = s_setup_root_draw;
    root_e.child = (p_gl_lay_elem)&menu;
    root_e.next = 0;
    menu.draw = s_setup_menu_draw;
    menu.child = 0;
    menu.next = 0;
    gl_lay_drawing(&root_e);
}

void s_setup_destroy(void)
{
    lcd_clear(BLACK);
}

int s_setup_event(uint32_t event, gl_scr_events * events)
{
    int ret = R_OK;
    
    switch (event) {
        case E_BUTTONS:
            switch(events->buttons) {
                case E_B_SET:
                    l_settings->prev = &s_watch;
                    ret = R_RETURN;
                    break;
                case E_B_UP:
                    if (menu_index <= 0)
                        menu_index = 1;
                    else
                        menu_index--;
                    gl_lay_drawing_once(&menu);
                    break;
                case E_B_DWN:
                    if (menu_index >= 1)
                        menu_index = 0;
                    else
                        menu_index++;
                    gl_lay_drawing_once(&menu);
                    break;
                case E_B_SU:
                    if (menu_index == 0)
                        l_settings->next = &s_clock_set;
                    else
                        l_settings->next = &s_date_set;
                    ret = R_GO;
                    break;
            }
            break;
    }
    
    return ret;
}