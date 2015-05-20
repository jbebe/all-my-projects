package hazi;

import java.util.Collection;
import org.jivesoftware.smack.Roster;
import org.jivesoftware.smack.RosterListener;
import org.jivesoftware.smack.packet.Presence;

public class FacebookPresenceHandler implements RosterListener
{
    FacebookChat fbChat;
    Roster roster;
    
    FacebookPresenceHandler(FacebookChat ref, Roster roster)
    {
        fbChat=ref;
        this.roster=roster;
    }
    
    @Override
    public void entriesAdded(Collection<String> addresses) {}
    
    @Override
    public void entriesDeleted(Collection<String> addresses) {}
    
    @Override
    public void entriesUpdated(Collection<String> addresses) {}
    
    @Override
    public void presenceChanged(Presence presence) {
        
        long jid=fbChat.getPosJabberId(presence.getFrom());        
        
        if(fbChat.friends.containsKey(jid))
        {
            if(!presence.isAvailable())
            {
                fbChat.friends.remove(jid);
                
                if(fbChat.chatWindows.containsKey(jid))
                {
                    ((ChatWindow)fbChat.chatWindows.get(jid)).dispose();
                    fbChat.chatWindows.remove(jid);
                }
                
                fbChat.fPanel.removeComp(jid);
                fbChat.cFrame.setVisible(false);
                fbChat.cFrame.repaint();
                fbChat.cFrame.setVisible(true);                
            }
        }
        else
        {
            if(presence.isAvailable())
            {                
                fbChat.friends.put(jid, new ChatFriendEntry(roster.getEntry(presence.getFrom()), presence.getStatus(), fbChat.getAvatar(presence.getFrom())) );                
                
                fbChat.fPanel.addComp(jid, new FriendsWindowView((ChatFriendEntry)fbChat.friends.get(jid), fbChat, fbChat.user));                
                fbChat.cFrame.setVisible(false);
                fbChat.cFrame.repaint();
                fbChat.cFrame.setVisible(true);
            }
            
        }
        
    }
    
}
