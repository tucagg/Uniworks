package media;

import observer.Observer;

import java.util.ArrayList;
import java.util.List;

public class Viewer implements Observer { // Class Viewer that implements Observer
    private List<Non_playable> viewList = new ArrayList<>(); // List of non-playables
    private int currentIndex = 0; // Index of the current non-playable

    @Override
    public void update(Object obj) {
        if (obj instanceof Non_playable) {
            if (viewList.contains(obj)) { // Check if the object is in the list
                viewList.remove(obj); // Remove the object from the list
            } else {
                if (((Non_playable) obj).getName().equals("no media")) { // Check if the name of the object is "no media" if so don't add it to the list
                    return;
                }
                viewList.add((Non_playable) obj); // Add the object to the list
            }
        }
    }

    public void show_list() { // Method to show the list of non-playables
        for (Non_playable np : viewList) { 
            np.info();
        }
        if (viewList.isEmpty()) {   // Check if the list is empty
            System.out.println("No media in the list");
        }
    }

    public Non_playable currently_viewing(){ // Method to get the current non-playable
        if (currentIndex >= 0 && currentIndex < viewList.size()) {
            return viewList.get(currentIndex);
        }
        return new Non_playable("no media", "no size", "no other info"); // Return a new non-playable with the name "no media" if the index is not valid
    }

    public void next(String type) { // Method to get the next non-playable 
        for (int i = currentIndex + 1; i < viewList.size(); i++) {
            Non_playable np = viewList.get(i);
            if (type.equals("text") && np instanceof Text) { // Check if the non-playable is a text and the type is text
                currentIndex = i;
                return;
            } else if (type.equals("image") && np instanceof Image) { // Check if the non-playable is an image and the type is image
                currentIndex = i;
                return;
            }
        }
        System.out.println("No more " + type + " in the list"); // Print a message if there is no more media in the list
    }

    public void previous(String type) { // Method to get the previous non-playable
        for (int i = currentIndex - 1; i >= 0; i--) {
            Non_playable np = viewList.get(i);
            if (type.equals("text") && np instanceof Text) { // Check if the non-playable is a text and the type is text
                currentIndex = i;
                return;
            } else if (type.equals("image")&& np instanceof Image) { // Check if the non-playable is an image and the type is images
                currentIndex = i;
                return;
            }
        }
        System.out.println("No more " + type + " in the list"); // Print a message if there is no more media in the list
        return;
    }
}
