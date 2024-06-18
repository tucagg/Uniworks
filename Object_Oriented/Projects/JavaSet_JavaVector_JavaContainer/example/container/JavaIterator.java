// Dosya Adı: JavaIterator.java
package example.container;

/**
 * JavaIterator
 * @author Tugce Polat
 * hasnext ve next metotlarını içeren interface
 * @param <T> generic tip 
 * hasNext metodu sonraki elemanın olup olmadığını kontrol eder
 * next metodu sonraki elemanı döndürür
 */
 

public interface JavaIterator<T> {
    /**
     * hasNext metodu
     * @return boolean
     */
    boolean hasNext();
    /**
     * next metodu
     * @return T
     */
    T next();
}
