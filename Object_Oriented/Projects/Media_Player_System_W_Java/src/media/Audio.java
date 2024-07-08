package media;  // Package of the class

import interfaces.Non_visual; // path: src/interfaces/NonVisual.java

public class Audio extends Playable implements Non_visual { // Class Audio that extends Playable and implements NonVisual

    public Audio(String name, String duration, String otherInfo) { // Constructor of the class
        super(name, duration, otherInfo);
    }

    @Override
    public void info() { // Method to print the information of the audio
        System.out.println("Audio: " + name + ", " + duration+ ", " + otherInfo) ;
    }
}