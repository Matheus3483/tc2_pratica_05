`ifndef DUAL_PORT_RAM_SV
`define DUAL_PORT_RAM_SV

typedef enum logic [3:0] {
    ST_DPRAM_IDLE             = 4'b0000, 
	ST_DPRAM_LER_AB           = 4'b0001, 
	ST_DPRAM_INICIAR          = 4'b0010, 
	ST_DPRAM_ESPERAR_FIM      = 4'b0011, 
	ST_DPRAM_GRAVAR_Y         = 4'b0100, 
	ST_DPRAM_GRAVAR_STATUS_1  = 4'b0101,
	ST_DPRAM_GRAVAR_STATUS_2  = 4'b0110,
	ST_DPRAM_ESPERAR_C0       = 4'b0111,  
	ST_DPRAM_LIMPAR_STATUS    = 4'b1000
} dpram_estado_t;


`define DPRAM_ADDR_CONTROL  0
`define DPRAM_ADDR_DATA_IN  1
`define DPRAM_ADDR_DATA_OUT 2
`define DPRAM_ADDR_STATUS   3



`endif