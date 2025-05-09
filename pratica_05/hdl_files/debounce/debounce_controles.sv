`include "./sv/debounce/debounce_defines.sv"

module debounce_controler
(
    //common signals
    input           clk_i,
    input           rst_i,
    //input signals
    input           signal_i,
    input           end_delay_i,
    //output signals 
    output estado_db_t state_o
);

// INTERNAL SIGNALS ################################

estado_db_t  state, next_state;

// INTERNAL LOGIC ##################################

// Output logic
assign state_o = state;

//#################### SEQUENTIAL LOGIC

    // state update and reset
    always @(posedge clk_i, negedge rst_i) 
	 begin
        if (rst_i == 1'b0)
            state <= ST_DB_INIT;
        else
            state <= next_state;
    end



    // transiction logic
    always @(signal_i,end_delay_i,state) begin
        case (state)
            ST_DB_INIT:
            begin
                if(signal_i)
                begin
                    next_state   <=  ST_DB_DELAY_ON;
                end
                else
                begin
                    next_state   <=  ST_DB_INIT;
                end
            end    
            ST_DB_DELAY_ON:
            begin
                if(end_delay_i)
                begin
                     next_state   <=  ST_DB_DELAY_END;
                end
                else
                begin
                     next_state   <=  ST_DB_DELAY_ON;
                end
            end
            ST_DB_DELAY_END:
            begin
                if(signal_i)
                begin
                     next_state   <=  ST_DB_END;
                end
                else
                begin
                     next_state   <=  ST_DB_INIT;
                end
            end
            ST_DB_END:
            begin
                if(signal_i)
                begin
                    next_state   <=  ST_DB_END;
                end
                else
                begin
                    next_state   <=  ST_DB_INIT;
                end
            end
            default: 
            begin   
                next_state     <= ST_DB_INIT;
            end
        endcase
    end

endmodule
