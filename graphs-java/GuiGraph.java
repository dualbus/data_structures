import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.JTextField;
import javax.swing.BoxLayout;
import javax.imageio.ImageIO;
import java.awt.BorderLayout;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.geom.Point2D;
import java.awt.geom.Line2D;
import java.awt.geom.Ellipse2D;
import java.awt.Dimension;
import java.awt.Image;
import java.awt.image.BufferedImage;
import java.lang.Math;
import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.IOException;
import java.util.List;
import java.util.ArrayList;
import java.awt.Color;
import java.awt.Paint;
import java.awt.Shape;

public class GuiGraph {
    private static final double VX_RAD = 15;
    private JFrame _frame;
    private GuiCanvas _canvas;
    private Graph _graph;
    private JPanel _pane;
    private JButton _buttonInsert;
    private JButton _buttonConnect;
    private JButton _buttonCalculate;
    private JTextField _textValue;
    private boolean _connect;
    private boolean _dijkstra;
    private BufferedImage _image;

    public GuiGraph() {
        _image = null;
        try {
            _image = ImageIO.read(new File("Croquis.png"));
        } catch (IOException e) {
        }
        _graph = new Graph();
        _buttonInsert = new JButton("Insertar");
        _buttonInsert.addActionListener(new ButtonInsertListener());
        _buttonConnect = new JButton("Conectar");
        _buttonConnect.addActionListener(new ButtonConnectListener());
        _buttonCalculate = new JButton("Calculare");
        _buttonCalculate.addActionListener(new ButtonCalculateListener());
        _textValue = new JTextField(5);
        _textValue.setPreferredSize(new Dimension(20, 20));
        _canvas = new GuiCanvas();
        _canvas.setPreferredSize(new Dimension(750, 600));
        _canvas.addMouseListener(_canvas);
        _canvas.addMouseMotionListener(_canvas);
        _canvas.addMouseListener(new ButtonConnectMotion());
        _canvas.addMouseListener(new ButtonCalculateMotion());
        _pane = new JPanel();
        _pane.setLayout(new BoxLayout(_pane, BoxLayout.PAGE_AXIS));
        _frame = new JFrame("GraphicGraph");
        _frame.setSize(800, 600);
        _frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        _pane.add(_buttonInsert);
        _pane.add(_buttonConnect);
        _pane.add(_textValue);
        _pane.add(_buttonCalculate);
        _pane.add(_canvas);
        _frame.getContentPane().add(_pane);
        _frame.setVisible(true);
    }

    private class GuiCanvas extends JPanel implements MouseListener, MouseMotionListener {
        private Vertex _lastDragged;

        public GuiCanvas() {
            _lastDragged = null;
        }

        public void paint(Graphics g) {
            super.paintComponent(g);

            int i, count;
            Vertex tmp;
            double slice, cx, cy, r;
            Dimension panel;
            Graphics2D g2 = (Graphics2D)g;
            Point2D center;

            g2.setPaint(Color.black);
            g2.drawImage(_image, 0, 0, null);
            count = _graph.getCount();
            slice = (2 * Math.PI) / count;
            panel = getSize();
            cx = panel.getWidth() / 2;
            cy = panel.getHeight() / 2;
            r = (cx < cy) ? cx / 2 : cy / 2;
            center = new Point2D.Double(cx, cy);

            for(i = 0, tmp = _graph.getRoot(); null != tmp; i++, tmp =
                    tmp.getNext()) {
                if(null == tmp.getPosition()) {
                    double x, y;
                    x = r * Math.cos(i * slice);
                    y = r * Math.sin(i * slice);
                    tmp.setPosition(new Point2D.Double(x - VX_RAD, y - VX_RAD));
                }
            }

            Paint paint = null;
            for(i = 0, tmp = _graph.getRoot(); null != tmp; i++, tmp =
                    tmp.getNext()) {
                Point2D position;
                double x, y;
                Edge etmp;
                if(null != tmp.getColor()) {
                    paint = g2.getPaint();
                    g2.setPaint(tmp.getColor());
                }
                Shape s = tmp.getShape(center);
                g2.fill(s);
                g2.draw(s);
                if(null != paint) {
                    g2.setPaint(paint);
                    paint = null;
                }
                for(etmp = tmp.getRoot(); null != etmp; etmp = etmp.getNext()) {
                    g2.draw(etmp.getShape(center));
                }
            }
        }

        public void mouseMoved(MouseEvent e) {}
        public void mouseDragged(MouseEvent e) {
            int i;
            Vertex tmp;
            Point2D mouse, center;
            double cx, cy;
            Dimension panel;
            panel = getSize();
            cx = panel.getWidth() / 2;
            cy = panel.getHeight() / 2;
            mouse = new Point2D.Double(e.getX(), e.getY());
            if(null == _lastDragged) {
                for(i = 0, tmp = _graph.getRoot(); null != tmp; i++, tmp =
                        tmp.getNext()) {
                    center = tmp.getPosition();
                    center = new Point2D.Double(cx + (center.getX() + VX_RAD), 
                                                    cy + (center.getY() + VX_RAD));
                    if(inCircle(center, VX_RAD, mouse)) {
                        _lastDragged = tmp;
                    }
                }
            }

            if(null != _lastDragged) {
                _lastDragged.setPosition(new Point2D.Double((mouse.getX() - VX_RAD) -
                    cx, (mouse.getY() - VX_RAD) - cy));
                repaint();
            }
        }
        public void mouseClicked(MouseEvent e) {}
        public void mouseEntered(MouseEvent e) {}
        public void mouseExited(MouseEvent e) {}
        public void mousePressed(MouseEvent e) {}
        public void mouseReleased(MouseEvent e) {
            _lastDragged = null;
        } 
    }

