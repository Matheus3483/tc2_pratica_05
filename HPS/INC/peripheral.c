/*
* FUNCTION       : library to creat, read, and write in peripherals in FPGA
* PROJECT        : RISC V + DCT
*/

//BEGIN INCLUDES
#include "peripheral.h"
//END INCLUDES

//BEGIN DEFINES
//END DEFINES

//BEGIN TYPEDEFS
//END TYPEDEFS

//BEGIN GLOBAL VARIABLES
/**
  * @brief  define the virtual_base.
  * @param  none
  * @retval none
  */
void* virtual_base = NULL; 
//END GLOBAL VARIABLES

//BEGIN LOCAL FUNCTION PROTOTYPES
uint8_t virtual_base_init();
//END LOCAL FUNCTION PROTOTYPES


//BEGIN LIBRARY FUNCTIONS
/**
  * @brief  read 32 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address to be read
  * @retval 32 bits
  */
peripheral peripheral_create(uint32_t mem_base, uint32_t mem_span)
{
  peripheral periferico;
  periferico.mem_base = mem_base;
  periferico.mem_span  = mem_span;
  if(virtual_base == NULL)
  {
    virtual_base_init();
  }
  periferico.base_addr =  virtual_base + ( ( uint32_t  )( ALT_LWFPGASLVS_OFST + mem_base ) & ( unsigned long)( HW_REGS_MASK ) );
  return periferico;
}

/**
  * @brief  read 32 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address to be read
  * @retval 32 bits
  */
uint32_t peripheral_read32(peripheral periferico, uint32_t address)
{
  uint32_t dataOut; 
  if(4*address >= periferico.mem_span)
  {
    printf( "ERROR: addres out of the periferal memory span\n" );
    return 0; 
  }
  dataOut =  *(uint32_t *)(periferico.base_addr +  4*address);
  return dataOut;
}

/**
  * @brief  read 16 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address to be read
  * @retval 16 bits
  */
uint16_t peripheral_read16(peripheral periferico, uint16_t address)
{
  uint16_t dataOut; 
  if(2*address >= periferico.mem_span)
  {
    printf( "ERROR: addres out of the periferal memory span\n" );
    return 0; 
  }
  dataOut =  *(uint16_t *)(periferico.base_addr +  2*address);
  return dataOut;
}

/**
  * @brief  read 8 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address to be read
  * @retval 8 bits
  */
uint8_t peripheral_read8(peripheral periferico, uint8_t address)
{
  uint8_t dataOut; 
  if(2*address >= periferico.mem_span)
  {
    printf( "ERROR: addres out of the periferal memory span\n" );
    return 0; 
  }
  dataOut =  *(uint8_t *)(periferico.base_addr +  address);
  return dataOut;
}

/**
  * @brief  write 32 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address 
  * @param  dataIn : data input
  * @retval none
  */
void peripheral_write32(peripheral periferico, uint32_t address, uint32_t dataIn)
{
  
  if(4*address >= periferico.mem_span)
  {
    printf( "ERROR: addres out of the periferal memory span\n" );
  }
  else
  {
    *(uint32_t *)(periferico.base_addr +  4*address) = dataIn;
  }
  
}


/**
  * @brief  write 16 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address 
  * @param  dataIn : data input
  * @retval none
  */
void peripheral_write16(peripheral periferico, uint32_t address, uint16_t dataIn)
{
  if(2*address >= periferico.mem_span)
  {
    printf( "ERROR: addres out of the periferal memory span\n" );
  }
  else
  {
    *(uint16_t *)(periferico.base_addr +  2*address) = dataIn;
  }
}


/**
  * @brief  write 8 bits in a FPGA peripheral.
  * @param  periferico: the peripheral struct
  * @param  address: address 
  * @param  dataIn : data input
  * @retval none
  */
void peripheral_write8(peripheral periferico, uint32_t address, uint8_t dataIn)
{
  if(address >= periferico.mem_span)
  {
    printf( "ERROR: addres out of the periferal memory span\n" );
  }
  else
  {
    *(uint8_t *)(periferico.base_addr +  address) = dataIn;
  }

}
//END LIBRARY FUNCTIONS


//BEGIN LOCAL FUNCTIONS
uint8_t virtual_base_init()
{
  int fd;
	printf("Montando a memoria da placa:\n");
	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) {
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}
	
	printf("Mapeia o inicio da mameoria:\n");
	virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );
	
	if( virtual_base == MAP_FAILED ) 
	{
		printf( "ERROR: mmap() failed...\n" );
		close( fd );
		return( 1 );
	}
}
//END LOCAL FUNCTIONS
