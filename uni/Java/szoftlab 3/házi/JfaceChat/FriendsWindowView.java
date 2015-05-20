package hazi;

import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;

public class FriendsWindowView extends javax.swing.JPanel {

	private static final long serialVersionUID = 1L;

	FriendsWindowView(ChatFriendEntry friend, FacebookChat ref, ChatUserEntry user) {
        
        this.ref=ref;
        this.cFriendEntry=friend;
        this.uEntry=user;
        initComponents(friend);
        setVisible(true);
        addMouseListener(new DoubleClickListener());
    }

    private void initComponents(ChatFriendEntry friend) {

        lName = new javax.swing.JLabel();
        iPanel = new ImagePanel(friend.avatar);        

        setBackground(new java.awt.Color(255, 255, 255));
        setToolTipText(friend.userStatMesg);        

        lName.setFont(new java.awt.Font("Tahoma", 1, 12));
        lName.setHorizontalAlignment(javax.swing.SwingConstants.CENTER);
        lName.setText(friend.rEntry.getName());

        iPanel.setBackground(new java.awt.Color(255, 255, 255));
        iPanel.setMaximumSize(new java.awt.Dimension(40, 40));
        iPanel.setMinimumSize(new java.awt.Dimension(40, 40));
        iPanel.setPreferredSize(new java.awt.Dimension(40, 40));

        javax.swing.GroupLayout iPanelLayout = new javax.swing.GroupLayout(iPanel);
        iPanel.setLayout(iPanelLayout);
        iPanelLayout.setHorizontalGroup(
            iPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 40, Short.MAX_VALUE)
        );
        iPanelLayout.setVerticalGroup(
            iPanelLayout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGap(0, 40, Short.MAX_VALUE)
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addComponent(iPanel, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(lName, javax.swing.GroupLayout.DEFAULT_SIZE, 150, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addComponent(lName, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
            .addComponent(iPanel, javax.swing.GroupLayout.Alignment.TRAILING, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
        );
    }
    
    private ImagePanel iPanel;
    private javax.swing.JLabel lName;
    private FacebookChat ref;
    private ChatFriendEntry cFriendEntry;
    private ChatUserEntry uEntry;
    
    private class DoubleClickListener extends MouseAdapter
    {

        @Override
        public void mouseClicked(MouseEvent e) {
            
            if(e.getClickCount()==2)
            {
                if(ref.chatWindows.containsKey(ref.getPosJabberId(cFriendEntry.rEntry.getUser())) )
                {
                    ChatWindow cMFrame=(ChatWindow)ref.chatWindows.get(ref.getPosJabberId(cFriendEntry.rEntry.getUser()));
                    cMFrame.setLocationRelativeTo(ref.cFrame);
                    cMFrame.repaint();                    
                    cMFrame.setVisible(true);
                }
                else
                {
                    ChatWindow cMFrame=new ChatWindow(cFriendEntry, uEntry, ref);
                    cMFrame.setLocationRelativeTo(ref.cFrame);                    
                    cMFrame.repaint();
                    cMFrame.setVisible(true);
                    
                    ref.chatWindows.put(ref.getPosJabberId(cFriendEntry.rEntry.getUser()), cMFrame);
                }
                
            }
            
        }
        
    }
    
}
