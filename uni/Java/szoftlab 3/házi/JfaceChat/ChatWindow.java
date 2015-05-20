package hazi;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.util.ArrayList;

import javax.swing.AbstractAction;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.KeyStroke;

public class ChatWindow extends javax.swing.JFrame {

	private static final long serialVersionUID = 1L;
	ChatWindow(ChatFriendEntry friend, ChatUserEntry user, FacebookChat ref) {
        
        this.friend=friend;
        //this.user=user;
        this.ref=ref;
        
        initComponents();
        
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        }
        catch (Exception ex) {
            java.util.logging.Logger.getLogger(ChatWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }         
    }

    @SuppressWarnings("unchecked")
	private void initComponents() {

        fScroll = new javax.swing.JScrollPane();
        //mesgPanel = new hazi.CMessagePanel();
        mesgPanel = new javax.swing.JPanel();
        mesgPanel.setLayout(new BoxLayout(mesgPanel, BoxLayout.PAGE_AXIS));
        mesgPanel.setVisible(true);
        mScroll = new javax.swing.JScrollPane();
        cMesgArea = new javax.swing.JTextArea();
        sendButton = new javax.swing.JButton();

        setTitle(friend.rEntry.getName());
        setBackground(new java.awt.Color(255, 255, 255));        
        setAlwaysOnTop(true);
        setName("mFrame");
        setResizable(false);
        setDefaultCloseOperation(javax.swing.WindowConstants.HIDE_ON_CLOSE); 
        getContentPane().setLayout(new java.awt.FlowLayout());        

        fScroll.setHorizontalScrollBarPolicy(javax.swing.ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);        
        fScroll.setVerticalScrollBarPolicy(javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
        
        fScroll.setViewportView(mesgPanel);
        
        getContentPane().add(fScroll);        

        cMesgArea.setColumns(20);
        cMesgArea.setLineWrap(true);
        cMesgArea.setRows(5);
        mScroll.setViewportView(cMesgArea);

        sendButton.setText("Send");
                
        sendButton.addActionListener(new java.awt.event.ActionListener() {
            @Override
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                sendButtonActionPerformed(evt);
            }
        });
        
        cMesgArea.getActionMap().put(cMesgArea.getInputMap().get(KeyStroke.getKeyStroke("ENTER")), new EnterAction());               
        
        getContentPane().setLayout(new BorderLayout());
        
        fScroll.setPreferredSize(new Dimension(260, 217));
        mScroll.setPreferredSize(new Dimension(166, 96));
        sendButton.setPreferredSize(new Dimension(57, 23));
        getContentPane().add(fScroll, BorderLayout.NORTH);
        getContentPane().add(mScroll, BorderLayout.WEST);
        getContentPane().add(sendButton, BorderLayout.CENTER);

        // serialize
        SJLabels = new ArrayList<JLabel>();
        try
        {
        	String userid = ""+ref.getPosJabberId(friend.rEntry.getUser());
        	File fLog = new File(userid);
			FileInputStream fileIn = new FileInputStream(fLog);
			ObjectInputStream in = new ObjectInputStream(fileIn);
			SJLabels = (ArrayList<JLabel>)in.readObject();
			in.close();
			fileIn.close();
        } catch(Throwable t){}
        for (JLabel lbl : SJLabels){
        	mesgPanel.add(lbl);
        }
        
        pack();          

    }
    
    public void addFriendMessage(String message)
    {
        //mesgPanel.addMessage(message, friend.avatar, friend.rEntry.getName(), true);
    	JLabel lbl = new JLabel(friend.rEntry.getName() + ":\n" + message);
    	lbl.setMaximumSize(new Dimension(230, 500));
        mesgPanel.add(lbl);
        
        // serialize
        saveJLabels(""+ref.getPosJabberId(friend.rEntry.getUser()), lbl);
        repaint();        
    }

    private void sendButtonActionPerformed(java.awt.event.ActionEvent evt)
    {                
        try
        {
            //ref.sendMessage(friend.rEntry, cMesgArea.getText());                
        }
        catch(Exception e)
        {
            return;
        }
        
        //mesgPanel.addMessage(cMesgArea.getText(), user.avatar, user.name, false);
        JLabel lbl = new JLabel("You:\n" + cMesgArea.getText());
        lbl.setMaximumSize(new Dimension(230, 500));
        mesgPanel.add(lbl);
        
        // serialize
        saveJLabels(""+ref.getPosJabberId(friend.rEntry.getUser()), lbl);

        cMesgArea.setText(null);
        this.setVisible(false);
        repaint();
        this.setVisible(true);
    }
    
    public class EnterAction extends AbstractAction
    {
		private static final long serialVersionUID = 1L;
		@Override
        public void actionPerformed(ActionEvent e) {
            sendButtonActionPerformed(e);
        }
    }


    private ArrayList<JLabel> SJLabels;
    private javax.swing.JTextArea cMesgArea;
    private javax.swing.JScrollPane fScroll;
    private javax.swing.JScrollPane mScroll;
    //private hazi.CMessagePanel mesgPanel;
    private javax.swing.JPanel mesgPanel;
    private javax.swing.JButton sendButton;
    private ChatFriendEntry friend;
    //private ChatUserEntry user; 
    private FacebookChat ref;    
    
    // serialize
    private void saveJLabels(String userid, JLabel lbl){
    	SJLabels.add(lbl);
        try {
        	File fLog = new File(userid);
        	if(!fLog.exists()) {
        		fLog.createNewFile();
        	}
    		FileOutputStream fileOut = new FileOutputStream(fLog);
            ObjectOutputStream out = new ObjectOutputStream(fileOut);
            out.writeObject(SJLabels);
			out.close();
            fileOut.close();
		} catch (Throwable t) {}
    }
}
