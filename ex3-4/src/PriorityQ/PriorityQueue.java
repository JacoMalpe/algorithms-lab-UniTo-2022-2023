package src.PriorityQ;
import src.Graph.Prim;

import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.Comparator;


public class PriorityQueue<E> implements AbstractQueue<E> {
    private ArrayList<E> heap;
    private Comparator<E> comparator;
    private Map<E, Integer> indexMap;

    public PriorityQueue(Comparator<E> comparator) {
        this.heap = new ArrayList<>();
        this.comparator = comparator;
        this.indexMap = new HashMap<>();
    }
    private int parent(int i){
        return (i - 1) / 2 ;
    }

    private int left(int i){
        return ((2 * i + 1) <= heap.size() - 1) ? (2 * i + 1) : i;
    }

    private int right(int i){
        return ((2 * i + 2) <= heap.size() - 1) ? (2 * i + 2) : i;
    }

    @Override
    public boolean empty() {
        return heap.isEmpty();
    }

    @Override
    public boolean push(E e) {
    if (e == null) {
        throw new NullPointerException("Element cannot be null");
    }
    if (contains(e)) {
        throw new IllegalArgumentException("Duplicate element");
    }
    heap.add(e);
    int i = heap.size() - 1;
    indexMap.put(e, i);
    heapifyUp(i);
    return true;
    }


    @Override
    public boolean contains(E e) {
        return indexMap.containsKey(e);
    }

    @Override
    public E top() {
        if (empty()) {
            return null;
        }
        return heap.get(0);
    }

    @Override
    public void pop() {
        if (empty()) {
            return;
        }
        int lastIndex = heap.size() - 1;
        swap(0, lastIndex);
        E removedElement = heap.remove(lastIndex);
        indexMap.remove(removedElement);
        heapifyDown(0);
    }

    @Override
    public boolean remove(E e) {
        Integer index = indexMap.get(e);
        if (index == null) {
            return false;
        }
        int lastIndex = heap.size() - 1;
        if (index != lastIndex) {
            swap(index, lastIndex);
            heap.remove(lastIndex);
            indexMap.remove(e);
            heapifyUp(index);
            heapifyDown(index);
        } else {
            heap.remove(lastIndex);
            indexMap.remove(e);
        }
        return true;
    }

    private void heapifyDown(int i){
        int m = min(i);
        if(m != i){
            swap(m, i);
            heapifyDown(m);
        }
    }
//
    private void heapifyUp(int i){
        while(i > 0 && comparator.compare(heap.get(i), heap.get(parent(i))) < 0) {
            swap(i, parent(i));
            i = parent(i);
        }
    }
    
      private int min(int i){
        int l = left(i);
        int r = right(i);
        if(l == r)
            return i;

        E min = heap.get(i);
        int ret = i;
        if(l != i)
            if(comparator.compare(heap.get(l), heap.get(i)) < 0){
                min = heap.get(l);
                ret = l;
            }
        if(r != i)
            if (comparator.compare(heap.get(r), min) < 0)
                return r;

        return ret;
    }

    public void increasePriority(E elem){
        remove(elem);
        push(elem);
    }

    private void swap(int i, int j) {
        E temp = heap.get(i);
        heap.set(i, heap.get(j));
        heap.set(j, temp);
        indexMap.put(heap.get(i), i);
        indexMap.put(heap.get(j), j);
    }

}