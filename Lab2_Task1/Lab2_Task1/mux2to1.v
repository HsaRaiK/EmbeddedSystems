module mux2to1 (data1, data2, select, out);
input [4:0]data1, data2;
input select;
output [4:0]out;
assign out = (select == 0) ? data1 : data2;
endmodule