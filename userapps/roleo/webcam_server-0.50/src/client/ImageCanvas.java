/*
 * ImageCanvas.java
 *
 * Created on February 25, 2002, 1:29 AM
 */
import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import java.net.URL;
import java.net.MalformedURLException;
import java.io.File;
/**
 *
 * @author  mike morrison
 */

 
public class ImageCanvas extends Canvas
{
	final static int CONNECTED = 0;
	final static int DISCONNECTED = 1;
	final static int STOPPED = 2;

	final private String connectingImageFilename = "init.jpg";
	final private String cannotConnectImageFilename = "error.jpg";
	
	private Applet applet;
	private String host;
	private int port;
	private double fps;	
	private int connected=STOPPED;
	private boolean first_image = true;

	private Dimension preferredSize;

	private Graphics offGraphics;
	private Image currentImage;
	private Image offImage;

	private PopupMenu popup;
	private MenuItem startStop;

	private Frame mainWindow = null;
	private ImageDownloader downloader;
	private ImageCanvas thisImageCanvas;
	private Frame about;
// chat not enabled...yet
	private Frame chat = null;
	private TextArea output;
	private	TextField input;
	private TextField name = new TextField("name", 10);

	/** Creates a new instance of ImageCanvas */
	public ImageCanvas(Applet applet, String host, int port, int fps, int width, int height) {
		this.applet = applet;
		this.host = host;
		this.port = port;
		this.fps = fps;
		
		preferredSize = new Dimension(width,height);
		
		if (applet == null)
		{
			File f = new File(connectingImageFilename);
			if(f.exists())
				setImage(Toolkit.getDefaultToolkit().getImage(connectingImageFilename));
			else
				System.out.println(connectingImageFilename + " not found");
		}
		else
		{
			try {
				setImage(applet.getImage(new URL(applet.getCodeBase().toString() + connectingImageFilename)));
			} catch(MalformedURLException e) {}
		}
		
		about = createAbout();
		add(createMenu());
		thisImageCanvas = this;

		// mouse listener
		addMouseListener(createMouseListener());
		downloader = new ImageDownloader(host,port, fps, this);
		downloader.start();
	}

	public Dimension getPreferredSize(){
		return preferredSize;
	}

	public double getFPS()
	{
		return fps;
	}
	
	public int getPort()
	{
		return port;
	}
	
	public String getHost()
	{
		return host;
	}
	
	public void setMainWindow(Frame f)
	{
		mainWindow = f;
	}
	
	/**
	 * returns the time it took to set the image 
	 */
	public void setImageSize(Dimension size)
	{
		preferredSize = size;
		setSize(size);
	}
	
	/**
	 * Sets Start/Stop menu item label
	 */
	public void setStartStopText(String text)
	{
		startStop.setLabel(text);
	}
	
	/**
	 * sets the current image (refreshes frame)
	 */
	public int setImage(Image img)
	{
		if(first_image && mainWindow != null)
		{
			int w, h;
			while((w = img.getWidth(null)) < 0 || (h = img.getHeight(null)) < 0);
			System.out.println("w = " + w + ", h = " + h);
			mainWindow.setBounds(100,100,w,h);
			first_image = false;
		}
		int count = 0, waitTime = 5;
		while (!prepareImage(img,this))
		{
			wait(waitTime);
			count ++;
			if (count * waitTime > 5000) break;
		}
		currentImage = img;
		repaint();
		return (count * waitTime);
	}

	/**
	 * displays image in cannotConnectImageFilename upon failed connection
	 */
	public void couldNotConnect()
	{
		setStartStopText("Start");
		if (applet == null)
		{
			File f = new File(cannotConnectImageFilename);
			if(f.exists())
				setImage(Toolkit.getDefaultToolkit().getImage(cannotConnectImageFilename));
			else
				System.out.println(cannotConnectImageFilename + " not found");
		}
		else
		{
			try {
			setImage(applet.getImage(new URL(applet.getCodeBase().toString() + cannotConnectImageFilename)));
			} catch(MalformedURLException e) {}
		}
	}

	/**
	 * sets connected state
	 */
	public void setConnected(int connected)
	{
		this.connected = connected;
		if(connected != CONNECTED)
		{
			if(chat != null)
			{
				chat.dispose();
				chat = null;
			}
		}
		repaint();
	}

