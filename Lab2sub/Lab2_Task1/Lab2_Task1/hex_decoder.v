module hex_decoder(in, out);
	input [3:0] in;
	output [6:0] out;
	reg [6:0] out;
	
	always @ (in)
	begin
	
		case (in)
		4'b0000 : out = 7'b111_1110;
		4'b0001 : out = 7'b000_0110;
		4'b0010 : out = 7'b101_0011;
		4'b0011 : out = 7'b000_1111;
		4'b0100 : out = 7'b110_0110;
		4'b0101 : out = 7'b110_1101;
		4'b0110 : out = 7'b111_1100;
		4'b0111 : out = 7'b000_0111;
		4'b1000 : out = 7'b111_1111;
		4'b1001 : out = 7'b110_1111;
	endcase
	
	end

	

	
endmodule