module registrador
#(
    parameter DATA_WIDTH = 32
)
(
    // common signal:
    input          	clk_i,
    input          	rst_i,
    input          	en_i,
    //:
    input   [DATA_WIDTH-1:0] 	data_i, // data In
    output	[DATA_WIDTH-1:0] 	data_o // data Out
);

// INTERNAL SIGNALS ################################

// INTERNAL REGISTERS ##############################
reg [DATA_WIDTH-1:0] data_reg;

// INTERNAL LOGIC ##################################

// SEQUENTIAL LOGIC 
// Update register

    // state update and reset
    always @(posedge clk_i, negedge rst_i) 
    begin
        if (rst_i == 1'b0)
        begin
            data_reg <= 0;
        end
        else
        begin
            data_reg <= en_i ? data_i : data_reg;
        end
    end

    // Output logic
    assign data_o = data_reg;

endmodule

