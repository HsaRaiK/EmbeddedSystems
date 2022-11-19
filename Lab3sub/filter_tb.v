`timescale 1 ns/10 ps

module filter_tb();

	reg rst, CLOCK_50;
	reg [7:0] x;
	wire y;
	
	
	localparam period = 20;
	
	labsubiii F20NS (.rst(rst),.CLOCK_50(CLOCK_50),.x(x),.y(y));
	
	initial begin
			
			x = 0;
			#period;
			x = 13;
			#period;
			x = 20;
			#period;
			x = 17;
			#period;
			x = 12;
			#period;
			x = 25;
			#period;
			x = 31;
			#period;
			x = 11;
			#period;
			x = 112;
			#period;
			x = 41;
			#period;
			x = 21;
			#period;
			x = 32;
			#period;
			x = 231;
			#period;
			x = 43;
			#period;
			x = 41;
			#period;
			x = 32;
			#period;
			x = 21;
			#period;
			x = 33;
			#period;
			x = 45;
			#period;
			x = 7;
			#period;
			x = 21;
			#period;
			x = 44;
			#period;
		end	
endmodule
 