
import java.awt.event.MouseEvent;
import java.awt.Color;
import java.awt.Graphics;
import java.util.Random;

public class PolyTool implements AnyTool 
{ 
  private Color cor=Color.BLACK;
  int x0, y0, x1, y1, x2, y2, status;
  /** Creates new LineTool */
  public PolyTool()
  {
      x1=y1=x2=y2=0;
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
              beginPoly(g, evt.getX(), evt.getY());
              status = 1;
              break;
          case (1):
          rubberP1Poly(g, evt.getX(), evt.getY());    
          default:
              break;
      }  
  }

  public void mouseMoved(Graphics g,java.awt.event.MouseEvent evt)
  {

  }
  public void mouseDragged(Graphics g,java.awt.event.MouseEvent evt)
  {
  }
  
  public void mouseReleased(Graphics g,java.awt.event.MouseEvent evt)
  {
  }

  public void mouseDoubleClicked(Graphics g,java.awt.event.MouseEvent evt)
  {
      switch(status)
      {
          case (1):
              endPoly(g);
              status = 0;
              break;
          default:
              break;
      }
  }

  public void mouseClicked(Graphics g,java.awt.event.MouseEvent evt)
  {
  }


  private void beginPoly(Graphics g, int x, int y)
  {
    x0 = x; y0 = y;
    x1 = x; y1 = y;
    g.setXORMode(Color.white);
  }

  private void rubberP1Poly(Graphics g, int x, int y)
  {
    g.setXORMode(Color.white);
    x2 = x; y2 = y;
    g.setColor(cor);
    g.drawLine(x1, y1, x2, y2);
    x1 = x2; y1=y2;
  }

  private void endPoly(Graphics g)
  {
    g.setXORMode(Color.white);
    g.drawLine(x0, y0, x1, y1);
    g.drawLine(x1, y1, x2, y2);
    g.setColor(cor);
    g.setPaintMode();
    g.drawLine(x0, y0, x1, y1);
    g.drawLine(x1, y1, x2, y2); 
  }

  private void polyPoint(Graphics g, int x, int y)
  {
  }
  public void changeColor(){
      int x=aleatorio(254);      
      int y=aleatorio(254);
      int z=aleatorio(254);
      cor=new Color(x,y,z);
  }
  /**
     * Função para gerar um valor inteiro aleatório entre 1 e mod
     * @param mod Valor máximo da gama de valores possiveis que podem ser gerados
     * @return Um inteiro compreendido entre 1 e mod
     */
  private int aleatorio (int mod){
     long x=System.currentTimeMillis();
     //Para fazer com que o Random ocorra em diferentes milisegundos
     //para gerar valores diferentes na mesma execução
     while(true){
        if (System.currentTimeMillis()!=x) break;
        }
        Random alea = new Random(System.currentTimeMillis());
        return 1+Math.abs(alea.nextInt()) % mod;
  }
  

}
