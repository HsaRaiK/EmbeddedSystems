module counter(CLOCK_50, enable, rst, out);
input CLOCK_50, enable, rst;
output reg[3:0] out;
always @ (posedge CLOCK_50) begin
	if (rst) begin
		out <= 0;
	end
	if (~ rst) begin
		if(enable) begin
		out <= out + 1;
		end
	end
end	
endmodule

		