    private class ButtonInsertListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            Vertex v = new Vertex();
            v.setName("a");
            v.setRadius(VX_RAD);
            _graph.insert(v);
            v.setPosition(new Point2D.Double(0,0));
            _pane.repaint();
        }
    }

    private class ButtonConnectListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            _connect = true;
        }
    }

    private class ButtonCalculateListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            _dijkstra = true;
        }
    }

    private class ButtonConnectMotion implements MouseListener {
        private Vertex _somefoo;

        public ButtonConnectMotion() {
            _somefoo = null;
        }

        public void mouseClicked(MouseEvent e) {}
        public void mouseEntered(MouseEvent e) {}
        public void mouseExited(MouseEvent e) {}
        public void mousePressed(MouseEvent e) {}
        public void mouseReleased(MouseEvent e) {
            if(_connect) {
                int i;
                Vertex tmp;
                Point2D mouse, center;
                double cx, cy;
                Dimension panel;
                panel = _canvas.getSize();
                cx = panel.getWidth() / 2;
                cy = panel.getHeight() / 2;
                mouse = new Point2D.Double(e.getX(), e.getY());
                if(null == _somefoo) {
                    for(i = 0, tmp = _graph.getRoot(); null != tmp; i++, tmp =
                            tmp.getNext()) {
                        center = tmp.getPosition();
                        center = new Point2D.Double(cx + (center.getX() + VX_RAD), 
                                                        cy + (center.getY() + VX_RAD));
                        if(inCircle(center, VX_RAD, mouse)) {
                            _somefoo = tmp;
                        }
                    }
                } else {
                    for(i = 0, tmp = _graph.getRoot(); null != tmp; i++, tmp =
                            tmp.getNext()) {
                        center = tmp.getPosition();
                        center = new Point2D.Double(cx + (center.getX() + VX_RAD), 
                                                        cy + (center.getY() + VX_RAD));
                        if(inCircle(center, VX_RAD, mouse)) {
                            int value = 0;
                            try {
                                value = Integer.parseInt(_textValue.getText());
                            } catch(Exception ex) {
                            }
                            if(!tmp.equals(_somefoo) && value > 0) {
                                _graph.connect(_somefoo, tmp, value);
                            }
                            _somefoo = null;
                            _connect = false;
                            _pane.repaint();
                        }
                    }
                }
            }
        } 
    }

    private class ButtonCalculateMotion implements MouseListener {
        private Vertex _somefoo;

        public ButtonCalculateMotion() {
            _somefoo = null;
        }

        public void mouseClicked(MouseEvent e) {}
        public void mouseEntered(MouseEvent e) {}
        public void mouseExited(MouseEvent e) {}
        public void mousePressed(MouseEvent e) {}
        public void mouseReleased(MouseEvent e) {
            if(_dijkstra) {
                int i;
                Vertex tmp;
                Point2D mouse, center;
                double cx, cy;
                Dimension panel;
                panel = _canvas.getSize();
                cx = panel.getWidth() / 2;
                cy = panel.getHeight() / 2;
                mouse = new Point2D.Double(e.getX(), e.getY());
                if(null == _somefoo) {
                    for(i = 0, tmp = _graph.getRoot(); null != tmp; i++, tmp =
                            tmp.getNext()) {
                        center = tmp.getPosition();
                        center = new Point2D.Double(cx + (center.getX() + VX_RAD), 
                                                        cy + (center.getY() + VX_RAD));
                        if(inCircle(center, VX_RAD, mouse)) {
                            _somefoo = tmp;
                        }
                    }
                } else {
                    for(i = 0, tmp = _graph.getRoot(); null != tmp; i++, tmp =
                            tmp.getNext()) {
                        center = tmp.getPosition();
                        center = new Point2D.Double(cx + (center.getX() + VX_RAD), 
                                                        cy + (center.getY() + VX_RAD));
                        if(inCircle(center, VX_RAD, mouse)) {
                            if(!tmp.equals(_somefoo)) {
                                List<Vertex> path = _graph.dijkstra(
                                                                        _somefoo,
                                                                        tmp);
                                for(Vertex v: path) {
                                    v.setColor(Color.green);
                                }
                            }
                            _somefoo = null;
                            _dijkstra = false;
                            _pane.repaint();
                        }
                    }
                }
            }
        } 
    }

    public static boolean inCircle(Point2D center, double radio, Point2D point) {
        double x2 = Math.pow(center.getX() - point.getX(), 2);
        double y2 = Math.pow(center.getY() - point.getY(), 2);
        return (Math.sqrt(x2 + y2) <= radio);
    }

    public static void main(String[] args) {
        new GuiGraph();
    }
}

