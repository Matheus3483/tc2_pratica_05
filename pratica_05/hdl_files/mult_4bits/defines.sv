`ifndef DEFINES_SV
`define DEFINES_SV

typedef enum logic [2:0] {
   ST_IDLE    		  = 3'b000, 
	ST_COMPUTE_BIT_0 = 3'b001,
	ST_COMPUTE_BIT_1 = 3'b010,
	ST_COMPUTE_BIT_2 = 3'b011,
	ST_COMPUTE_BIT_3 = 3'b100,
	ST_END			  = 3'b101
} estado_t;


`endif

