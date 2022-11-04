module frequency_divider(
CLOCK_50,
outEnb,
rst);
//output reg outEnb;
//input CLOCK_50;
//input rst;
//always @(posedge CLOCK_50)
//begin
//if (~rst)
//     outEnb <= 1'b0;
//else
//     outEnb <= ~outEnb;	
//end
//endmodule
//parameter WIDTH = 3,
//parameter N = 5)
 
//(clk,reset, clk_out);
parameter WIDTH = 3;
parameter N = 50000; 
input CLOCK_50;
input rst;
output outEnb;
 
reg [WIDTH-1:0] pos_count, neg_count;
wire [WIDTH-1:0] r_nxt;
 
 always @(posedge CLOCK_50)
 if (rst)
 pos_count <=0;
 else if (pos_count ==N-1) pos_count <= 0;
 else pos_count<= pos_count +1;
 
 always @(negedge CLOCK_50)
 if (rst)
 neg_count <=0;
 else  if (neg_count ==N-1) neg_count <= 0;
 else neg_count<= neg_count +1; 
 
assign outEnb = ((pos_count > (N>>1)) | (neg_count > (N>>1))); 
endmodule