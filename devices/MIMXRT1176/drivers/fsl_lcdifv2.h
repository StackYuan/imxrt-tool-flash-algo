/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_LCDIFV2_H_
#define _FSL_LCDIFV2_H_

#include "fsl_common.h"

/*!
 * @addtogroup lcdifv2
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief LCDIF v2 driver version */
#define FSL_LCDIFV2_DRIVER_VERSION (MAKE_VERSION(2, 0, 1))
/*@}*/

/*! @brief LCDIF v2 FIFO empty interrupt. */
#define LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(layer) (1U << ((uint32_t)(layer) + 24U))
/*! @brief LCDIF v2 DMA done interrupt. */
#define LCDIFV2_MAKE_DMA_DONE_INTERRUPT(layer) (1U << ((uint32_t)(layer) + 16U))
/*! @brief LCDIF v2 DMA error interrupt. */
#define LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(layer) (1U << ((uint32_t)(layer) + 8U))

/* LUT memory entery number. */
#define LCDIFV2_LUT_ENTRY_NUM 256

/*!
 * @brief LCDIF v2 signal polarity flags
 */
enum _lcdifv2_polarity_flags
{
    kLCDIFV2_VsyncActiveLow            = LCDIFV2_CTRL_INV_VS_MASK,   /*!< VSYNC active low. */
    kLCDIFV2_VsyncActiveHigh           = 0U,                         /*!< VSYNC active high. */
    kLCDIFV2_HsyncActiveLow            = LCDIFV2_CTRL_INV_HS_MASK,   /*!< HSYNC active low. */
    kLCDIFV2_HsyncActiveHigh           = 0U,                         /*!< HSYNC active high. */
    kLCDIFV2_DataEnableActiveLow       = LCDIFV2_CTRL_INV_DE_MASK,   /*!< Data enable line active low. */
    kLCDIFV2_DataEnableActiveHigh      = 0U,                         /*!< Data enable line active high. */
    kLCDIFV2_DriveDataOnFallingClkEdge = LCDIFV2_CTRL_INV_PXCK_MASK, /*!< Drive data on falling clock edge, capture data
                                                 on rising clock edge. */
    kLCDIFV2_DriveDataOnRisingClkEdge = 0U,                          /*!< Drive data on falling
                                                                                                 clock edge, capture data
                                                                                                 on rising clock edge. */
    kLCDIFV2_DataActiveLow  = LCDIFV2_CTRL_NEG_MASK,                 /*!< Data active high. */
    kLCDIFV2_DataActiveHigh = 0U,                                    /*!< Data active high. */
};

/*!
 * @brief The LCDIF v2 interrupts.
 */
enum _lcdifv2_interrupt
{
    kLCDIFV2_Layer0FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(0), /*!< Layer 0 FIFO empty. */
    kLCDIFV2_Layer1FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(1), /*!< Layer 1 FIFO empty. */
    kLCDIFV2_Layer2FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(2), /*!< Layer 2 FIFO empty. */
    kLCDIFV2_Layer3FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(3), /*!< Layer 3 FIFO empty. */
    kLCDIFV2_Layer4FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(4), /*!< Layer 4 FIFO empty. */
    kLCDIFV2_Layer5FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(5), /*!< Layer 5 FIFO empty. */
    kLCDIFV2_Layer6FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(6), /*!< Layer 6 FIFO empty. */
    kLCDIFV2_Layer7FifoEmptyInterrupt  = LCDIFV2_MAKE_FIFO_EMPTY_INTERRUPT(7), /*!< Layer 7 FIFO empty. */
    kLCDIFV2_Layer0DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(0),   /*!< Layer 0 DMA done. */
    kLCDIFV2_Layer1DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(1),   /*!< Layer 1 DMA done. */
    kLCDIFV2_Layer2DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(2),   /*!< Layer 2 DMA done. */
    kLCDIFV2_Layer3DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(3),   /*!< Layer 3 DMA done. */
    kLCDIFV2_Layer4DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(4),   /*!< Layer 4 DMA done. */
    kLCDIFV2_Layer5DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(5),   /*!< Layer 5 DMA done. */
    kLCDIFV2_Layer6DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(6),   /*!< Layer 6 DMA done. */
    kLCDIFV2_Layer7DmaDoneInterrupt    = LCDIFV2_MAKE_DMA_DONE_INTERRUPT(7),   /*!< Layer 7 DMA done. */
    kLCDIFV2_Layer0DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(0),  /*!< Layer 0 DMA error. */
    kLCDIFV2_Layer1DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(1),  /*!< Layer 1 DMA error. */
    kLCDIFV2_Layer2DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(2),  /*!< Layer 2 DMA error. */
    kLCDIFV2_Layer3DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(3),  /*!< Layer 3 DMA error. */
    kLCDIFV2_Layer4DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(4),  /*!< Layer 4 DMA error. */
    kLCDIFV2_Layer5DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(5),  /*!< Layer 5 DMA error. */
    kLCDIFV2_Layer6DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(6),  /*!< Layer 6 DMA error. */
    kLCDIFV2_Layer7DmaErrorInterrupt   = LCDIFV2_MAKE_DMA_ERROR_INTERRUPT(7),  /*!< Layer 7 DMA error. */
    kLCDIFV2_StoreErrorInterrupt       = (1U << 5U), /*!< Store frame error on AXI interface. */
    kLCDIFV2_StoreFrameDoneInterrupt   = (1U << 4U), /*!< Current frame being stored has finished. */
    kLCDIFV2_VerticalBlankingInterrupt = (1U << 2U), /*!< Start of vertical blanking period. */
    kLCDIFV2_OutputUnderrunInterrupt   = (1U << 1U), /*!< Output buffer underrun. */
    kLCDIFV2_VsyncEdgeInterrupt        = (1U << 0U), /*!< Interrupt at VSYNC edge. */
};

