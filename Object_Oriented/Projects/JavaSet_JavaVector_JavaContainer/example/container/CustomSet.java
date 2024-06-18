// Dosya Adı: CustomSet.java
package example.container;

/**
 * CustomSet
 * @param <T> generic tip
 */
public class CustomSet<T> {
    private static final int DEFAULT_CAPACITY = 10;

    /**
     * array dizisi ve size değişken
     */
    private Object[] array;
    private int size;
    

    /**
     * CustomSet constructor
     * array dizisini ve size değişkenini oluşturur
     */
    public CustomSet() {
        array = new Object[DEFAULT_CAPACITY];
        size = 0;
    }

    /**
     * add metodu
     * @param element
     * elementi array dizisine ekler
     * eğer array dizisinin boyutu dolmuşsa boyutunu 2 katına çıkarır ensureCapacity metodu ile
     */
    public void add(T element) {
        if (!contains(element)) {
            ensureCapacity();
            array[size++] = element;
        }
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
     * @return iterator nesnesi
     */
    public JavaIterator<T> iterator() {
        return new CustomSetIterator();
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
     * @return index
     * elementin array dizisindeki indexini döndürür
     * eğer element array dizisinde yoksa -1 döndürür
     */
    private int indexOf(T element) {
        for (var i = 0; i < size; i++) {
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

    /**
     * contains metodu
     * @param element
     * @return boolean
     * element array dizisinde varsa true yoksa false döndürür
     */
    private boolean contains(T element) {
        for (var i = 0; i < size; i++) {
            if (element == null && array[i] == null || element.equals(array[i])) {
                return true;
            }
        }
        return false;
    }

    /**
     * indexBul metodu
     * @param index index işte
     * @return T
     * indexin array dizisindeki karşılığını döndürür
     * eğer index array dizisinde yoksa null döndürür
     */
    @SuppressWarnings("unchecked")
    public T indexBul(int index) {
        if (index >= 0 && index < size) {
            return (T) array[index];
        }
        return null;
    }

    /**
     * CustomSetIterators
     */
    private class CustomSetIterator implements JavaIterator<T> {
        private int currentIndex;

        @Override
        public boolean hasNext() {
            return currentIndex < size;
        }

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
     */
    @Override
    public String toString() {
        StringBuilder sb = new StringBuilder();
        sb.append("[");
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
     * obj CustomSet sınıfından değilse false döndürür
     * obj CustomSet sınıfından ise obj'nin size'ı bu sınıfın size'ına eşit değilse false döndürür
     * obj CustomSet sınıfından ise obj'nin elementleri bu sınıfın elementlerine eşit değilse false döndürür
     * obj CustomSet sınıfından ise obj'nin elementleri bu sınıfın elementlerine eşitse true döndürür
     */
    @Override
    public boolean equals(Object obj) {
        if (this == obj) return true;
        if (!(obj instanceof CustomSet)) return false;
        CustomSet<?> customSet = (CustomSet<?>) obj;
        if (size != customSet.size) return false;
        for (int i = 0; i < size; i++) {
            if (array[i] == null && customSet.array[i] == null || array[i].equals(customSet.array[i])) {
                continue;
            }
            return false;
        }
        return true;
    }
}