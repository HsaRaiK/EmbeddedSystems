module boom_comprator(in, outled);
	input [3:0]in;
	output outled;
	reg [2:0]decider;
	
	always @(in) begin
		decider = in % 6;
	end
		
	assign outled = (decider == 0) ? 1 : 0;


	
	
	 

endmodule