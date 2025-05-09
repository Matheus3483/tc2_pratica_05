`include "./dual_port_ram_defines.sv"


module dual_port_ram_controller
(
    //sinais comuns
    input           clk_i,
    input           rst_i,
    //sinais aos quais o controlador e sensivel
    input           crlt0_i,
    input           fim_i,
    //estado atual para gerar as saidas
    output dpram_estado_t state_o
);

// INTERNAL SIGNALS ################################

dpram_estado_t  state, next_state;

// INTERNAL LOGIC ##################################

// Output logic
assign state_o = state;

//#################### SEQUENTIAL LOGIC

    // state update and reset
    always @(posedge clk_i, negedge rst_i) 
	 begin
        if (rst_i == 1'b0)
            state <= ST_DPRAM_IDLE;
        else
            state <= next_state;
    end



    // transiction logic
    always @(crlt0_i,fim_i,state) begin
        case (state)
            ST_DPRAM_IDLE:
            begin
                if(crlt0_i)
                begin
                    next_state   <=  ST_DPRAM_LER_AB;
                end
                else
                begin
                    next_state   <=  ST_DPRAM_IDLE;
                end
            end    
            ST_DPRAM_LER_AB:
            begin   
                next_state     <= ST_DPRAM_INICIAR;
            end
            ST_DPRAM_INICIAR:
            begin   
                next_state     <= ST_DPRAM_ESPERAR_FIM;
            end
            ST_DPRAM_ESPERAR_FIM:
            begin   
                 if(fim_i)
                begin
                    next_state   <=  ST_DPRAM_GRAVAR_Y;
                end
                else
                begin
                    next_state   <=  ST_DPRAM_ESPERAR_FIM;
                end
            end
            ST_DPRAM_GRAVAR_Y:
            begin   
                next_state     <= ST_DPRAM_GRAVAR_STATUS_1;
            end
            ST_DPRAM_GRAVAR_STATUS_1:
            begin   
                next_state     <= ST_DPRAM_GRAVAR_STATUS_2;
            end
            ST_DPRAM_GRAVAR_STATUS_2:
            begin   
                next_state     <= ST_DPRAM_ESPERAR_C0;
            end
            ST_DPRAM_ESPERAR_C0:
            begin
                if(crlt0_i)
                begin
                    next_state   <=  ST_DPRAM_ESPERAR_C0;
                end
                else
                begin
                    next_state   <=  ST_DPRAM_LIMPAR_STATUS;
                end
            end
            ST_DPRAM_LIMPAR_STATUS:
            begin   
                next_state     <= ST_DPRAM_IDLE;
            end
            default: 
            begin   
                next_state     <= ST_DPRAM_IDLE;
            end
        endcase
    end

endmodule