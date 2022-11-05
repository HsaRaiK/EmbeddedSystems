module frequency_divider(CLOCK_50, outEnb, rst);

    parameter N = 50_000_000;
    input CLOCK_50, rst;
    output outEnb;
    
    reg [25:0] clkCtr;
    
    always @(posedge CLOCK_50) begin
        clkCtr <= clkCtr + 1;
        
        if (rst)
            clkCtr <= 0;
            
            
    end
        
    assign outEnb = (clkCtr >= N) ? 1 : 0;
        
    
endmodule