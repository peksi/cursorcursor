// Get pozyx osc data and send it to localhost
// Original code by John Lee 30 Jan 2019

String IP = "10.100.4.221";  // change this
String tagId = "0x6735";  // change this

String localhost = "127.0.0.1"; 
NetAddress myRemoteLocation;

import oscP5.*;
import netP5.*;
import java.util.Map;

OscP5 oscP5;
float SCALE = 10;

/* a NetAddress contains the ip address and port number of a remote location in the network. */
NetAddress myBroadcastLocation; 

HashMap<String, PVector> tagPositions;

void setup() 
{
  //fullScreen();
  size(100,100);
   
  //create a new instance of oscP5. 
  //12000 is the port number you are listening for incoming osc messages.
  
  oscP5 = new OscP5(this,12000);
  
  /* the address of the osc broadcast server */
  myBroadcastLocation = new NetAddress(IP,32000);
  
  initDefaultData();
  
  myRemoteLocation = new NetAddress("127.0.0.1",12001);
}

void initDefaultData()
{
  tagPositions = new HashMap<String, PVector>();

  connectToServer();
}

void connectToServer()
{
  OscMessage msg;
  
  msg = new OscMessage("/server/connect",new Object[0]);
  
  oscP5.flush(msg,myBroadcastLocation); 
}

void disconnectServer()
{
  OscMessage msg;
  
  msg = new OscMessage("/server/disconnect",new Object[0]);
  
  oscP5.flush(msg,myBroadcastLocation); 
}

  
void oscEvent(OscMessage theOscMessage) 
{
  String recvData;
  String []parseData;
    
  if (theOscMessage.addrPattern().equals("/pozyx") == true)
  {
    println("received data");
    
    recvData = (String) theOscMessage.arguments()[0];
    
                                      //              array index   0   1 2 3  4   5   6
    parseData = split(recvData, ","); // here is data structure,  tagID,x,y,z,yaw,roll,pitch

    if (parseData[0].equals("POS") == true && parseData[1].equals(tagId))
    {  
      tagPositions.put(parseData[1], new PVector(int(parseData[2]), int(parseData[3]), int(parseData[4])));
      
      println(recvData);
      //println(tagPositions); // for make sure , if we have correct data
      
      OscMessage myMessage = new OscMessage("/pozyx");
      myMessage.add(recvData);
      oscP5.send(myMessage, myRemoteLocation); 
      
    }
  }
}

void displayTags()
{
  PVector tagPos;

  background(0);

  fill(255);

  for (Map.Entry tagInfo : tagPositions.entrySet()) 
  {
    tagPos = (PVector)tagInfo.getValue();

    ellipse(tagPos.x/SCALE, tagPos.y/SCALE, 20, 20);

    text((String)tagInfo.getKey(), tagPos.x/SCALE-20, tagPos.y/SCALE+25);
  }
}
  
void draw()
{
  displayTags();
  
  text("I'm OSC listener!!",20,20);
}
