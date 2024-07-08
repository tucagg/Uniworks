package media;

import interfaces.Non_visual; 

public class Text extends Non_playable implements Non_visual { // Class Text that extends Non_playable and implements NonVisual
    public Text(String name, String otherInfo) { // Constructor of the class
        super(name, otherInfo);
    }
    @Override
    public void info() { // Method to print the information of the text
        System.out.println("Text: " + name + ", " + otherInfo);
    }
}
