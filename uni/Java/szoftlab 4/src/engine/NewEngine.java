package engine;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Random;

public class NewEngine {
    // ezek csak azért kellenek mert még nem tudjuk milyen értékek lesznek
    public static int DIRECTIONS = 4, FIELD_WIDTH = 0, FIELD_HEIGHT = 0, ROBOTSTORES = 2;
    public static int UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;

    // jelen helyzetben egy ArrayList elég absztrakt, hogy eltároljunk valamit
    private ArrayList<ArrayList<Field>> fields;
    private ArrayList<Robot> robots;
    private ArrayList<AIRobot> airobots;
    
    public NewEngine() throws Exception {
        robots = new ArrayList<Robot>();
        fields = new ArrayList<ArrayList<Field>>();
        airobots = new ArrayList<AIRobot>();
        
        String filename = "map.txt";

        BufferedReader buffer = new BufferedReader(
                new InputStreamReader(
                        new FileInputStream(
                                new File(filename)), Charset.defaultCharset()));

        for (int r, w = 0, h = 0; (r = buffer.read()) != -1;) {
            char ch = (char) r;
            if (ch == '\n') {
                h++;
                if (FIELD_HEIGHT < h) {
                    FIELD_HEIGHT = h;
                }
                if (FIELD_WIDTH < w) {
                    FIELD_WIDTH = w;
                }
                w = 0;
            } else {
                if (w == 0) {
                    fields.add(new ArrayList<Field>());
                }
                switch (ch) {
                    case '.':
                        fields.get(h).add(null);
                        break;
                    case '#':
                        fields.get(h).add(new Field(null, null));
                        break;
                    case 'C':
                        fields.get(h).add(new Checkpoint(null, null, generateUniqueID()));
                        break;
                    default:
                        break;
                }
                w++;
            }
        }
        buffer.close();

        System.out.println("width: " + FIELD_WIDTH);
        System.out.println("height: " + FIELD_HEIGHT);

        for (int h = 0; h < FIELD_HEIGHT; h++) {
            for (int w = 0; w < FIELD_WIDTH; w++) {
                if (fields.get(h).get(w) != null) {
                    fields.get(h).get(w).setNeighbor(h != 0 ? fields.get(h - 1).get(w) : null, UP);
                    fields.get(h).get(w).setNeighbor(w != 0 ? fields.get(h).get(w - 1) : null, LEFT);
                    fields.get(h).get(w).setNeighbor(h != FIELD_HEIGHT - 1 ? fields.get(h + 1).get(w) : null, DOWN);
                    fields.get(h).get(w).setNeighbor(w != FIELD_WIDTH - 1 ? fields.get(h).get(w + 1) : null, RIGHT);
                }
            }
        }
    }
    
    public void init(int numPlayers) {
        int sticyStore = 3;
        int oilStore = 3;
        
        for(int i = 0; i < numPlayers; i++) {
            robots.add(new Robot(sticyStore, oilStore, generateUniqueID(), null));
        }
        
        // összes létező field
        ArrayList<Field> temp = new ArrayList<Field>();
        for(int y = 0; y < fields.size(); y++) {
            ArrayList<Field> yy = fields.get(y);
            for(int x = 0; x < yy.size(); x++) {
                Field xx = yy.get(x);
                if(xx.getRobot() == null || xx.getID() == 0) {
                    temp.add(xx);
                }
            }
        }
        
        Random r = new Random();
        
        // robotok lerakása
        for(int i = 0; i < robots.size(); i++) {
            int random = r.nextInt(temp.size());
            temp.get(random).setRobot(robots.get(i));
            robots.get(i).setField(temp.get(random));
            temp.remove(random);
        }
        
        // akadályok lerakása
        int numOil = 2;
        int numSticky = 2;
        for(int i = 0; i < numOil; i++) {
            int random = r.nextInt(temp.size());
            Oil o = new Oil();
            temp.get(random).setObstacle(o);
            temp.remove(random);
        }
        for(int i = 0; i < numSticky; i++) {
            int random = r.nextInt(temp.size());
            Sticky s = new Sticky();
            temp.get(random).setObstacle(s);
            temp.remove(random);
        }
    }
    
    private static int robotIDCounter = 1;
    private static int generateUniqueID() {
        robotIDCounter++;
        System.out.println("Next UID: " + robotIDCounter);
        return robotIDCounter;
    }
}
