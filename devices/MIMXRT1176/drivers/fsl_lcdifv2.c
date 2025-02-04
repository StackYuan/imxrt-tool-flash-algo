/*
 * Copyright 2019-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lcdifv2.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lcdifv2"
#endif

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Get instance number for LCDIF module.
 *
 * @param base LCDIF peripheral base address
 */
static uint32_t LCDIFV2_GetInstance(LCDIFV2_Type *base);

/*!
 * @brief Reset register value to default status.
 *
 * @param base LCDIF peripheral base address
 */
static void LCDIFV2_ResetRegister(LCDIFV2_Type *base);

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to LCDIF bases for each instance. */
static LCDIFV2_Type *const s_lcdifv2Bases[] = LCDIFV2_BASE_PTRS;

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
/*! @brief Pointers to LCDIF clock for each instance. */
static const clock_ip_name_t s_lcdifv2Clocks[] = LCDIFV2_CLOCKS;
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

/*******************************************************************************
 * Codes
 ******************************************************************************/
static uint32_t LCDIFV2_GetInstance(LCDIFV2_Type *base)
{
    uint32_t instance;

    /* Find the instance index from base address mappings. */
    for (instance = 0; instance < ARRAY_SIZE(s_lcdifv2Bases); instance++)
    {
        if (s_lcdifv2Bases[instance] == base)
        {
            break;
        }
    }

    assert(instance < ARRAY_SIZE(s_lcdifv2Bases));

    return instance;
}

static void LCDIFV2_ResetRegister(LCDIFV2_Type *base)
{
    int32_t i;

    base->DISP_PARA         = 0U;
    base->CTRL              = 0x80000000U;
    base->DISP_SIZE         = 0U;
    base->HSYN_PARA         = 0x00C01803U;
    base->VSYN_PARA         = 0x00C01803U;
    base->INT[0].INT_ENABLE = 0U;
    base->INT[1].INT_ENABLE = 0U;
    base->PDI_PARA          = 0x00001000U;
    base->WR_CTRL           = 0x007C0000U;
    base->BASE_ADDR         = 0U;
    base->PITCH             = 0U;

    for (i = 0; i < LCDIFV2_LAYER_COUNT; i++)
    {
        base->LAYER[i].CTRLDESCL5 = 0U;
        base->LAYER[i].CTRLDESCL1 = 0U;
        base->LAYER[i].CTRLDESCL2 = 0U;
        base->LAYER[i].CTRLDESCL3 = 0U;
        base->LAYER[i].CTRLDESCL4 = 0U;
        base->LAYER[i].CTRLDESCL6 = 0U;
    }

    for (i = 0; i < LCDIFV2_CSC_COUNT; i++)
    {
        base->LAYER[i].CSC_COEF0 = 0x04000000U;
        base->LAYER[i].CSC_COEF1 = 0x01230208U;
        base->LAYER[i].CSC_COEF2 = 0x076B079CU;
    }

    /* Clear interrupt status. */
    base->INT[0].INT_STATUS = 0xFFFFFFFFU;
    base->INT[1].INT_STATUS = 0xFFFFFFFFU;
}

/*!
 * brief Initializes the LCDIF v2.
 *
 * This function ungates the LCDIF v2 clock and release the peripheral reset.
 *
 * param base LCDIF v2 peripheral base address.
 */
