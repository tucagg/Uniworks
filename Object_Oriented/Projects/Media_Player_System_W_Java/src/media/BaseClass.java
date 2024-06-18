package media; // Package of the class

public abstract class BaseClass { // Abstract class BaseClass
    protected String name;
    protected String type;
    protected String otherInfo;

    public BaseClass(String name, String otherInfo) { // Constructor of the class
        this.name = name;
        this.otherInfo = otherInfo;
    }

    public String getName() { // Method to get the name of the class
        return name;
    }

    public void setName(String name) { // Method to set the name of the class
        this.name = name;
    }

    public String getType() { // Method to get the type of the class
        return type;
    }

    public void setType(String type) { // Method to set the type of the class
        this.type = type;
    }

    public String getOtherInfo() { // Method to get the other information of the class
        return otherInfo;
    }

    public void setOtherInfo(String otherInfo) { // Method to set the other information of the class
        this.otherInfo = otherInfo;
    }

}
