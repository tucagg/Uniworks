package media;

import observer.Observable;
import java.util.ArrayList;
import java.util.List;

public class Dataset extends Observable {
    private List<Playable> playList = new ArrayList<>(); // List of playables
    private List<Non_playable> nonPlayableList = new ArrayList<>(); // List of non-playables
    private int currentIndexForPlayable = 0; // Index of the current playable
    private int currentIndexForNonPlayable = 0; // Index of the current non-playable

    public void add(Playable p) { // Method to add a playable
        playList.add(p);
        notifyObservers(p);
    }

    public void add(Non_playable np) { // Method to add a non-playable
        nonPlayableList.add(np);
        notifyObservers(np);
    }

    public void remove(Playable p) {
        playList.remove(p); // remove from the list of playables
        if (currentIndexForPlayable >= playList.size()) {
            currentIndexForPlayable = 0;
        }
        notifyObservers(p); // remove from the list of observers
    }

    public void remove(Non_playable np) { // Method to remove a non-playable
        nonPlayableList.remove(np);
        if (currentIndexForNonPlayable >= nonPlayableList.size()) { 
            currentIndexForNonPlayable = 0;
        }
        notifyObservers(np); // remove from the list of observers
    }

    public void showList() { // Method to show the list of playables and non-playables
        for (Playable p : playList) { // Loop to show the playables
            p.info();
        }
        for (Non_playable np : nonPlayableList) { // Loop to show the non-playables
            np.info();
        }
    }

    public Playable currently_playing() { // Method to get the current playable
        if (currentIndexForPlayable >= 0 && currentIndexForPlayable < playList.size()) { // Check if the index is valid
            return playList.get(currentIndexForPlayable);
        }
        return null; // Return null if the index is not valid so that the caller can handle it
    }

    public void next(String type) { // Method to get the next playable
        if (type.equals("audio")) {
            for (int i = currentIndexForPlayable + 1; i < playList.size(); i++) {
                Playable p = playList.get(i);
                if (p instanceof Audio) { // Check if the playable is an audio
                    currentIndexForPlayable = i;
                    return;
                }
            }
        } else if (type.equals("video")) {
            for (int i = currentIndexForPlayable + 1; i < playList.size(); i++) {
                Playable p = playList.get(i); 
                if (p instanceof Video) { // Check if the playable is a video
                    currentIndexForPlayable = i;
                    return;
                }
            }
        }else if (type.equals("text")) {
            for (int i = currentIndexForNonPlayable + 1; i < nonPlayableList.size(); i++) {
                Non_playable np = nonPlayableList.get(i);
                if (np instanceof Text) { // Check if the non-playable is a text
                    currentIndexForNonPlayable = i;
                    return;
                }
            }
        }else if (type.equals("image")) {
            for (int i = currentIndexForNonPlayable + 1; i < nonPlayableList.size(); i++) {
                Non_playable np = nonPlayableList.get(i);
                if (np instanceof Image) { // Check if the non-playable is an image
                    currentIndexForNonPlayable = i;
                    return;
                }
            }
        }
    }

    public void previous(String type) { // Method to get the previous playable
        if (type.equals("audio")) {
            for (int i = currentIndexForPlayable - 1; i >= 0; i--) { 
                Playable p = playList.get(i);
                if (p instanceof Audio) { // Check if the playable is an audio
                    currentIndexForPlayable = i;
                    return;
                }
            }
        } else if (type.equals("video")) {
            for (int i = currentIndexForPlayable - 1; i >= 0; i--) {
                Playable p = playList.get(i);
                if (p instanceof Video) { // Check if the playable is a video
                    currentIndexForPlayable = i;
                    return;
                }
            }
        }
        else if (type.equals("text")) {
            for (int i = currentIndexForNonPlayable - 1; i >= 0; i--) {
                Non_playable np = nonPlayableList.get(i);
                if (np instanceof Text) { // Check if the non-playable is a text
                    currentIndexForNonPlayable = i;
                    return;
                }
            }
        }else if (type.equals("image")) {
            for (int i = currentIndexForNonPlayable - 1; i >= 0; i--) {
                Non_playable np = nonPlayableList.get(i);
                if (np instanceof Image) { // Check if the non-playable is an image
                    currentIndexForNonPlayable = i;
                    return;
                }
            }
        }
    }

    public void register(Player p) { // Method to register a player
        addObserver(p);
    }

    public void register(Viewer v) { // Method to register a viewer
        addObserver(v);
    }

}
