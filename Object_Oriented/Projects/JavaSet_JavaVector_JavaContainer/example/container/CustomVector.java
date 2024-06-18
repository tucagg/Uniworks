// Dosya Adı: CustomVector.java
package example.container;


/**
 * CustomVector
 * @author Tuğçe Polat
 * @param <T> generic tip
 */

public class CustomVector<T> {
    private static final int DEFAULT_CAPACITY = 10;

    /**
     * array dizisi ve size değişkeni
     */
    private Object[] array;
    private int size;

    /**
     * CustomVector constructor
     * array dizisini ve size değişkenini oluşturur
     */
    public CustomVector() {
        array = new Object[DEFAULT_CAPACITY];
        size = 0;
    }

    @SuppressWarnings("unchecked")
    T indexBul(int index) {
        return (T) array[index];
    }

    /**
     * add metodu
     * @param element
     * elementi array dizisine ekler
     * eğer array dizisinin boyutu dolmuşsa boyutunu 2 katına çıkarır ensureCapacity metodu ile
     */
    public void add(T element) {
        ensureCapacity();
        array[size++] = element;
    }

    /**
     * remove metodu
     * @param element
     * elementi array dizisinden siler
     * eğer element array dizisinde yoksa hiçbir şey yapmaz
     */
    public void remove(T element) {
        int index = indexOf(element);
        if (index != -1) {
            removeAt(index);
        }
    }

    /**
     * size metodu
     * @return size
     * size değişkenini döndürür
     */
    public int size() {
        return size;
    }

    /**
     * iterator metodu
     * @return CustomVectorIterator
     * CustomVectorIterator sınıfından bir nesne döndürür
     */
    public JavaIterator<T> iterator() {
        return new CustomVectorIterator();
    }

    /**
     * ensureCapacity metodu
     * eğer array dizisinin boyutu dolmuşsa boyutunu 2 katına çıkarır
     */
    private void ensureCapacity() {
        if (size == array.length) {
            int newCapacity = array.length * 2;
            Object[] newArray = new Object[newCapacity];
            System.arraycopy(array, 0, newArray, 0, size);
            array = newArray;
        }
    }

    /**
     * indexOf metodu
     * @param element
     * @return int
     * elementin array dizisindeki indexini döndürür
     * eğer element array dizisinde yoksa -1 döndürür
     */
    private int indexOf(T element) {
        for (var i = 0; i < size; i++){
            if (element == null && array[i] == null || element.equals(array[i])) {
                return i;
            }
        }
        return -1;
    }

    /**
     * removeAt metodu
     * @param index
     * indexi array dizisinden siler
     * eğer index array dizisinde yoksa hiçbir şey yapmaz
     */
    private void removeAt(int index) {
        if (index >= 0 && index < size) {
            System.arraycopy(array, index + 1, array, index, size - index - 1);
            array[--size] = null;
        }
    }


    private class CustomVectorIterator implements JavaIterator<T> {
        private int currentIndex;

        /**
         * hasNext metodu
         * @return boolean
         * eğer currentIndex size'dan küçükse true döndürür
         */
        @Override
        public boolean hasNext() {
            return currentIndex < size;
        }

        /**
         * next metodu
         * @return T
         * array dizisindeki elementi döndürür
         */
        @SuppressWarnings("unchecked")
        @Override
        public T next() {
            return (T) array[currentIndex++];
        }
    }

    /**
     * toString metodu
     * @return String
     * array dizisini stringe çevirir
     * örneğin: [1, 2, 3, 4, 5]
     * override toString metodu Object sınıfından override edilmiştir
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder("[");
        for (var i = 0; i < size; i++){
            sb.append(array[i]);
            if (i != size - 1) {
                sb.append(", ");
            }
        }
        sb.append("]");
        return sb.toString();
    }

    /**
     * equals metodu
     * @param obj alınan obje
     * @return boolean
     * obj CustomVector sınıfından değilse false döndürür
     * obj CustomVector sınıfından ise obj'nin size'ı bu CustomVector'ün size'ına eşit değilse false döndürür
     * obj CustomVector sınıfından ise obj'nin array dizisinin elemanları bu CustomVector'ün array dizisinin elemanlarına eşit değilse false döndürür
     * obj CustomVector sınıfından ise obj'nin size'ı bu CustomVector'ün size'ına ve obj'nin array dizisinin elemanları bu CustomVector'ün array dizisinin elemanlarına eşitse true döndürür
     * override equals metodu Object sınıfından override edilmiştir 
     */
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof CustomVector)) return false;
        CustomVector<?> customVector = (CustomVector<?>) obj;
        if (size != customVector.size) return false;
        for (int i = 0; i < size; i++) {
            if (array[i] == null && customVector.array[i] == null || array[i].equals(customVector.array[i])) {
                continue;
            }
            return false;
        }
        return true;
    }
}