/*
A filter that takes average of the 4 consicutive numbers in stream and normalizes/ smoothens its graph
*/
module labsubiii(rst, x, CLOCK_50, y);
	input rst;
	input [7:0] x;
	input CLOCK_50;
	output [7:0] y;
	
	wire [7:0] w0 ,w1, w2,w3;
	wire [7:0] out_wire;
	wire [7:0] input_res_checked;
	reg [7:0]x_1, x_2, x_3;
	assign input_res_checked=(rst)?0:x;
	
	assign w0 = input_res_checked >> 2;
	assign w1 = x_1 >> 2;
	assign w2 = x_2 >> 2;
	assign w3 = x_3 >> 2;
	
	
	
	assign out_wire = w0 + w1 + w2 + w3;
	always @(posedge CLOCK_50) begin 
		
		//if (rst) begin 
		//	x_1 <= 1'b0;
		//	x_2 <= 1'b0;
		//	x_3 <= 1'b0;
		//end
		
		x_1 <= input_res_checked;
		x_2 <= x_1;
		x_3 <= x_2;
		
	end
	
	assign y = out_wire;
endmodule 