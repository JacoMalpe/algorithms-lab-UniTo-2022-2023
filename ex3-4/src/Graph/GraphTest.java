package src.Graph;

import org.junit.Before;
import org.junit.Test;

import static org.junit.Assert.*;

public class GraphTest {
    private char a, b, c;
    private Graph<Character, Integer> directed;
    private Graph<Character, Integer> not_directed;

    @Before
    public void createGraphs() {
        a = 'a';
        b = 'b';
        c = 'c';
        directed = new Graph<>(true, true);
        not_directed = new Graph<>(false, true);
    }

    @Test
    public void testIsDirected(){
        assertTrue(directed.isDirected());
        assertFalse(not_directed.isDirected());
    }

    @Test
    public void testIsLabelled(){
        assertTrue(directed.isLabelled());
        assertTrue(directed.isLabelled());
    }

    @Test
    public void testAddNode(){
        assertTrue(directed.addNode(a));
        assertFalse(directed.addNode(a));
        assertTrue(not_directed.addNode(a));
        assertTrue(not_directed.addNode(b));

        assertTrue(directed.containsNode(a));
        assertFalse(directed.containsNode(b));
    }

    @Test
    public void testAddEdge(){
        directed.addNode(a);
        directed.addNode(b);
        directed.addNode(c);
        not_directed.addNode(a);
        not_directed.addNode(b);
        not_directed.addNode(c);

        assertTrue(directed.addEdge(a, b, 5));
        assertTrue(directed.addEdge(b, a, 7));
        assertFalse(directed.addEdge(c, b, null));
        assertTrue(not_directed.addEdge(b, c, 1));
        assertFalse(not_directed.addEdge(c, b, 99));
        assertFalse(not_directed.addEdge(c, 'd', 0));
    }

    @Test
    public void testContainsNode(){
        directed.addNode(a);
        directed.addNode(b);
        directed.addNode(c);
        not_directed.addNode(a);
        not_directed.addNode(b);

        assertTrue(directed.containsNode(a));
        assertFalse(not_directed.containsNode(c));

        directed.removeNode(c);

        assertFalse(directed.containsNode(c));
    }

    @Test
    public void testContainsEdge(){
        directed.addNode(a);
        directed.addNode(b);
        directed.addNode(c);
        not_directed.addNode(a);
        not_directed.addNode(b);
        directed.addEdge(a, b, 5);
        not_directed.addEdge(a, b, 5);

        assertTrue(directed.containsEdge(a, b));
        assertFalse(not_directed.containsEdge(b, c));
        assertTrue(not_directed.containsEdge(b, a));

        not_directed.removeEdge(a, b);

        assertFalse(not_directed.containsEdge(b, a));
    }

    @Test
    public void testRemoveNode(){
        directed.addNode(a);
        directed.addNode(b);
        directed.addNode(c);
        not_directed.addNode(a);
        not_directed.addNode(b);
        directed.addEdge(a, b, 5);
        not_directed.addEdge(a, b, 5);

        assertTrue(directed.removeNode(a));
        assertTrue(not_directed.removeNode(a));
        assertFalse(not_directed.removeNode(c));

        assertFalse(directed.containsNode(a));
        assertFalse(not_directed.containsNode(a));
        assertFalse(not_directed.containsEdge(b, a));
        assertFalse(not_directed.containsEdge(a, b));
    }

    @Test
    public void testRemoveEdge(){
        directed.addNode(a);
        directed.addNode(b);
        directed.addNode(c);
        not_directed.addNode(a);
        not_directed.addNode(b);
        directed.addEdge(a, b, 5);
        directed.addEdge(a, c, null);
        not_directed.addEdge(a, b, 5);

        assertTrue(directed.removeEdge(a, b));
        assertFalse(directed.removeEdge(b, a));
        assertFalse(not_directed.removeEdge(a, c));
        assertTrue(not_directed.removeEdge(b, a));
        assertFalse(not_directed.removeEdge(a, b));

        assertFalse(directed.containsEdge(a, b));
        assertFalse(not_directed.containsEdge(a, b));
    }

    @Test
    public void testNumNodes(){
        assertEquals(0, directed.numNodes());

        directed.addNode(a);
        directed.addNode(b);
        directed.addNode(c);
        not_directed.addNode(a);
        not_directed.addNode(b);

        assertEquals(3, directed.numNodes());
        assertEquals(2, not_directed.numNodes());

        directed.removeNode(c);

        assertEquals(2, directed.numNodes());
    }

    @Test
    public void testNumEdges(){
        assertEquals(0, directed.numEdges());

        directed.addNode(a);
        directed.addNode(b);
        directed.addNode(c);
        not_directed.addNode(a);
        not_directed.addNode(b);
        directed.addEdge(a, b, 5);
        not_directed.addEdge(a, b, 5);

        assertEquals(1, directed.numEdges());
        assertEquals(1, not_directed.numEdges());

        directed.removeEdge(a, b);

        assertEquals(0, directed.numEdges());
    }

    @Test
    public void testGetNodes() {
        assertTrue(directed.getNodes().isEmpty());

        directed.addNode(a);
        directed.addNode(b);
        not_directed.addNode(a);
        not_directed.addNode(b);

        assertTrue(directed.getNodes().contains(a));
        assertFalse(directed.getNodes().contains(c));

        not_directed.removeNode(a);

        assertTrue(directed.getNodes().contains(b));
        assertFalse(not_directed.getNodes().contains(a));
    }

    @Test
    public void testGetEdges() {
        assertTrue(directed.getEdges().isEmpty());

        directed.addNode(a);
        directed.addNode(b);
        directed.addNode(c);
        not_directed.addNode(a);
        not_directed.addNode(b);
        directed.addEdge(a, b, 5);
        directed.addEdge(b, c, 5);
        not_directed.addEdge(a, b, 5);
        not_directed.addEdge(b, c, 5);

        assertEquals(2, directed.getEdges().size());
        assertEquals(2, not_directed.getEdges().size());

        directed.removeEdge(a, b);
        not_directed.removeNode(b);

        assertEquals(1, directed.getEdges().size());
        assertEquals(0, not_directed.getEdges().size());
    }


    @Test
    public void testGetNeighbours() {
        directed.addNode(a);
        directed.addNode(b);
        directed.addEdge(a, b, 5);

        assertTrue(directed.getNeighbours(a).contains(b));
        assertFalse(directed.getNeighbours(a).contains(a));

        directed.removeNode(b);

        assertTrue(directed.getNeighbours(a).isEmpty());
    }


    @Test
    public void testGetLabel() {
        directed.addNode(a);
        directed.addNode(b);
        directed.addEdge(a, b, 5);

        assertEquals((Object) 5, directed.getLabel(a, b));
        assertFalse(directed.getNeighbours(a).contains(a));

        directed.removeNode(b);

        assertTrue(directed.getNeighbours(a).isEmpty());
    }
}
