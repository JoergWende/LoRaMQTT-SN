/*!
 * \file      utilities.h
 *
 * \brief     Helper functions implementation
 *
 * \copyright Revised BSD License, see section \ref LICENSE.
 *
 * \code
 *                ______                              _
 *               / _____)             _              | |
 *              ( (____  _____ ____ _| |_ _____  ____| |__
 *               \____ \| ___ |    (_   _) ___ |/ ___)  _ \
 *               _____) ) ____| | | || |_| ____( (___| | | |
 *              (______/|_____)_|_|_| \__)_____)\____)_| |_|
 *              (C)2013-2017 Semtech
 *
 * \endcode
 *
 * \author    Miguel Luis ( Semtech )
 *
 * \author    Gregory Cristian ( Semtech )
 *
 * \Modified by Tomoaki Yamaguchi
 *
 */
#ifndef __UTILITIES_H__
#define __UTILITIES_H__

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
#include "stm32l0xx.h"

#define DEBUGLOG

/*!
 * Generic definition
 */

#ifndef SUCCESS
#define SUCCESS                                     1
#endif

#ifndef FAIL
#define FAIL                                        0
#endif

/*!
 * DebugLog
 */
#ifdef DEBUGLOG
#define DLOG(...)            printf( __VA_ARGS__ )
#define DLOG_MSG(...)        printf( "%s %d %s\r\n", __func__, __LINE__, __VA_ARGS__ )
#define DLOG_INT(...)        printf( "%s %d %d\r\n", __func__, __LINE__, __VA_ARGS__ )
#define DLOG_MSG_INT(...)    printf( "%s %d  %s %d\r\n", __func__, __LINE__, __VA_ARGS__ )
#else
#define DLOG_MSG(...)
#define DLOG_INT(...)
#define DLOG_MSG_INT(...)
#endif


/*!
 * \brief Returns the minimum value between a and b
 *
 * \param [IN] a 1st value
 * \param [IN] b 2nd value
 * \retval minValue Minimum value
 */
#ifndef MIN
#define MIN( a, b ) ( ( ( a ) < ( b ) ) ? ( a ) : ( b ) )
#endif

/*!
 * \brief Returns the maximum value between a and b
 *
 * \param [IN] a 1st value
 * \param [IN] b 2nd value
 * \retval maxValue Maximum value
 */
#ifndef MAX
#define MAX( a, b ) ( ( ( a ) > ( b ) ) ? ( a ) : ( b ) )
#endif

/*!
 * \brief Returns 2 raised to the power of n
 *
 * \param [IN] n power value
 * \retval result of raising 2 to the power n
 */
#define POW2( n ) ( 1 << n )

/*!
 * Version
 */
typedef union Version_u
{
    struct Version_s
    {
        uint8_t Rfu;
        uint8_t Revision;
        uint8_t Minor;
        uint8_t Major;
    }Fields;
    uint32_t Value;
}Version_t;

/*!
 * \brief Initializes the pseudo random generator initial value
 *
 * \param [IN] seed Pseudo random generator initial value
 */
void srand1( uint32_t seed );

/*!
 * \brief Computes a random number between min and max
 *
 * \param [IN] min range minimum value
 * \param [IN] max range maximum value
 * \retval random random value in range min..max
 */
int32_t randr( int32_t min, int32_t max );

/*!
 * \brief Copies size elements of src array to dst array
 *
 * \remark STM32 Standard memcpy function only works on pointers that are aligned
 *
 * \param [OUT] dst  Destination array
 * \param [IN]  src  Source array
 * \param [IN]  size Number of bytes to be copied
 */
void memcpy1( uint8_t *dst, const uint8_t *src, uint16_t size );

/*!
 * \brief Copies size elements of src array to dst array reversing the byte order
 *
 * \param [OUT] dst  Destination array
 * \param [IN]  src  Source array
 * \param [IN]  size Number of bytes to be copied
 */
void memcpyr( uint8_t *dst, const uint8_t *src, uint16_t size );

/*!
 * \brief Set size elements of dst array with value
 *
 * \remark STM32 Standard memset function only works on pointers that are aligned
 *
 * \param [OUT] dst   Destination array
 * \param [IN]  value Default value
 * \param [IN]  size  Number of bytes to be copied
 */
void memset1( uint8_t *dst, uint8_t value, uint16_t size );

/*!
 * \brief Converts a nibble to an hexadecimal character
 *
 * \param [IN] a   Nibble to be converted
 * \retval hexChar Converted hexadecimal character
 */
int8_t Nibble2HexChar( uint8_t a );

/*!
 * Begins critical section
 */
#define CRITICAL_SECTION_BEGIN( )  uint32_t mask; DeviceCriticalSectionBegin( &mask )

/*!
 * Ends critical sectionutilities
 */
#define CRITICAL_SECTION_END( ) DeviceCriticalSectionEnd( &mask )

/*
 * ============================================================================
 * Following functions must be implemented inside the specific platform 
 * board.c file.
 * ============================================================================
 */
/*!
 * Disable interrupts, begins critical section
 * 
 * \param [IN] mask Pointer to a variable where to store the CPU IRQ mask
 */
void DeviceCriticalSectionBegin( uint32_t *mask );

/*!
 * Ends critical section
 * 
 * \param [IN] mask Pointer to a variable where the CPU IRQ mask was stored
 */
void DeviceCriticalSectionEnd( uint32_t *mask );

//void SetTraceMode(uint8_t flg);
uint16_t getUint16(const uint8_t* pos);
void setUint16(uint8_t* pos, uint16_t val);
uint32_t getUint32(const uint8_t* pos);
uint32_t getUint24(const uint8_t* pos);
void setUint32(uint8_t* pos, uint32_t val);
float getFloat32(const uint8_t* pos);
void setFloat32(uint8_t* pos, float flt);

/**
 *  Calculate free SRAM
 */
int GetFreeRam(void);

#ifdef __cplusplus
}
#endif

#endif // __UTILITIES_H__
