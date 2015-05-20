`timescale 1ns / 1ps

module vtf_btn_bounce;

	// Inputs
	reg clk;
	reg btn;
	reg rtg_btn;

	// Outputs
	reg run_flag = 0;
	wire btn_output_state;

	// Instantiate the Unit Under Test (UUT)
	btn_debounce uut (
		.clk(clk), 
		.btn(btn), 
		.rtg_btn(rtg_btn), 
		.btn_output_state(btn_output_state)
	);

	initial begin
		// Initialize Inputs
		clk = 0;
		btn = 0;
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
	
	always @ (posedge clk)
		if (btn_output_state)
			run_flag <= 1;
	
endmodule

