/*
 * ImageDownloader.java
 *
 * Created on February 24, 2002, 12:25 AM
 */

import java.net.*;
import java.io.*;
import java.awt.*;
import java.lang.Thread;
import java.awt.image.*;
import java.util.Vector;
/**
 *
 * @author  mike morrison
 */
public class ImageDownloader extends Thread {
    private Socket socket;
    private ImageCanvas imageCanvas = null;
    private String host;
    private int port;
    private boolean done;
    private String len_hdr = "content-length: ";
    private final String request = "GET / WCS/0.50";
    private double maxFPS = 1; // maximum frames per second, defaults to 10
    private int timeToWait = 0; //time to wait between image downloads
	private Vector chatQueue = new Vector();



    /** Creates a new instance of ImageDownloader */
    public ImageDownloader(String host, int port, double maxFPS, ImageCanvas ic) {
        this.host = host;
        this.port = port;
        imageCanvas = ic;
        setMaxFPS(maxFPS);
    }
	public void queueChatText(String message)
	{
		chatQueue.addElement(message);	
	}

    public void setMaxFPS(double maxFPS){
        if (maxFPS > 0){
            this.maxFPS = maxFPS;
            timeToWait = (int)(1000.0/maxFPS);
        }
    }
    public double getMaxFPS(){
        return maxFPS;
    }
    public boolean connect(){
        try{
            socket = new Socket(host,port);
        }catch (IOException e){
            e.printStackTrace();
            return false;
        }
        return true;
    }
    public boolean disconnect(){
        done = true;
        return true;
    }
    public boolean isConnected(){
        return (!done);
    }
    public void run(){
        
        done = false;
        if(!connect())
	{
		imageCanvas.couldNotConnect();
		imageCanvas.setConnected(ImageCanvas.DISCONNECTED);
		imageCanvas.setStartStopText("Start");
	}
	else
	{
		imageCanvas.setConnected(ImageCanvas.CONNECTED);
        	try{
        	    PrintWriter printWriter = new PrintWriter(socket.getOutputStream());
        	    InputStream input = socket.getInputStream();
        	    BufferedInputStream bufferedInput = new BufferedInputStream(input);
        	    //socket.setKeepAlive(true);
        	    //socket.setSoTimeout(1000);
        	    //socket.setReceiveBufferSize(10000);
        	    byte imgSize[] = new byte[4];
		    byte header[] = new byte[1024];

        	    //int count = 0;
        	    long startTime = System.currentTimeMillis();
        	    long stopTime  = startTime, decodeStop, downloadStop,prepareStop=0;

        	    Image img;
        	    while (!done){
                	//time the image started being downloaded
                	startTime = System.currentTimeMillis();
                	printWriter.println(request);
			if(chatQueue.size() > 0)
			{
				System.out.println((String)chatQueue.elementAt(0));
				printWriter.println((String)chatQueue.elementAt(0));
				chatQueue.removeElementAt(0);
			}	
                	printWriter.flush();
			int i=0;
			while((header[i] = (byte)bufferedInput.read()) != -1)
			{
				//System.out.print((char)header[i]);
				if(i>0)
				if(header[i] == '\n' && header[i-1] == '\n')
					break;
				i++;
			}
			String s = new String(header).toLowerCase();

			int start = s.indexOf(len_hdr) + len_hdr.length();
			int end = s.indexOf("\n", start);
			s = s.substring(start, end);

	 		int size = Integer.parseInt(s);
                	if (size < 0) break;
                	byte imageBytes[] = new byte[size];

                	int newSize = 0;
                	int totalSize = 0;

                	while ((newSize = bufferedInput.read(imageBytes,totalSize,size- totalSize)) != -1){
                	    totalSize += newSize;
                	    if (totalSize == size) break;
                	    wait(10);
                	}
                	if (totalSize != size){
                	    System.out.println("Did not read everything!");
                	    break;
                	}
                	//System.out.println("Download Time: " + (System.currentTimeMillis() - startTime) + "ms");

                	img = Toolkit.getDefaultToolkit().createImage(imageBytes);                

                	//create and draw the image
                	if (imageCanvas !=null) imageCanvas.setImage(img);

                	stopTime = System.currentTimeMillis();
                	// wait before reqesting another image.
                	// to maintain maxFPS

                	if ((timeToWait - (stopTime - startTime)) > 0){
                	     wait((int) (timeToWait - (stopTime - startTime)));
                	}

        	    }
        	}catch(IOException e){
        	    e.printStackTrace();
		    imageCanvas.setConnected(ImageCanvas.DISCONNECTED);
                    imageCanvas.setStartStopText("Start");
        	}finally{
        	    disconnect();
		    imageCanvas.setConnected(ImageCanvas.STOPPED);
		    imageCanvas.setStartStopText("Start");
		    try{
                	socket.close();
        	    }catch (IOException ioe){
                	ioe.printStackTrace();
        	    }
        	}
	}
    }

    public int FourBytesToInt(byte buf[])
    {
        int i = 0;
        int pos = 0;
        i += unsignedByteToInt(buf[pos++]) << 0;
        i += unsignedByteToInt(buf[pos++]) << 8;
        i += unsignedByteToInt(buf[pos++]) << 16;
        i += unsignedByteToInt(buf[pos++]) << 24;
	return i;
    }
    public static int unsignedByteToInt(byte b) {
       return (int) b & 0xFF;
    }

    public void wait(int n){
        try{
            sleep(n);
        }catch(InterruptedException e){}
    }        
    
    public static void main (String args[]){
        ImageDownloader downloader = new ImageDownloader(args[1], Integer.parseInt(args[2]), 30, null);
        downloader.start();
    }
}


