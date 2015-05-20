package hazi;

import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import java.awt.image.BufferedImage;
import java.io.ByteArrayInputStream;
import javax.imageio.ImageIO;
import org.jivesoftware.smack.RosterEntry;

class ChatFriendEntry {
    
    RosterEntry rEntry;
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

    ChatFriendEntry(RosterEntry entry, String status, byte[] bytes)
    {
        
        rEntry=entry;
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
