module processor
	#(
		parameter RAM_WIDTH 		= 32,
		parameter RAM_ADDR_BITS 	= 9,
		parameter DATA_FILE 		= "data_file.txt",
		parameter DATA_START_ADDR 	= 0,
		parameter DATA_END_ADDR		= 5,
		parameter PROG_FILE 		= "program.hex",
		parameter PROG_START_ADDR 	= 0,
		parameter PROG_END_ADDR		= 8
	)

(
	input clk,
	input reset
);

parameter ADD  = 'd0;
parameter SUB  = 'd1;
parameter MUL  = 'd2;
parameter NAND = 'd3;
parameter LW   = 'd4;
parameter SW   = 'd5;

reg 	[RAM_ADDR_BITS-1:0] prog_cnt;
wire	[RAM_WIDTH-1:0]		instr;
	
wire	[RAM_WIDTH-1:0]		op1;
wire	[RAM_WIDTH-1:0]		op2;
reg 	[RAM_WIDTH-1:0]		alu_out;
reg 	[RAM_WIDTH-1:0]		reg_data_in;
wire	[RAM_WIDTH-1:0]		dram_data_out;
reg		[4:0]				opcode;
reg						ctl1,ctl2,ctl3;

// Instruction Fetch
always@(posedge clk)
	if(reset) 	prog_cnt <= 0;
	else 		prog_cnt <= prog_cnt + 1;

bram
#(
	.RAM_WIDTH 		(RAM_WIDTH 			),
	.RAM_ADDR_BITS 	(RAM_ADDR_BITS 		),
	.DATA_FILE 		(PROG_FILE 			),
	.INIT_START_ADDR(PROG_START_ADDR 	),
	.INIT_END_ADDR	(PROG_END_ADDR		)
)
prog_mem
(
	.clock			(clk			),
	.ram_enable		(1'b1			),
	.write_enable	(1'b0			),
	.address		(prog_cnt		),
	.input_data		(0				),
	.output_data    (instr			)
);

// Operand Fetch & Write back
reg_file regfile_inst
(
		.clk			(clk),
		.rd_addr1		(instr[21:17]),
		.rd_addr2		(instr[16:12]),
		.rd_data1		(op1),
		.rd_data2		(op2),
		.wr_addr		(instr[26:22]),
		.wr_en			(ctl1),
		.wr_data		(reg_data_in)
);

// ALU
always@* opcode = instr[31:27];
always@*
	case(opcode[1:0])
	ADD : alu_out =   op1 + op2;
	SUB : alu_out =   op1 - op2;
	MUL : alu_out =   op1 * op2;
	NAND: alu_out = ~(op1 & op2);
	endcase

always@* reg_data_in = ctl2 ? dram_data_out : alu_out;

// Data Memory
bram
#(
	.RAM_WIDTH 		(RAM_WIDTH 		),
	.RAM_ADDR_BITS 	(RAM_ADDR_BITS 	),
	.DATA_FILE 		(DATA_FILE		),
	.INIT_START_ADDR(DATA_START_ADDR),
	.INIT_END_ADDR	(DATA_END_ADDR	)
)
data_mem
(
	.clock			(clk			),
	.ram_enable		(1'b1			),
	.write_enable	(ctl3			),
	.address		(instr[8:0]		),
	.input_data		(op1			),
	.output_data    (dram_data_out	)
);

// Control Signals
always@* ctl1 = ~ctl3; 
always@* ctl2 = opcode == LW; 
always@* ctl3 = opcode == SW; 

endmodule