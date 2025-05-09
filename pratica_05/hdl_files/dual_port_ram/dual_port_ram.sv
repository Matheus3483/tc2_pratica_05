`include "./dual_port_ram_defines.sv"

module dual_port_ram(
    //common signal
    input       clk_i,
    input       rst_i,
    //Av-M-M interface
    output         write_o,
    output  [ 3:0] address_o,
    input   [31:0] readdata_i,
    output  [31:0] writedata_o,
    //mult_4bits interface
    output dpram_estado_t state_o,
    output [4:0] A_o,
    output [4:0] B_o,
    output       enable_o,
    input  [7:0] Y_i,
    input        fim_i
);


//Instanciando o controle
//Definindo sinais do modulo de controle
dpram_estado_t state_w;
wire crlt0_w;

assign crlt0_w = (state_w == ST_DPRAM_IDLE      )? readdata_i[0]:
                 (state_w == ST_DPRAM_ESPERAR_C0)? readdata_i[0]:
                 enable_o;

dual_port_ram_controller dual_port_ram_controller_inst
(
    .clk_i        (clk_i),
    .rst_i        (rst_i),
    .crlt0_i      (crlt0_w),
    .fim_i        (fim_i),
    .state_o      (state_w)
);


 // output logic
    always @(state_w,readdata_i,fim_i,Y_i) begin
        case (state_w)
            ST_DPRAM_IDLE:
            begin
                write_o     <= 1'b0;
                writedata_o <= 32'hXXXX;
                address_o   <= `DPRAM_ADDR_CONTROL;
                A_o         <= 4'hX;  
                B_o         <= 4'hX;
                enable_o    <= 1'b0;
            end
            ST_DPRAM_LER_AB: 
            begin
                write_o     <= 1'b0;
                writedata_o <= 32'hXXXX;
                address_o   <= `DPRAM_ADDR_DATA_IN;
                A_o         <= readdata_i[3:0];  
                B_o         <= readdata_i[7:4];
                enable_o    <= 1'b0;
            end       
            ST_DPRAM_INICIAR:       
            begin
                write_o     <= 1'b0;
                writedata_o <= 32'hXXXX;
                address_o   <= `DPRAM_ADDR_DATA_IN;
                A_o         <= readdata_i[3:0];  
                B_o         <= readdata_i[7:4];
                enable_o    <= 1'b1;
            end
            ST_DPRAM_ESPERAR_FIM:   
            begin
                write_o     <= 1'b0;
                writedata_o <= {24'h0,Y_i};
                address_o   <= `DPRAM_ADDR_DATA_OUT;
                A_o         <= 4'hX;  
                B_o         <= 4'hX;
                enable_o    <= 1'b1;
            end
            ST_DPRAM_GRAVAR_Y:      
            begin
                write_o     <= 1'b1;
                writedata_o <= {24'h0,Y_i};
                address_o   <= `DPRAM_ADDR_DATA_OUT;
                A_o         <= 4'hX;  
                B_o         <= 4'hX;
                enable_o    <= 1'b1;
            end
            ST_DPRAM_GRAVAR_STATUS_1: 
            begin
                write_o     <= 1'b0;
                writedata_o <= 32'h3;
                address_o   <= `DPRAM_ADDR_STATUS;
                A_o         <= 4'hX;  
                B_o         <= 4'hX;
                enable_o    <= 1'b1;
            end
            ST_DPRAM_GRAVAR_STATUS_2: 
            begin
                write_o     <= 1'b1;
                writedata_o <= 32'h1;
                address_o   <= `DPRAM_ADDR_STATUS;
                A_o         <= 4'hX;  
                B_o         <= 4'hX;
                enable_o    <= 1'b1;
            end
            ST_DPRAM_ESPERAR_C0:    
            begin
                write_o     <= 1'b0;
                writedata_o <= 32'hXXXX;
                address_o   <= `DPRAM_ADDR_CONTROL;
                A_o         <= 4'hX;  
                B_o         <= 4'hX;
                enable_o    <= readdata_i[0];
            end
            ST_DPRAM_LIMPAR_STATUS: 
            begin
                write_o     <= 1'b1;
                writedata_o <= 32'h00000000;
                address_o   <= `DPRAM_ADDR_STATUS;
                A_o         <= 4'hX;  
                B_o         <= 4'hX;
                enable_o    <= 1'b0;
            end
            default: 
            begin   
                write_o     <= 1'b0;
                writedata_o <= 32'hXXXX;
                address_o   <= `DPRAM_ADDR_CONTROL;
                A_o         <= 4'hX;  
                B_o         <= 4'hX;
                enable_o    <= 1'b0;
            end
        endcase

    end


//Saida de Testes:
assign state_o = state_w;

endmodule
