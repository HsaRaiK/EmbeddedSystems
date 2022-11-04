module Lab2Submission(in,out,CLOCK_50);
input in, CLOCK_50;
output out;
frequency_divider nametag (.CLOCK_50(CLOCK_50),.outEnb(out),.rst(in));
endmodule
