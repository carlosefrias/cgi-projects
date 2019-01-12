
import java.awt.event.MouseEvent;
import java.awt.Color;
import java.awt.Graphics;
import java.util.Random;
public class RectTool implements AnyTool 
{
  private Color cor=Color.BLACK;
  private int x0, y0, x1, y1;
  private int status;
  public RectTool()
  {
    x0=x1=y0=y1=0;
  }

  public void startTool()
  {
      status=0;
  }

  public void stopTool()
  {
     
  }

  public void mousePressed(Graphics g,java.awt.event.MouseEvent evt)
  {
      switch(status)
      {
          case (0):
              beginRect(g, evt.getX(), evt.getY());
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
              rubberP1Rect(g, evt.getX(), evt.getY());
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
              endRect(g, evt.getX(), evt.getY());
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

  private void beginRect(Graphics g, int x, int y)
  {
    x0 = x; y0 = y;
    x1 = x; y1 = y;
    g.setXORMode(Color.white);
    g.drawLine(x0, y0, x0, y1);
    g.drawLine(x0, y0, x1, y0);
    g.drawLine(x1, y0, x1, y1);
    g.drawLine(x0, y1, x1, y1);
  }

  private void rubberP1Rect(Graphics g, int x, int y)
  {
    g.setXORMode(Color.white);
    g.drawLine(x0, y0, x0, y1);
    g.drawLine(x0, y0, x1, y0);
    g.drawLine(x1, y0, x1, y1);
    g.drawLine(x0, y1, x1, y1);
    x1 = x; y1 = y;
    g.drawLine(x0, y0, x0, y1);
    g.drawLine(x0, y0, x1, y0);
    g.drawLine(x1, y0, x1, y1);
    g.drawLine(x0, y1, x1, y1);
  }

  private void endRect(Graphics g, int x, int y)
  {
    g.setXORMode(Color.white);
    g.drawLine(x0, y0, x0, y1);
    g.drawLine(x0, y0, x1, y0);
    g.drawLine(x1, y0, x1, y1);
    g.drawLine(x0, y1, x1, y1);
    g.setColor(cor);
    g.setPaintMode();
    g.drawLine(x0, y0, x0, y1);
    g.drawLine(x0, y0, x1, y0);
    g.drawLine(x1, y0, x1, y1);
    g.drawLine(x0, y1, x1, y1);
  }
  

  private void drawRectAux(Graphics g, int xi,int yi,int xf, int yf)
  {
  // Detectar qual √© o v√©rtice superior esquerdo (menor x e menor y) 
  // e as dimens√µes do rect√¢ngulo: ABS(x2-x1), ABS(y2-y1)
  // Isto √© necessario para se poder chamar o m√©todo
  //           g.drawRect(xleft,ytop,width,height)
               
  }
  public void changeColor(){
      int x=aleatorio(254);      
      int y=aleatorio(254);
      int z=aleatorio(254);
      cor=new Color(x,y,z);
  }
      /**
     * FunÁ„o para gerar um valor inteiro aleatÛrio entre 1 e mod
     * @param mod Valor m·ximo da gama de valores possiveis que podem ser gerados
     * @return Um inteiro compreendido entre 1 e mod
     */
  private int aleatorio (int mod){
     long x=System.currentTimeMillis();
     //Para fazer com que o Random ocorra em diferentes milisegundos
     //para gerar valores diferentes na mesma execuÁ„o
     while(true){
        if (System.currentTimeMillis()!=x) break;
        }
        Random alea = new Random(System.currentTimeMillis());
        return 1+Math.abs(alea.nextInt()) % mod;
  }
  
}
