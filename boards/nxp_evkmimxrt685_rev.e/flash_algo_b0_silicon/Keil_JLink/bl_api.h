/*
 * The Clear BSD License
 * Copyright 2017-2018 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted (subject to the limitations in the
 * disclaimer below) provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 *
 * * Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
 * GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
 * HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#include "flexspi_nor_flash.h"


////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief Boot parameters of the user application
//!  WORD    OFFSET      FIELD                            DESCRIPTION
//!          [31:24]     TAG                             Must be '0xEB'
//!          [23:20]     Boot mode                       0:Master boot mode; 1: ISP boot
//!          [19:16]     Boot interface                  0:USART 1:I2C 2:SPI 3:USB HID 4:QSPI 5:USB DFU 6:SD 7:MMC
//!          [15:12]     Boot instance                   0 or 1; This instance is only used when boot interface is SD or
//!          MMC,
//!                                                      for other interfaces it is ignored
//!          [11:08]     Redundant boot image index      Redundant boot image index for FlexSPI NOR flash
//!          [07:00]     Reserved
//!
//!  TAG[31:24]	BOOT MODE[23:20]       INTERFACE[19:16]	  INSTANCE[15:12]	 RBII            Reserved[07:00]	COMBINATION
//!  BOOT ACTION
//!   0xEB	0	                0	                X	          X                X	                0xEB00XXXX	MASTR BOOT:
//!   USART
//!	        0	                1	                X	          X                X	                0xEB01XXXX	MASTR BOOT:
//! I2C
//!	        0	                2	                X	          X                X	                0xEB02XXXX	MASTR BOOT:
//! SPI
//!	        0	                3	                X	          X                X	                0xEB03XXXX	MASTR BOOT:
//! USB HID
//!	        0	                4	                X	          0                X	                0xEB04X0XX	MASTR BOOT:
//! FlexSPI:boot image index 0
//!	        0	                4	                X	          1                X	                0xEB04X1XX	MASTR BOOT:
//! FlexSPI:boot image index 1
//!	        0	                5	                X	          X                X	                0xEB05XXXX	MASTR BOOT:
//! USB DFU
//!	        0	                6	                0	          X                X	                0xEB060XXX	MASTR BOOT:
//! SDINSTANCE 0)
//!	        0	                6	                1	          X                X	                0xEB061XXX	MASTR BOOT:
//! SDINSTANCE 1)
//!	        0	                7	                0	          X                X	                0xEB070XXX	MASTR BOOT:
//! MMC(INSTANCE 0)
//!	        0	                7	                1	          X                X	                0xEB071XXX	MASTR BOOT:
//! MMC(INSTANCE 1)
//!	        1	                0	                X	          X                X	                0xEB10XXXX	ISP BOOT:
//! USART
//!	        1	                1	                X	          X                X	                0xEB11XXXX	ISP BOOT: I2C
//!	        1	                2	                X	          X                X	                0xEB12XXXX	ISP BOOT: SPI
//!

typedef struct _user_app_boot_invoke_option
{
    union
    {
        struct
        {
            uint32_t reserved : 8;
            uint32_t boot_image_index : 4;
            uint32_t instance : 4;
            uint32_t boot_interface : 4;
            uint32_t mode : 4;
            uint32_t tag : 8;
        } B;
        uint32_t U;
    } option;
} user_app_boot_invoke_option_t;

//! @brief Boot interface can be selected by user application
//! @note  For USB-HID QSPI USB-DFU SD MMC, these interfaces are invalid for ISP boot
enum
{
    kUserAppBootPeripheral_UART = 0u,
    kUserAppBootPeripheral_I2C = 1u,
    kUserAppBootPeripheral_SPI = 2u,
    kUserAppBootPeripheral_USB_HID = 3u,
    kUserAppBootPeripheral_QSPI = 4u,
    kUserAppBootPeripheral_DFU = 5u,
    kUserAppBootPeripheral_SD = 6u,
    kUserAppBootPeripheral_MMC = 7u,
};

//! @brief Boot mode can be selected by user application
//! @note  For master boot, valid boot insterfaces for user application are USART I2C SPI USB-HID USB-DFU SD MMC
//!        For ISP boot, valid boot interfaces for user application are USART I2C SPI
enum
{
    kUserAppBootMode_MasterBoot = 0,
    kUserAppBootMode_IspBoot = 1,
};

//!@brief FLEXSPI ROOT CLOCK soruce related definitions
enum
{
    kFlexSpiClockSrc_MainClk = 0,
    kFlexSpiClockSrc_MainPllClk,
    kFlexSpiClockSrc_Aux0PllClk,
    kFlexSpiClockSrc_FFRO_Clk,
    kFlexSpiClockSrc_Aux1PllClk,
};

//!@brief FLEXSPI clock configuration - When clock source is PLL
enum
{
    kFlexSpiSerialClk_30MHz = 1,
    kFlexSpiSerialClk_50MHz = 2,
    kFlexSpiSerialClk_60MHz = 3,
    kFlexSpiSerialClk_80MHz = 4,
    kFlexSpiSerialClk_100MHz = 5,
    kFlexSpiSerialClk_120MHz = 6,
    kFlexSpiSerialClk_133MHz = 7,
    kFlexSpiSerialClk_166MHz = 8,
    kFlexSpiSerialClk_200MHz = 9,
};

//!@brief FLEXSPI clock configuration - When clock source is FRO192
enum
{
    kFlexSpiSerialClk_32MHz = 1,
    kFlexSpiSerialClk_48MHz = 2,
    kFlexSpiSerialClk_64MHz = 3,
    kFlexSpiSerialClk_96MHz = 4,
};

//!@brief FLEXSPI Flash driver API Interface
typedef struct
{
    uint32_t version;
    status_t (*init)(uint32_t instance, flexspi_nor_config_t *config);
    status_t (*page_program)(uint32_t instance, flexspi_nor_config_t *config, uint32_t dstAddr, const uint32_t *src);
    status_t (*erase_all)(uint32_t instance, flexspi_nor_config_t *config);
    //    status_t (*wait_busy)(uint32_t instance, flexspi_nor_config_t *config, bool isParallelMode, uint32_t address);
    status_t (*erase)(uint32_t instance, flexspi_nor_config_t *config, uint32_t start, uint32_t length);
    status_t (*erase_sector)(uint32_t instance, flexspi_nor_config_t *config, uint32_t address);
    status_t (*erase_block)(uint32_t instance, flexspi_nor_config_t *config, uint32_t address);
    status_t (*get_config)(uint32_t instance, flexspi_nor_config_t *config, serial_nor_config_option_t *option);
    status_t (*read)(uint32_t instance, flexspi_nor_config_t *config, uint32_t *dst, uint32_t start, uint32_t bytes);
    //    status_t (*hw_reset)(uint32_t instance, flexspi_nor_config_t *config);
    status_t (*xfer)(uint32_t instance, flexspi_xfer_t *xfer);
    status_t (*update_lut)(uint32_t instance, uint32_t seqIndex, const uint32_t *lutBase, uint32_t numberOfSeq);
    status_t (*set_clock_source)(uint32_t clockSrc);
    void (*config_clock)(uint32_t instance, uint32_t freqOption, uint32_t sampleClkMode);
} flexspi_nor_flash_driver_t;

//!@brief OTP driver API Interface
typedef struct
{
    status_t (*init)(uint32_t src_clk_freq);
    status_t (*deinit)(void);
    status_t (*fuse_read)(uint32_t addr, uint32_t *data);
    status_t (*fuse_program)(uint32_t addr, uint32_t data, bool lock);
    status_t (*crc_calc)(uint32_t *src, uint32_t numberOfWords, uint32_t *crcChecksum);
    status_t (*reload)(void);
    status_t (*crc_check)(uint32_t start_addr, uint32_t end_addr, uint32_t crc_addr);
} ocotp_driver_t;

//! @brief Root of the bootloader API tree.
//!
//! An instance of this struct resides in read-only memory in the bootloader. It
//! provides a user application access to APIs exported by the bootloader.
//!
//! @note The order of existing fields must not be changed.
//!
//! @ingroup context
typedef struct BootloaderTree
{
    void (*runBootloader)(void *arg); //!< Function to start the bootloader executing.
    uint32_t version;                 //!< Bootloader version number.
    const char *copyright;            //!< Copyright string.
    const uint32_t reserved0;
    const uint32_t reserved1;
    const uint32_t reserved2;
    const uint32_t reserved3;
    const flexspi_nor_flash_driver_t *flexspiNorDriver; //!< FlexSPI NOR FLASH Driver API.
    const ocotp_driver_t *otpDriver;                    //!< OTP driver API.
    const uint32_t reserved4;
} bootloader_tree_t;


/* ROM API Tree address */
#define g_bootloaderTree ((bootloader_tree_t*)(0x1303f000))


#if defined(__cplusplus)
extern "C" {
#endif

#if defined(__cplusplus)
}
#endif

