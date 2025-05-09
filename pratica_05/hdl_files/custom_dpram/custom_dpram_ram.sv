`include "./custom_dpram_defines.sv"

module custom_dpram
    #(
        parameter  BUS_WIDTH  = 1,
        parameter  DATA_WIDTH = 32,
        parameter  BE_WIDTH   = 4
    )
    (
    //common signal
    input       clk_i,
    input       rst_i,
    //Wishbone Slave interface
    //Wishbone interface:
    input  [BUS_WIDTH-1:0]  adr_i,  //Address In
    input  [DATA_WIDTH-1:0] data_i, //Data In
    output [DATA_WIDTH-1:0] data_o, //Data Out
    input  we_i,                    //Write Enable In
    input  [BE_WIDTH-1:  0] sel_i,  //Select input array
    input  stb_i,                   //Strobe In
    output ack_o,                   //Acknowledged Out
    //mult_4bits interface
    //output dpram_estado_t state_o,
    output [3:0] A_o,
    output [3:0] B_o,
    output       enable_o,
    input  [7:0] Y_i,
    input        fim_i
);


// Instanciando o Registrador de Comando: fazendo como um registrado, para caso precise aumentar os comandos
// Definindo sinais de reg_Control_inst
wire Control_input_w;
wire Control_output_w;

//Definindo a logica de atualizacao de Control_input_w
assign Control_input_w = ((we_i == 1'b1)&& (sel_i[`CDPRAM_SEL_CONTROL]) == 1'b1)?  data_i[0]: Control_output_w;

registrador                      //Instanciando uma entidade;
	#(
	.DATA_WIDTH(1)               //parametro que controla o tamanho do registrador;
	)
	 reg_Control_inst
    (
    .clk_i   (clk_i),       //clok da placa;
    .rst_i   (rst_i),       //veja que o reset e ativo em zero;
	.en_i (1'b1),
    .data_i  (Control_input_w),    
    .data_o  (Control_output_w) 
    ); 

assign enable_o = Control_output_w;


// Instanciando os Registradores que guardarao os operandos
//Definindo sinais de reg_AB_inst
wire [7:0] AB_input_w;
wire [7:0] AB_output_w;

//Definindo a logica de atualizacao de A_input_w
assign AB_input_w = ((we_i == 1'b1)&& (sel_i[`CDPRAM_SEL_DATA_IN]) == 1'b1)?  data_i[17:8]: AB_output_w;

registrador                      //Instanciando uma entidade;
	#(
	.DATA_WIDTH(8)               //parametro que controla o tamanho do registrador;
	)
	 reg_A_inst
    (
    .clk_i   (clk_i),       //clok da placa;
    .rst_i   (rst_i),       //veja que o reset e ativo em zero;
	 .en_i (1'b1),
    .data_i  (AB_input_w),    
    .data_o  (AB_output_w) 
    ); 

assign A_o = AB_output_w[3:0];
assign B_o = AB_output_w[7:4];

//Leitura
assign data_o = {7'd0,fim_i,Y_i,AB_output_w,7'd0,Control_output_w};


endmodule
