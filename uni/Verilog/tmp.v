`timescale 1ns / 1ps

module section_output (
	input clk,
	input run_flag,
	input size_flag,
	input usrt_pedge,
	output rts,
   output txd
);	

reg adas = 0;
reg [3:0] select_cntr = 4'b0;
reg out01 = 0;
reg reg_txd = 0;
reg reg_rts = 0;

always @ (posedge clk)
begin
	if (usrt_pedge) begin
		// ha a run_flag 1-be jut, elkezdjük az adást
		if (run_flag) begin
			// ADAS
			adas <= 1;
			// RTS out
			reg_rts <= 1;
		end
		// ha a runflag már 0 (tehát megállítottuk)
		else begin
			// de még van adás
			if (adas) begin
				// akkor ha eléri a 10-et a cntr, akkor megállunk
				if (select_cntr == 4'd10) begin
					adas <= 0;
					reg_rts <= 0;
					reg_txd <= 1;
				end
			end
			else begin
				reg_txd <= 1;
			end
		end
		// ha van adás akkor adunk
		if (adas) begin
			// multiplexer
			// start bit
			if (select_cntr == 0) begin
				reg_txd <= 0; 
			end
			else begin
				// output
				if (select_cntr < 4'd9)
					reg_txd <= out01;
				else 
					// stop bit
					if (select_cntr < 4'd11)
						reg_txd <= 1;
			end
			// select_cntr működése
			// ha 10 akkor resetelünk 0-ra és megfordítjuk az adat outputot
			if (select_cntr == 4'd10) begin
				select_cntr <= 0;
				out01 <= ~out01;
			end
			// egyébként növeljük
			else begin
				// ha a size 1 (8 bites) akkor simán növelünk
				if (size_flag)
					select_cntr <= select_cntr + 1;
				else
					// de ha size 0 (7 bites) akkor 1-ről 3-ra ugrunk
					if (select_cntr == 1)
						select_cntr <= select_cntr + 4'd2;
					else
						select_cntr <= select_cntr + 1;
				// ezt az egész részt lehetne így is de nem merem:
				// select_cntr <= select_cntr + ((~size_flag) & (select_cntr == 1));
			end
		end
	end
end

assign rts = reg_rts;
assign txd = reg_txd;

endmodule
