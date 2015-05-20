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
		// ha stop-ban vagyunk és nincs adás akkor txd magas, rts alacsony
		if ((run_flag == 0) && (adas == 0)) begin
			reg_txd <= 1;
			reg_rts <= 0;
		end
		else begin
			// ha start-ban vagyunk de még nincs adás, csak kiadjuk az adás parancsot
			// ez azért jobb így, mert akkor rts nem fog sietni egy órajelet
			if ((run_flag == 1) && (adas == 0)) begin
				adas <= 1;
			end
			else begin
				// itt kezeljük le azt, amikor adásban vagyunk
				if (adas == 1) begin
					// az, hogy run_flag már 0, csak akkor érdekel minket
					// ha eljutottunk 10-ig a select-tel
					if ((run_flag == 0) && (select_cntr == 10)) begin
						// ekkor txd-t 1-be állítjuk
						// lenullázzuk a cntr-t
						// és az adást kikapcsoljuk
						reg_txd <= 1;
						select_cntr <= 0;
						adas <= 0;
					end
					else begin
						// ha a run flag éppen nem 0 akkor csak simán
						// adjuk ki a jeleket egymás után
						if (select_cntr == 0) begin // start bit
							reg_txd <= 0;
							// mivel a start bit minden 7/8 bitnél csak 1x jelenik meg
							// ezért itt negáljuk az outputot
							// stop bitnél már macerásabb lenne
							out01 <= ~out01;
						end
						else begin
							if (select_cntr < 9) // 00000000-11111111
								reg_txd <= out01; 
							else
								if (select_cntr < 11) // 11 stop bitek
									reg_txd <= 1;
						end
						// ha elértük a 10-et, akkor lenullázzuk
						// run_flag itt 1, tehát nincs konkurrens izé
						if (select_cntr == 10)
							select_cntr <= 0;
						else
							// ha 0-nál járunk, és a size_flag is 0
							// akkor 0 után 2 jön, tehát 8 helyett 7 adatbitünk lesz
							if ((select_cntr == 0) && (size_flag == 0))
								select_cntr <= select_cntr + 2;
							else
								select_cntr <= select_cntr + 1;
					end
					// ha adás van, rts kimenete folyamatosan 1
					// így rts nem siet txd-hez képest
					reg_rts <= 1;
				end
			end
		end
	end
end

// kivezetjük õket
assign rts = reg_rts;
assign txd = reg_txd;

endmodule
