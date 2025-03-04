#ifndef SRC_ADRV9001_H_
#define SRC_ADRV9001_H_
/***************************************************************************//**
*  \ingroup    RFLAN
*  \defgroup   ADRV9001 ADRV9001 Interface Driver
*  @{
*******************************************************************************/
/***************************************************************************//**
*  \file       adrv9001.h
*
*  \details
*
*  This file contains definitions for the adrv9001 interface driver.  The
*  adrv9001 interface driver implements algorithms that call one or several
*  adi_adrv9001 API functions.
*
*  \copyright
*
*  Copyright 2021(c) NextGen RF Design, Inc.
*
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*   - The use of this software may or may not infringe the patent rights of one
*     or more patent holders.  This license does not release you from the
*     requirement that you obtain separate licenses from these patent holders
*     to use this software.
*   - Use of the software either in source or binary form, must be run on or
*     directly connected to a NextGen RF Design, Inc. product.
*
*  THIS SOFTWARE IS PROVIDED BY NEXTGEN RF DESIGN "AS IS" AND ANY EXPRESS OR
*  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, NON-INFRINGEMENT,
*  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
*  EVENT SHALL NEXTGEN RF DESIGN BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
*  INTELLECTUAL PROPERTY RIGHTS, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
*  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
*  ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
*  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*******************************************************************************/
#include <stdint.h>
#include <stdbool.h>



#define ADRV9001_STATUS_OFFSET              (-1000)
#define ADRV9001_PROFILE_SIZE               (0x80000)

/**
**  ADRV9001 Status
*/
typedef enum
{
  Adrv9001Status_Success                      = (0),
  Adrv9001Status_InvalidPort                  = (ADRV9001_STATUS_OFFSET - 1),
  Adrv9001Status_InvalidParameter             = (ADRV9001_STATUS_OFFSET - 2),
  Adrv9001Status_Initialized                  = (ADRV9001_STATUS_OFFSET - 3),
  Adrv9001Status_MemoryError                  = (ADRV9001_STATUS_OFFSET - 3),
  Adrv9001Status_InvalidSSI                   = (ADRV9001_STATUS_OFFSET - 4),
  Adrv9001Status_InvalidGpio                  = (ADRV9001_STATUS_OFFSET - 5),
  Adrv9001Status_InvalidRadioState            = (ADRV9001_STATUS_OFFSET - 6),
  Adrv9001Status_CommError                    = (ADRV9001_STATUS_OFFSET - 7),
  Adrv9001Status_ProfileInitError             = (ADRV9001_STATUS_OFFSET - 8),
  Adrv9001Status_ProfileCfgError              = (ADRV9001_STATUS_OFFSET - 9),
  Adrv9001Status_ProfileCalError              = (ADRV9001_STATUS_OFFSET - 10),
  Adrv9001Status_ProfilePrimeError            = (ADRV9001_STATUS_OFFSET - 11),
  Adrv9001Status_NotSupported                 = (ADRV9001_STATUS_OFFSET - 12),
  Adrv9001Status_DriverError                  = (ADRV9001_STATUS_OFFSET - 13),
  Adrv9001Status_DmaError                     = (ADRV9001_STATUS_OFFSET - 14),
  Adrv9001Status_ExceedsDmaBuffer             = (ADRV9001_STATUS_OFFSET - 15),
  Adrv9001Status_PortDisabled                 = (ADRV9001_STATUS_OFFSET - 16),
  Adrv9001Status_SpiError                     = (ADRV9001_STATUS_OFFSET - 17),
  Adrv9001Status_GpioError                    = (ADRV9001_STATUS_OFFSET - 18),
  Adrv9001Status_MemoryAlignmentError         = (ADRV9001_STATUS_OFFSET - 19),
} adrv9001_status_t;

/**
 **  ADRV9001 Port
 */
typedef enum
{
  Adrv9001Port_Rx1    = (0),
  Adrv9001Port_Rx2    = (1),
  Adrv9001Port_Tx1    = (2),
  Adrv9001Port_Tx2    = (3),
  Adrv9001Port_Num    = (4),

} adrv9001_port_t;

