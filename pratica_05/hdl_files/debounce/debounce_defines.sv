`ifndef DEBOUNCE_DEFINES_SV
`define DEBOUNCE_DEFINES_SV

`define CONTA_1S 32'd50000000

typedef enum logic [1:0] {
    ST_DB_INIT       = 2'b00, 
	ST_DB_DELAY_ON   = 2'b01, 
	ST_DB_DELAY_END  = 2'b10, 
	ST_DB_END        = 2'b11
} estado_db_t;



`endif
