`timescale 1ns / 1ps

module sw4_debounce(
	input clk,
	input btn,
	input run_flag,
	input rtg_btn,
	output size_flag
);

// a button-nel ellentétben itt elég két állapot
// mivel örökké 1-ben vagy 0-ban van
reg [1:0] btn_states = 2'b0;

always @ (posedge clk) begin
	if (rtg_btn)
		// csak akkor vegyünk mintát a kapcsoló állapotából,
		// ha nem fut a program. egyébként semmi értelme.
		// mégis ki az az eszelõs aki egyszer csak 7 helyett 8 bitet küld át
		// nem is lehet ezt ellenõrizni a másik oldalon
		// + run_flag nem egyezik meg az RTS-sel, 
		// ezért ha stop-ot nyomunk, de RTS még aktív, akkor 
		// size_flag váltani fog. de mikor vált? 
		// szerencsére usrt_clk-hoz képest túl lassan ahhoz,
		// hogy fedésbe kerüljenek
		if (!run_flag)
			// balra shifteljük
			btn_states <= {btn_states[0], btn};
end

// ha SW4 gomb 2x aktív jelet ad akkor a size_flag 1-be megy, 
// de ha visszakapcsoljuk 0-ba akkor már 1 rategen-re visszamegy
assign size_flag = (btn_states == 2'b11);

endmodule
