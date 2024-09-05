package src.Edge;

public class Edge<V,L> implements AbstractEdge<V,L>{

    private V start;
    private V end;
    private L label;

    public Edge(V start, V end, L label) {
        this.start = start;
        this.end = end;
        this.label = label;
    }

    /**
     * @return the starting node
     */
    @Override
    public V getStart() {
        return start;
    }

    /**
     * @return the ending node
     */
    @Override
    public V getEnd() {
        return end;
    }

    /**
     * @return the label
     */
    @Override
    public L getLabel() {
        return label;
    }
}