/*! @brief The LCDIF v2 output line order. */
typedef enum _lcdifv2_line_order
{
    kLCDIFV2_LineOrderRGB = 0, /*!< RGB */
    kLCDIFV2_LineOrderRBG,     /*!< RBG */
    kLCDIFV2_LineOrderGBR,     /*!< GBR */
    kLCDIFV2_LineOrderGRB,     /*!< GRB */
    kLCDIFV2_LineOrderBRG,     /*!< BRG */
    kLCDIFV2_LineOrderBGR,     /*!< BGR */
} lcdifv2_line_order_t;

/*!
 * @brief LCDIF v2 display configure structure.
 */
typedef struct _lcdifv2_display_config
{
    uint16_t panelWidth;    /*!< Display panel width, pixels per line. */
    uint16_t panelHeight;   /*!< Display panel height, how many lines per panel. */
    uint8_t hsw;            /*!< HSYNC pulse width. */
    uint8_t hfp;            /*!< Horizontal front porch. */
    uint8_t hbp;            /*!< Horizontal back porch. */
    uint8_t vsw;            /*!< VSYNC pulse width. */
    uint8_t vfp;            /*!< Vrtical front porch. */
    uint8_t vbp;            /*!< Vertical back porch. */
    uint32_t polarityFlags; /*!< OR'ed value of @ref _lcdifv2_polarity_flags, used to contol the signal polarity. */
    lcdifv2_line_order_t lineOrder; /*!< Line order. */
} lcdifv2_display_config_t;

/*! @brief LCDIF v2 color space conversion mode. */
typedef enum _lcdifv2_csc_mode
{
    kLCDIFV2_CscDisable = 0U, /*!< Disable the CSC. */
    kLCDIFV2_CscYUV2RGB,      /*!< YUV to RGB. */
    kLCDIFV2_CscYCbCr2RGB,    /*!< YCbCr to RGB. */
} lcdifv2_csc_mode_t;

