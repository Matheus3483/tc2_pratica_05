`include "./sv/debounce/debounce_defines.sv"


module debounce
    #(               
        parameter  TIME_DEBOUCE = `CONTA_1S
    )
	 (
    //common signal
    input       clk_i,
    input       rst_i,
    //module inputs
    input       signal_i,
    //module outputs
    output      singal_o
);


//Sinais do modulo contador_inst
wire [31:0] contador_o_w;
wire [31:0] contador_i_w;
wire        enable_w;



registrador    
	#(
	.DATA_WIDTH(32)               //parametro que controla o tamanho do contador
	)
	 contador_inst
    (
    .clk_i  (clk_i),              //clok da placa
    .rst_i (rst_i),              //veja que o reset e ativo em zero
    .en_i (1'b1),
    .data_i (contador_i_w), //Incremeta 1 ao contador a cada pulso de clock
    .data_o (contador_o_w) 
    ); 

assign contador_i_w = (state_w == ST_DB_DELAY_ON )? contador_o_w + 'd1:
                      (state_w == ST_DB_DELAY_END)? contador_o_w:
                                                 'd0;

//assign enable_w = (state_w == ST_DELAY_ON)? 1'b1: 1'b0;

//Sinais do modulo debounce_controler_inst
estado_db_t state_w;
wire     end_delay_w;


debounce_controler debounce_controler_inst
(
    //common signals
    .clk_i         (clk_i),
    .rst_i         (rst_i),
    //input signals
    .signal_i      (signal_i),
    .end_delay_i   (end_delay_w),
    //output signals        
    .state_o       (state_w)
);

assign end_delay_w = (contador_o_w >= TIME_DEBOUCE)? 1'b1: 1'b0;

//Sinal de saida 
assign singal_o = (state_w == ST_DB_END)? 1'b1: 1'b0;

endmodule
