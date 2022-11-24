module comparator_9(in, out, outTens);

	input [3:0] in;
	output out;
	output [3:0] outTens;
	
	assign out = (in > 4'b1001) ? 1 : 0;
	assign outTens = (in > 4'b1001) ? 1 : 0;
	

endmodule