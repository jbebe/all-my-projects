package engine;

import controller.Controller;
import java.util.ArrayList;
import java.util.Stack;

public class Robot {

    private Stack<Sticky> stickyStore;
    private Stack<Oil> oilStore;
    private DirectionVector directionVector;
    private int lastCheckpointID;
    private int ID;
    private Field field;
    public boolean isPlaying;

    public Robot(int stickyStoreSize, int oilStoreSize, int ID, Field startField) {
        stickyStore = new Stack<Sticky>();
        for (int i = 0; i < stickyStoreSize; i++) {
            stickyStore.push(new Sticky());
        }
        oilStore = new Stack<Oil>();
        for (int i = 0; i < oilStoreSize; i++) {
            oilStore.push(new Oil());
        }
        this.ID = ID;
        field = startField;

        isPlaying = true;
        lastCheckpointID = 0;

        directionVector = new DirectionVector(0, 0);
    }

    public int getVelocity() {
        return directionVector.velocity;
    }

    public int getDirection() {
        return directionVector.direction;
    }

    public void setVelocity(int velocity) {
        directionVector.velocity = velocity;
    }

    public boolean move(int velocityDiff, int direction, boolean deploySticky, boolean deployOil, boolean isLive, ArrayList<AIRobot> airobots) throws Exception {
        // alapvető hibák:
        if (deploySticky && deployOil) {
            System.out.println("[Info] Cannot place two Obstacle!");
            return false; // nem lehet lerakni két szart egyszerre
        }
        if (velocityDiff < -1 || velocityDiff > 1) {
            System.out.println("[Info] Velocity must be between -1 and 1!");
            return false;
        }
        if (direction < 0 || direction > (Controller.DIRECTIONS - 1)) {
            System.out.println("[Info] Direction must be between 0 and " + (Controller.DIRECTIONS - 1) + "!");
            return false;
        }

        // Engine nem látja robotot, csak diff-et adott. Így most már newDV rendes velocity-t tárol
        DirectionVector newDV = new DirectionVector(directionVector.velocity + velocityDiff, direction);

        // ha lassítóra lépett mér előzőleg
        if (field.getObstacle() != null && isLive) {
            newDV = field.getObstacle().affectDirectionVector(newDV, directionVector);
        }

        // ha lerak valamit
        if (deploySticky) {
            if (stickyStore.size() > 0) {
                if (field.getObstacle() == null) {
                    if (isLive) {
                        field.setObstacle(stickyStore.pop());
                    }
                } else {
                    System.out.println("[Info] Már le van rakva akadály erre a mezőre!");
                    return false;
                }
            } else {
                System.out.println("[Info] Kifogytál a sticky-ből!");
                return false;
            }
        } else if (deployOil) {
            if (oilStore.size() > 0) {
                if (field.getObstacle() == null) {
                    if (isLive) {
                        field.setObstacle(oilStore.pop());
                    }
                } else {
                    System.out.println("[Info] Már le van rakva akadály erre a mezőre!");
                    return false;
                }
            } else {
                System.out.println("[Info] Kifogytál az oil-ból!");
                return false;
            }
        }

        // lépés kivitelezése
        // 		konkrét lépési művelet
        Field tempField = field;
        for (int i = 0; i < newDV.velocity; i++) {
            tempField = tempField.getNeighbor(newDV.direction);
            if (tempField == null) {
                if (isLive) {
                    isPlaying = false; // Engine innen tudja meg hogy kiestünk
                    field.removeRobot(ID); // eltűntetjük magunkat a régi field-ről
                    field = null;
                }
                return true;
            }
        }
        
        if (isLive){
            // airobot eltakarítása ha a robot lába alatt van
            if (field != null && field.getAIRobot() != null) {
                for (int i = 0; i < airobots.size(); i++) {
                    if (field.getAIRobot().equals(airobots.get(i))) {
                        field.removeAIRobot();
                        airobots.remove(i);
                        System.out.println("[Info] Volt alattunk egy kisrobot!");
                    }
                }
            }
        }

        if (isLive && (tempField.getRobot() != null && tempField.getRobot().getID() != ID)) {
            int newVelocity = (tempField.getRobot().directionVector.velocity + directionVector.velocity) / 2;
            if (directionVector.velocity >= tempField.getRobot().directionVector.velocity) {
                // ha a mi sebességünk nagyobb, az idegen hal meg
                tempField.getRobot().field = null;
                tempField.getRobot().isPlaying = false;
                tempField.removeRobot(tempField.getRobot().getID());

                field.removeRobot(ID);
                field = tempField;
                field.setRobot(this);
                directionVector.velocity = newVelocity;
                System.out.printf("meghalt ID: %d robot\n", ID);
            } else {
                // ha az ő sebessége, mi halunk meg
                tempField.getRobot().directionVector.velocity = newVelocity;
                field.removeRobot(ID);
                field = null;
                isPlaying = false;
                System.out.printf("meghalt ID: %d robot\n", ID);
            }

        }
        else {
            if (isLive){
                // lépés kivitelezése
                field.removeRobot(ID);
                field = tempField;
                field.setRobot(this);
                
                // új sebesség beállítása
                directionVector = newDV;
            }
        }
        
        if (isLive) {
            // checkpoint nézés
            if (field != null && field.getType().compareTo("Checkpoint") == 0) {
                lastCheckpointID = field.getID();
            }
        }

        return true; // Engine megtudja, hogy lehet lépni
    }

    public int getCheckpoint() {
        return lastCheckpointID;
    }

    public boolean getPlayingState() {
        return isPlaying;
    }

    public int getID() {
        return ID;
    }

    public void setField(Field f) {
        field = f;
    }
}
