#include "stm32f4xx_rcc.h"
#include "stm32f4xx_rtc.h"
#include "stm32f4xx_pwr.h"
#include "rtc.h"
#include "xprintf.h"
/* Setup RTC */
void rtc_setup(void)
{
    RTC_InitTypeDef   RTC_InitStructure;

    /* Enable the PWR clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);

    /* LSI used as RTC source clock */
    /* The RTC Clock may varies due to LSI frequency dispersion. */
    /* Enable the LSI OSC */
    RCC_LSICmd(ENABLE);

    /* Wait till LSI is ready */
    while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);

    /* Select the RTC Clock Source */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);

    /* Enable the RTC Clock */
    RCC_RTCCLKCmd(ENABLE);

    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();

    /* Calendar Configuration with LSI supposed at 32KHz */
    RTC_InitStructure.RTC_AsynchPrediv = 0x7F;
    RTC_InitStructure.RTC_SynchPrediv       =  0xFF; /* (32KHz / 128) - 1 = 0xFF*/
    RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
    RTC_Init(&RTC_InitStructure);
}
/* Get current time */
void rtc_get_time(char *time_buff)
{
    RTC_TimeTypeDef time;
    RTC_GetTime(RTC_Format_BIN, &time);
    
    xsprintf(time_buff, "%02d:%02d:%02d", time.RTC_Hours, time.RTC_Minutes, time.RTC_Seconds);
}