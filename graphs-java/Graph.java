import java.util.List;
import java.util.ArrayList;
import java.awt.Color;

public class Graph {

    private Vertex _root;
    private int _count;

    public Vertex getRoot() {
        return _root;
    }

    public void setRoot(Vertex root) {
        _root = root;
    }

    public void insert(Vertex vertex) {
        if(null == getRoot()) {
            setRoot(vertex);
        } else {
            Vertex tmp = getRoot();
            while(null != tmp.getNext()) {
                tmp = tmp.getNext();
            }
            tmp.setNext(vertex);
        }
        _count++;
    }

    public void connect(Vertex a, Vertex b, int value) {
        a.connect(b, value);
    }

    public int getCount() {
        return _count;
    }

    public List<Vertex> dijkstra(Vertex a, Vertex b) {
        List<Vertex> visited = new ArrayList<Vertex>();
        List<Vertex> unvisited = new ArrayList<Vertex>();
        List<Vertex> shortestPath = new ArrayList<Vertex>();
        if(null == getRoot()) {
            return shortestPath;
        } else {
            Vertex tmp = getRoot();
            while(null != tmp) {
                tmp.setVisited(false);
                tmp.setDistance(99999999);
                unvisited.add(tmp);
                tmp = tmp.getNext();
            }
        }
        a.setDistance(0);
        Vertex current = a;
        while(null != current) {
            for(Vertex v: unvisited) {
                Edge tmp;
                for(tmp = current.getRoot(); tmp != null; tmp = tmp.getNext()) {
                    if(tmp.getDest().equals(v)) {
                        int t = current.getDistance() + tmp.getValue();
                        if(t < tmp.getDest().getDistance()) {
                            tmp.getDest().setDistance(t);
                        }
                    }
                }
            }
            current.setVisited(true);
            visited.add(current);
            unvisited.remove(current);
            int min = -1;
            Vertex minv = null;
            for(Vertex v : unvisited) {
                if(0 > min) {
                    min = v.getDistance();
                    minv = v;
                } else if(v.getDistance() < min) {
                    min = v.getDistance();
                    minv = v;
                }
            }
            current = minv;
        }
        Edge edge;
        int min = -1;
        Vertex minv = null;
        current = a;
        int mina = -1;
        while(!b.equals(current)) {
            min = -1;
            for(edge = current.getRoot(); edge != null; edge = edge.getNext()) {
                if(0 > min) {
                    min = edge.getDest().getDistance();
                    minv = edge.getDest();
                } else if(edge.getDest().getDistance() > mina && min > edge.getDest().getDistance()) {
                    min = edge.getDest().getDistance();
                    minv = edge.getDest();
                }
            }
            shortestPath.add(current);
            current = minv;
            mina =  min;
        }
        shortestPath.add(current);
        return shortestPath;
    }
}
