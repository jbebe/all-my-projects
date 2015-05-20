`timescale 1ns / 1ps

module vtf_ssa3_top;

	// Inputs
	reg clk;
	reg btn1;
	reg btn2;
	reg sw4;
	reg usrt_clk;

	// Outputs
	wire rts;
	wire txd;

	// Instantiate the Unit Under Test (UUT)
	ssa3_top uut (
		.clk(clk), 
		.btn1(btn1), 
		.btn2(btn2), 
		.sw4(sw4), 
		.usrt_clk(usrt_clk), 
		.rts(rts), 
		.txd(txd)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		btn1 = 0;
		btn2 = 0;
		sw4 = 0;
		usrt_clk = 0;
		
		#1000
		sw4 <= 1;
		
		#2000
		btn1 <= 1;
		#6621440
		btn1 <= 0;
		
		#5000000
		btn2 <= 1;
		#6621440
		btn2 <= 0;
		
		#10000
		sw4 <= 0;
		
		#2000
		btn1 <= 1;
		#6621440
		btn1 <= 0;
		
		#5000000
		btn2 <= 1;
		#6621440
		btn2 <= 0;
	end

	//clk
	always #5
		clk <= ~clk;
		
	always #75
		usrt_clk <= ~usrt_clk;
      
endmodule

