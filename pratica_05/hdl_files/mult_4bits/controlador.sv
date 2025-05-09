`include "./defines.sv"


module controlador
(
    input          	    clk_i,
    input          	    rst_i,
    input          	    en_i,
	output	estado_t 	state_o
);

// INTERNAL SIGNALS ################################

estado_t  state, next_state;

// INTERNAL LOGIC ##################################

// Output logic
assign state_o = state;

//#################### SEQUENTIAL LOGIC

    // state update and reset
    always @(posedge clk_i, negedge rst_i) 
	 begin
        if (rst_i == 1'b0)
            state <= ST_IDLE;
        else
            state <= next_state;
    end



    // transiction logic
    always @(en_i, state) begin
        case (state)
            ST_IDLE:
            begin
                if(en_i)
						begin
                    next_state   <=  ST_COMPUTE_BIT_0;
						end
                else
						begin
                    next_state   <=  ST_IDLE;
						end
            end    
				
            ST_COMPUTE_BIT_0:
            begin	
               next_state     <= ST_COMPUTE_BIT_1 ;
            end
				
			ST_COMPUTE_BIT_1:
            begin	
               next_state     <= ST_COMPUTE_BIT_2 ;
            end
				
			ST_COMPUTE_BIT_2:
            begin	
               next_state     <= ST_COMPUTE_BIT_3 ;
            end
				
			ST_COMPUTE_BIT_3:
            begin	
               next_state     <= ST_END ;
            end
            
            ST_END:
            begin
                if(en_i)
				begin
                    next_state   <=  ST_END;
				end
                else
				begin
                    next_state   <=  ST_IDLE;
				end
            end
            default: 
            begin   
                next_state     <= ST_IDLE;
            end
        endcase
    end

endmodule

