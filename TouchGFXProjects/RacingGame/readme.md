# STM32F429I_DISCO_REV_E01 TBS Version 3.0.4.

Please note this TouchGFX Board Setup is only supported from TouchGFX 4.20.0. Configuration is done using CubeMX 6.5.0 based on STM32Cube FW_F4 V1.27.0 drivers. The default IDE is set to STM32CubeIDE, to change IDE open the STM32F429I_DISCO_REV_E01.ioc with CubeMX and select from the supported IDEs (EWARM from version 8.50.9, MDK-ARM, and STM32CubeIDE). Supports flashing of the STM32F429I_DISCO_REV_E01 board directly from TouchGFX Designer using GCC and STM32CubeProgrammer.Flashing the board requires STM32CubeProgrammer which can be downloaded from the ST webpage. 

This TBS is configured for 320 x 240 pixels 16bpp screen resolution.  

Performance testing can be done using the GPIO pins designated with the following signals: VSYNC_FREQ  - Pin PE2, RENDER_TIME - Pin PE3, FRAME_RATE  - Pin PE4, MCU_ACTIVE  - Pin PE5
 