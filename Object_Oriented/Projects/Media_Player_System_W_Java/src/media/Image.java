package media; // Package of the class

import interfaces.Visual; 

public class Image extends Non_playable implements Visual { // Class Image that extends Non_playable and implements Visual
    public Image(String name, String dimensions, String otherInfo) { // Constructor of the classs
        super(name, dimensions, otherInfo);
    }

    @Override
    public void info() { // Method to print the information of the image
        System.out.println("Image: " + name + ", " + dimension + ", " + otherInfo);
    }

}
