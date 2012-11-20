import java.awt.geom.Point2D;
import java.awt.geom.Line2D;
import java.awt.geom.Ellipse2D;
import java.awt.Shape;

public class Edge {
    private Edge _next;
    private Vertex _orig;
    private Vertex _dest;
    private int _value;
    private double _radius;
    private int _distance;

    public Edge(Vertex orig, Vertex dest, int value) {
        _next = null;
        _orig = orig;
        _dest = dest;
        _value = value;
    }

    public Edge getNext() {
        return _next;
    }

    public void setNext(Edge next) {
        _next = next;
    }

    public Vertex getOrig() {
        return _orig;
    }

    public Vertex getDest() {
        return _dest;
    }

    public double getRadius() {
        return _radius;
    }

    public void setRadius(double radius) {
        _radius = radius;
    }

    public int getValue() {
        return _value;
    }

    public void setDistance(int distance) {
        _distance = distance;
    }

    public int getDistance() {
        return _distance;
    }

    public Shape getShape(Point2D center) {
        return new Line2D.Double(
                                    center.getX() 
                                        + _orig.getPosition().getX()
                                        + _orig.getRadius(),
                                    center.getY() 
                                        + _orig.getPosition().getY()
                                        + _orig.getRadius(),
                                    center.getX() 
                                        + _dest.getPosition().getX()
                                        + _dest.getRadius(),
                                    center.getY() 
                                        + _dest.getPosition().getY()
                                        + _dest.getRadius()
                                    );
    }
}

