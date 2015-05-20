`timescale 1ns / 1ps

module sw4_debounce(
	input clk,
	input btn,
	input run_flag,
	input rtg_btn,
	output size_flag
);

// a button-nel ellent�tben itt el�g k�t �llapot
// mivel �r�kk� 1-ben vagy 0-ban van
reg [1:0] btn_states = 2'b0;

always @ (posedge clk) begin
	if (rtg_btn)
		// csak akkor vegy�nk mint�t a kapcsol� �llapot�b�l,
		// ha nem fut a program. egy�bk�nt semmi �rtelme.
		// m�gis ki az az eszel�s aki egyszer csak 7 helyett 8 bitet k�ld �t
		// nem is lehet ezt ellen�rizni a m�sik oldalon
		// + run_flag nem egyezik meg az RTS-sel, 
		// ez�rt ha stop-ot nyomunk, de RTS m�g akt�v, akkor 
		// size_flag v�ltani fog. de mikor v�lt? 
		// szerencs�re usrt_clk-hoz k�pest t�l lassan ahhoz,
		// hogy fed�sbe ker�ljenek
		if (!run_flag)
			// balra shiftelj�k
			btn_states <= {btn_states[0], btn};
end

// ha SW4 gomb 2x akt�v jelet ad akkor a size_flag 1-be megy, 
// de ha visszakapcsoljuk 0-ba akkor m�r 1 rategen-re visszamegy
assign size_flag = (btn_states == 2'b11);

endmodule
