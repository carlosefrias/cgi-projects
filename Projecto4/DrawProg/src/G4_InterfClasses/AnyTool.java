
import java.awt.Graphics;

public interface AnyTool {
  
  public void startTool();
  public void stopTool();
	
  public void mousePressed(Graphics g, java.awt.event.MouseEvent evt);
  public void mouseMoved(Graphics g, java.awt.event.MouseEvent evt);
  public void mouseDragged(Graphics g, java.awt.event.MouseEvent evt);
  public void mouseReleased(Graphics g, java.awt.event.MouseEvent evt);
  public void mouseClicked(Graphics g, java.awt.event.MouseEvent evt);
  public void mouseDoubleClicked(Graphics g, java.awt.event.MouseEvent evt);
  public void changeColor();
  }
