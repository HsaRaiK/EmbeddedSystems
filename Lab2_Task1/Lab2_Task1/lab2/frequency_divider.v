module frequency_divider(CLOCK_50, outEnb, rst);

    parameter N = 50;
    input CLOCK_50, rst;
    output outEnb;
    
	 wire inner_res;
	 
    reg [25:0] clkCtr;
    
    always @(posedge CLOCK_50) begin
        clkCtr <= clkCtr + 1;
        
        if (rst || inner_res)
            clkCtr <= 0;
			
            
            
    end
        
    assign outEnb = (clkCtr >= N) ? 1 : 0;
	 
	 assign inner_res = (outEnb) ? 1 : 0;
        
    
endmodule