void LCDIFV2_Init(LCDIFV2_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = LCDIFV2_GetInstance(base);
    /* Enable the clock. */
    CLOCK_EnableClock(s_lcdifv2Clocks[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

    LCDIFV2_ResetRegister(base);

    /* Out of reset. */
    base->CTRL = 0U;
}

/*!
 * brief Deinitializes the LCDIF peripheral.
 *
 * param base LCDIF peripheral base address.
 */
void LCDIFV2_Deinit(LCDIFV2_Type *base)
{
    LCDIFV2_ResetRegister(base);

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
    uint32_t instance = LCDIFV2_GetInstance(base);
    /* Disable the clock. */
    CLOCK_DisableClock(s_lcdifv2Clocks[instance]);
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

/*!
 * brief Reset the LCDIF v2.
 *
 * param base LCDIF peripheral base address.
 */
void LCDIFV2_Reset(LCDIFV2_Type *base)
{
    LCDIFV2_ResetRegister(base);

    /* Release and ready to work. */
    base->CTRL = 0U;
}

/*!
 * brief Gets the LCDIF display default configuration structure.
 *
 * param config Pointer to the LCDIF configuration structure.
 */
void LCDIFV2_DisplayGetDefaultConfig(lcdifv2_display_config_t *config)
{
    assert(config);

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
    config->lineOrder = kLCDIFV2_LineOrderRGB;
}

/*!
 * brief Set the LCDIF v2 display configurations.
 *
 * param base LCDIF peripheral base address.
 * param config Pointer to the LCDIF configuration structure.
 */
void LCDIFV2_SetDisplayConfig(LCDIFV2_Type *base, const lcdifv2_display_config_t *config)
{
    assert(config);

    /* Configure the parameters. */
    base->DISP_SIZE = (config->panelWidth << LCDIFV2_DISP_SIZE_DELTA_X_SHIFT) |
                      (config->panelHeight << LCDIFV2_DISP_SIZE_DELTA_Y_SHIFT);

    base->HSYN_PARA = (config->hsw << LCDIFV2_HSYN_PARA_PW_H_SHIFT) | (config->hbp << LCDIFV2_HSYN_PARA_BP_H_SHIFT) |
                      (config->hfp << LCDIFV2_HSYN_PARA_FP_H_SHIFT);

    base->VSYN_PARA = (config->vsw << LCDIFV2_VSYN_PARA_PW_V_SHIFT) | (config->vbp << LCDIFV2_VSYN_PARA_BP_V_SHIFT) |
                      (config->vfp << LCDIFV2_VSYN_PARA_FP_V_SHIFT);

    base->DISP_PARA = LCDIFV2_DISP_PARA_LINE_PATTERN(config->lineOrder);

    base->CTRL = (uint32_t)(config->polarityFlags);
}

/*!
 * brief Set the color space conversion mode.
 *
 * Supports YUV2RGB and YCbCr2RGB.
 *
 * param base LCDIFv2 peripheral base address.
 * param layerIndex Index of the layer.
 * param mode The conversion mode.
 */
void LCDIFV2_SetCscMode(LCDIFV2_Type *base, uint8_t layerIndex, lcdifv2_csc_mode_t mode)
{
    assert(layerIndex < LCDIFV2_CSC_COUNT);

    /*
     * The equations used for Colorspace conversion are:
     *
     * R = C0*(Y+Y_OFFSET)                   + C1(V+UV_OFFSET)
     * G = C0*(Y+Y_OFFSET) + C3(U+UV_OFFSET) + C2(V+UV_OFFSET)
     * B = C0*(Y+Y_OFFSET) + C4(U+UV_OFFSET)
     */

    if (kLCDIFV2_CscYUV2RGB == mode)
    {
        base->LAYER[layerIndex].CSC_COEF0 = LCDIFV2_CSC_COEF0_ENABLE_MASK | LCDIFV2_CSC_COEF0_C0(0x100U) /* 1.00. */
                                            | LCDIFV2_CSC_COEF0_Y_OFFSET(0x0U)                           /* 0. */
                                            | LCDIFV2_CSC_COEF0_UV_OFFSET(0x0U);                         /* 0. */

        base->LAYER[layerIndex].CSC_COEF1 = LCDIFV2_CSC_COEF1_C1(0x0123U)    /* 1.140. */
                                            | LCDIFV2_CSC_COEF1_C4(0x0208U); /* 2.032. */
        base->LAYER[layerIndex].CSC_COEF2 = LCDIFV2_CSC_COEF2_C2(0x076BU)    /* -0.851. */
                                            | LCDIFV2_CSC_COEF2_C3(0x079BU); /* -0.394. */
    }
    else if (kLCDIFV2_CscYCbCr2RGB == mode)
    {
        base->LAYER[layerIndex].CSC_COEF0 = LCDIFV2_CSC_COEF0_ENABLE_MASK | LCDIFV2_CSC_COEF0_YCBCR_MODE_MASK |
                                            LCDIFV2_CSC_COEF0_C0(0x12AU)           /* 1.164. */
                                            | LCDIFV2_CSC_COEF0_Y_OFFSET(0x1F0U)   /* -16. */
                                            | LCDIFV2_CSC_COEF0_UV_OFFSET(0x180U); /* -128. */
        base->LAYER[layerIndex].CSC_COEF1 = LCDIFV2_CSC_COEF1_C1(0x0198U)          /* 1.596. */
                                            | LCDIFV2_CSC_COEF1_C4(0x0204U);       /* 2.017. */
        base->LAYER[layerIndex].CSC_COEF2 = LCDIFV2_CSC_COEF2_C2(0x0730U)          /* -0.813. */
                                            | LCDIFV2_CSC_COEF2_C3(0x079CU);       /* -0.392. */
    }
    else
    {
        base->LAYER[layerIndex].CSC_COEF0 = 0U;
        base->LAYER[layerIndex].CSC_COEF1 = 0U;
        base->LAYER[layerIndex].CSC_COEF2 = 0U;
    }
}

/*!
 * brief Set the layer source buffer configuration.
 *
 * param base LCDIFv2 peripheral base address.
 * param layerIndex Layer layerIndex.
 * param config Pointer to the configuration.
 */
void LCDIFV2_SetLayerBufferConfig(LCDIFV2_Type *base, uint8_t layerIndex, const lcdifv2_buffer_config_t *config)
{
    assert(config);
    uint32_t reg;

    base->LAYER[layerIndex].CTRLDESCL3 = config->strideBytes;

    reg = base->LAYER[layerIndex].CTRLDESCL5;
    reg = (reg & ~(LCDIFV2_CTRLDESCL5_BPP_MASK | LCDIFV2_CTRLDESCL5_YUV_FORMAT_MASK)) | (uint32_t)config->pixelFormat;

    if (0U == (reg & LCDIFV2_CTRLDESCL5_AB_MODE_MASK))
    {
        reg |= LCDIFV2_CTRLDESCL5_SAFETY_EN_MASK;
    }

    base->LAYER[layerIndex].CTRLDESCL5 = reg;
}

/*!
 * brief Set the store buffer configuration.
 *
 * param base LCDIFv2 peripheral base address.
 * param config Pointer to the store buffer.
 */
void LCDIFV2_SetStoreBufferConfig(LCDIFV2_Type *base, const lcdifv2_store_buffer_config_t *config)
{
    assert(config);

    base->BASE_ADDR = config->bufferAddr;
    base->PITCH     = config->strideBytes;
    base->WR_CTRL   = (base->WR_CTRL & ~LCDIFV2_WR_CTRL_BPP_MASK) | LCDIFV2_WR_CTRL_BPP(config->pixelFormat);
}

/*!
 * brief Set the LUT data.
 *
 * This function sets the specific layer LUT data, if useShadowLoad is true,
 * call LCDIFV2_TriggerLayerShadowLoad after this function, the
 * LUT will be loaded to the hardware during next vertical blanking period.
 * If useShadowLoad is false, the LUT data is loaded to hardware directly.
 *
 * param base LCDIF v2 peripheral base address.
 * param layerIndex Which layer to set.
 * param lutData The LUT data to load.
 * param count Count of lutData.
 * retval kStatus_Success Set success.
 * retval kStatus_Fail Previous LUT data is not loaded to hardware yet.
 */
status_t LCDIFV2_SetLut(
    LCDIFV2_Type *base, uint8_t layerIndex, const uint32_t *lutData, uint16_t count, bool useShadowLoad)
{
    assert(count < LCDIFV2_LUT_ENTRY_NUM);

    uint32_t i;
    status_t status;

    /* Previous setting is not updated. */
    if ((base->CLUT_LOAD & LCDIFV2_CLUT_LOAD_CLUT_UPDATE_EN_MASK) != 0U)
    {
        status = kStatus_Fail;
    }
    else
    {
        if (useShadowLoad)
        {
            base->CLUT_LOAD = LCDIFV2_CLUT_LOAD_SEL_CLUT_NUM(layerIndex) | LCDIFV2_CLUT_LOAD_CLUT_UPDATE_EN_MASK;
        }
        else
        {
            base->CLUT_LOAD = LCDIFV2_CLUT_LOAD_SEL_CLUT_NUM(layerIndex);
        }

        for (i = 0; i < count; i++)
        {
            base->CLUT_RAM[i + LCDIFV2_LUT_ENTRY_NUM * layerIndex] = lutData[i];
        }

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Set the layer alpha blend mode.
 *
 * param base LCDIFv2 peripheral base address.
 * param layerIndex Index of the CSC unit.
 * param config Pointer to the blend configuration.
 */
void LCDIFV2_SetLayerBlendConfig(LCDIFV2_Type *base, uint8_t layerIndex, const lcdifv2_blend_config_t *config)
{
    assert(config);

    uint32_t reg;

    reg = base->LAYER[layerIndex].CTRLDESCL5;
    reg &= ~(LCDIFV2_CTRLDESCL5_GLOBAL_ALPHA_MASK | LCDIFV2_CTRLDESCL5_AB_MODE_MASK |
             LCDIFV2_CTRLDESCL5_PD_FACTOR_MODE_MASK | LCDIFV2_CTRLDESCL5_PD_ALPHA_MODE_MASK |
             LCDIFV2_CTRLDESCL5_PD_COLOR_MODE_MASK | LCDIFV2_CTRLDESCL5_PD_GLOBAL_ALPHA_MODE_MASK |
             LCDIFV2_CTRLDESCL5_SAFETY_EN_MASK);

    reg |=
        (LCDIFV2_CTRLDESCL5_GLOBAL_ALPHA(config->globalAlpha) | LCDIFV2_CTRLDESCL5_AB_MODE(config->alphaMode) |
         LCDIFV2_CTRLDESCL5_PD_FACTOR_MODE(config->pdFactorMode) |
         LCDIFV2_CTRLDESCL5_PD_ALPHA_MODE(config->pdAlphaMode) | LCDIFV2_CTRLDESCL5_PD_COLOR_MODE(config->pdColorMode) |
         LCDIFV2_CTRLDESCL5_PD_GLOBAL_ALPHA_MODE(config->pdGlobalAlphaMode));

    if (config->alphaMode == kLCDIFV2_AlphaDisable)
    {
        reg |= LCDIFV2_CTRLDESCL5_SAFETY_EN_MASK;
    }

    base->LAYER[layerIndex].CTRLDESCL5 = reg;
}

/*!
 * brief Start the store.
 *
 * If repeat mode not enabled, the store function stops after one frame. If the
 * repeat mode is enabled, the store continues working until reset the module.
 *
 * param base LCDIFv2 peripheral base address.
 * param repeat Use repeat mode or not.
 */
void LCDIFV2_StartStore(LCDIFV2_Type *base, bool repeat)
{
    uint32_t reg = LCDIFV2_WR_CTRL_ENABLE_MASK;

    if (repeat)
    {
        reg |= LCDIFV2_WR_CTRL_REPEAT_MASK;
    }

    base->WR_CTRL |= reg;
}