typedef enum _lcdifv2_pixel_format
{
    kLCDIFV2_PixelFormatIndex1BPP = LCDIFV2_CTRLDESCL5_BPP(0U), /*!< LUT index 1 bit. */
    kLCDIFV2_PixelFormatIndex2BPP = LCDIFV2_CTRLDESCL5_BPP(1U), /*!< LUT index 2 bit. */
    kLCDIFV2_PixelFormatIndex4BPP = LCDIFV2_CTRLDESCL5_BPP(2U), /*!< LUT index 4 bit. */
    kLCDIFV2_PixelFormatIndex8BPP = LCDIFV2_CTRLDESCL5_BPP(3U), /*!< LUT index 8 bit. */
    kLCDIFV2_PixelFormatRGB565    = LCDIFV2_CTRLDESCL5_BPP(4U), /*!< RGB565, two pixels use 32 bits. */
    kLCDIFV2_PixelFormatARGB1555  = LCDIFV2_CTRLDESCL5_BPP(5U), /*!< ARGB1555, two pixels use 32 bits. */
    kLCDIFV2_PixelFormatARGB4444  = LCDIFV2_CTRLDESCL5_BPP(6U), /*!< ARGB4444, two pixels use 32 bits. */
    kLCDIFV2_PixelFormatUYVY      = LCDIFV2_CTRLDESCL5_BPP(7U) |
                               LCDIFV2_CTRLDESCL5_YUV_FORMAT(0U), /*!< UYVY, only layer 0 and layer 1 support this. */
    kLCDIFV2_PixelFormatVYUY = LCDIFV2_CTRLDESCL5_BPP(7U) |
                               LCDIFV2_CTRLDESCL5_YUV_FORMAT(1U), /*!< VYUY, only layer 0 and layer 1 support this. */
    kLCDIFV2_PixelFormatYUYV = LCDIFV2_CTRLDESCL5_BPP(7U) |
                               LCDIFV2_CTRLDESCL5_YUV_FORMAT(2U), /*!< YUYV, only layer 0 and layer 1 support this. */
    kLCDIFV2_PixelFormatYVYU = LCDIFV2_CTRLDESCL5_BPP(7U) |
                               LCDIFV2_CTRLDESCL5_YUV_FORMAT(3U), /*!< YVYU, only layer 0 and layer 1 support this. */
    kLCDIFV2_PixelFormatRGB888   = LCDIFV2_CTRLDESCL5_BPP(8U),    /*!< RGB888 packed, one pixel uses 24 bits. */
    kLCDIFV2_PixelFormatARGB8888 = LCDIFV2_CTRLDESCL5_BPP(9U),    /*!< ARGB8888 unpacked, one pixel uses 32 bits. */
    kLCDIFV2_PixelFormatABGR8888 = LCDIFV2_CTRLDESCL5_BPP(10U),   /*!< ABGR8888 unpacked, one pixel uses 32 bits. */
} lcdifv2_pixel_format_t;

/*! @brief LCDIF v2 source buffer configuration. */
typedef struct _lcdifv2_buffer_config
{
    uint16_t strideBytes; /*!< Number of bytes between two vertically adjacent pixels, suggest 64-bit aligned. */
    lcdifv2_pixel_format_t pixelFormat; /*!< Source buffer pixel format. */
} lcdifv2_buffer_config_t;

/*!
 * @brief LCDIF v2 layer alpha blending mode.
 */
typedef enum _lcdifv2_alpha_mode
{
    kLCDIFV2_AlphaDisable,   /*!< Disable alpha blend. */
    kLCDIFV2_AlphaOverride,  /*!< Use the gobal alpha value, pixel defined alpha value is overridden. */
    kLCDIFV2_AlphaEmbedded,  /*!< Use the pixel defined alpha value. */
    kLCDIFV2_AlphaPoterDuff, /*!< Use the PoterDuff alpha blending. */
} lcdifv2_alpha_mode_t;

/*!
 * @brief LCDIF v2 PoterDuff alpha mode.
 */
typedef enum _lcdifv2_pd_alpha_mode
{
    kLCDIFV2_PD_AlphaStraight = 0, /*!< Straight mode. */
    kLCDIFV2_PD_AlphaInversed = 1, /*!< Inversed mode. */
} lcdifv2_pd_alpha_mode_t;

/*!
 * @brief LCDIF v2 PoterDuff color mode.
 */
typedef enum _lcdifv2_pd_color_mode
{
    kLCDIFV2_PD_ColorStraight = 0, /*!< Straight mode. */
    kLCDIFV2_PD_ColorInversed = 1, /*!< Inversed mode. */
} lcdifv2_pd_color_mode_t;

/*!
 * @brief LCDIF v2 PoterDuff global alpha mode.
 */
typedef enum _lcdifv2_pd_global_alpha_mode
{
    kLCDIFV2_PD_GlobalAlpha = 0, /*!< Use global alpha. */
    kLCDIFV2_PD_LocalAlpha  = 1, /*!< Use local alpha. */
    kLCDIFV2_PD_ScaledAlpha = 2, /*!< Use scaled alpha. */
} lcdifv2_pd_global_alpha_mode_t;

/*!
 * @brief LCDIF v2 PoterDuff factor mode.
 */
