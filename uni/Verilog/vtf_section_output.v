`timescale 1ns / 1ps

module vtf_section_output;

	// Inputs
	reg clk;
	reg run_flag;
	reg size_flag;
	reg [4:0] usrt_pedge = 5'b0;

	// Outputs
	wire rts;
	wire txd;

	// Instantiate the Unit Under Test (UUT)
	section_output uut (
		.clk(clk), 
		.run_flag(run_flag), 
		.size_flag(size_flag), 
		.usrt_pedge(usrt_pedge[4]), 
		.rts(rts), 
		.txd(txd)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		run_flag = 0;
		size_flag = 1;
	end
      
	//clk
	always #5
		clk <= ~clk;
		
	//usrt_pedge
	always #5 begin
		if (usrt_pedge == 5'b10000)
			usrt_pedge <= 0;
		else 
			usrt_pedge <= usrt_pedge + 1;
	end
		
	always #262144
		run_flag <= ~run_flag;
	
endmodule

