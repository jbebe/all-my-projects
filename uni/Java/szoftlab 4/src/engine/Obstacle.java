package engine;

public abstract class Obstacle {
        public int life;
	public abstract DirectionVector affectDirectionVector(DirectionVector newDV, DirectionVector oldDV);
}