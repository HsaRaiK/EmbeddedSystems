module Lab2Submission(in,out,CLOCK_50,rst);
input in, CLOCK_50, rst;
output out;
wire [4:0]w1, w2, w3; 
wire w4;
frequency_divider fd (.CLOCK_50(CLOCK_50),.outEnb(w1),.rst(rst));
counter ct (.CLOCK_50(CLOCK_50) , .enable(w1), .rst(rst), .out(w2));
boom_comprator bc (.in(w2),.outdecod(w3), .outled(w4));
endmodule
