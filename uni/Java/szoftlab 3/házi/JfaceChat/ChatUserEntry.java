package hazi;

import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import javax.imageio.ImageIO;

class ChatUserEntry {
    
    String name;
    String userStatMesg;
    BufferedImage avatar;
    
    private BufferedImage getScaledImage(Image srcImg, int w, int h)
    {
        BufferedImage resizedImg = new BufferedImage(w, h, BufferedImage.TRANSLUCENT);
        
        Graphics2D g2 = resizedImg.createGraphics();
        g2.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
        
        g2.drawImage(srcImg, 0, 0, w, h, null);
        g2.dispose();
        
        return resizedImg;
    }    

    ChatUserEntry(String fName, String status, byte[] bytes)
    {
        
        name=fName;
        userStatMesg=status;
        
        try
        {            
            if(bytes!=null)
                avatar = getScaledImage((BufferedImage)ImageIO.read(new ByteArrayInputStream(bytes)),40, 40);                                
            else
                avatar=null;
        }
        catch(Exception e)
        {
            avatar=null;
        }
        
    }
    
}
