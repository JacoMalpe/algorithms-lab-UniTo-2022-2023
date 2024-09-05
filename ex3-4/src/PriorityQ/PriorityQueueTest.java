package src.PriorityQ;

import java.util.Comparator;
import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertFalse;
import static org.junit.Assert.assertNull;
import static org.junit.Assert.assertTrue;
import org.junit.Before;
import org.junit.Test;


public class PriorityQueueTest {

  class IntegerComparator implements Comparator<Integer> {
    @Override
    public int compare(Integer i1, Integer i2) {
      return i1.compareTo(i2);
    }
  }

  private Integer i1,i2,i3;
  private PriorityQueue<Integer> pq;

  @Before
  public void createPriorityQueue() {
    i1 = -7;
    i2 = 1;
    i3 = 93;
    pq = new PriorityQueue<>(new IntegerComparator());
  }

  @Test
  public void testEmpty_zeroEl(){
    assertTrue(pq.empty());
  }

  @Test
  public void testEmpty_oneEl() throws Exception{
    pq.push(i1);
    assertFalse(pq.empty());
  }

  @Test
  public void testPush_oneEl() throws Exception{
    assertTrue(pq.push(i1));
  }

  @Test
  public void testPush_threeEl() throws Exception{
    assertTrue(pq.push(i1));
    assertTrue(pq.push(i2));
    assertTrue(pq.push(i3));
  }

  @Test
  public void testContains_zeroEl() throws Exception{
    assertFalse(pq.contains(i1));
  }

  @Test
  public void testContains_ElPresent() throws Exception{
    pq.push(i1);
    assertTrue(pq.contains(i1));
  }

  @Test
  public void testContains_ElNotPresent() throws Exception{
    pq.push(i1);
    assertFalse(pq.contains(i2));
  }

  @Test
  public void testTop_zeroEl() throws Exception{
    assertNull(pq.top());
  }

  @Test
  public void testTop_threeEl() throws Exception{
    pq.push(i1);
    pq.push(i2);
    pq.push(i3);

    pq.pop();
    assertEquals(i2, pq.top());
    pq.pop();
    assertEquals(i3, pq.top());
  }

  @Test
  public void testPop_El() throws Exception{
    pq.push(i1);
    pq.pop();
    assertFalse(pq.contains(i1));
  }

  @Test
  public void testPop_threeEl() throws Exception{
    pq.push(i1);
    pq.push(i2);
    pq.push(i3);
    pq.pop();
    pq.pop();
    pq.pop();

    assertFalse(pq.contains(i1));
    assertFalse(pq.contains(i2));
    assertFalse(pq.contains(i3));
    assertTrue(pq.empty());
  }

  @Test
  public void testRemove_El() throws Exception{
    pq.push(i1);
    pq.pop();
    assertFalse(pq.contains(i1));
  }

  @Test
  public void testRemove_threeEl() throws Exception{
    pq.push(i1);
    pq.push(i2);
    pq.push(i3);

    assertTrue(pq.remove(i2));
    assertTrue(pq.remove(i3));
    assertTrue(pq.remove(i1));
    assertTrue(pq.empty());
  }

}
