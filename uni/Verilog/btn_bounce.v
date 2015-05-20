`timescale 1ns / 1ps

module btn_debounce(
    input clk,
    input btn,
	 input rtg_btn,
    output btn_output_state
    );
	 
// 3 �llapotot fogunk m�rni
reg [2:0] btn_states = 3'b000;

always @ (posedge clk) begin
	// balra shift regiszter
	if (rtg_btn)
		btn_states <= {btn_states[1], btn_states[0], btn};
end

// szab�lyos output: 110, azaz 2x akt�v �s v�g�l passz�v
// magyarul el is engedte az illet� a gombot
// ez az�rt j� mert �gy nem akad �ssze a start/stop
assign btn_output_state = (btn_states == 3'b110);

endmodule
