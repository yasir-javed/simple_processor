module bram
	#(
		parameter RAM_WIDTH 		= 32,
		parameter RAM_ADDR_BITS 	= 9,
		parameter DATA_FILE 		= "data_file.txt",
		parameter INIT_START_ADDR 	= 0,
		parameter INIT_END_ADDR		= 10
	)
	(
	input							clock,
	input							ram_enable,
	input							write_enable,
    input 		[RAM_ADDR_BITS-1:0]	address,
    input 		[RAM_WIDTH-1:0] 	input_data,
	output reg 	[RAM_WIDTH-1:0] 	output_data
	);
	
   
   (* RAM_STYLE="BLOCK" *)
   reg [RAM_WIDTH-1:0] ram_name [(2**RAM_ADDR_BITS)-1:0];


   //  The forllowing code is only necessary if you wish to initialize the RAM 
   //  contents via an external file (use $readmemb for binary data)
   initial
      $readmemh(DATA_FILE, ram_name, INIT_START_ADDR, INIT_END_ADDR);

   always @(posedge clock)
      if (ram_enable) begin
         if (write_enable)
            ram_name[address] <= input_data;
         output_data <= ram_name[address];
      end

endmodule
						