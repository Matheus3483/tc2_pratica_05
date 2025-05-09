//=======================================================
//  Title: Avalon Memory Mapped to Wishbone Bridge
//  Description: Wait request is not implemented yet!!
//=======================================================

module avalon_to_wishone_bridge
    #(
        parameter  BUS_WIDTH  = 5,
        parameter  DATA_WIDTH = 32,
        parameter  BE_WIDTH   = 4
    )
    (
    //Common signal:
    input clk_i, 
    input rst_i, 
    //Avalon MM interface:
    input  avmm_chipselect, //The System Interconnect Fabric has to generate this signal
    input  [BUS_WIDTH-1:0] avmm_address,
    input  avmm_read, 
    output [DATA_WIDTH-1:0] avmm_readdata,
    input  avmm_write, 
    input  [DATA_WIDTH-1:0] avmm_writedata,
    input  [BE_WIDTH-1:  0] avmm_byteenable, 
    input  avmm_begintransfer, //Is this necessary?
    output avmm_waitrequest,   //It is not implemented yet
    //Wishbone interface:
    output [BUS_WIDTH-1:0]  adr_o,  //Address Out
    input  [DATA_WIDTH-1:0] data_i, //Data In
    output [DATA_WIDTH-1:0] data_o, //Data Out
    output we_o,                    //Write Enable Out
    output [BE_WIDTH-1:  0] sel_o,  //Select output array
    output stb_o,                   //Strobe Out
    input  ack_i                   //Acknowledged Out
    );
 
assign adr_o  = avmm_address;
assign data_o = avmm_writedata;
assign stb_o  = avmm_chipselect;
assign we_o   = avmm_write;
assign sel_o  = avmm_byteenable;

assign avmm_readdata = data_i;


endmodule