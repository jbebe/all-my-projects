`timescale 1ns / 1ps

module rategen(
	input clk,
	output rtg_out
   );
	 
// 19 biten tároljuk el mert 
// 262144 ciklus az pont 2.62 ms ami elég idõ
// check-elni btn értékét
reg [18:0] cntr_rtg = 19'b0;

always @ (posedge clk)
	if (cntr_rtg == 19'b1000000000000000000)
		cntr_rtg <= 0;
	else
		cntr_rtg <= cntr_rtg + 1;

// kivezetjük a legfelsõ bitet
// így csak kis tüske lesz belõle
assign rtg_out = cntr_rtg[18];

endmodule
