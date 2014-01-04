#include "lcd.h"
#include "glib.h"
#include "buttons.h"
#include "s_date_set.h"
#include "s_clock_set.h"
#include "s_setup.h"
#include "xprintf.h"
#include "stm32f4xx_rtc.h" 

gl_lay_elem root_e, date, years, months, days;
gl_scr_settings * l_settings;
RTC_DateTypeDef m_date;
int s_date_digit = 0;

void s_date_create(gl_scr_settings * settings);
void s_date_destroy(void);
int s_date_event(uint32_t event, gl_scr_events * events);

gl_screen s_date_set = {
    (p_gl_lay_elem)&root_e,
    s_date_create,
    s_date_destroy,
    s_date_event
};

void s_date_root_draw(void)
{
    lcd_area(24, 0, 9, 48, BLUE);
    lcd_string("DATE SET", 25, 1, 1, WHITE, BLUE);
}

void s_date_date_draw(void)
{
    lcd_string("  /  /  ", 2, 25, 2, WHITE, BLACK);
}

void s_date_draw_years(void)
{
    twice_draw(m_date.RTC_Year, 2, 0, &s_date_digit);
}

void s_date_draw_months(void)
{
    twice_draw(m_date.RTC_Month, 2 + 3 * 6 * 2, 2, &s_date_digit);
}

void s_date_draw_days(void)
{
    twice_draw(m_date.RTC_Date, 2 + 6 * 6 * 2, 4, &s_date_digit);
}

void s_date_create(gl_scr_settings * settings)
{
    l_settings = settings;
    root_e.draw = s_date_root_draw;
    root_e.child = (p_gl_lay_elem)&date;
    root_e.next = 0;
    date.draw = s_date_date_draw;
    date.child = (p_gl_lay_elem)&years;
    date.next = 0;
    years.draw = s_date_draw_years;
    years.child = 0;
    years.next = (p_gl_lay_elem)&months;
    months.draw = s_date_draw_months;
    months.child = 0;
    months.next = (p_gl_lay_elem)&days;
    days.draw = s_date_draw_days;
    days.child = 0;
    days.next = 0;
    RTC_GetDate(RTC_Format_BIN, &m_date);
    gl_lay_drawing(&root_e);
}

void s_date_destroy(void)
{
    lcd_clear(BLACK);
}

void s_date_change_number(int8_t diff)
{
    int8_t dig;
    switch(s_date_digit) {
        case 0:
            dig = m_date.RTC_Year / 10;
            m_date.RTC_Year -= dig * 10;
            change_digit(&dig, diff, 9);
            m_date.RTC_Year += dig * 10;
            break;
        case 1:
            dig = m_date.RTC_Year % 10;
            m_date.RTC_Year -= dig;
            change_digit(&dig, diff, 9);
            m_date.RTC_Year += dig;
            break;
        case 2:
            dig = m_date.RTC_Month / 10;
            m_date.RTC_Month -= dig * 10;
            change_digit(&dig, diff, 1);
            m_date.RTC_Month += dig * 10;
            break;
        case 3:
            dig = m_date.RTC_Month % 10;
            m_date.RTC_Month -= dig;
            change_digit(&dig, diff, 9);
            m_date.RTC_Month += dig;
            break;
        case 4:
            dig = m_date.RTC_Date / 10;
            m_date.RTC_Date -= dig * 10;
            change_digit(&dig, diff, 3);
            m_date.RTC_Date += dig * 10;
            break;
        case 5:
            dig = m_date.RTC_Date % 10;
            m_date.RTC_Date -= dig;
            change_digit(&dig, diff, 9);
            m_date.RTC_Date += dig;
            break;
    }
    if (m_date.RTC_Month < 1)
        m_date.RTC_Month = 1;
    if (m_date.RTC_Month > 12)
        m_date.RTC_Month = 12;
    if (m_date.RTC_Date < 1)
        m_date.RTC_Date = 1;
    if (m_date.RTC_Date > 31)
        m_date.RTC_Date = 31;
}

int s_date_event(uint32_t event, gl_scr_events * events)
{
    int ret = R_OK;
    
    switch (event) {
        case E_BUTTONS:
            switch(events->buttons) {
                case E_B_SET:
                    RTC_SetDate(RTC_Format_BIN, &m_date);
                    l_settings->prev = &s_setup;
                    ret = R_RETURN;
                    break;
                case E_B_SU:
                    if (s_date_digit >= 5)
                        s_date_digit = 0;
                    else
                        s_date_digit++;
                    gl_lay_drawing_once(&date);
                    break;
                case E_B_UP:
                    s_date_change_number(1);
                    gl_lay_drawing_once(&date);
                    break;
                case E_B_DWN:
                    s_date_change_number(-1);
                    gl_lay_drawing_once(&date);
                    break;
            }
            break;
    }
    
    return ret;
}