typedef enum _lcdifv2_pd_factor_mode
{
    kLCDIFV2_PD_FactorOne           = 0, /*!< Use 1. */
    kLCDIFV2_PD_FactorZero          = 1, /*!< Use 0. */
    kLCDIFV2_PD_FactorStraightAlpha = 2, /*!< Use straight alpha. */
    kLCDIFV2_PD_FactorInversedAlpha = 3, /*!< Use inversed alpha. */
} lcdifv2_pd_factor_mode_t;

/*!
 * @brief LCDIF v2 layer alpha blending configuration.
 */
typedef struct _lcdifv2_blend_config
{
    uint8_t globalAlpha;                              /*!< Global alpha value, only used when
                                                        @ref alphaMode is @ref kLCDIFV2_AlphaOverride or
                                                        @ref kLCDIFV2_AlphaPoterDuff */
    lcdifv2_alpha_mode_t alphaMode;                   /*!< Alpha mode. */
    lcdifv2_pd_alpha_mode_t pdAlphaMode;              /*!< PoterDuff alpha mode, only used when @ref alphaMode is @ref
                                                        kLCDIFV2_AlphaPoterDuff */
    lcdifv2_pd_color_mode_t pdColorMode;              /*!< PoterDuff color mode, only used when @ref alphaMode is @ref
                                                        kLCDIFV2_AlphaPoterDuff */
    lcdifv2_pd_global_alpha_mode_t pdGlobalAlphaMode; /*!< PoterDuff global alpha mode, only used when @ref alphaMode is
                                           @ref kLCDIFV2_AlphaPoterDuff */
    lcdifv2_pd_factor_mode_t pdFactorMode;            /*!< PoterDuff factor mode, only used when @ref alphaMode is @ref
                                                      kLCDIFV2_AlphaPoterDuff */
} lcdifv2_blend_config_t;

/*!
 * @brief LCDIF v2 write buffer pixel format.
 */
typedef enum _lcdifv2_store_pixel_format
{
    kLCDIFV2_StorePixelFormatARGB8888, /*!< 32-bpp ARGB8888. */
    kLCDIFV2_StorePixelFormatRGB888,   /*!< 24-bpp RGB888. */
} lcdifv2_store_pixel_format_t;

