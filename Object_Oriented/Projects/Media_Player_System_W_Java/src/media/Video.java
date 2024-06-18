package media;

import interfaces.Visual;

public class Video extends Playable implements Visual{
    
    public Video(String name, String duration, String otherInfo) { // Constructor of the class
        super(name, duration, otherInfo);
    }

    @Override
    public void info() { // Method to print the information of the video
        System.out.println("Video: " + name + ", " + duration + ", " + otherInfo);
    }
}
