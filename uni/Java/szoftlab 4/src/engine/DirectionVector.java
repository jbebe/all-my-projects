package engine;

public class DirectionVector {

	public int velocity;
	public int direction;
	
	public DirectionVector(int velocity, int direction){
		this.velocity = velocity;
		this.direction = direction;
	}
	
	public DirectionVector(DirectionVector dv){
		this.velocity = dv.velocity;
		this.direction = dv.direction;
	}
}