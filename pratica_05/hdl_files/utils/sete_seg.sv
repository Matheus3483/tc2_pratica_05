module sete_seg(
    //common signal
    input          	    clk_i,
    //input          	    rst_i,
    //module inputs
    input [3:0] Y_i,
    //module outputs
    output [6:0] HEX_o
);

always @(Y_i) begin
    case(Y_i)
        4'h0: HEX_o = 7'b1000000; // 0
        4'h1: HEX_o = 7'b1111001; // 1
        4'h2: HEX_o = 7'b0100100; // 2
        4'h3: HEX_o = 7'b0110000; // 3
        4'h4: HEX_o = 7'b0011001; // 4
        4'h5: HEX_o = 7'b0010010; // 5
        4'h6: HEX_o = 7'b0000010; // 6
        4'h7: HEX_o = 7'b1111000; // 7
        4'h8: HEX_o = 7'b0000000; // 8
        4'h9: HEX_o = 7'b0010000; // 9
        4'hA: HEX_o = 7'b0001000; // A
        4'hB: HEX_o = 7'b0000011; // b
        4'hC: HEX_o = 7'b1000110; // C
        4'hD: HEX_o = 7'b0100001; // d
        4'hE: HEX_o = 7'b0000110; // E
        4'hF: HEX_o = 7'b0001110; // F
        default: HEX_o = 7'b1111111; // -
    endcase
end

endmodule
