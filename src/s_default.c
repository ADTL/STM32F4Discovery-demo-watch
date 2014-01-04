#include "lcd.h"
#include "glib.h"
#include "buttons.h"
#include "test-img.h"
#include "s_default.h"
#include "s_watch.h"

gl_lay_elem root_e;
gl_scr_settings * l_settings;

void s_default_create(gl_scr_settings * settings);
void s_default_destroy(void);
int s_default_event(uint32_t event, gl_scr_events * events);

gl_screen s_default = {
    (p_gl_lay_elem)&root_e,
    s_default_create,
    s_default_destroy,
    s_default_event
};

void s_default_root_draw(void)
{
    int i;
    for (i = 0; i < 2; i++)
        lcd_image(i * 10, i * 10, test.height, test.width, test.data);
}

void s_default_create(gl_scr_settings * settings)
{
    l_settings = settings;
    
    root_e.draw = s_default_root_draw;
    root_e.child = 0;
    root_e.next = 0;
    
    gl_lay_drawing(&root_e);
}

void s_default_destroy(void)
{
    lcd_clear(BLACK);
}

int s_default_event(uint32_t event, gl_scr_events * events)
{
    int ret = R_OK;
    switch (event) {
        case E_BUTTONS:
            switch(events->buttons) {
                case E_B_MOD:
                    l_settings->next = &s_watch;
                    ret = R_GO;
                    break;
            }
            break;
    }
    
    return ret;
}
