package engine;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStreamReader;
import java.nio.charset.Charset;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Engine {

    public static class GameException extends Exception {

        private static final long serialVersionUID = 1L;

        public GameException(String message) {
            super(message);
        }
    }
    // ezek csak azért kellenek mert még nem tudjuk milyen értékek lesznek
    public static int DIRECTIONS = 4, FIELD_WIDTH = 0, FIELD_HEIGHT = 0, ROBOTSTORES = 2;
    public static int UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;

    // jelen helyzetben egy ArrayList elég absztrakt, hogy eltároljunk valamit
    private ArrayList<ArrayList<Field>> fields;
    private ArrayList<Robot> robots;
    private ArrayList<AIRobot> airobots;
    //private int time;
    //private UserInterface ui;

    public Engine(int numOfPlayers) throws Exception {

        //ui = new UserInterface();
        robots = new ArrayList<Robot>(numOfPlayers);
        fields = new ArrayList<ArrayList<Field>>();
        airobots = new ArrayList<AIRobot>();

        // bekérjük a pálya nevét fájlból
        String filename = "map.txt";//_protoCommand("init_map <filename>", 1).get(0);

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

        //ui.drawBoard(fields, -1);

        for (int i = 0; i < numOfPlayers; i++) {
            System.out.println("Robot #" + i);
            ArrayList<String> xy = _protoCommand("init_robot <x coord> <y coord>", 2);
            int x = Integer.parseInt(xy.get(0));
            int y = Integer.parseInt(xy.get(1));
            Field fieldRef = fields.get(y).get(x);
            Robot robotObj = new Robot(ROBOTSTORES, ROBOTSTORES, generateUniqueID(), fieldRef);
            fieldRef.setRobot(robotObj);
            robots.add(robotObj);

            //ui.drawBoard(fields, -1);
        }

        System.out.println("Type [add_obstacle exit 0 0] to finish placing obstacles");
        while (true) {
            ArrayList<String> cmds = _protoCommand("add_obstacle <sticky/oil/exit> <x> <y>", 3);
            String obstacleType = cmds.get(0);
            if (obstacleType.compareTo("exit") == 0) {
                break;
            }
            int x = Integer.parseInt(cmds.get(1));
            int y = Integer.parseInt(cmds.get(2));
            Obstacle o;
            if (obstacleType.compareTo("sticky") == 0) {
                o = new Sticky();
            } else {
                o = new Oil();
            }
            if (fields.get(y).get(x) != null) {
                fields.get(y).get(x).setObstacle(o);
            }

           // ui.drawBoard(fields, -1);
        }
    }

    public void run() throws Throwable {
        int playerIterator = 0;
        ArrayList<String> cmds;

        GAME_LOOP_ENTRY:
        while (true) {
            System.out.println("If you want to quit, do it now.");
            cmds = _protoCommand("exit <true/false>", 1);
            if (cmds.get(0).compareTo("true") == 0) {
                break GAME_LOOP_ENTRY;
            }

            if (robots.get(playerIterator).getPlayingState() == false) {
                boolean allDead = true;
                for (int i = 0; i < robots.size(); i++) {
                    if (robots.get(i).getPlayingState() == true) {
                        allDead = false;
                    }
                }
                if (allDead) {
                    break GAME_LOOP_ENTRY;
                } else {
                    System.out.println("[Info] Skipping Robot with ID " + robots.get(playerIterator).getID() + " because It's dead");
                    playerIterator = (playerIterator + 1) % robots.size();
                    continue GAME_LOOP_ENTRY;
                }
            }

            //ui.drawBoard(fields, robots.get(playerIterator).getID());

            System.out.println("exit AIRobot placing with [add_airobot exit 0]");
            while (true) {
                cmds = _protoCommand("add_airobot <x> <y>", 2);
                if (cmds.get(0).compareTo("exit") == 0) {
                    break;
                }
                int x = Integer.parseInt(cmds.get(0));
                int y = Integer.parseInt(cmds.get(1));
                Field fieldRef = fields.get(y).get(x);
                if (fieldRef != null) {
                    AIRobot newRobot = new AIRobot(fieldRef, 4);
                    airobots.add(newRobot);
                    fieldRef.setAIRobot(newRobot);
                }
                //ui.drawBoard(fields, -1);
            }

            _protoCommand("move_airobot", 0);
            for (int i = 0; i < airobots.size(); i++) {
                if (airobots.get(0).move(fields)) {
                    airobots.remove(i--);
                }
            }
            //ui.drawBoard(fields, -1);

            System.out.println("Robots:");
            for(int i = 0; i < robots.size(); i++) {
                System.out.println(robots.get(i).getID() + " velocity: " + robots.get(i).getVelocity() + " direction: " + robots.get(i).getDirection());
            }
            cmds = _protoCommand("deploy_obstacle <RobotID> <Oil/Sticky/No>", 2);
            int robotID = Integer.parseInt(cmds.get(0));
            Robot robot = null;
            for(int i = 0; i < robots.size(); i++) {
                if(robots.get(i).getID() == robotID) {
                    robot = robots.get(i);
                    break;
                }
            }
            boolean placeSticky = "Sticky".compareTo(cmds.get(1)) == 0;
            boolean placeOil = "Oil".compareTo(cmds.get(1)) == 0;
            //ui.drawBoard(fields, robotID);

            cmds = _protoCommand("mod_vector <velocity> <direction>", 2);
            //robotID = Integer.parseInt(cmds.get(0));
            int velocityDiff = Integer.parseInt(cmds.get(0));
            int direction = Integer.parseInt(cmds.get(1));
            //ui.drawBoard(fields, robotID);

            while (robot.move(velocityDiff, direction, placeSticky, placeOil, false, airobots) == false) {
                System.out.println("[Info] Bad input. Try again.");
                continue GAME_LOOP_ENTRY;
            }

            robot.move(velocityDiff, direction, placeSticky, placeOil, true, airobots);
            if (robot.getPlayingState() == false) {
                System.out.println("[Info] Game Over for Robot ID" + robot.getID());
            }

        }

        // ha lejár az idő kiírjuk kivel mi van:
        for (int i = 0; i < robots.size(); i++) {
            Robot robotRef = robots.get(i);
            System.out.println(
                    "[Scoreboard] ID: " + robotRef.getID()
                    + ", Score: " + robotRef.getCheckpoint()
                    + ", Status: " + (robotRef.getPlayingState() ? "alive" : "dead")
            );
        }

    }

    private static int robotIDCounter = 1;

    private static int generateUniqueID() {
        robotIDCounter++;
        System.out.println("Next UID: " + robotIDCounter);
        return robotIDCounter;
    }
    /*
    public static void main(String[] args) throws Throwable {
        int numOfPlayers = -1;
        // bekérjük a játékosok számát
        numOfPlayers = Integer.parseInt(_protoCommand("set_players <num>", 1).get(0));
        System.out.printf("Initializing game with %d player(s)...\n", numOfPlayers);
        Engine e = new Engine(numOfPlayers);
        e.run();
        System.out.println("Exiting...");
    }
    */
    private static ArrayList<String> _protoCommand(String rawCommandName, int numOfArgs) throws Exception {
        String commandName = rawCommandName.split(" ")[0];
        BufferedReader cmdInput = new BufferedReader(new InputStreamReader(System.in));
        StringBuffer builtPattern = new StringBuffer(commandName);
        StringBuffer helpPattern = new StringBuffer(commandName);
        ArrayList<String> argsList = new ArrayList<String>(numOfArgs);

        // pattern felépítése az adat bekéréséhez, hibás típus nincs kezelve
        for (int i = 0; i < numOfArgs; i++) {
            builtPattern.append(" ([\\w\\.]+)");
            helpPattern.append(" <arg>");
        }
        Pattern pattern = Pattern.compile(builtPattern.toString());

        // mégmielőtt bekérjük, megmutatjuk, hogy kéne
        _listOptions(rawCommandName);

        GET_VALID_INPUT:
        while (true) {
            // bekérjük a szöveget
            System.out.printf("%s@game:~$ ", System.getProperty("user.name"));
            String input = cmdInput.readLine();
            if (input == null) {
                System.out.printf("Correct syntax: %s\n", helpPattern);
                continue;
            }
            // rá match-elünk
            Matcher matches = pattern.matcher(input);
            if (!matches.find()) {
                System.out.printf("Correct syntax: %s\n", helpPattern);
                continue;
            }
            // lekérdezzük az összes számot
            for (int i = 0; i < numOfArgs; i++) {
                argsList.add(matches.group(1 + i));
            }
            break GET_VALID_INPUT;
        }
        return argsList;
    }

    private static void _listOptions(String options) {
        String list[] = options.split("\\|");
        System.out.println("Your options:");
        for (int i = 0; i < list.length; i++) {
            System.out.printf("- %s\n", list[i]);
        }
    }
}
