package engine;

import java.util.ArrayList;

public class Field {

	private ArrayList<Field> neighbors;
	private Obstacle obstacle;
	private Robot robot;
        private AIRobot airobot;

	public Field(Obstacle initObstacle, Robot initRobot){
		neighbors = new ArrayList<Field>();
		neighbors.add(null);neighbors.add(null);neighbors.add(null);neighbors.add(null);
		obstacle = initObstacle;
		robot = initRobot;
	}

	public String getType(){
		return "Field";
	}
        
       public boolean setAIRobot(AIRobot aiRobotRef){
		if (robot == null){
			airobot = aiRobotRef;
			return true;
		}
		else {
			return false;
		}
	}
       
        public AIRobot getAIRobot(){
            return airobot;
        }
        
        public void removeAIRobot(){
            airobot = null;
        }

	public boolean setRobot(Robot robotRef){
		if (robot == null){
			robot = robotRef;
			return true;
		}
		else {
			return false;
		}
	}

	public boolean setObstacle(Obstacle obstacleRef){
		if (obstacle == null){
			obstacle = obstacleRef;
			return true;
		}
		else {
			return false;
		}
	}

	public Robot getRobot(){
		return robot;
	}

	public Obstacle getObstacle(){
		return obstacle;
	}

	public int getID(){
		return 0;
	}

	public void removeObstacle(){
		this.obstacle = null;
	}

	public void setNeighbor(Field newNeighbor, int direction){
		neighbors.set(direction, newNeighbor);
	}
	
	public Field getNeighbor(int direction){
		return neighbors.get(direction);
	}

	public boolean removeRobot(int ID){
		if (robot.getID() == ID){
			robot = null;
			return true;
		}
		else {
			return false;
		}
	}

}