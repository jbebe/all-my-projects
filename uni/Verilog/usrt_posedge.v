`timescale 1ns / 1ps

module usrt_posedge(
	input clk,
	input usrt_clk,
	output usrt_pedge
	);

reg [1:0] edge_state;

always @ (posedge clk)
begin
	edge_state <= {edge_state[0], usrt_clk};
end

assign usrt_pedge = (edge_state == 2'b01);

endmodule