#define ADRV9001_IS_PORT_TX(p)              ((( p == Adrv9001Port_Tx1 ) || ( p == Adrv9001Port_Tx2 )) ? true : false)
#define ADRV9001_IS_PORT_RX(p)              ((( p == Adrv9001Port_Rx1 ) || ( p == Adrv9001Port_Rx2 )) ? true : false)
#define ADRV9001_PORT_2_STR(p)              (( p == Adrv9001Port_Tx1 )? "Tx1" :                 \
                                             ( p == Adrv9001Port_Tx2 )? "Tx2" :                 \
                                             ( p == Adrv9001Port_Rx1 )? "Rx1" :                 \
                                             ( p == Adrv9001Port_Rx2 )? "Rx2" : "Unknown")

/**
 **  ADRV9001 Radio State
 */
typedef enum
{
  Adrv9001RadioState_Standby          = 0,
  Adrv9001RadioState_Calibrated       = 1,
  Adrv9001RadioState_Primed           = 2,
  Adrv9001RadioState_Enabled          = 3,
} adrv9001_radio_state_t;

/**
 **  ADRV9001 IQ Data Sample
 */
typedef struct
{
  uint16_t    idata;
  uint16_t    qdata;
} adrv9001_iqdata_t;

/**
 **  ADRV9001 Event Data
 */
typedef union
{
  struct
  {
    adrv9001_port_t     Port;
    adrv9001_status_t   Status;
  }Stream;
} adrv9001_evt_data_t;

/**
 **  ADRV9001 Event Type
 */
typedef enum
{
  Adrv9001EvtType_StreamStart   = 0,
  Adrv9001EvtType_StreamDone    = 1,
} adrv9001_evt_type_t;

/**
** ADRV9001 Callback
*/
typedef void (*adrv9001_callback_t)( adrv9001_evt_type_t EvtType, adrv9001_evt_data_t EvtData, void *param );

/**
 **  ADRV9001 DMA Configuration
 */
typedef struct {
  uint32_t              IrqId[Adrv9001Port_Num];     ///< DMA Processor IRQ ID
  uint32_t              BaseAddr[Adrv9001Port_Num];  ///< DMA AXI Bus Address
} adrv9001_dma_cfg_t;

/**
 **  ADRV9001 GPIO Configuration
 */
typedef struct {
  uint32_t              DeviceId;           ///< Device ID
  uint32_t              RstnPin;            ///< Reset pin number
  uint32_t              Rx1EnPin;           ///< Rx1 enable pin number
  uint32_t              Rx2EnPin;           ///< Rx2 enable pin number
  uint32_t              Tx1EnPin;           ///< Tx1 enable pin number
  uint32_t              Tx2EnPin;           ///< Tx2 enable pin number
  uint32_t              IrqPin;             ///< Irq enable pin number
} adrv9001_gpio_cfg_t;

/**
 **  ADRV9001 SPI Configuration
 */
typedef struct {
  uint32_t              DeviceId;           ///< Device ID
  uint32_t              CsPinId;            ///< Chip Select pin number relative to the SPI hardware (0 to 3)
} adrv9001_spi_cfg_t;

/**
 **  ADRV9001 Configuration
 */
typedef struct
{
  adrv9001_callback_t   Callback;           ///< Callback
  void                 *CallbackRef;        ///< Callback reference data
  adrv9001_dma_cfg_t   *DmaCfg;             ///< DMA Configuration
  adrv9001_gpio_cfg_t  *GpioCfg;            ///< GPIO Configuration
  adrv9001_spi_cfg_t   *SpiCfg;             ///< SPI Configuration
  void                 *IrqInstance;        ///< Processor Interrupt Instance
} adrv9001_cfg_t;

/**
 **  ADRV9001 Version Info
 */
typedef struct
{
  struct
  {
    uint32_t major;                         ///< API Major Version number
    uint32_t minor;                         ///< API Minor Version number
    uint32_t patch;                         ///< API Patch Version number
  }Api;                                     ///< adi_adrv9001 API Version
  struct
  {
    uint8_t major;                          ///< ARM Major Version number
    uint8_t minor;                          ///< ARM Minor Version number
    uint8_t maint;                          ///< ARM Maintenance Version number
    uint8_t rcVer;                          ///< ARM RC Version number
  }Arm;
  struct
  {
    uint8_t major;                          ///< Major silicon version (0xA, 0xB, etc)
    uint8_t minor;                          ///< Minor silicon version
  }Silicon;
} adrv9001_ver_t;

