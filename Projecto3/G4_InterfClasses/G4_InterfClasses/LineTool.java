
import java.awt.event.MouseEvent;
import java.awt.Color;
import java.awt.Graphics;

public class LineTool implements AnyTool 
{
  private int x0, y0, x1, y1;
  private int status;

  /** Creates new LineTool */
  public LineTool()
  {
    x0 = y0 = x1 = y1 = 0;
  }

  public void startTool()
  {
    /* Esta função é chamada quando se selecciona a ferramenta "Line",
     * ou seja, quando se carrega no botão "Line".
     * Neste caso particular, a inicialização a fazer e'
       definir o estado em Zero */
      
      status=0;
  }

  public void stopTool()
  {
   /* Esta função é chamada quando por exemplo se selecciona outra ferramenta.
     * Neste caso particular, não há terminações a fazer */ 
  }

  public void mousePressed(Graphics g,java.awt.event.MouseEvent evt)
  {
      switch(status)
      {
          case (0):
              beginLine(g, evt.getX(), evt.getY());
              status = 1;
              break;
          default:
              break;
      }
  }

  public void mouseMoved(Graphics g,java.awt.event.MouseEvent evt)
  {
  }

  public void mouseDragged(Graphics g,java.awt.event.MouseEvent evt)
  {
      switch(status)
      {
          case (1):
              rubberP1Line(g, evt.getX(), evt.getY());
              status = 1; // nao e' necessario...
              break;
          default:
              break;
      }
  }

  public void mouseReleased(Graphics g,java.awt.event.MouseEvent evt)
  {
      switch(status)
      {
          case (1):
              endLine(g, evt.getX(), evt.getY());
              status = 0;
              break;
          default:
              break;
      }
  }

  public void mouseDoubleClicked(Graphics g,java.awt.event.MouseEvent evt)
  {
  }

  public void mouseClicked(Graphics g,java.awt.event.MouseEvent evt)
  {
  }

  private void beginLine(Graphics g, int x, int y)
  {
    x0 = x; y0 = y;
    x1 = x; y1 = y;
    g.setXORMode(Color.white);
    g.drawLine(x0, y0, x1, y1);
  }

  private void rubberP1Line(Graphics g, int x, int y)
  {
    g.setXORMode(Color.white);
    g.drawLine(x0, y0, x1, y1);
    x1 = x; y1 = y;
    g.drawLine(x0, y0, x1, y1);
  }

  private void endLine(Graphics g, int x, int y)
  {
    g.setXORMode(Color.white);
    g.drawLine(x0, y0, x1, y1);
    g.setColor(Color.black);
    g.setPaintMode();
    g.drawLine(x0, y0, x, y);

  }
}

