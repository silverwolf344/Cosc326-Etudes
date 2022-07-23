using System;

public sealed class VideoManager
{
  private static VideoManager _instance = null;
  private VideoManager() { }

  private static Dictionary<int, Video> videoDict = new Dictionary<int, Video>();

  public static VideoManager Instance
  {
    get
    {
      if (_instance == null)
      {
        _instance = new VideoManager();
      }
      return _instance;
    }
  }


  public void addVideo(int _id, Video video)
  {
    if (videoDict.ContainsKey(_id))
    {
      throw new InvalidOperationException(_id + " has already been included in the library");
    }
    else
    {
      videoDict.Add(_id, video);
    }
  }


  public void deleteVideo(int _id)
  {
    if (videoDict.ContainsKey(_id))
    {
      videoDict.Remove(_id);
    }
    else
    {
      {
        throw new InvalidOperationException(_id + " is not in the library :(");
      }
    }
  }
}