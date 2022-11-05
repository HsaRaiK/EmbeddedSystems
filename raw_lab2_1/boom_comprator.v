module boom_comprator(in,outdecod, outled);
input [4:0]in;
output [4:0]outdecod;
output outled;
reg [4:0]boomdetect;
reg decider;
wire selwire;
always @(in) begin
boomdetect = 5'b11111;
decider = in % 6;
end
	//if (decider == 0)begin
assign selwire = (decider == 0) ? 1 : 0;
assign outled = (decider == 0) ? 1 : 0;
		//end
	//end

assign outdecod = (decider == 0)? boomdetect : in;
//mux2to1 mx (.data1(in), .data2(boomdetect), .select(selwire), .out(outdecod));
 

endmodule