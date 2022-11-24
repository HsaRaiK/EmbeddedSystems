module Circuit_A (A, V, en);

input [3:0] V;
input en;

output [3:0] A;

assign A = (en) ? (V - 10):(V);

endmodule