module tb_processor;

reg 			clk;
reg 			reset;

processor 
#(
	.RAM_WIDTH 			(32				),
	.RAM_ADDR_BITS 		(9				),
	.DATA_FILE 			("data_file.txt"),
	.DATA_START_ADDR 	(0				),
	.DATA_END_ADDR		(7				),
	.PROG_FILE 			("program.hex"	),
	.PROG_START_ADDR 	(0				),
	.PROG_END_ADDR		(14             )
)

processor_inst(
	.clk			(clk		),
	.reset			(reset		)
);

initial
begin
	clk = 0;
	forever
		#5 clk = ~clk;
end

initial
begin
	$dumpfile("wave.vcd");
	$dumpvars(0,tb_processor);

	reset	= 0;
	@(posedge clk);
	#1 reset = 1;
	
	@(posedge clk);
	#1 reset = 0;

	
	repeat(30)@(posedge clk);
	$finish;
end
endmodule
