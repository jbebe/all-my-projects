package engine;

public class Oil extends Obstacle {
	public DirectionVector affectDirectionVector(DirectionVector newDV, DirectionVector oldDV){
		return new DirectionVector(oldDV);
	}
}