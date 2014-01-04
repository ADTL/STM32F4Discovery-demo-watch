/*-----------------------------------------------------------------------------
* Author: Boris Vinogradov(nis) : no111u3@gmail.com
* File: gpio_af.h
* Type: C header file
* Project: f4examples/05-timers/02-ccr-in-comp-mode
* 2012
*-----------------------------------------------------------------------------*/
/* alternative function of pins */
enum {GPIO_AF0_SYS,
      GPIO_AF1_TIM1_2,
      GPIO_AF2_TIM3_5,
      GPIO_AF3_TIM8_11,
      GPIO_AF4_I2C1_3,
      GPIO_AF5_SPI1_2,
      GPIO_AF6_SPI3,
      GPIO_AF7_USART1_3,
      GPIO_AF8_USART4_6,
      GPIO_AF9_CAN1_2_TIM12_14,
      GPIO_AF10_OTG_FS_HS,
      GPIO_AF11_ETH,
      GPIO_AF12_FSMC_SDIO_OTG_HS,
      GPIO_AF13_DCMI,
      GPIO_AF14,
      GPI0_AF15_EVENTOUT};
/* pin shifting */
#define GPIO_AFP0 0
#define GPIO_AFP1 4
#define GPIO_AFP2 8
#define GPIO_AFP3 12
#define GPIO_AFP4 16
#define GPIO_AFP5 20
#define GPIO_AFP6 24
#define GPIO_AFP7 28
#define GPIO_AFP8 0
#define GPIO_AFP9 4
#define GPIO_AFP10 8
#define GPIO_AFP11 12
#define GPIO_AFP12 16
#define GPIO_AFP13 20
#define GPIO_AFP14 24
#define GPIO_AFP15 28
