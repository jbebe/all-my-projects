`timescale 1ns / 1ps

module ssa3_top(
    input clk, // fpga �rajele
    input btn1,// BTN1 - start
    input btn2,// BTN2 - stop
    input sw4, // SW4 - size
	 input usrt_clk, // k�ls� �rajel
    output rts, // ad�s van
    output txd // maga az ad�s
	 //,output [33:0] LANAL
    );
// debug
//assign LANAL = {run_flag, size_flag, usrt_pedge, rtg_btn, 30'b0};

// bels� "v�ltoz�k"
reg run_flag = 0; // run_flag azt jelenti a gomb szerint futnia kell-e
wire run_flag_out_btn1; // kett�v�lasztottuk a gombok kimenet�t,
wire run_flag_out_btn2; // hogy ne legyen error

reg size_flag = 1; // 7 bit: 0, 8 bit: 1
wire size_flag_out;// jobb ha a m�ret se zsin�r, hanem  elt�rol�dik
wire usrt_pedge; // a posedge el�g ha csak wire, mert 1 clk-ig sz�ks�ges
wire rtg_btn; // rategen a button-nek

// mindent amit top levelen regiszterbe ment�nk, itt van
always @ (posedge clk) begin
	// ha a start gomb lett megnyomva
	// be�ll�tjuk a run_flaget 1-be
	if (run_flag_out_btn1) begin
		run_flag <= 1;
	end
	else begin
		// ha nem nyomtuk meg a start gombot legal�bb 1 �rajel �ta,
		// akkor a stop gomb be�ll�tja 0-ba
		if (run_flag_out_btn2)
			run_flag <= 0;
	end
	// k�zben size_flag �rt�ke mindig annyi, 
	// amennyire r� van kattanva SW4
	size_flag <= size_flag_out;
end

// reategen-hez
rategen btn_rategen(.clk(clk), .rtg_out(rtg_btn));

// gombok dibuncol�sa
btn_debounce b1bnc (
	.clk(clk), 
	.btn(btn1), 
	.rtg_btn(rtg_btn), 
	.btn_output_state(run_flag_out_btn1)
);
btn_debounce b2bnc (
	.clk(clk), 
	.btn(btn2), 
	.rtg_btn(rtg_btn),
	.btn_output_state(run_flag_out_btn2)
);
sw4_debounce sw4bnc(
	.clk(clk),
	.btn(sw4),
	.run_flag(run_flag),
	.rtg_btn(rtg_btn),
	.size_flag(size_flag_out)
);

// USRT clockja posedge-re akt�v
usrt_posedge upe(
	.clk(clk),
	.usrt_clk(usrt_clk),
	.usrt_pedge(usrt_pedge)
);

// output megval�s�t�sa
section_output so(
	.clk(clk),
	.run_flag(run_flag),
	.size_flag(size_flag),
	.usrt_pedge(usrt_pedge),
	.rts(rts),
   .txd(txd)
);	

endmodule
