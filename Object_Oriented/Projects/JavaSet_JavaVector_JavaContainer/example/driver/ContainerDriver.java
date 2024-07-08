// Dosya Adı: ContainerDriver.java
package example.driver;

import example.container.JavaContainer;
import example.container.JavaIterator;
import example.container.JavaSet;
import example.container.JavaVector;

import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Scanner;

/**
 * ContainerDriver
 * 
 * JavaSet, JavaVector ve JavaContainer interface'ini kullanır
 * mainimin olduğu class
 * set.txt ve vector.txt dosyalarına yazdırır
 */
public class ContainerDriver {
    /**
     * main metodu
     * @param args argümanlar
     * JavaSet ve JavaVector'ü test eder
     * set.txt ve vector.txt dosyalarına yazdırır
     */
    public static void main(String[] args) {
        // Test JavaSet
        /**
         * set'i oluşturur
         * addElements metodu ile set'e eleman ekler
         * set'i yazdırır
         */
        var set = new JavaSet<>();
        addElements(set);
        System.out.println(set);

        /**
         * testSet'i oluşturur
         * testSet2'yi oluşturur
         * eklemeler yapar ve remove add kontrol eder.
         */
        var testSet = new JavaSet<Integer>();
        testSet.add(1);
        testSet.add(2);
        testSet.add(3);
        testSet.add(4);
        testSet.add(5);
        testSet.remove(4);
        testSet.remove(5);

        var testSet2 = new JavaSet<Integer>();
        testSet2.add(1);
        testSet2.add(3);
        testSet2.add(2);
        testSet2.add(5);
        testSet2.remove(5);

        var testVector = new JavaVector<Integer>();
        testVector.add(1);
        testVector.add(2);
        testVector.add(3);
        testVector.add(4);
        testVector.add(5);
        testVector.remove(4);

        var testVector2 = new JavaVector<Integer>();
        testVector2.add(1);
        testVector2.add(3);
        testVector2.add(2);
        testVector2.add(5);
        testVector2.remove(5);
    
        /**
         * eşitlik doğru çalışıyo mu bakar (set için ayrı vec için ayrı)
         */
        
        if (testSet.equals(testSet2)) {
            System.out.println("Eşit");
        } 

        /**
         * eşitlik doğru çalışıyo mu bakar (set için ayrı vec için ayrı)
         */
        if (testSet.equals(testSet2)) {
            System.out.println("Eşit");
        }

        /**
         * toString doğru çalışıyo mu bakar (set için ayrı vec için ayrı)
         */
        System.out.println("----------------------");
        System.out.println("toString");
        System.out.println(testSet.toString());
        System.out.println(testVector.toString());

        /**
         * iterator doğru çalışıyo mu bakar (set için ayrı vec için ayrı)
         */

        System.out.println("----------------------");
        System.out.println("Iterator");
        JavaIterator<Integer> iterator = testSet.getIterator();
        while (iterator.hasNext()) {
            System.out.println(iterator.next());
        }



        /**
         * kaydetmeleri dener
         */
        // Save sets to text files
        saveToFile(testSet, "set.txt");
        saveToFile(testVector, "vector.txt");
    }

    /**
     * saveToFile metodu
     * 
     * @param <T>  generic tip
     * @param container container tipi
     * @param fileName  dosya adı
     * @throws IOException dosya bulunamazsa hata verir
     */
    private static <T> void saveToFile(JavaContainer<T> container, String fileName) {
        try (PrintWriter writer = new PrintWriter(new FileWriter(fileName))) {
            JavaIterator<T> iterator = container.getIterator();
            while (iterator.hasNext()) {
                writer.println(iterator.next());
            }
            System.out.println("Saved " + container.getClass().getSimpleName() + " to " + fileName);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    /**
     * addElements metodu
     * 
     * @param <T>  generic tip
     * @param container container tipi
     * @throws NumberFormatException giriş tipi kontol kullanıcı yanlış giriş yaparsa hata verir
     * @throws NullPointerException
     */
    private static <T> void addElements(JavaContainer<T> container) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter elements (type 'exit' to finish):");
        String input;
        while (!(input = scanner.nextLine()).equalsIgnoreCase("exit")) {
            try {
                // Kullanıcının girdisinin doğru tip olup olmadığını kontrol et
                T element = parseInput(input);
                container.add(element);
            } catch (NumberFormatException e) {
                System.out.println("Invalid input. Please enter a valid element.");
            }
        }
        scanner.close();
    }

    
    /**
     * parseInput metodu
     * @param <T>   generic tip
     * @param input kullanıcı girişi
     * @return T
     * @throws NumberFormatException giriş tipi kontol
     * kullanıcı yanlış giriş yaparsa hata verir
     */
    // Helper method to parse user input to the correct type
    @SuppressWarnings("unchecked")
    private static <T> T parseInput(String input) throws NumberFormatException {
        // Bu örnekte sadece Integer tipini destekleyelim
        if (input.matches("\\d+")) {
            return (T) Integer.valueOf(input);
        } else {
            throw new NumberFormatException();
        }
    }
}