/*******************************************************************************
*
* \details
*
* This function enables or disables the external LNA
*
* \param[in]  Port is the port being requested
*
* \param[in]  Enable true for enabling and false for disabling
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_LnaEnable( adrv9001_port_t Port, bool Enable );

/*******************************************************************************
*
* \details
*
* This function performs a SPI write
*
* \param[in]  txData is the data to be sent
*
* \param[in]  numTxBytes specifies how many bytes are to be sent
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_SpiWrite( const uint8_t txData[], uint32_t numTxBytes );

/*******************************************************************************
*
* \details
*
* This function performs a SPI read
*
* \param[in]  txData is the data to be sent
*
* \param[out] rxData is the data that is read
*
* \param[in]  numRxBytes specifies how many bytes are to be read
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_SpiRead( const uint8_t txData[], uint8_t rxData[], uint32_t numRxBytes );

/*******************************************************************************
*
* \details
*
* This function sets the RESETN pin
*
* \param[in]  PinLevel
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_ResetbPinSet( uint8_t PinLevel );

/*******************************************************************************
*
* \details
*
* This function sets the RX1 enable pin
*
* \param[in]  PinLevel
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_Rx1EnablePinSet( uint8_t PinLevel );

/*******************************************************************************
*
* \details
*
* This function sets the TX1 enable pin
*
* \param[in]  PinLevel
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_Tx1EnablePinSet( uint8_t PinLevel );

/*******************************************************************************
*
* \details
*
* This function sets the RX2 enable pin
*
* \param[in]  PinLevel
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_Rx2EnablePinSet( uint8_t PinLevel );

/*******************************************************************************
*
* \details
*
* This function sets the TX2 enable pin
*
* \param[in]  PinLevel
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_Tx2EnablePinSet( uint8_t PinLevel );

/*******************************************************************************
*
* \details
*
* This function gets the adrv9001 version information
*
* \param[out] Version Information
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_GetVersionInfo( adrv9001_ver_t *VerInfo );

/*******************************************************************************
*
* \details
*
* This function gets the junction temperature of the ADRV9002
*
* \param[out] Temperature in degrees C
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_GetTemperature( int16_t *Temp_C );

/*******************************************************************************
*
* \details
*
* This function sets the transmit port power boost setting
*
* \param[in]  Port is the port being requested
*
* \param[in]  Enable indicates if power boost is enabled
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_SetTxBoost( adrv9001_port_t Port, bool Enable );

/*******************************************************************************
*
* \details
*
* This function gets the transmit port power boost setting
*
* \param[in]  Port is the port being requested
*
* \param[in]  Enable indicates if power boost is enabled
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_GetTxBoost( adrv9001_port_t Port, bool *Enable );

/*******************************************************************************
*
* \details
*
* This function sets the transmit port attenuation
*
* \param[in]  Port is the port being requested
*
* \param[in]  Attn_mdB is the attenuation in milli dB, ie 10000 = 10.000dB
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_SetTxAttenuation( adrv9001_port_t Port, uint16_t Attn_mdB );

/*******************************************************************************
*
* \details
*
* This function gets the transmit port attenuation
*
* \param[in]  Port is the port being requested
*
* \param[in]  Attn_mdB is the attenuation in milli dB, ie 10000 = 10.000dB
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_GetTxAttenuation( adrv9001_port_t Port, uint16_t *Attn_mdB );

/*******************************************************************************
*
* \details
*
* This function gets the sample rate for the requested port.
*
* \param[in]  Port is the port being requested
*
* \param[in]  FreqHz is the sample frequency in Hz
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_GetSampleRate( adrv9001_port_t Port, uint32_t *FreqHz );

/*******************************************************************************
*
* \details
*
* This function gets the carrier frequency for the requested port.
*
* \param[in]  Port is the port being requested
*
* \param[in]  FreqHz is the carrier frequency in Hz
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_GetCarrierFrequency( adrv9001_port_t Port, uint64_t *FreqHz );

/*******************************************************************************
*
* \details
*
* This function enables or disables the internal loop back within the ADRV9001
* based on the requested port.  The requested port results in the following loop
* back path within the ADRV9001.
*
*             |       Port        | Loop back Path |
*             |-------------------|----------------|
*             | Adrv9001Port_Rx1  |   RX1 -> TX1   |
*             | Adrv9001Port_Rx2  |   RX2 -> TX2   |
*             | Adrv9001Port_Tx1  |   TX1 -> RX1   |
*             | Adrv9001Port_Tx2  |   TX2 -> RX2   |
*
* \param[in]  Port is the port being requested
*
* \param[in]  Enabled indicates whether the loop back should be enabled or
*             disabled.
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_SetInternalLoopBack( adrv9001_port_t Port, bool Enabled );

/*******************************************************************************
*
* \details
*
* This function sets the state of the radio for the requested port.
*
* \param[in]  Port is the port being requested
*
* \param[in]  State is the radio state set for the requested port
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_SetRadioState( adrv9001_port_t Port, adrv9001_radio_state_t State );

/*******************************************************************************
*
* \details
*
* This function returns the state of the radio for the requested port.
*
* \param[in]  Port is the port being requested
*
* \param[out] State is the returned State for the requested port
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_GetRadioState( adrv9001_port_t Port, adrv9001_radio_state_t *State );

/*******************************************************************************
*
* \details
*
* This function will transition the specified port to the PRIMED state from any
* state where it is valid to do so.
*
* \param[in]  Port is the port being requested
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_ToRfPrimed( adrv9001_port_t Port );

/*******************************************************************************
*
* \details
*
* This function will transition the specified port to the Enabled state from any
* state where it is valid to do so.
*
* \param[in]  Port is the port being requested
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_ToRfEnabled( adrv9001_port_t Port );

/*******************************************************************************
*
* \details
*
* This function will transition the specified port to the Calibrated state from
* any state where it is valid to do so.
*
* \param[in]  Port is the port being requested
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_ToRfCalibrated( adrv9001_port_t Port );

/*******************************************************************************
*
* \details
*
* This function enables continuous streaming of IQ data.  This function enables
* the appropriate radio state and sets up the appropriate DMA to transfer IQ
* samples from memory to the SSI or vice versa.  The DMA streams directly from
* the buffer provided by the caller.  This buffer and its contents must not be
* modified until the Adrv9001EvtType_StreamDone callback event is received by
* the caller.
*
* If the DMA is setup to stream continuously the IQ samples will be streamed
* continuously streamed to the SSI looping back to the first IQ sample
* after a SampleCnt number of samples are reached.  To disable the stream for
* a particular port call this function with SampleCnt set to zero.
*
* \param[in]  Port is the port being requested
*
* \param[in]  Buf is a buffer of 32bit IQ data
*
* \param[in]  SampleCnt is the number of samples and the length of Buf
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_IQStream( adrv9001_port_t Port, bool Cyclic, adrv9001_iqdata_t *Buf, uint32_t SampleCnt );

/*******************************************************************************
*
* \details
*
* This function clears any errors within the adi_adrv9001 device driver.
*
* \return     none
*
*******************************************************************************/
adrv9001_status_t Adrv9001_ClearError( void );

/*******************************************************************************
*
* \details
*
* This function initializes the ADRV9001 with the provided profile..
*
* \param[in]  Profile contains a reference to the profile to be loaded
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_LoadProfile( void );

/*******************************************************************************
*
* \details
*
* This function performs a hard reset of the ADRV9001.
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_HwReset( void );

/*******************************************************************************
*
* \details
*
* This function initializes the ADRV9001 using the adi_adrv9001 device driver
* along with initializing the HDL associated with the ADRV9001.
*
* \param[out] Instance returns the adi_adrv9001_Device_t Instance which can be
*             used by the caller to call adi_adrv9001 APIs directly.
*
* \param[in]  Cfg contains configuration data for initializing the ADRV9001
*
* \return     Status
*
*******************************************************************************/
adrv9001_status_t Adrv9001_Initialize( void **Instance, adrv9001_cfg_t *Cfg );

#endif
