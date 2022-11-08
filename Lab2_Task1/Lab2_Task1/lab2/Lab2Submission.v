
module Lab2Submission(HEX0, HEX1, LED0,CLOCK_50,rst);
	input CLOCK_50, rst;
	output [7:0]HEX0, HEX1;
	output LED0;
	wire [3:0]w1, w2;
	wire w3, w4;
	wire [3:0]w5, w6;
	
	frequency_divider fd (.CLOCK_50(CLOCK_50),.outEnb(w1),.rst(rst));
	counter ct (.CLOCK_50(CLOCK_50) , .enable(w1), .rst(rst), .out(w2));
	boom_comprator bc (.in(w2), .outled(w3)); // w2 => number-to write hex in decimal, w3 => boom comparator result.
	
	comparator_9 cmp (.in(w2), .out(w4), .outTens(w6)); // w4 => 1: w2 is greater than 10, 0: less than 10
	//wire w6 = (w4) ? (4'b0001) : (4'b0000); // assign the tens digit to w6
	
	Circuit_A cA (.A(w5), .V(w2), .en(w4)); // if w2 is greater than 10, subtract 10
	
	hex_decoder hxd0 (.boom(w3), .in(w5), .out(HEX0)); // writes the ones digit to hex0.
	
	hex_decoder hxd1 (.boom(w3), .in(w6), .out(HEX1)); // writes the tens digit to hex1.
	assign LED0 = w3;
	
endmodule
