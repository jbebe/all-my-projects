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

always @ (posedge clk) begin
	if (usrt_pedge) begin
		// ha stop-ban vagyunk �s nincs ad�s akkor txd magas, rts alacsony
		if ((run_flag == 0) && (adas == 0)) begin
			reg_txd <= 1;
			reg_rts <= 0;
		end
		else begin
			// ha start-ban vagyunk de m�g nincs ad�s, csak kiadjuk az ad�s parancsot
			// ez az�rt jobb �gy, mert akkor rts nem fog sietni egy �rajelet
			if ((run_flag == 1) && (adas == 0)) begin
				adas <= 1;
			end
			else begin
				// itt kezelj�k le azt, amikor ad�sban vagyunk
				if (adas == 1) begin
					// az, hogy run_flag m�r 0, csak akkor �rdekel minket
					// ha eljutottunk 10-ig a select-tel
					if ((run_flag == 0) && (select_cntr == 10)) begin
						// ekkor txd-t 1-be �ll�tjuk
						// lenull�zzuk a cntr-t
						// �s az ad�st kikapcsoljuk
						reg_txd <= 1;
						select_cntr <= 0;
						adas <= 0;
					end
					else begin
						// ha a run flag �ppen nem 0 akkor csak sim�n
						// adjuk ki a jeleket egym�s ut�n
						if (select_cntr == 0) begin // start bit
							reg_txd <= 0;
							// mivel a start bit minden 7/8 bitn�l csak 1x jelenik meg
							// ez�rt itt neg�ljuk az outputot
							// stop bitn�l m�r macer�sabb lenne
							out01 <= ~out01;
						end
						else begin
							if (select_cntr < 9) // 00000000-11111111
								reg_txd <= out01; 
							else
								if (select_cntr < 11) // 11 stop bitek
									reg_txd <= 1;
						end
						// ha el�rt�k a 10-et, akkor lenull�zzuk
						// run_flag itt 1, teh�t nincs konkurrens iz�
						if (select_cntr == 10)
							select_cntr <= 0;
						else
							// ha 0-n�l j�runk, �s a size_flag is 0
							// akkor 0 ut�n 2 j�n, teh�t 8 helyett 7 adatbit�nk lesz
							if ((select_cntr == 0) && (size_flag == 0))
								select_cntr <= select_cntr + 2;
							else
								select_cntr <= select_cntr + 1;
					end
					// ha ad�s van, rts kimenete folyamatosan 1
					// �gy rts nem siet txd-hez k�pest
					reg_rts <= 1;
				end
			end
		end
	end
end

// kivezetj�k �ket
assign rts = reg_rts;
assign txd = reg_txd;

endmodule
