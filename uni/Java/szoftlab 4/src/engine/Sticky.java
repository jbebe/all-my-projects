package engine;

public class Sticky extends Obstacle {
	public DirectionVector affectDirectionVector(DirectionVector newDV, DirectionVector oldDV){
		return new DirectionVector(newDV.velocity/2, newDV.direction);
	}
}