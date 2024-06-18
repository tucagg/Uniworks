import media.*;

public class Main {
    public static void main(String[] args) {
        // This is our dataset. We have only one dataset.
        Dataset ds = new Dataset();
        // Lets create different observers.
        Player p1 = new Player();
        Player p2 = new Player();

        Viewer v1 = new Viewer();
        Viewer v2 = new Viewer();
        // Lets register them to our dataset so that they can reach to data and updates.
        // You can also register them to the dataset when you create them.
        // ds has to figure out the type of the observer.
        // it should not send unrelated information.
        // For example, viewer objects don't want to know anything about playable
        // objects.
        ds.register(p1);
        ds.register(p2);
        ds.register(v1);
        ds.register(v2);
        // Dataset should also support un-registering.
        // ds.remove_observer(p1);
        // p1 no longer receives any update or list of items.
        // Here we create different objects.
        ds.add(new Image("imagename1", "dimension info1", "other info1"));
        ds.add(new Image("imagename2", "dimension info2", "other info2"));
        ds.add(new Image("imagename3", "dimension info3", "other info3"));
        ds.add(new Image("imagename4", "dimension info4", "other info4"));
        ds.add(new Image("imagename5", "dimension info5", "other info5"));

        ds.add(new Audio("audioname1", "duration1", "other info1"));
        ds.add(new Audio("audioname2", "duration2", "other info2"));
        ds.add(new Audio("audioname3", "duration3", "other info3"));

        ds.add(new Video("videoname1", "duration1", "other info1"));
        ds.add(new Video("videoname2", "duration2", "other info2"));
        ds.add(new Video("videoname3", "duration3", "other info3"));

        ds.add(new Text("textname1", "other info1"));
        ds.add(new Text("textname2", "other info2"));
        ds.add(new Text("textname3", "other info3"));

        // Lets use one of the player objects.
        // We can get the currently playing object
        System.out.println("------------------Show the Player 1's List------------------");
        p1.show_list();

        Playable po = p1.currently_playing();
        // This prints info about the playing object.
        System.out.println("------------------Show the currently playing object------------------(As said in pdf it ,currently playing is the first item in the received list,");
        po.info();
        // we can remove this object from the dataset
        System.out.println("------------------Remove the currently playing object and see what is currently playing now------------------");
        ds.remove(po);
        Playable po2 = p1.currently_playing();
        po2.info();

        System.out.println("------------------Show the Player 1's List------------------ (to see if the removed object is removed from the list)");
        p1.show_list();

        
        System.out.println("------------------Let's try p2.next(audio)------------------");
        p2.next("audio");
        Playable po3 = p2.currently_playing();
        po3.info();

        System.out.println("------------------Let's try p2.next(video)------------------");
        p2.next("video");
        Playable po4 = p2.currently_playing();
        po4.info();

        System.out.println("----------------Let's try p2.next(audio) (we shouldnt see audio object because videos was end of the list and we are playing videos now, so there is no audio after this video)------------------");
        p2.next("audio");
        System.out.println("------------------But we can see the previous audio now.------------------");
        p2.previous("audio");
        Playable po5 = p2.currently_playing();
        po5.info();

        System.out.println("------------------Let's try to add an audio end of the playlist------------------");
        ds.add(new Audio("audioname4", "duration4", "other info4"));
        System.out.println("------------------Let's try p2.next(audio) (so we can go to the end of the list)------------------");
        p2.next("audio");
        Playable po6 = p2.currently_playing();
        po6.info();

        System.out.println("------------------Let's delete this audio from end of the file------------------");
        ds.remove(po6);
        System.out.println("------------------After these audio there is no audio or video object because we added this end of the list, so when i try to see p2.current_playing i should see no media------------------");
        Playable po7 = p2.currently_playing();
        po7.info();

        System.out.println("------------------Lets try go to previous audio from here and see what is p2.currently_playing now, so we can understand i handled all these situations------------------");
        p2.previous("audio");
        Playable po8 = p2.currently_playing();
        po8.info();

        System.out.println("------------------Show the Player 1's List------------------");
        p1.show_list();
        
        System.out.println("------------------Show the p1.currently_playing so we can understand all player's have different current index------------------");
        Playable po9 = p1.currently_playing();
        po9.info();

        System.out.println("------------------Let's remove all of the playable object to see how can i handled this situation.------------------");
        ds.remove(po9);
        ds.next("audio");
        Playable po10 = p1.currently_playing();
        ds.remove(po10);
        ds.next("audio");
        Playable po11 = p1.currently_playing();
        ds.remove(po11);
        ds.next("video");
        Playable po12 = p1.currently_playing();
        ds.remove(po12);
        ds.next("video");
        Playable po13 = p1.currently_playing();
        ds.remove(po13);

        System.out.println("------------------Show the Player 1's List------------------");
        p1.show_list();
        System.out.println("------------------Show the Player 2's List------------------");
        p2.show_list();
    }
}
