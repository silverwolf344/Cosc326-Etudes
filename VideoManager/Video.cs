using System;

public class Video 

{
  private int _id;
  private int _duration;
  private int _currFrame;
  private int _startFrame;
  private int _endFrame;
  private float _fps;


  public Video( int _id, int _duration ) {
    this._id = _id;
    this._duration = _duration;
  }

  public int getID() 
  {
    return _id;
  }
  public int getDuration() 
  {
    return _duration;
  }
  public int getCurrFrame()
  {
    return _currFrame;
  }
  public int getStartFrame()
  {
    return _startFrame;
  }
  public int getEndFrame()
  {
    return _endFrame;
  }
  public float getFps()
  {
    return _fps;
  }

}
