`timescale 1ns / 1ps

module vft_usrt_posedge;

	// Inputs
	reg clk;
	reg usrt_clk;

	// Outputs
	wire usrt_pedge;

	// Instantiate the Unit Under Test (UUT)
	usrt_posedge uut (
		.clk(clk), 
		.usrt_clk(usrt_clk), 
		.usrt_pedge(usrt_pedge)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		usrt_clk = 0;
	end
   
	//clk
	always #5
		clk <= ~clk;
		
	//usrt_clk
	always #75
		usrt_clk <= ~usrt_clk;
	
endmodule

