import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class RetroNixApplet extends JPanel implements ActionListener {
    // Animation state
    private int x = 50;
    private int y = 50;
    private int dx = 4;
    private int dy = 3;
    
    // Environment data
    private final String shellMessage;
    private final String javaMessage;
    
    // Aesthetic
    private final Font retroFont;
    private final Color phosphorGreen = new Color(170, 255, 170); // Washed-out green
    private final Color phosphorGhost = new Color(70, 140, 70, 120); 
    private final Color crtBackground = new Color(15, 20, 15);

    public RetroNixApplet() {
        // Read Nix environment variables
        String inNix = System.getenv("IN_NIX_SHELL");
        String nixName = System.getenv("name");
        
        if (inNix != null) {
            shellMessage = "> NIX_SHELL ACTIVE: [" + (nixName != null ? nixName : "impure") + "]";
        } else {
            shellMessage = "> WARNING: NO NIX SHELL DETECTED";
        }
        
        javaMessage = "> JVM: " + System.getProperty("java.version");

        // Classic bold monospaced font
        retroFont = new Font("Monospaced", Font.BOLD, 28);

        // Set up the animation loop (~60 FPS)
        Timer timer = new Timer(16, this);
        timer.start();
        
        setBackground(crtBackground);
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        
        // Cast to Graphics2D but strictly AVOID turning on anti-aliasing 
        // to keep those crisp, pixelated 90s edges.
        Graphics2D g2d = (Graphics2D) g;
        g2d.setFont(retroFont);
        
        // 1. Draw the "ghost" trail (rendered slightly behind the current coordinates)
        g2d.setColor(phosphorGhost);
        g2d.drawString(shellMessage, x - (dx * 3), y - (dy * 3));
        g2d.drawString(javaMessage, x - (dx * 3), y + 35 - (dy * 3));
        
        // 2. Draw the main text
        g2d.setColor(phosphorGreen);
        g2d.drawString(shellMessage, x, y);
        g2d.drawString(javaMessage, x, y + 35); // Offset the second line
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        // Move the text
        x += dx;
        y += dy;

        // Calculate dynamic boundaries so the text bounces perfectly off the edges
        FontMetrics metrics = getFontMetrics(retroFont);
        int textWidth = Math.max(metrics.stringWidth(shellMessage), metrics.stringWidth(javaMessage));
        int textHeight = metrics.getHeight();

        // Screen collision detection
        if (x < 0 || x + textWidth > getWidth()) {
            dx = -dx;
            x = Math.max(0, Math.min(x, getWidth() - textWidth)); // Prevent getting stuck
        }
        // y coordinate in drawString is the baseline, so we offset by textHeight for the top edge
        if (y - textHeight < 0 || y + 45 > getHeight()) { 
            dy = -dy;
            y = Math.max(textHeight, Math.min(y, getHeight() - 45));
        }

        // Trigger a repaint for the next frame
        repaint();
    }

    public static void main(String[] args) {
        // Run GUI construction on the Event Dispatch Thread (Standard Java practice)
        SwingUtilities.invokeLater(() -> {
            JFrame frame = new JFrame("Retro Nix Shell Info Applet");
            frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame.setSize(800, 600);
            
            // Add our custom bouncing panel
            frame.add(new RetroNixApplet());
            
            // Center on screen and show
            frame.setLocationRelativeTo(null);
            frame.setVisible(true);
        });
    }
}
