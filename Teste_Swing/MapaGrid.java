package mapagrid;
import javax.swing.*;
import java.awt.GridLayout;


public class MapaGrid {
    private int heroiX;
    private int heroiY;
    public static void main(String[] args) {
        JFrame frame = new JFrame("Mapa Grid");
        frame.setSize(400, 400);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new GridLayout(5, 5));
        for (int i = 0; i < 25; i++) {
            JButton button = new JButton();
            button.setEnabled(false);
            frame.add(button);
            button.addActionListener(a -> {});
            
            if (i == 0){
                button.setIcon(new ImageIcon("/home/aluno/Downloads/images.jpeg")); // Substitu "heroi.png" pelo caminho da imagem
                button.setEnabled(true);
            }
        }
    frame.setVisible(true);
    // Adiciona o herói na posição inicial (0, 0)

    }
}
    /*
    private static void moverHeroi(int deltaX, int deltaY) {
        int novoX = heroiX + deltaX;
        int novoY = heroiY + deltaY;
        if (novoX >= 0 && novoX < 5 && novoY >= 0 && novoY < 5) {
            // Limpa a posição atual do herói
            grid[heroiX][heroiY].setIcon(null);
            // Atualiza a posição do herói
            heroiX = novoX;
            heroiY = novoY;
            // Define o ícone do herói na nova posição
            grid[heroiX][heroiY].setIcon(new
            ImageIcon("heroi.png"));
            }
    }
    
}*/
