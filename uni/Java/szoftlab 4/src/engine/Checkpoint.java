package engine;

public class Checkpoint extends Field {
	
	private final int ID;

	public Checkpoint(Obstacle initObstacle, Robot initRobot, int ID){
		super(initObstacle, initRobot);
		this.ID = ID;
	}

	public String getType(){
		return "Checkpoint";
	}

	public int getID(){
		return ID;
	}

}