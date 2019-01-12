/*
 * MyCanvas.java
 *
 /*
 * MyCanvas.java
 *
 * Created on 22 de Janeiro de 2003, 16:31
 */

/**
 *
 * @author  barbosa
 */
 
import java.awt.Graphics;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.event.MouseEvent;
import javax.swing.SwingUtilities;
import javax.swing.*;

public class MyCanvas extends JPanel {

  DrawArea drawArea;
  
  /** Creates new XORCanvas */
  public MyCanvas(DrawArea d) {
    drawArea = d;
    this.setBackground(new Color(255,255,255));
    addMouseListener(new java.awt.event.MouseAdapter () {
        public void mousePressed (java.awt.event.MouseEvent evt) {
          myCanvasMousePressed (evt);
        }
        public void mouseReleased (java.awt.event.MouseEvent evt) {
          myCanvasMouseReleased (evt);
        }
        public void mouseClicked (java.awt.event.MouseEvent evt) {
          myCanvasMouseClicked (evt);
        }
      }
      );

    addMouseMotionListener(new java.awt.event.MouseMotionAdapter () {
        public void mouseMoved (java.awt.event.MouseEvent evt) {
          myCanvasMouseMoved (evt);
        }
        public void mouseDragged (java.awt.event.MouseEvent evt) {
          myCanvasMouseDragged (evt);
        }
      }
      );
  }
  
  private void myCanvasMousePressed(java.awt.event.MouseEvent evt) {
// Add your handling code here:
    if( SwingUtilities.isLeftMouseButton(evt))
    {
      drawArea.drawProg.getToolSelected().mousePressed(this.getGraphics(), evt);
    }
  }
  
  private void myCanvasMouseReleased(java.awt.event.MouseEvent evt) {
// Add your handling code here:
    if( SwingUtilities.isLeftMouseButton(evt))
    {
      drawArea.drawProg.getToolSelected().mouseReleased(this.getGraphics(), evt);
    }
  }
  
  private void myCanvasMouseClicked(java.awt.event.MouseEvent evt) {
// Add your handling code here:
    if( SwingUtilities.isLeftMouseButton(evt))
    {
      if(evt.getClickCount() == 1 )
         drawArea.drawProg.getToolSelected().mouseClicked(this.getGraphics(), evt);
      else if(evt.getClickCount() == 2 )
        drawArea.drawProg.getToolSelected().mouseDoubleClicked(this.getGraphics(), evt);
    }
  }
  
  private void myCanvasMouseMoved(java.awt.event.MouseEvent evt) {
// Add your handling code here:
    drawArea.drawProg.setTexto(evt.getX(),evt.getY());
    drawArea.drawProg.getToolSelected().mouseMoved(this.getGraphics(), evt);
    
  }
  
  private void myCanvasMouseDragged(java.awt.event.MouseEvent evt) {
// Add your handling code here:
    
    drawArea.drawProg.setTexto(evt.getX() , evt.getY());
    if( SwingUtilities.isLeftMouseButton(evt))
    {
      drawArea.drawProg.getToolSelected().mouseDragged(this.getGraphics(), evt);
    }
  }
  
}