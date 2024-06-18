// Dosya Adı: JavaContainer.java
package example.container;

/**
 * JavaContainer
 * @param <T> generic tip
 * genel interface
 * toString ve equals metotları hepsinde olsun dediniz diye interface ekledim
 */
public interface JavaContainer<T> {
   /**
    * add metodu
    * @param element işlenecek eleman
    */
    void add(T element);
    /**
     * remove metodu
     * @param element işlenecek eleman
     */
    void remove(T element);
    /**
     * size metodu
     * @return int size
     */
    int size();
    /**
     * getIterator metodu
     * @return  iterator
     */
    JavaIterator<T> getIterator();
    /**
     * toString metodu
     * @return string
     */
    public String toString();
    /**
     * equals metodu
     * @param obj işlenirken karşılaştırılacak obje
     * @return boolean
     */
    public boolean equals(Object obj);
    /**
     * indexBul metodu
     * @param index işlenecek index
     * @return T
     */
    T indexBul(int index);
}
