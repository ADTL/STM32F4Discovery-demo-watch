#include "lcd.h"
#include "glib.h"
#include "buttons.h"
#include "s_clock_set.h"
#include "s_setup.h"
#include "xprintf.h"
#include "stm32f4xx_rtc.h"

gl_lay_elem root_e, clock, hours, minutes;
gl_scr_settings * l_settings;
RTC_TimeTypeDef m_time;
int digit = 0;

void create(gl_scr_settings * settings);
void destroy(void);
int event(uint32_t event, gl_scr_events * events);

gl_screen s_clock_set = {
    (p_gl_lay_elem)&root_e,
    create,
    destroy,
    event
};

void root_draw(void)
{
    lcd_area(24, 0, 9, 54, BLUE);
    lcd_string("CLOCK SET", 25, 1, 1, WHITE, BLUE);
}

void clock_draw(void)
{
    lcd_string(":", 20 + 2 * 6 * 2, 25, 2, WHITE, BLACK);
}

void twice_draw(int number, int x_pos, int begin_index, int *digit)
{
    int i, num;
    int16_t font, back;
    
    for (i = 0; i < 2; i++) {
        if (!i)
            num = number / 10;
        else
            num = number % 10;
        if (*digit == i + begin_index) {
            font = BLACK;
            back = WHITE;
        }
        else {
            font = WHITE;
            back = BLACK;
        }
        lcd_area(x_pos + 1 + i * 6 * 2, 24, 17, 12, back);
        lcd_char('0' + num, x_pos + i * 6 * 2, 25, 2, font, back);
    }
}

void change_digit(int8_t *dig, int8_t diff, int8_t lim)
{
    if (diff == 1) {
        if (*dig >= lim)
            *dig = 0;
        else
            (*dig)++;
    }
    else {
        if (*dig <= 0)
            *dig = lim;
        else
            (*dig)--;
    }
}

void change_number(int8_t diff)
{
    int8_t dig;
    switch(digit) {
        case 0:
            dig = m_time.RTC_Hours / 10;
            m_time.RTC_Hours -= dig * 10;
            change_digit(&dig, diff, 2);
            m_time.RTC_Hours += dig * 10;
            break;
        case 1:
            dig = m_time.RTC_Hours % 10;
            m_time.RTC_Hours -= dig;
            change_digit(&dig, diff, 9);
            m_time.RTC_Hours += dig;
            break;
        case 2:
            dig = m_time.RTC_Minutes / 10;
            m_time.RTC_Minutes -= dig * 10;
            change_digit(&dig, diff, 5);
            m_time.RTC_Minutes += dig * 10;
            break;
        case 3:
            dig = m_time.RTC_Minutes % 10;
            m_time.RTC_Minutes -= dig;
            change_digit(&dig, diff, 9);
            m_time.RTC_Minutes += dig;
            break;   
    }
    if (m_time.RTC_Hours > 23)
        m_time.RTC_Hours = 23;
}

void hours_draw(void)
{
    twice_draw(m_time.RTC_Hours, 20, 0, &digit);
}

void minutes_draw(void)
{
    twice_draw(m_time.RTC_Minutes, 20 + 3 * 6 * 2, 2, &digit);
}

void create(gl_scr_settings * settings)
{
    l_settings = settings;
    root_e.draw = root_draw;
    root_e.child = (p_gl_lay_elem)&clock;
    root_e.next = 0;
    clock.draw = clock_draw;
    clock.child = (p_gl_lay_elem)&hours;
    clock.next = 0;
    hours.draw = hours_draw;
    hours.child = 0;
    hours.next = (p_gl_lay_elem)&minutes;
    minutes.draw = minutes_draw;
    minutes.child = 0;
    minutes.next = 0;
    RTC_GetTime(RTC_Format_BIN, &m_time);
    gl_lay_drawing(&root_e);
}

void destroy(void)
{
    lcd_clear(BLACK);
}

int event(uint32_t event, gl_scr_events * events)
{
    int ret = R_OK;
    
    switch (event) {
        case E_BUTTONS:
            switch(events->buttons) {
                case E_B_SET:
                    m_time.RTC_Seconds = 0;
                    RTC_SetTime(RTC_Format_BIN, &m_time);
                    l_settings->prev = &s_setup;
                    ret = R_RETURN;
                    break;
                case E_B_SU:
                    if (digit >= 3)
                        digit = 0;
                    else
                        digit++;
                    gl_lay_drawing_once(&clock);
                    break;
                case E_B_UP:
                    change_number(1);
                    gl_lay_drawing_once(&clock);
                    break;
                case E_B_DWN:
                    change_number(-1);
                    gl_lay_drawing_once(&clock);
                    break;
            }
            break;
    }
    
    return ret;
}