// Dosya Adı: JavaSet.java
package example.container;

/**
 * JavaSet
 * @param <T> generic tip
 * JavaContainer interface'ini implement eder
 * toString ve equals metotları hepsinde olsun dediniz diye interface ekledim
 */
public class JavaSet<T> implements JavaContainer<T> {
    private CustomSet<T> set;

    /**
     * JavaSet constructor
     * set'i oluşturur
     */
    public JavaSet() {
        set = new CustomSet<>();
    }

    /**
     * indexBul metodu
     * @param index işlenecek index
     * @return T
     * set'in index'ini bulur
     */
    public T indexBul(int index) {
        return set.indexBul(index);
    }

    /**
     * add metodu
     * @param element
     * elementi set'e ekler
     */
    @Override
    public void add(T element) {
        set.add(element);
    }

    /**
     * remove metodu
     * @param element
     * elementi set'ten siler
     */
    @Override
    public void remove(T element) {
        set.remove(element);
    }

    /**
     * size metodu
     * @return int
     * set'in size'ını döndürür
     */
    @Override
    public int size() {
        return set.size();
    }

    /**
     * getIterator metodu
     * @return T
     * set'in iterator'ını döndürür
     */
    @Override
    public JavaIterator<T> getIterator() {
        return set.iterator();
    }

    /**
     * toString metodu
     * @return String
     * set'i string olarak döndürür
     */
    @Override
    public String toString() {
        return String.format("Set: %s", set);
    }

    /**
     * equals metodu
     * @param obj işlenecek obje
     * @return boolean
     * set'lerin eşit olup olmadığını kontrol eder
     */
    @Override
    public boolean equals(Object obj) {

        JavaSet<?> javaSet = (JavaSet<?>) obj;
        JavaSet<?> javaSet2 = this;
        if (this == obj)
            return true;
        else {
            int count = 0;
            for (var i = 0; i < size(); i++) {
                for (var j = 0; j < size(); j++) {
                    if (javaSet2.indexBul(i) == javaSet.indexBul(j)) {
                        count++;
                    }

                }
            }
            if (count == size()) {
                return true;
            }
        }
        return false;
    }

}