typedef struct _lcdifv2_store_buffer_config
{
    uint32_t bufferAddr;  /*!< Output buffer address, suggest 64-bit aligned for better performance. */
    uint16_t strideBytes; /*!< Number of bytes between two vertically adjacent pixels, suggest 64-bit aligned for
                            better performance. */
    lcdifv2_store_pixel_format_t pixelFormat; /*!< Store pixel format. */
} lcdifv2_store_buffer_config_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @name LCDIF v2 initialization and de-initialization
 * @{
 */

/*!
 * @brief Initializes the LCDIF v2.
 *
 * This function ungates the LCDIF v2 clock and release the peripheral reset.
 *
 * @param base LCDIF v2 peripheral base address.
 */
void LCDIFV2_Init(LCDIFV2_Type *base);

/*!
 * @brief Deinitializes the LCDIF peripheral.
 *
 * @param base LCDIF peripheral base address.
 */
void LCDIFV2_Deinit(LCDIFV2_Type *base);

/*!
 * @brief Reset the LCDIF v2.
 *
 * @param base LCDIF peripheral base address.
 */
void LCDIFV2_Reset(LCDIFV2_Type *base);

/* @} */

/*!
 * @name Display
 * @{
 */

/*!
 * @brief Gets the LCDIF display default configuration structure.
 *
 * This function sets the configuration structure to default values.
 * The default configuration is set to the following values.
 * @code
    config->panelWidth    = 0U;
    config->panelHeight   = 0U;
    config->hsw           = 3U;
    config->hfp           = 3U;
    config->hbp           = 3U;
    config->vsw           = 3U;
    config->vfp           = 3U;
    config->vbp           = 3U;
    config->polarityFlags = kLCDIFV2_VsyncActiveHigh | kLCDIFV2_HsyncActiveHigh | kLCDIFV2_DataEnableActiveHigh |
                            kLCDIFV2_DriveDataOnRisingClkEdge | kLCDIFV2_DataActiveHigh;
    config->lineOrder       = kLCDIFV2_LineOrderRGB;
    @code
 *
 * @param config Pointer to the LCDIF configuration structure.
 */
void LCDIFV2_DisplayGetDefaultConfig(lcdifv2_display_config_t *config);

/*!
 * @brief Set the LCDIF v2 display configurations.
 *
 * @param base LCDIF peripheral base address.
 * @param config Pointer to the LCDIF configuration structure.
 */
void LCDIFV2_SetDisplayConfig(LCDIFV2_Type *base, const lcdifv2_display_config_t *config);

/*!
 * @brief Enable or disable the display
 *
 * @param base LCDIF peripheral base address.
 * @param enable Enable or disable.
 */
static inline void LCDIFV2_EnableDisplay(LCDIFV2_Type *base, bool enable)
{
    if (enable)
    {
        base->DISP_PARA |= LCDIFV2_DISP_PARA_DISP_ON_MASK;
    }
    else
    {
        base->DISP_PARA &= ~LCDIFV2_DISP_PARA_DISP_ON_MASK;
    }
}

/* @} */

/*!
 * @name Interrupts
 * @{
 */

/*!
 * @brief Enables LCDIF interrupt requests.
 *
 * @param base LCDIF peripheral base address.
 * @param domain CPU domain the interrupt signal routed to.
 * @param mask interrupt source, OR'ed value of _lcdifv2_interrupt.
 */
static inline void LCDIFV2_EnableInterrupts(LCDIFV2_Type *base, uint8_t domain, uint32_t mask)
{
    base->INT[domain].INT_ENABLE |= mask;
}

/*!
 * @brief Disables LCDIF interrupt requests.
 *
 * @param base LCDIF peripheral base address.
 * @param domain CPU domain the interrupt signal routed to.
 * @param mask interrupt source, OR'ed value of _lcdifv2_interrupt.
 */
static inline void LCDIFV2_DisableInterrupts(LCDIFV2_Type *base, uint8_t domain, uint32_t mask)
{
    base->INT[domain].INT_ENABLE &= ~mask;
}

/*!
 * @brief Get LCDIF interrupt peding status.
 *
 * @param base LCDIF peripheral base address.
 * @param domain CPU domain the interrupt signal routed to.
 * @return Interrupt pending status, OR'ed value of _lcdifv2_interrupt.
 */
static inline uint32_t LCDIFV2_GetInterruptStatus(LCDIFV2_Type *base, uint8_t domain)
{
    return base->INT[domain].INT_STATUS;
}

/*!
 * @brief Clear LCDIF interrupt peding status.
 *
 * @param base LCDIF peripheral base address.
 * @param domain CPU domain the interrupt signal routed to.
 * @param mask of the flags to clear, OR'ed value of _lcdifv2_interrupt.
 */
static inline void LCDIFV2_ClearInterruptStatus(LCDIFV2_Type *base, uint8_t domain, uint32_t mask)
{
    base->INT[domain].INT_STATUS = mask;
}

/* @} */

/*!
 * @name LUT
 * @{
 */

/*!
 * @brief Set the LUT data.
 *
 * This function sets the specific layer LUT data, if @p useShadowLoad is true,
 * call @ref LCDIFV2_TriggerLayerShadowLoad after this function, the
 * LUT will be loaded to the hardware during next vertical blanking period.
 * If @p useShadowLoad is false, the LUT data is loaded to hardware directly.
 *
 * @param base LCDIF v2 peripheral base address.
 * @param layerIndex Which layer to set.
 * @param lutData The LUT data to load.
 * @param count Count of @p lutData.
 * @retval kStatus_Success Set success.
 * @retval kStatus_Fail Previous LUT data is not loaded to hardware yet.
 */
status_t LCDIFV2_SetLut(
    LCDIFV2_Type *base, uint8_t layerIndex, const uint32_t *lutData, uint16_t count, bool useShadowLoad);

/* @} */

/*!
 * @name Layer operation
 * @{
 */

/*!
 * @brief Set the layer dimension.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param width Layer width in pixel.
 * @param height Layer height.
 *
 * @note The layer width must be in multiples of the number of pixels that can be stored in 32 bits
 */
static inline void LCDIFV2_SetLayerSize(LCDIFV2_Type *base, uint8_t layerIndex, uint16_t width, uint16_t height)
{
    base->LAYER[layerIndex].CTRLDESCL1 =
        (height << LCDIFV2_CTRLDESCL1_HEIGHT_SHIFT) | (width << LCDIFV2_CTRLDESCL1_WIDTH_SHIFT);
}

/*!
 * @brief Set the layer position in output frame.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param offsetX Horizontal offset, start from 0.
 * @param offsetY Vertical offset, start from 0.
 */
static inline void LCDIFV2_SetLayerOffset(LCDIFV2_Type *base, uint8_t layerIndex, uint16_t offsetX, uint16_t offsetY)
{
    base->LAYER[layerIndex].CTRLDESCL2 =
        (offsetX << LCDIFV2_CTRLDESCL2_POSX_SHIFT) | (offsetY << LCDIFV2_CTRLDESCL2_POSY_SHIFT);
}

/*!
 * @brief Set the layer source buffer configuration.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param config Pointer to the configuration.
 */
void LCDIFV2_SetLayerBufferConfig(LCDIFV2_Type *base, uint8_t layerIndex, const lcdifv2_buffer_config_t *config);

/*!
 * @brief Set the layer source buffer address.
 *
 * This function is used for fast runtime source buffer change.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param addr The new source buffer address passed to the layer, should be 64-bit aligned.
 */
static inline void LCDIFV2_SetLayerBufferAddr(LCDIFV2_Type *base, uint8_t layerIndex, uint32_t addr)
{
    base->LAYER[layerIndex].CTRLDESCL4 = addr;
}

/*!
 * @brief Enable or disable the layer.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Layer layerIndex.
 * @param enable Pass in true to enable, false to disable.
 */
static inline void LCDIFV2_EnableLayer(LCDIFV2_Type *base, uint8_t layerIndex, bool enable)
{
    if (enable)
    {
        base->LAYER[layerIndex].CTRLDESCL5 |= LCDIFV2_CTRLDESCL5_EN_MASK;
    }
    else
    {
        base->LAYER[layerIndex].CTRLDESCL5 &= ~LCDIFV2_CTRLDESCL5_EN_MASK;
    }
}

/*!
 * @brief Trigger the layer configuration shadow load.
 *
 * The new layer configurations are written to the shadow registers first,
 * When all configurations written finished, call this function, then shadowed
 * control registers are updated to the active control registers on VSYNC of
 * next frame.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Layer layerIndex.
 */
static inline void LCDIFV2_TriggerLayerShadowLoad(LCDIFV2_Type *base, uint8_t layerIndex)
{
    base->LAYER[layerIndex].CTRLDESCL5 |= LCDIFV2_CTRLDESCL5_SHADOW_LOAD_EN_MASK;
}

/*!
 * @brief Set the layer back ground color.
 *
 * The back ground color is used when layer not actived.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Index of the layer.
 * @param backGroundColor Background color to use when this layer is not active.
 */
static inline void LCDIFV2_SetLayerBackGroundColor(LCDIFV2_Type *base, uint8_t layerIndex, uint32_t backGroundColor)
{
    base->LAYER[layerIndex].CTRLDESCL6 = backGroundColor;
}

/*!
 * @brief Set the layer alpha blend mode.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Index of the CSC unit.
 * @param config Pointer to the blend configuration.
 */
void LCDIFV2_SetLayerBlendConfig(LCDIFV2_Type *base, uint8_t layerIndex, const lcdifv2_blend_config_t *config);

/*!
 * @brief Set the color space conversion mode.
 *
 * Supports YUV2RGB and YCbCr2RGB.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param layerIndex Index of the layer.
 * @param mode The conversion mode.
 */
void LCDIFV2_SetCscMode(LCDIFV2_Type *base, uint8_t layerIndex, lcdifv2_csc_mode_t mode);

/* @} */

/*!
 * @name Store
 * @{
 */

/*!
 * @brief Set the store buffer configuration.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param config Pointer to the store buffer.
 */
void LCDIFV2_SetStoreBufferConfig(LCDIFV2_Type *base, const lcdifv2_store_buffer_config_t *config);

/*!
 * @brief Start the store.
 *
 * If repeat mode not enabled, the store function stops after one frame. If the
 * repeat mode is enabled, the store continues working until reset the module.
 *
 * @param base LCDIFv2 peripheral base address.
 * @param repeat Use repeat mode or not.
 */
void LCDIFV2_StartStore(LCDIFV2_Type *base, bool repeat);

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* @} */

#endif /*_FSL_LCDIFV2_H_*/
