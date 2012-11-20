import java.awt.geom.Point2D;
import java.awt.geom.Ellipse2D;
import java.awt.Shape;
import java.awt.Color;
class Vertex {
    private Vertex _next;
    private Edge _root;
    private String _name;
    private Point2D _position;
    private double _radius;
    private int _distance;
    private boolean _visited;
    private Color _color;

    public Vertex() {
        _next = null;
        _root = null;
        _name = "";
        _position = null;
        _radius = 0;
        _color = null;
    }

    public void connect(Vertex dest, int value) {
        Edge thisToDest = new Edge(this, dest, value);
        Edge destToThis = new Edge(dest, this, value);
        if(null == getRoot()) {
            setRoot(thisToDest);
        } else {
            Edge tmp = getRoot();
            while(null != tmp.getNext()) {
                tmp = tmp.getNext();
            }
            tmp.setNext(thisToDest);
        }
        if(null == dest.getRoot()) {
            dest.setRoot(destToThis);
        } else {
            Edge tmp = dest.getRoot();
            while(null != tmp.getNext()) {
                tmp = tmp.getNext();
            }
            tmp.setNext(destToThis);
        }
    }

    public Vertex getNext() {
        return _next;
    }

    public void setNext(Vertex next) {
        _next = next;
    }

    public Edge getRoot() {
        return _root;
    }

    public void setRoot(Edge root) {
        _root = root;
    }

    public String getName() {
        return _name;
    }

    public void setName(String name) {
        _name = name;
    }

    public Point2D getPosition() {
        return _position;
    }

    public void setPosition(Point2D position) {
        _position = position;
    }

    public double getRadius() {
        return _radius;
    }

    public void setRadius(double radius) {
        _radius = radius;
    }

    public int getDistance() {
        return _distance;
    }

    public void setDistance(int distance) {
        _distance = distance;
    }

    public boolean getVisited() {
        return _visited;
    }

    public void setVisited(boolean visited) {
        _visited = visited;
    }

    public Color getColor() {
        return _color;
    }

    public void setColor(Color color) {
        _color = color;
    }

    public Shape getShape(Point2D center) {
        return new Ellipse2D.Double(
                                        center.getX() + _position.getX(),
                                        center.getY() + _position.getY(),
                                        2*_radius,
                                        2*_radius
                                        );
    }
}
