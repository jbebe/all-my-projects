package hazi;

//import org.apache.commons.collections.BidiMap;
import org.apache.commons.collections4.BidiMap;
import org.apache.commons.collections4.bidimap.DualHashBidiMap;

public class FriendsWindowController extends javax.swing.JPanel {

	private static final long serialVersionUID = 1L;
	BidiMap<Long, FriendsWindowView> components = new DualHashBidiMap<Long, FriendsWindowView>();
    
    public FriendsWindowController() {
        
        initComponents();
    }

    private void initComponents() {

        setBackground(new java.awt.Color(255, 255, 255));
        setLayout(new javax.swing.BoxLayout(this, javax.swing.BoxLayout.Y_AXIS));
        setVisible(false);
    }

    public void addComp(long jid, FriendsWindowView fPanel)
    {
        add(fPanel); 
        components.put(jid, fPanel);
    }    
    
    public void removeComp(long jid)
    {
        this.remove((FriendsWindowView)components.get(jid));
        components.remove(jid);
    }
    
}
