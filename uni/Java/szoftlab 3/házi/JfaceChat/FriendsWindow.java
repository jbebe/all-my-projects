package hazi;

public class FriendsWindow extends javax.swing.JFrame {
	private static final long serialVersionUID = 1L;

	public FriendsWindow(FriendsWindowController fPanel) {

		initComponents(fPanel);

		try {
			for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager
					.getInstalledLookAndFeels()) {
				if ("Nimbus".equals(info.getName())) {
					javax.swing.UIManager.setLookAndFeel(info.getClassName());
					break;
				}
			}
		} catch (Exception ex) {
			java.util.logging.Logger.getLogger(FriendsWindow.class.getName()).log(
					java.util.logging.Level.SEVERE, null, ex);
		}
	}

	private void initComponents(FriendsWindowController fPanel) {

		fScroll = new javax.swing.JScrollPane();

		setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
		setTitle("Facebook Chat");
		setAlwaysOnTop(true);
		setName("cFrame");
		setResizable(false);

		fScroll.setHorizontalScrollBarPolicy(javax.swing.ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
		fScroll.setVerticalScrollBarPolicy(javax.swing.ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		fScroll.setViewportView(fPanel);

		javax.swing.GroupLayout layout = new javax.swing.GroupLayout(
				getContentPane());
		getContentPane().setLayout(layout);
		layout.setHorizontalGroup(layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addComponent(
				fScroll, javax.swing.GroupLayout.PREFERRED_SIZE,
				javax.swing.GroupLayout.DEFAULT_SIZE,
				javax.swing.GroupLayout.PREFERRED_SIZE));
		layout.setVerticalGroup(layout.createParallelGroup(
				javax.swing.GroupLayout.Alignment.LEADING).addComponent(
				fScroll, javax.swing.GroupLayout.Alignment.TRAILING,
				javax.swing.GroupLayout.PREFERRED_SIZE, 242,
				javax.swing.GroupLayout.PREFERRED_SIZE));

		pack();
	}

	private javax.swing.JScrollPane fScroll;

}
