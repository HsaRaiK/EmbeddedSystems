module hex_decoder(boom,in, out);
	input boom; // whether or not the current number is a BOOM
	input [3:0] in; 
	output [6:0] out;
	reg [6:0] out;
	
	always @ (in)
	begin
		
		if (boom) begin 
			out = 7'b010_0000;
		end
		
		else begin
			case (in)
			4'b00000 : out = 7'b111_1110;
			4'b00001 : out = 7'b000_0110;
			4'b00010 : out = 7'b101_0011;
			4'b00011 : out = 7'b000_1111;
			4'b00100 : out = 7'b110_0110;
			4'b00101 : out = 7'b110_1101;
			4'b00110 : out = 7'b111_1100;
			4'b00111 : out = 7'b000_0111;
			4'b01000 : out = 7'b111_1111;
			4'b01001 : out = 7'b110_1111;
		endcase
	end
	end

	

	
endmodule