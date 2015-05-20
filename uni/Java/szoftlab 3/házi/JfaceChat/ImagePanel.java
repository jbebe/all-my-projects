package hazi;

import java.awt.Graphics;
import java.awt.image.BufferedImage;
import javax.swing.JPanel;

class ImagePanel extends JPanel{

	private static final long serialVersionUID = 1L;
	BufferedImage img;
    
    ImagePanel(BufferedImage img)
    {
        this.img=img;
    }

    @Override
    protected void paintComponent(Graphics g) {
        
        super.paintComponent(g);
        g.drawImage(img, 0, 0, null);        
    }
    
}
