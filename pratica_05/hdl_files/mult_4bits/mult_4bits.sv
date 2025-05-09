`include "./defines.sv"

module mult_4bits(
    // commom signal
    input   clk_i,  // clock
    input   rst_i,  // reset
    // module inputs
    input [3:0] A_i,
    input [3:0] B_i,
    input       en_i,
    // module outputs
    output [2:0] estado_o,
    output [7:0] Y_o,
    output       fim_o
);

// Instanciando os Registradores que guardarao os operandos
//Definindo sinais de reg_A_inst
wire [7:0] A_input_w;
wire [7:0] A_output_w;

//Definindo a logica de atualização de A_input_w
assign A_input_w = (state_w == ST_IDLE) ? {4'h0, A_i} : A_output_w << 1;

registrador     // instanciando uma entidade;
    #(
    .DATA_WIDTH(8)      // parametro que controla o tamanho do registrador
    ) 
    reg_A_inst 
    (
    .clk_i  (clk_i),
    .rst_i  (rst_i),
    .en_i   (en_i),
    .data_i (A_input_w),
    .data_o (A_output_w)
    );

//Definindo sinais de reg_B_inst
wire [3:0] B_input_w;
wire [3:0] B_output_w;

//Definindo a logica de atualizacao de B_input_w
assign B_input_w = (state_w == ST_IDLE)? B_i: B_output_w >> 1;


registrador                      //Instanciando uma entidade;
	#(
	.DATA_WIDTH(4)               //parametro que controla o tamanho do registrador;
	)
	 reg_B_inst
    (
    .clk_i   (clk_i),       //clok da placa;
    .rst_i   (rst_i),       //veja que o reset e ativo em zero;
	 .en_i (1'b1),
    .data_i  (B_input_w),    
    .data_o  (B_output_w) 
    ); 

//Definindo sinais de reg_Y_inst
wire [7:0] Y_input_w;
wire [7:0] Y_output_w;

//Definindo a logica de atualizacao de A_input_w
assign Y_input_w = (state_w == ST_IDLE)? 8'd0:
                   (state_w == ST_END)? Y_output_w:
                   (B_output_w[0])? Y_output_w + A_output_w: Y_output_w;


registrador                      //Instanciando uma entidade;
	#(
	.DATA_WIDTH(8)               //parametro que controla o tamanho do registrador;
	)
	 reg_Y_inst
    (
    .clk_i  (clk_i),       //clok da placa;
    .rst_i  (rst_i),       //veja que o reset e ativo em zero;
	 .en_i (1'b1),
    .data_i (Y_input_w),    
    .data_o (Y_output_w) 
    ); 


//Instanciando o controle
//Definindo sinais do modulo de controle
estado_t state_w;

controlador controlador_inst
(
    .clk_i   (clk_i),
    .rst_i   (rst_i),
    .en_i    (en_i),
    .state_o (state_w)
);


//Saidas do sistema
assign Y_o = Y_output_w;

assign fim_o = (state_w == ST_END)? 1'b1: 1'b0;

assign estado_o = state_w;


endmodule

