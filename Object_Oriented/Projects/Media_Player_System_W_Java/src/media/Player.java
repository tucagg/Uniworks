package media;

import observer.Observer;
import java.util.ArrayList;
import java.util.List;

public class Player implements Observer {
    private List<Playable> playList = new ArrayList<>(); // List of playables
    private int currentIndex = 0;   // Index of the current playable

    @Override
    public void update(Object obj) { // Method to update the player
        if (obj instanceof Playable) {
            if (playList.contains(obj)) { // Check if the object is in the list
                playList.remove(obj); // Remove the object from the list
            } else {
                if (((Playable) obj).getName().equals("no media")) { // Check if the name of the object is "no media" if so don't add it to the list
                    return;
                }
                playList.add((Playable) obj); // Add the object to the list
            }
        }
    }

    public void show_list() { // Method to show the list of playables
        for (Playable p : playList) {   // Loop to show the playables
            p.info();
        }
        if (playList.isEmpty()) { // Check if the list is empty
            System.out.println("No media in the list");
        }
    }

    public Playable currently_playing(){ // Method to get the current playable
        if (currentIndex >= 0 && currentIndex < playList.size()) { // Check if the index is valid
            return playList.get(currentIndex);
        }
        return new Playable("no media", "no duration", "no other info"); // Return a new playable with the name "no media" if the index is not valid
    }

    public void next(String type) { // Method to get the next playable
        for (int i = currentIndex + 1; i < playList.size(); i++) {
            Playable p = playList.get(i);
            if (type.equals("audio") && p instanceof Audio) { // Check if the playable is an audio and the type is audio
                currentIndex = i;
                return;
            } else if (type.equals("video") && p instanceof Video) { // Check if the playable is a video and the type is video
                currentIndex = i; 
                return;
            }
        }
        System.out.println("No more " + type + " in the list"); // Print a message if there is no more media in the list
        return;
    }

    public void previous(String type) { // Method to get the previous playable
        for (int i = currentIndex - 1; i >= 0; i--) {
            Playable p = playList.get(i);
            if (type.equals("audio") && p instanceof Audio) { // Check if the playable is an audio and the type is audio
                currentIndex = i;
                return;
            } else if (type.equals("video") && p instanceof Video) { // Check if the playable is a video and the type is video
                currentIndex = i;
                return;
            }
        }
        System.out.println("No more " + type + " in the list"); // Print a message if there is no more media in the list
        return;
    }

}
