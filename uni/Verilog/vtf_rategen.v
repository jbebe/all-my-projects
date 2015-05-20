`timescale 1ns / 1ps

module vtf_rategen;

	// Inputs
	reg clk = 0;

	// Outputs
	wire rtg_out;

	// Instantiate the Unit Under Test (UUT)
	rategen uut (
		.clk(clk), 
		.rtg_out(rtg_out)
	);

	//clk
	always #5
		clk <= ~clk;
      
endmodule

