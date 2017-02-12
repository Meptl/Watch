/*
 usi_twi.c
 Adapted from TinyWireM.cpp
   TinyWireM.cpp - a wrapper class for TWI/I2C Master library for the ATtiny on Arduino
   1/21/2011 BroHogan -  brohoganx10 at gmail dot com

 **** See TinyWireM.h for Credits and Usage information ****

 This library is free software; you can redistribute it and/or modify it under the
 terms of the GNU General Public License as published by the Free Software
 Foundation; either version 2.1 of the License, or any later version.

 This program is distributed in the hope that it will be useful, but WITHOUT ANY
 WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 PARTICULAR PURPOSE.  See the GNU General Public License for more details.
 */

#include "USI_TWI_Master.h"
#include "usi_twi.h"

uint8_t usi_buf[USI_BUF_SIZE];             // holds I2C send and receive data
uint8_t usi_bufidx = 0;                    // current number of bytes in the send buff
uint8_t usi_lastread = 0;                  // number of bytes read so far
uint8_t usi_bytes_available = 0;           // number of bytes requested but not read

void twi_init(void)
{
    USI_TWI_Master_Initialise();
}

void twi_begin_transmission(uint8_t slaveAddr)
{
    // setup address & write bit
    usi_bufidx = 0;
    usi_buf[usi_bufidx] = (slaveAddr << TWI_ADR_BITS) | USI_SEND;
}

// Buffers data to be sent out.
void twi_send(uint8_t data)
{
    if (usi_bufidx >= USI_BUF_SIZE)
        return;

    usi_buf[usi_bufidx++] = data;
}

// Sends out all buffered data
uint8_t twi_end_transmission(void)
{
    unsigned char xferOK = USI_TWI_Start_Read_Write(usi_buf, usi_bufidx + 1);
    usi_bufidx = 0;

    if (xferOK == TRUE) {
        return 0;
    } else {
        uint8_t errorCode = USI_TWI_Get_State_Info();
        return errorCode;
    }
}

uint8_t twi_request_from(uint8_t slaveAddr, uint8_t numBytes)
{
    usi_lastread = 0;
    usi_bytes_available = numBytes;
    usi_buf[0] = (slaveAddr << TWI_ADR_BITS) | USI_RCVE;  // setup address & receive bit

    // numBytes + 1 to transmit header
    unsigned char xferOK = USI_TWI_Start_Read_Write(usi_buf, numBytes + 1);

    // usi_buf now holds the data read
    if (xferOK == TRUE) {
        return 0;
    } else {
        uint8_t errorCode = USI_TWI_Get_State_Info();
        return errorCode;
    }
}

// Returns the bytes received one at a time
uint8_t twi_receive(void)
{
    // inc first since first uint8_t read is in usi_buf[1]
    return usi_buf[++usi_lastread];
}

uint8_t twi_available(void)
{
    // the bytes available that haven't been read yet
    return usi_bytes_available - (usi_lastread);
}

