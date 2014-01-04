/*-----------------------------------------------------------------------------
* Author: Boris Vinogradov(nis) : no111u3@gmail.com
* File: vectors.c
* Type: C code file
* Project: STM32F4D
* 2013
*-----------------------------------------------------------------------------*/
/* include headers */
#include "stm32f4xx.h"
#include "reset-handler.h"
#include "vectors.h"
/* external vars */
extern unsigned long _estack;
/* default(weak) handler */
void default_handler(void) {
    while (1);
}
/* table of Cortex vectors */
void *vector_table[] __attribute__ ((section(".vectors"))) = {
    &_estack,                   /*! stack begin */
    /* ARM CortexCore interrupts */
    reset_handler,              /*!#0 cortex-m4 reset interrupt begin code of this */
    nmi_handler,                /*!#1 cortex-m4 non maskable interrupt */
    hard_fault_handler,         /*!#2 cortex-m4 hardware fault interrupt */
    mem_manage_handler,         /*!#3 cortex-m4 memory management interrupt */
    bus_fault_handler,          /*!#4 cortex-m4 bus fault interrupt */
    usage_fault_handler,        /*!#5 cortex-m4 usage fault interrupt */
    0,                          /*!#6 reserved */
    0,                          /*!#7 reserved */
    0,                          /*!#8 reserved */
    0,                          /*!#9 reserved */
    svcall_handler,             /*!#10 cortex-m4 system service interrupt */
    debug_monitor_handler,      /*!#11 cortex-m4 debug monitor interrupt */
    0,                          /*!#12 reserved */
    pend_sv_handler,            /*!#13 cortex-m4 penable request for system service interrupt */
    systic_handler,             /*!#14 cortex-m4 system tick timer interrupt */
    /* STM32F4 specific interrupts */
    wwdg_handler,               /*!%0 Window WatchDog              */                                        
    pvd_handler,                /*!%1 PVD through EXTI Line detection */                        
    tamp_stamp_handler,         /*!%2 Tamper and TimeStamps through the EXTI line */            
    rtc_wkup_handler,           /*!%3 RTC Wakeup through the EXTI line */                      
    flash_handler,              /*!%4 FLASH                        */
    rcc_handler,                /*!%5 RCC                          */
    exti0_handler,              /*!%6 EXTI Line0                   */                        
    exti1_handler,              /*!%7 EXTI Line1                   */                          
    exti2_handler,              /*!%8 EXTI Line2                   */                          
    exti3_handler,              /*!%9 EXTI Line3                   */                          
    exti4_handler,              /*!%10 EXTI Line4                   */                          
    dma1_str0_handler,          /*!%11 DMA1 Stream 0                */                  
    dma1_str1_handler,          /*!%12 DMA1 Stream 1                */                   
    dma1_str2_handler,          /*!%13 DMA1 Stream 2                */                   
    dma1_str3_handler,          /*!%14 DMA1 Stream 3                */                   
    dma1_str4_handler,          /*!%15 DMA1 Stream 4                */                   
    dma1_str5_handler,          /*!%16 DMA1 Stream 5                */                   
    dma1_str6_handler,          /*!%17 DMA1 Stream 6                */                   
    adc_handler,                /*!%18 ADC1, ADC2 and ADC3s         */                   
    can1_tx_handler,            /*!%19 CAN1 TX                      */                        
    can1_rx0_handler,           /*!%20 CAN1 RX0                     */                          
    can1_rx1_handler,           /*!%21 CAN1 RX1                     */                          
    can1_sce_handler,           /*!%22 CAN1 SCE                     */                          
    exit9_5_handler,            /*!%23 External Line[9:5]s          */                          
    tim1_brk_tim9_handler,      /*!%24 TIM1 Break and TIM9          */         
    tim1_up_tim10_handler,      /*!%25 TIM1 Update and TIM10        */         
    tim1_trg_com_tim11_handler, /*!%26 TIM1 Trigger and Commutation and TIM11 */
    tim1_cc_handler,            /*!%27 TIM1 Capture Compare         */                          
    tim2_handler,               /*!%28 TIM2                         */                   
    tim3_handler,               /*!%29 TIM3                         */                   
    tim4_handler,               /*!%30 TIM4                         */                   
    i2c1_ev_handler,            /*!%31 I2C1 Event                   */                          
    i2c1_er_handler,            /*!%32 I2C1 Error                   */                          
    i2c2_ev_handler,            /*!%33 I2C2 Event                   */                          
    i2c2_er_handler,            /*!%34 I2C2 Error                   */                            
    spi1_handler,               /*!%35 SPI1                         */                   
    spi2_handler,               /*!%36 SPI2                         */                   
    usart1_handler,             /*!%37 USART1                       */                   
    usart2_handler,             /*!%38 USART2                       */                   
    usart3_handler,             /*!%39 USART3                       */                   
    exti15_10_handler,          /*!%40 External Line[15:10]s        */                          
    rtc_alarm_handler,          /*!%41 RTC Alarm (A and B) through EXTI Line */                 
    usb_otg_fs_wkup_handler,    /*!%42 USB OTG FS Wakeup through EXTI line */                       
    tim8_brk_tim12_handler,     /*!%43 TIM8 Break and TIM12         */         
    tim8_up_tim13_handler,      /*!%44 TIM8 Update and TIM13        */         
    tim8_trg_com_tim14_handler, /*!%45 TIM8 Trigger and Commutation and TIM14 */
    tim8_cc_handler,            /*!%46 TIM8 Capture Compare         */                          
    dma1_str7_handler,          /*!%47 DMA1 Stream7                 */                          
    fsmc_handler,               /*!%48 FSMC                         */                   
    sdio_handler,               /*!%49 SDIO                         */                   
    tim5_handler,               /*!%50 TIM5                         */                   
    spi3_handler,               /*!%51 SPI3                         */                   
    uart4_handler,              /*!%52 UART4                        */                   
    uart5_handler,              /*!%53 UART5                        */                   
    tim6_dac_handler,           /*!%54 TIM6 and DAC1&2 underrun errors */                   
    tim7_handler,               /*!%55 TIM7                         */
    dma2_str0_handler,          /*!%56 DMA2 Stream 0                */                   
    dma2_str1_handler,          /*!%57 DMA2 Stream 1                */                   
    dma2_str2_handler,          /*!%58 DMA2 Stream 2                */                   
    dma2_str3_handler,          /*!%59 DMA2 Stream 3                */                   
    dma2_str4_handler,          /*!%60 DMA2 Stream 4                */                   
    eth_handler,                /*!%61 Ethernet                     */                   
    eth_wkup_handler,           /*!%62 Ethernet Wakeup through EXTI line */                     
    can2_tx_handler,            /*!%63 CAN2 TX                      */                          
    can2_rx0_handler,           /*!%64 CAN2 RX0                     */                          
    can2_rx1_handler,           /*!%65 CAN2 RX1                     */                          
    can2_sce_handler,           /*!%66 CAN2 SCE                     */                          
    otg_fs_handler,             /*!%67 USB OTG FS                   */                   
    dma2_str5_handler,          /*!%68 DMA2 Stream 5                */                   
    dma2_str6_handler,          /*!%69 DMA2 Stream 6                */                   
    dma2_str7_handler,          /*!%70 DMA2 Stream 7                */                   
    usart6_handler,             /*!%71 USART6                       */                    
    i2c3_ev_handler,            /*!%72 I2C3 event                   */                          
    i2c3_er_handler,            /*!%73 I2C3 error                   */                          
    otg_hs_ep1_out_handler,     /*!%74 USB OTG HS End Point 1 Out   */                   
    otg_hs_ep1_in_handler,      /*!%75 USB OTG HS End Point 1 In    */                   
    otg_hs_wkup_handler,        /*!%76 USB OTG HS Wakeup through EXTI */                         
    oth_hs_handler,             /*!%77 USB OTG HS                   */                   
    dcmi_handler,               /*!%78 DCMI                         */                   
    cryp_handler,               /*!%79 CRYP crypto                  */                   
    hash_rng_handler,           /*!%80 Hash and Rng                 */
    fpu_handler,                /*!%81 FPU                          */
};
