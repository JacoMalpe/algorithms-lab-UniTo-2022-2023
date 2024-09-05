package src.Graph;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.text.DecimalFormat;
import java.util.*;


import src.Edge.*;
import src.PriorityQ.PriorityQueue;

import java.io.*;

public class Prim {
    public static final double INFINITY = Double.POSITIVE_INFINITY;

    public static class Node<V, L extends Number> implements Comparable<Node<V, Double>> {
        private V vertex;
        private V parent;
        private L key;

        public Node(V vertex, V parent, L key) {
            this.vertex = vertex;
            this.parent = parent;
            this.key = key;
        }

        public Node(V vertex) {
            this.vertex = vertex;
            this.parent = null;
            this.key = null;
        }

        public L getKey(){
            return key;
        }

        @Override
        public int compareTo(Node n) {
            if(n.key == null)
                return -1;
            if(this.key == null)
                return 1;
            return java.lang.Double.compare(this.key.doubleValue(), n.key.doubleValue());
        }

        @Override
        public boolean equals(Object n) {
            if (this == n)
                return true;
            if (n == null)
                return false;
            if(!(n instanceof Node<?, ?> nVertex))
                return false;
            return this.vertex.equals(nVertex.vertex);
        }

        @Override
        public int hashCode() {
            return Objects.hash(vertex);
        }
    }

    public static Graph<String, Double> graphLoader(String filename, boolean directed, boolean labelled) throws NumberFormatException {
        Graph<String, Double> graph = new Graph<>(directed, labelled);
        try (Scanner scanner = new Scanner(Files.newBufferedReader(Paths.get(filename)))) {

            while (scanner.hasNext()) {
                String line = scanner.nextLine();
                String[] fields = line.split(",");

                if (fields.length != 3) {
                    throw new IllegalArgumentException("Formato CSV non valido: " + line);
                }

                String start = fields[0].trim();
                String end = fields[1].trim();
                Double distance = Double.valueOf(fields[2].trim());

                graph.addNode(start);
                graph.addNode(end);
                graph.addEdge(start, end, distance);
            }
        } catch (IOException e) {
            System.err.println("Errore durante l'apertura del file: " + filename);
            e.printStackTrace();
            return null;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
        return graph;
    }

    public static <V, L extends Number> Collection<? extends AbstractEdge<V, L>> minimumSpanningForest(Graph<V, L> graph){
        if(!graph.isLabelled()) {
            System.out.println("Il grafo deve essere etichettato\n");
            return null;
        }

        Graph<V, L> msf = new Graph<>(false, true);
        HashMap<V, Double> map = new HashMap<>();
        src.PriorityQ.PriorityQueue<Node<V, L>> q = new PriorityQueue<>(Node::compareTo);
        for(V vertex : graph.getNodes()){
            Node<V, L> u = new Node<>(vertex);
            q.push(u);
            map.put(vertex, INFINITY);
        }

        while(!q.empty()){
            Node<V, L> u = q.top();
            q.pop();
            msf.addNode(u.vertex);
            if (u.parent != null)
                msf.addEdge(u.parent, u.vertex, u.key);
            for(V v : graph.getNeighbours(u.vertex)){
                Node<V, L> vNode = new Node<>(v);
                if(q.contains(vNode) && (Double.compare(graph.getLabel(u.vertex, v).doubleValue(), map.get(v)) < 0)){
                    vNode.parent = u.vertex;
                    vNode.key = graph.getLabel(u.vertex, v);
                    q.increasePriority(vNode);
                    map.put(v, graph.getLabel(u.vertex, v).doubleValue());
                }
            }
        }

        return msf.getEdges();
    }



    public static void main(String[] args) throws IOException {
        Graph<String, Double> graph = graphLoader("/Users/jacopo/UNI/Anno 2/ASD/laboratorio-algoritmi-2022-2023/ex3-4/data/italian_dist_graph.csv", false, true);
        if (graph == null) throw new NullPointerException("Graph was not loaded correctly\n");
        Collection<? extends AbstractEdge<String, Double>> msf = minimumSpanningForest(graph);
        if (msf == null) throw new NullPointerException("Msf is null\n");

        double weight = 0;
        for(AbstractEdge<String, Double> edge : msf)
            weight += edge.getLabel();

        PrintWriter pw = new PrintWriter(new OutputStreamWriter(System.out));
        DecimalFormat df = new DecimalFormat(".###");

        for (AbstractEdge<String, Double> edge : msf) {
            String formattedLabel = df.format(edge.getLabel());
            pw.println(edge.getStart() + "," + edge.getEnd() + "," + formattedLabel);
        }

        pw.flush();

        System.err.printf("Num edges: %d | Expected: 18637\n", msf.size() / 2);
        System.err.printf("Weight: %.3f km | Expected ~ 89939,913 Km\n", weight / 1000 / 2);
    }

}

