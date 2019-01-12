
import java.awt.event.MouseEvent;
import java.awt.Color;
import java.awt.Graphics;
import java.util.Random;

public class LineTool implements AnyTool 
{
  private int x0, y0, x1, y1;
  private int status;
  private Color cor;

  /** Creates new LineTool */
  public LineTool()
  {
    x0 = y0 = x1 = y1 = 0;
    cor=Color.BLACK;
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
      status=-1;//
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
    g.setColor(cor);
    g.setPaintMode();
    g.drawLine(x0, y0, x, y);

  }
  public void changeColor(){
      int x=aleatorio(254);      
      int y=aleatorio(254);
      int z=aleatorio(254);
      cor=new Color(x,y,z);
  }
      /**
     * Fun��o para gerar um valor inteiro aleat�rio entre 1 e mod
     * @param mod Valor m�ximo da gama de valores possiveis que podem ser gerados
     * @return Um inteiro compreendido entre 1 e mod
     */
  private int aleatorio (int mod){
     long x=System.currentTimeMillis();
     //Para fazer com que o Random ocorra em diferentes milisegundos
     //para gerar valores diferentes na mesma execu��o
     while(true){
        if (System.currentTimeMillis()!=x) break;
        }
        Random alea = new Random(System.currentTimeMillis());
        return 1+Math.abs(alea.nextInt()) % mod;
    }
}

