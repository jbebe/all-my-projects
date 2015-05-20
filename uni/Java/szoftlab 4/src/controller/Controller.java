package controller;


import engine.AIRobot;
import engine.Checkpoint;
import engine.Field;
import engine.Oil;
import engine.Robot;
import engine.Sticky;
import gui.*;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.Random;

public class Controller {
    private static Controller instance;
    private final StartForm view = new StartForm();

    private int numOfPlayers = 0;
    public int activeRobot = 0;

    public static int DIRECTIONS = 4, FIELD_WIDTH = 0, FIELD_HEIGHT = 0, ROBOTSTORES = 2;
    public static int UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;

    public ArrayList<ArrayList<Field>> fields = new ArrayList<ArrayList<Field>>();
    public ArrayList<Robot> robots = new ArrayList<Robot>();
    public ArrayList<AIRobot> airobots = new ArrayList<AIRobot>();
    
    public Controller() {}
    
    private static int robotIDCounter = 1;
    private static int generateUniqueID() {
        robotIDCounter++;
        // System.out.println("Next UID: " + robotIDCounter);
        return robotIDCounter;
    }

    private int getPlaying() {
        int playing = 0;
        for(int i = 0; i < robots.size(); i++) {
            if(robots.get(i).getPlayingState())
                playing++;
        }
        return playing;
    }
    
    public void setNumOfPlayers(int num) throws Throwable {
        if(num < 1 || num > 5)
            throw new Exception();
        this.numOfPlayers = num;
    }

    public static Controller getInstance() throws Throwable {
        if(instance == null)
            instance = new Controller();
        return instance;
    }

    public void loadMainMenu() {
        view.setActive("StartPanel");
        view.setVisible(true);
    };

    public void loadMap() throws Throwable {
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

        // System.out.println("width: " + FIELD_WIDTH);
        // System.out.println("height: " + FIELD_HEIGHT);

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

    public void initMap() {
        int sticyStore = 3;
        int oilStore = 3;
        
        
        for(int i = 0; i < numOfPlayers; i++) {
            robots.add(new Robot(sticyStore, oilStore, generateUniqueID(), null));
        }
        
        // összes létező field
        ArrayList<Field> temp = new ArrayList<Field>();
        for(int y = 0; y < fields.size(); y++) {
            ArrayList<Field> yy = fields.get(y);
            for(int x = 0; x < yy.size(); x++) {
                Field xx = yy.get(x);
                if(xx != null && xx.getRobot() == null && xx.getID() == 0) {
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
    
    public void play() {
        try {
            loadMap();
            initMap();
            view.updateGamePanel(robots.get(activeRobot));
            view.setActive("GamePanel");
            view.setVisible(true);
        } catch(Throwable t) {
            t.printStackTrace();
        }
    }
    
    public void step(int modSpeed, int modDir, String deployable) throws Throwable {
        
        boolean dropOil = deployable.compareTo("olajfolt") == 0;
        boolean dropSticky = deployable.compareTo("ragacsfolt") == 0;
        
        if (robots.get(activeRobot).move(modSpeed, modDir, dropSticky, dropOil, false, airobots) == false) {
            System.out.println("[Info] Bad input. Try again.");
            return;
        }
        robots.get(activeRobot).move(modSpeed, modDir, dropSticky, dropOil, true, airobots);
        
        if(getPlaying() > 1) {
            view.updateGamePanel(robots.get(activeRobot));
            
            activeRobot = (activeRobot + 1) % robots.size();
            while (robots.get(activeRobot).getPlayingState() == false)
                activeRobot = (activeRobot + 1) % robots.size();
        }
        else {
            showScores();
        }
        
        ArrayList<Field> temp = new ArrayList<Field>();
        for(int y = 0; y < fields.size(); y++) {
            ArrayList<Field> yy = fields.get(y);
            for(int x = 0; x < yy.size(); x++) {
                Field xx = yy.get(x);
                if(xx != null && xx.getRobot() == null && xx.getID() == 0) {
                    temp.add(xx);
                }
            }
        }
        if(activeRobot == 0){
            int rand = (int) (temp.size() * Math.random());
            airobots.add(new AIRobot(temp.get(rand), 2));
            
            for (int i = 0; i < airobots.size(); ) {
                if (airobots.get(i).life == 0){
                    airobots.remove(i);
                }
                else {
                    airobots.get(i).move(fields);
                    i++;
                }
            }
        }
    }
    
    public void showScores() {
        view.setActive("ScorePanel");
        view.setVisible(true);
        for (Robot robot : robots) {
            view.insertScore(new Data(robot.getCheckpoint(), robot.getID()));
        }
    }

    public static void main(String args[]) throws Throwable { 
        Controller app = Controller.getInstance();
        app.loadMainMenu();
    }
}
