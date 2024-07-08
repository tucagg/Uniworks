package media; // Package of the class

public class Playable extends BaseClass {
    protected String duration; // it has a duration
    public Playable(String name, String duration,String otherInfo) { // Constructor of the class
        super(name, otherInfo);
        this.duration = duration;
    }

    public void info() { // Method to print the information of the playable
        System.out.println("Playable: " + name + ", " + duration + ", " + otherInfo);
    }

    public String getDuration() { // Method to get the duration of the playable
        return duration;
    }

    public void setDuration(String duration) { // Method to set the duration of the playable
        this.duration = duration;
    }

}