	/**
	 * sleeps current thread for n milliseconds
	 */
	public void wait(int n){
		try {
			Thread.sleep(n);
		} catch(InterruptedException e) {}
	}

	public void disconnect()
	{
		downloader.disconnect();
		if(chat != null)
		{
			chat.dispose();
			chat = null;
		}
	}

	public MouseListener createMouseListener(){
		return (new MouseListener(){
			public void mouseClicked(MouseEvent e){}
			public void mouseEntered(MouseEvent e){}
			public void mouseExited(MouseEvent e){}
			public void mousePressed(MouseEvent e){}
			public void mouseReleased(MouseEvent e){
				switch(e.getModifiers()){
				case 16:
					//left
					break;
				case 8:
					//middle
					break;
				case 4:
					if (connected != CONNECTED)
						thisImageCanvas.startStop.setLabel("Start");
					else
						thisImageCanvas.startStop.setLabel("Stop");

					popup.show(e.getComponent(),e.getX(), e.getY());
					break;
				default:
					break;                       
				}                  
			}
		});
	}

	/**
	 * create a simple chat window
	 */
	public Frame createChat()
	{
		if(connected != CONNECTED)
			return null;
		Frame f = new Frame("WebCam Chat");
		Panel p = new Panel();
		input = new TextField();
		output = new TextArea("please type your name in the 'name' field\n");

		p.setLayout(new BorderLayout());	

		f.setLayout(new BorderLayout());

		p.add(input, BorderLayout.CENTER);
		p.add(name, BorderLayout.WEST);
		f.add(p, BorderLayout.SOUTH);
		f.add(output, BorderLayout.CENTER);
		output.setEditable(false);

		input.addKeyListener(new KeyListener(){
			public void keyTyped(KeyEvent e){}
			public void keyPressed(KeyEvent e)
			{
				if(e.getKeyCode() == KeyEvent.VK_ENTER && !input.getText().equals(""))
				{	
					String message = name.getText() + ": " + input.getText() + "\n";
					output.append(message);
					input.setText("");
					downloader.queueChatText(message);
				}
			}
			public void keyReleased(KeyEvent e) {}
		});

		f.addWindowListener(new WindowListener()
		{
			public void windowActivated(WindowEvent e){}
			public void windowClosed(WindowEvent e){}
			public void windowClosing(WindowEvent e){
				chat.dispose();
				chat = null;
			}
			public void windowDeactivated(WindowEvent e){}
			public void windowDeiconified(WindowEvent e){}
			public void windowIconified(WindowEvent e){}
			public void windowOpened(WindowEvent e){}
		});

		f.setBounds(200,200,300,150);
		f.show();
		return f;
	}

