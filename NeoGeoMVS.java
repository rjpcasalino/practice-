import javax.swing.*;
import javax.swing.border.EmptyBorder;
import javax.swing.border.LineBorder;
import java.awt.*;
import java.util.HashMap;
import java.util.Map;

public class NeoGeoMVS extends JFrame {

    // The internal Data Structure
    private final Map<Integer, String> mvsCabinet = new HashMap<>();

    // Retro Aesthetic Palette
    private static final Color CRT_BG = new Color(15, 20, 15);
    private static final Color PHOSPHOR = new Color(170, 255, 170); // Washed-out green
    private static final Font TERMINAL_FONT = new Font("Monospaced", Font.BOLD, 16);
    private static final Font TITLE_FONT = new Font("Monospaced", Font.BOLD, 24);

    // UI Components
    private final JTextArea consoleOutput;
    private final JTextField idInput;
    private final JTextField titleInput;

    public NeoGeoMVS() {
        // Initialize the MVS with some default memory
        mvsCabinet.put(201, "Metal Slug");
        mvsCabinet.put(242, "King of Fighters '98");
        mvsCabinet.put(98,  "Samurai Shodown");

        // ---------------------------------------------------------
        // 1. Frame Setup
        // ---------------------------------------------------------
        setTitle("MVS-2 DIAGNOSTIC & LIBRARY SYSTEM");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setSize(700, 500);
        getContentPane().setBackground(CRT_BG);
        setLayout(new BorderLayout(10, 10));

        // ---------------------------------------------------------
        // 2. Header Panel
        // ---------------------------------------------------------
        JLabel headerLabel = new JLabel("NEO-GEO MVS MEMORY MAPPER v1.0");
        headerLabel.setFont(TITLE_FONT);
        headerLabel.setForeground(PHOSPHOR);
        headerLabel.setHorizontalAlignment(SwingConstants.CENTER);
        headerLabel.setBorder(new EmptyBorder(10, 10, 10, 10));
        add(headerLabel, BorderLayout.NORTH);

        // ---------------------------------------------------------
        // 3. Central Console (The Hash Map View)
        // ---------------------------------------------------------
        consoleOutput = new JTextArea();
        consoleOutput.setEditable(false);
        consoleOutput.setBackground(CRT_BG);
        consoleOutput.setForeground(PHOSPHOR);
        consoleOutput.setFont(TERMINAL_FONT);
        consoleOutput.setBorder(new EmptyBorder(10, 10, 10, 10));
        consoleOutput.setCaretColor(PHOSPHOR);

        JScrollPane scrollPane = new JScrollPane(consoleOutput);
        scrollPane.setBorder(new LineBorder(PHOSPHOR, 2));
        scrollPane.setBackground(CRT_BG);
        scrollPane.getViewport().setBackground(CRT_BG);
        add(scrollPane, BorderLayout.CENTER);

        // ---------------------------------------------------------
        // 4. Input Panel (Bottom)
        // ---------------------------------------------------------
        JPanel inputPanel = new JPanel();
        inputPanel.setLayout(new FlowLayout(FlowLayout.LEFT, 10, 10));
        inputPanel.setBackground(CRT_BG);
        inputPanel.setBorder(new LineBorder(PHOSPHOR, 1));

        JLabel idLabel = createRetroLabel("NGH ID:");
        idInput = createRetroTextField(6);

        JLabel titleLabel = createRetroLabel("TITLE:");
        titleInput = createRetroTextField(20);

        JButton loadButton = new JButton("INSTALL CART");
        styleRetroButton(loadButton);

        // Action Listener to handle inserting into the Hash Map
        loadButton.addActionListener(e -> handleCartridgeInstall());

        inputPanel.add(idLabel);
        inputPanel.add(idInput);
        inputPanel.add(titleLabel);
        inputPanel.add(titleInput);
        inputPanel.add(loadButton);

        add(inputPanel, BorderLayout.SOUTH);

        // Run initial boot sequence print
        refreshConsole("SYSTEM BOOT... OK\nMEMORY CHECK... OK\n\n");
    }

    // ---------------------------------------------------------
    // Logic & Hardware Interaction
    // ---------------------------------------------------------
    private void handleCartridgeInstall() {
        try {
            int id = Integer.parseInt(idInput.getText().trim());
            String title = titleInput.getText().trim().toUpperCase();

            if (title.isEmpty()) {
                refreshConsole("ERROR: INVALID CARTRIDGE TITLE\n");
                return;
            }

            // Map insertion
            mvsCabinet.put(id, title);
            
            idInput.setText("");
            titleInput.setText("");
            refreshConsole("CARTRIDGE 0x" + String.format("%04X", id) + " INSTALLED SUCCESSFULLY.\n\n");

        } catch (NumberFormatException ex) {
            refreshConsole("ERROR: NGH ID MUST BE NUMERIC.\n\n");
        }
    }

    private void refreshConsole(String prefixText) {
        StringBuilder sb = new StringBuilder(prefixText);
        sb.append("CURRENT SYSTEM MEMORY MAP:\n");
        sb.append("==========================\n");

        // Iterate over the HashMap
        for (Map.Entry<Integer, String> entry : mvsCabinet.entrySet()) {
            sb.append(String.format("SLOT [%03d] : %s\n", entry.getKey(), entry.getValue()));
        }

        sb.append("==========================\n");
        sb.append("READY.\n_");
        
        consoleOutput.setText(sb.toString());
    }

    // ---------------------------------------------------------
    // Aesthetic Helpers
    // ---------------------------------------------------------
    private JLabel createRetroLabel(String text) {
        JLabel label = new JLabel(text);
        label.setForeground(PHOSPHOR);
        label.setFont(TERMINAL_FONT);
        return label;
    }

    private JTextField createRetroTextField(int columns) {
        JTextField field = new JTextField(columns);
        field.setBackground(CRT_BG);
        field.setForeground(PHOSPHOR);
        field.setCaretColor(PHOSPHOR);
        field.setFont(TERMINAL_FONT);
        field.setBorder(new LineBorder(PHOSPHOR, 1));
        return field;
    }

    private void styleRetroButton(JButton button) {
        button.setBackground(CRT_BG);
        button.setForeground(PHOSPHOR);
        button.setFont(TERMINAL_FONT);
        button.setFocusPainted(false);
        button.setBorder(BorderFactory.createCompoundBorder(
                new LineBorder(PHOSPHOR, 2),
                new EmptyBorder(5, 15, 5, 15)
        ));
    }

    public static void main(String[] args) {
        // Force the UI manager to drop any modern OS styling for option panes/dialogs
        UIManager.put("OptionPane.background", CRT_BG);
        UIManager.put("Panel.background", CRT_BG);

        SwingUtilities.invokeLater(() -> {
            NeoGeoMVS app = new NeoGeoMVS();
            app.setLocationRelativeTo(null);
            app.setVisible(true);
        });
    }
}
