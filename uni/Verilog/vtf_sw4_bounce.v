`timescale 1ns / 1ps

module vtf_sw4_bounce;

	// Inputs
	reg clk;
	reg btn;
	reg run_flag;
	reg rtg_btn;

	// Outputs
	wire size_flag_out;

	// Instantiate the Unit Under Test (UUT)
	sw4_debounce uut (
		.clk(clk), 
		.btn(btn), 
		.run_flag(run_flag), 
		.rtg_btn(rtg_btn), 
		.size_flag(size_flag_out)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		btn = 0;
		run_flag = 0;
		rtg_btn = 0;
		
		#86214 
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= 1;
		#1310720
		btn <= 0;
		#86214 
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		
		// második változat run_flag-gel
		#131072
		run_flag <= 1;
		#86214 
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= 1;
		#1310720
		btn <= 0;
		#86214 
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
		#86214
		btn <= ~btn;
	end

	//clk
	always #5
		clk <= ~clk;
		
	always #262144
		rtg_btn <= 1;
		
	always #262144 begin
		#5
		rtg_btn <= 0;
	end

endmodule

