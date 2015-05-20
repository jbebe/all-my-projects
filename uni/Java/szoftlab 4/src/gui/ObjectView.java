package gui;

import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;

public class ObjectView {

    protected final String imageUrl;
    protected final int x;
    protected final int y;
    protected final int size;

    public ObjectView(String url, int x, int y, int blockSize) {
        this.imageUrl = url;
        this.x = x;
        this.y = y;
        this.size = blockSize;
    }

    protected BufferedImage loadImage(String name) throws Throwable {
        String imgFileName = "rsrc/" + name;
        File f = new File(imgFileName);
        return (BufferedImage)(ImageIO.read(f));
    }

    public void draw(Graphics g) throws Throwable {
        Graphics2D g2D = (Graphics2D)g;
        BufferedImage img = loadImage(imageUrl);
        g2D.drawImage(img,
                x, y, x+size, y+size,
                0, 0, size*2, size*2,
                null);
    }
}
