/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package engine;

import java.util.ArrayList;

/**
 *
 * @author borgee
 */
public class AIRobot {

    private Field field;
    public int life;

    private class Coord {

        public int x, y;

        public Coord(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    private class RelCoord extends Coord {

        public RelCoord(int x, int y) {
            super(x, y);
        }
    }

    private Coord getCoord(ArrayList<ArrayList<Field>> fields) {
        for (int i = 0; i < fields.size(); i++) {
            for (int j = 0; j < fields.get(i).size(); j++) {
                if (this.field == fields.get(i).get(j)) {
                    return new Coord(j, i);
                }
            }
        }
        return null;
    }

    private double distance(Coord a, Coord b) {
        return Math.sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
    }

    private RelCoord search(ArrayList<ArrayList<Field>> fields) {
        ArrayList<Coord> obstacles = new ArrayList<Coord>();
        Coord myCoord = getCoord(fields);
        for (int i = 0; i < fields.size(); i++) {
            for (int j = 0; j < fields.get(i).size(); j++) {
                if ((fields.get(i).get(j) != null) && (fields.get(i).get(j).getObstacle() != null)) {
                    obstacles.add(new Coord(j, i));
                }
            }
        }
        int minIndex = 0;
        for (int i = 0; i < obstacles.size(); i++) {
            if (distance(myCoord, obstacles.get(i)) < distance(myCoord, obstacles.get(minIndex))) {
                minIndex = i;
            }
        }
        if (!obstacles.isEmpty()) {
            Coord moveTo = obstacles.get(minIndex);
            return new RelCoord(moveTo.x - myCoord.x, moveTo.y - myCoord.y);
        } else {
            return null;
        }
    }

    public boolean move(ArrayList<ArrayList<Field>> fields) {
        life--;
        if (life <= 0) {
            this.field.removeAIRobot();
            field = null;
            return true;
        }
        RelCoord c = search(fields);
        if (c == null) return false;

        int dir;
        if (Math.abs(c.x) > Math.abs(c.y)) {
            if (Math.signum(c.x) == 1) {
                dir = 1;
            } else {
                dir = 3;
            }
        } else if (Math.signum(c.y) == 1) {
            dir = 2;
        } else {
            dir = 0;
        }
        Field tempField = field.getNeighbor(dir);
        if (tempField != null) {
            if (tempField.getAIRobot() == null) {
                System.out.println("valid lepes");
                field.removeAIRobot();
                field = tempField;
                tempField.setAIRobot(this);
                tempField.removeObstacle();
            } else {
                System.out.println("utkozott");
                tempField = field.getNeighbor((dir + 2) % 4);
                field.removeAIRobot();
                field = tempField;
                tempField.setAIRobot(this);
            }
        } else {
            System.out.println("nullra lepett");
            field.removeAIRobot();
            field = null;
            return true;
        }
        return false;
    }

    public AIRobot(Field initialField, int life) {
        field = initialField;
        this.life = life;
    }
}
