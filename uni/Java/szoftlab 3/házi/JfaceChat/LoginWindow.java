package hazi;

import org.jivesoftware.smack.XMPPException;

public class LoginWindow extends javax.swing.JFrame {

	private static final long serialVersionUID = 1L;
	private FacebookChat mainWindow;

	public LoginWindow(FacebookChat fbChat) {

        mainWindow = fbChat;
        
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
            java.util.logging.Logger.getLogger(LoginWindow.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }        
    }
    
    private void lButtonActionPerformed(java.awt.event.ActionEvent evt) {
        
        try
        {
            mainWindow.connect();
            
            if(mainWindow.login(lTextField.getText(), new String(pField.getPassword())) )
            {
                mainWindow.getFriends();
                dispose();
            }
            else
                throw new XMPPException();
        }
        catch (XMPPException e){
            //mainWindow.errorFrame.setError("Login Failed. Please try again.");
            mainWindow.disconnect();
            lTextField.setText(null);
            pField.setText(null);
            
        }
        
    }    

    private void initComponents() {

        lLabel = new javax.swing.JLabel();
        lTextField = new javax.swing.JTextField();
        pLabel = new javax.swing.JLabel();
        pField = new javax.swing.JPasswordField();
        lButton = new javax.swing.JButton();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Login Info");
        setAlwaysOnTop(true);
        setName("fLogin");
        setResizable(false);

        lLabel.setText("Facebook ID");
        lLabel.setToolTipText("Login Label");

        lTextField.setToolTipText("Login Text Field");
        lTextField.setText("balint.juhasz");

        pLabel.setText("Password");
        pLabel.setToolTipText("Password Label");

        pField.setToolTipText("Password Field");
        pField.setText("szolamajomreterat1993*");

        lButton.setToolTipText("Login Button");
        lButton.setText("Login");
        
        lButton.addActionListener(new java.awt.event.ActionListener() {
            @Override
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                lButtonActionPerformed(evt);
            }
        });        

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                            .addComponent(lLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                            .addComponent(pLabel, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(pField, javax.swing.GroupLayout.PREFERRED_SIZE, 173, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(lTextField)))
                    .addGroup(layout.createSequentialGroup()
                        .addGap(103, 103, 103)
                        .addComponent(lButton)
                        .addGap(0, 0, Short.MAX_VALUE)))
                .addContainerGap())
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(lLabel)
                    .addComponent(lTextField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addGap(18, 18, 18)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(pLabel)
                    .addComponent(pField, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(lButton)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        pack();
    }

    private javax.swing.JButton lButton;
    private javax.swing.JLabel lLabel;
    private javax.swing.JTextField lTextField;
    private javax.swing.JPasswordField pField;
    private javax.swing.JLabel pLabel;

}
