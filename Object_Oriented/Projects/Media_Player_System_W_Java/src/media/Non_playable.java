package media; // Package of the class

public class Non_playable extends BaseClass { // Class Non_playable that extends BaseClass
    protected String dimension = ""; // it has a dimension
    public Non_playable(String name, String dimension, String otherInfo) { // Constructor of the class
        super(name, otherInfo);
        this.dimension = dimension;
    }

    public Non_playable(String name, String otherInfo) { // Constructor of the class because it can be created without a dimension
        super(name, otherInfo);
    }

    public void info() { // Method to print the information of the non-playable
        System.out.println("Non-playable: " + name + ", " + dimension + ", " + otherInfo);
    }

    public String getDimension() { // Method to get the dimension of the non-playable 
        return dimension;
    }

    public void setDimension(String dimension) { // Method to set the dimension of the non-playable
        this.dimension = dimension;
    }

}