	public Frame createAbout()
	{
		Frame f = new Frame("About");
		Panel p = new Panel();
		p.setLayout(new GridLayout(0,1));

		p.add(new Label(" "));
		p.add(new Label("Copyright (C) 2002"));
		p.add(new Label("Applet by Mike Morrison"));
		p.add(new Label("Server by Donn Morrison"));
		p.add(new Label(" "));

		Button b = new Button("Ok");
		b.addActionListener(new ActionListener(){
			public void actionPerformed(ActionEvent e)
			{
				about.hide();
			}
		});
		
		f.add(p,BorderLayout.NORTH);
		p = new Panel();
		p.setLayout(new FlowLayout());
		p.add(b);
		f.add(p,BorderLayout.CENTER);
		f.pack();
		f.setBackground(Color.lightGray);
		f.setResizable(false);
		return f;          
	}
    public PopupMenu createMenu()
    {
        //create the menu
        MenuItem menuItem;
        popup = new PopupMenu("WebCam Options");
        startStop = new MenuItem("Stop");
        startStop.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                if (downloader == null || !downloader.isConnected()){
                    downloader = new ImageDownloader(thisImageCanvas.getHost(),thisImageCanvas.getPort(),thisImageCanvas.getFPS(),thisImageCanvas);
                    downloader.start();
                    downloader.setMaxFPS(thisImageCanvas.fps);
                }else{
                    thisImageCanvas.fps = downloader.getMaxFPS();
                    downloader.disconnect();
                    downloader = null;
                }
                
            }
        });
        popup.add(startStop);
        

        //frames per second submenu
        Menu subMenu = new Menu("Max FPS");
        menuItem = new MenuItem("0.1");
        menuItem.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                //set maxfps to 0.1
                if (downloader != null){
                    downloader.setMaxFPS(.1);
                    thisImageCanvas.fps = .1;
                }
            }
        });
        subMenu.add(menuItem);

        menuItem = new MenuItem("0.2");
        menuItem.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                //set maxfps to 0.2
                if (downloader != null){
                    downloader.setMaxFPS(.2);
                    thisImageCanvas.fps = .2;
                }
            }
        });
        subMenu.add(menuItem);
	
	menuItem = new MenuItem("0.5");
        menuItem.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                //set maxfps to 0.5
                if (downloader != null){
                    downloader.setMaxFPS(.5);
                    thisImageCanvas.fps =.5;
                }
            }
        });
        subMenu.add(menuItem);
        menuItem = new MenuItem("1");
        menuItem.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                //set maxfps to 1
                if (downloader != null){
                    downloader.setMaxFPS(1.0);
                    thisImageCanvas.fps = 1.0;
                }
            }
        });
        subMenu.add(menuItem);
        menuItem = new MenuItem("2");
        menuItem.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                //set maxfps to 2
                if (downloader != null){
                    downloader.setMaxFPS(2.0);
                    thisImageCanvas.fps = 2.0;
                }
            }
        });
        subMenu.add(menuItem);
        menuItem = new MenuItem("5");
        menuItem.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                //set maxfps to 5
                if (downloader != null){
                    downloader.setMaxFPS(5.0);
                    thisImageCanvas.fps = 5.0;
                }
            }
        });
        subMenu.add(menuItem);
        menuItem = new MenuItem("10");
        menuItem.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                //set maxfps to 10
                if (downloader != null){
                    downloader.setMaxFPS(10.0);
                    thisImageCanvas.fps = 10.0;
                }
            }
        });
        subMenu.add(menuItem);
        menuItem = new MenuItem("Unlimited");
        menuItem.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                //set maxfps to 30
                if (downloader != null){
                    downloader.setMaxFPS(30.0);
                    thisImageCanvas.fps = 30.0;
                }
            }
        });
        subMenu.add(menuItem);

        popup.add(subMenu);
        popup.addSeparator();
        
        //about
        menuItem = new MenuItem("About");
        menuItem.addActionListener(new ActionListener(){
            public void actionPerformed(ActionEvent e){
                //display about box
                about.show();
            }
        });

        popup.add(menuItem);
/* chat not enabled...yet
	menuItem = new MenuItem("Chat");
	menuItem.addActionListener(new ActionListener()
	{
		public void actionPerformed(ActionEvent e)
		{
			if(chat == null)
				chat = createChat();
		}
	});
      popup.add(menuItem);
*/
        return (popup);
    }

//////////////////////////////////////////
// paint methods /////////////////////////
//////////////////////////////////////////

	public void paint(Graphics g)
	{
		update(g);
	}

	public void update(Graphics g)
	{
		Color color = Color.black;
		if (currentImage != null)
		{
			// dubble buffer
			offImage = createImage(preferredSize.width,preferredSize.height);
			offGraphics = offImage.getGraphics();
			offGraphics.drawImage(currentImage,0,0,preferredSize.width,preferredSize.height,this);
			g.drawImage(offImage,0,0,this);

			switch(connected)
			{
			case CONNECTED:
				color = new Color(30, 175, 30); // dark green
				break;
			case DISCONNECTED:
				color = new Color(175,30,30); // dark red
				break;
			case STOPPED:
				color = new Color(175,30,30); // dark red
				break;
			default:
				break;
			}

			// display an indicator in bottom corner of frame
			g.setColor(Color.black);
			g.fillOval(preferredSize.width - 11, preferredSize.height - 11, 7, 7);
			g.setColor(color);
			g.fillOval(preferredSize.width - 12, preferredSize.height - 12, 7, 7);

			// no double buffer
			// g.drawImage(currentImage,0,0,preferredSize.width,preferredSize.height,this);
		}
	}
}
