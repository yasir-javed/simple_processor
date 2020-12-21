module reg_file(
		input 			clk,
		input 	[4:0]	rd_addr1,
		input	[4:0]	rd_addr2,
		output	[31:0]	rd_data1,
		output	[31:0]	rd_data2,
		
		input	[4:0]	wr_addr,
		input			wr_en,
		input	[31:0]	wr_data
);

reg [31:0] regs[0:31];

always@(posedge clk)
	if(wr_en)	regs[wr_addr] <= wr_data;
		
assign	rd_data1 = regs[rd_addr1];
assign	rd_data2 = regs[rd_addr2];

endmodule