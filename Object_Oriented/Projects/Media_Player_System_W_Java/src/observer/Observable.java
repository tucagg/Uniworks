package observer;

import java.util.ArrayList;
import java.util.List;

public class Observable {
    private List<Observer> observers = new ArrayList<>(); // List of observers

    public void addObserver(Observer observer) { // Method to add an observer
        observers.add(observer);
    }

    public void remove_observer(Observer observer) { // Method to remove an observer
        observers.remove(observer);
    }

    public void notifyObservers(Object obj) { // Method to notify the observers
        for (Observer observer : observers) {
            observer.update(obj); // Update the observer
        }
    }
    
}
