#include "lcd.h"
#include "glib.h"
#include "buttons.h"
#include "s_watch.h"
#include "s_default.h"
#include "s_setup.h"
#include "xprintf.h"
#include "stm32f4xx_rtc.h"

/* globals */
RTC_TimeTypeDef m_time;
RTC_DateTypeDef m_date;
/* watch postion */
#define X_POS 24
#define Y_POS 30
#define HEIGHT 18
#define WIDTH 47

gl_lay_elem root_e, pane, hours, minutes, seconds, years, months, days;
gl_scr_settings * l_settings;
/* draw pane */
void draw_pane(void)
{
    lcd_area(X_POS, Y_POS, HEIGHT, WIDTH, BLUE);
}
/* draw hours */
void draw_hours(void)
{
    char time[3] = {0};
    xsprintf(time, "%02d", m_time.RTC_Hours);
    lcd_string(time, X_POS + 1, Y_POS + 1, 1, WHITE, BLUE);
}
/* draw minutes */
void draw_minutes(void)
{
    char time[3] = {0};
    xsprintf(time, ":%02d", m_time.RTC_Minutes);
    lcd_string(time, X_POS + 1 + 6 * 2, Y_POS + 1, 1, WHITE, BLUE);
}
/* draw seconds */
void draw_seconds(void)
{
    char time[3] = {0};
    xsprintf(time, ":%02d", m_time.RTC_Seconds);
    lcd_string(time, X_POS + 1 + 6 * 5, Y_POS + 1, 1, WHITE, BLUE);
}
/* draw years */
void draw_years(void)
{
    char date[3] = {0};
    xsprintf(date, "%02d", m_date.RTC_Year);
    lcd_string(date, X_POS + 1, Y_POS + 1 + 9, 1, WHITE, BLUE);
}
/* draw months */
void draw_months(void)
{
    char date[3] = {0};
    xsprintf(date, "/%02d", m_date.RTC_Month);
    lcd_string(date, X_POS + 1 + 6 * 2, Y_POS + 1 + 9, 1, WHITE, BLUE);
}
/* draw days */
void draw_days(void)
{
    char date[3] = {0};
    xsprintf(date, "/%02d", m_date.RTC_Date);
    lcd_string(date, X_POS + 1 + 6 * 5, Y_POS + 1 + 9, 1, WHITE, BLUE);
}
/* update time */
void update_time(void)
{
    RTC_TimeTypeDef n_time;
    RTC_GetTime(RTC_Format_BIN, &n_time);
    
    if (n_time.RTC_Hours != m_time.RTC_Hours) {
        m_time.RTC_Hours = n_time.RTC_Hours;
        gl_lay_drawing_once(&hours);
    }
    if (n_time.RTC_Minutes != m_time.RTC_Minutes) {
        m_time.RTC_Minutes = n_time.RTC_Minutes;
        gl_lay_drawing_once(&minutes);
    }
    if (n_time.RTC_Seconds != m_time.RTC_Seconds) {
        m_time.RTC_Seconds = n_time.RTC_Seconds;
        gl_lay_drawing_once(&seconds);
    }
}
/* update date */
void update_date(void)
{
    RTC_DateTypeDef n_date;
    RTC_GetDate(RTC_Format_BIN, &n_date);
    
    if (n_date.RTC_Year != m_date.RTC_Year) {
        m_date.RTC_Year = n_date.RTC_Year;
        gl_lay_drawing_once(&years);
    }
    if (n_date.RTC_Month != m_date.RTC_Month) {
        m_date.RTC_Month = n_date.RTC_Month;
        gl_lay_drawing_once(&months);
    }
    if (n_date.RTC_Date != m_date.RTC_Date) {
        m_date.RTC_Date = n_date.RTC_Date;
        gl_lay_drawing_once(&days);
    }
}

void s_watch_create(gl_scr_settings * settings);
void s_watch_destroy(void);
int s_watch_event(uint32_t event, gl_scr_events * events);

gl_screen s_watch = {
    (p_gl_lay_elem)&root_e,
    s_watch_create,
    s_watch_destroy,
    s_watch_event
};

void s_watch_root_draw(void)
{
    lcd_area(X_POS - 5, Y_POS - 5, HEIGHT + 10, WIDTH + 10, BLUE / 4);
}

void s_watch_create(gl_scr_settings * settings)
{
    l_settings = settings;
    
    root_e.draw = s_watch_root_draw;
    root_e.child = (p_gl_lay_elem)&pane;
    root_e.next = 0;
    /* drawing clock */
    RTC_GetTime(RTC_Format_BIN, &m_time);
    RTC_GetDate(RTC_Format_BIN, &m_date);
    pane.draw = draw_pane;
    pane.child = (p_gl_lay_elem)&hours;
    pane.next = 0;
    hours.draw = draw_hours;
    hours.child = 0;
    minutes.draw = draw_minutes;
    minutes.child = 0;
    seconds.draw = draw_seconds;
    seconds.child = 0;
    years.draw = draw_years;
    years.child = 0;
    months.draw = draw_months;
    months.child = 0;
    days.draw = draw_days;
    days.child = 0;
    days.next = 0;
    months.next = (p_gl_lay_elem)&days;
    years.next = (p_gl_lay_elem)&months;
    seconds.next = (p_gl_lay_elem)&years;
    hours.next = (p_gl_lay_elem)&minutes;
    minutes.next = (p_gl_lay_elem)&seconds;
    
    gl_lay_drawing(&root_e);
}

void s_watch_destroy(void)
{
    lcd_clear(BLACK);
}

int s_watch_event(uint32_t event, gl_scr_events * events)
{
    int ret = R_OK;
    
    switch (event) {
        case E_BUTTONS:
            switch(events->buttons) {
                case E_B_MOD:
                    l_settings->prev = &s_default;
                    ret = R_RETURN;
                    break;
                case E_B_SET:
                    l_settings->next = &s_setup;
                    ret = R_GO;
                    break;
            }
            break;
    }
    
    update_time();
    update_date();
    
    return ret;
}