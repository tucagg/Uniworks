// Dosya Adı: JavaVector.java
package example.container;

/**
 * JavaVector
 * @param <T> generic tip
 * JavaContainer interface'ini implement eder
 */
public class JavaVector<T> implements JavaContainer<T> {
    private CustomVector<T> vector;

    /**
     * JavaVector constructor
     * vector'ü oluşturur
     */
    public JavaVector() {
        vector = new CustomVector<>();
    }

    
    @Override
    public void add(T element) {
        vector.add(element);
    }

    /**
     * remove metodu
     * @param element
     * elementi vector'den siler
     */
    @Override
    public void remove(T element) {
        vector.remove(element);
    }

    /**
     * size metodu
     * @return int
     * vector'ün size'ını döndürür
     */
    @Override
    public int size() {
        return vector.size();
    }

    /**
     * getIterator metodu
     * @return T
     * vector'ün iterator'ünü döndürür
     */
    @Override
    public JavaIterator<T> getIterator() {
        return vector.iterator();
    }

    /**
     * toString metodu
     * @return String
     * vector'ün string karşılığını döndürür
     */
    @Override
    public String toString() {
        return String.format("Vector: %s", vector);
    }

    /**
     * equals metodu
     * @param obj işlenirken karşılaştırılacak obje
     * @return boolean
     * vector'lerin eşitliğini kontrol eder, vectorde sıralama önemli olduğundan yani 2,3 ve 3,2 eşit olmadığından ona göre yazdım
     */
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (obj == null || getClass() != obj.getClass()) return false;
        JavaVector<?> javaVector = (JavaVector<?>) obj;
        return vector.equals(javaVector.vector);
    }

    /**
     * indexBul metodu
     * @param index işlenecek index
     * @return T
     * indexin vector'deki karşılığını döndürür
     * eğer index vector'de yoksa null döndürür
     */
    @Override
    public T indexBul(int index) {
        return vector.indexBul(index);
    }

}