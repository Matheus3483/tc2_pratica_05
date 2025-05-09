/*
* FUNCTION       : library to creat, read, and write in peripherals in FPGA
* PROJECT        : RISC V + DCT
*/

#ifndef PERIPHERAL_H
#define PERIPHERAL_H

//BEGIN INCLUDES
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <time.h> 
#include <math.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "hwlib.h"
#include "socal.h"
#include "hps.h"
#include "alt_gpio.h"
#include "hps_0.h"
//END INCLUDES

//BEGIN DEFINES
#define HW_REGS_BASE ( ALT_STM_OFST )
#define HW_REGS_SPAN ( 0x04000000 )
#define HW_REGS_MASK ( HW_REGS_SPAN - 1 )
//END DEFINES

//BEGIN TYPEDEFS
struct peripheral
{
    void *base_addr;
    uint32_t mem_base;
    uint32_t mem_span;
};
typedef struct peripheral peripheral;
//END TYPEDEFS

//BEGIN FUNCTION PROTOTYPES
/**
  * @brief  read 32 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address to be read
  * @retval 32 bits
  */
peripheral peripheral_create(uint32_t mem_base, uint32_t mem_span);

/**
  * @brief  read 32 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address to be read
  * @retval 32 bits
  */
uint32_t peripheral_read32(peripheral periferico, uint32_t address);

/**
  * @brief  read 16 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address to be read
  * @retval 16 bits
  */
uint16_t peripheral_read16(peripheral periferico, uint16_t address);

/**
  * @brief  read 8 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address to be read
  * @retval 8 bits
  */
uint8_t peripheral_read8(peripheral periferico, uint8_t address);

/**
  * @brief  write 32 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address 
  * @param  dataIn : data input
  * @retval none
  */
void peripheral_write32(peripheral periferico, uint32_t address, uint32_t dataIn);


/**
  * @brief  write 16 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address 
  * @param  dataIn : data input
  * @retval none
  */
void peripheral_write16(peripheral periferico, uint32_t address, uint16_t dataIn);


/**
  * @brief  write 8 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address 
  * @param  dataIn : data input
  * @retval none
  */
void peripheral_write8(peripheral periferico, uint32_t address, uint8_t dataIn);
//END FUNCTION PROTOTYPES

#endif