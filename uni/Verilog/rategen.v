`timescale 1ns / 1ps

module rategen(
	input clk,
	output rtg_out
   );
	 
// 19 biten t�roljuk el mert 
// 262144 ciklus az pont 2.62 ms ami el�g id�
// check-elni btn �rt�k�t
reg [18:0] cntr_rtg = 19'b0;

always @ (posedge clk)
	if (cntr_rtg == 19'b1000000000000000000)
		cntr_rtg <= 0;
	else
		cntr_rtg <= cntr_rtg + 1;

// kivezetj�k a legfels� bitet
// �gy csak kis t�ske lesz bel�le
assign rtg_out = cntr_rtg[18];

endmodule
