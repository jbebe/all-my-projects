package gui;

import controller.Controller;
import java.awt.BasicStroke;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;

public class MyGameCanvas extends Canvas {
    @Override
    public void paint(Graphics g) {
        super.paint(g);
        Graphics2D g2;
        g2 = (Graphics2D) g;
        try {
            Controller ctrlInst = Controller.getInstance();
            int blockWidth = this.getWidth() / ctrlInst.fields.get(0).size();
            int blockHeight = this.getHeight() / ctrlInst.fields.size();
            
            for (int h = 0; h < ctrlInst.fields.size(); h++) {
                for (int w = 0; w < ctrlInst.fields.get(0).size(); w++) {
                    int h_screen = h * blockHeight;
                    int w_screen = w * blockWidth;
                    
                    g2.setColor(Color.BLACK);
                    g2.setStroke(new BasicStroke(1));
                    g2.drawRect(w_screen, h_screen, blockWidth, blockHeight);
                    
                    if (ctrlInst.fields.get(h).get(w) == null){
                        g2.setColor(Color.BLACK);
                        g2.fillRect(w_screen, h_screen, blockWidth, blockHeight);
                        continue;
                    }
                    if (ctrlInst.fields.get(h).get(w).getObstacle() != null){
                        boolean isSticky = ctrlInst.fields.get(h).get(w).getObstacle().getClass().getSimpleName().compareTo("Sticky") == 0;
                        if (isSticky){
                            new ObjectView("sticky.png", w_screen + blockWidth/4, h_screen, blockWidth/4).draw(g2);
                        }
                        else {
                            new ObjectView("oil.png", w_screen + blockWidth/4, h_screen, blockWidth/4).draw(g2);
                        }
                    }
                    if (ctrlInst.fields.get(h).get(w).getRobot() != null){
                        new ObjectView("robot.png", w_screen, h_screen, blockWidth/4).draw(g2);
                        if (ctrlInst.fields.get(h).get(w).getRobot() == ctrlInst.robots.get(ctrlInst.activeRobot)){
                            g2.setStroke(new BasicStroke(3));
                            g2.setColor(Color.RED);
                            g2.drawRect(w_screen-3, h_screen-3, blockWidth/4 + 6, blockWidth/4 + 6);
                            
                            g.setFont(new Font("Arial", Font.PLAIN, 15)); 
                            char idArr[] = String.format("ID: %d", ctrlInst.robots.get(ctrlInst.activeRobot).getID()).toCharArray();
                            g2.drawChars(idArr, 0, idArr.length, w_screen-10, h_screen-8);
                        }
                    }
                    if (ctrlInst.fields.get(h).get(w).getAIRobot() != null){
                        new ObjectView("airobot.png", w_screen, h_screen + blockWidth/4, blockWidth/4).draw(g2);
                    }
                    if (ctrlInst.fields.get(h).get(w).getID() != 0){
                        new ObjectView("checkpoint.png", w_screen + blockWidth/4, h_screen + blockWidth/4, blockWidth/4).draw(g2);
                    }
                }
            }
        } catch (Throwable t) {
            t.printStackTrace();
        }
    }
}