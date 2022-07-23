package videomanager.core;
public class VideoClip{

    private int id;
    private int length;
    private int startFrame;
    private int endFrame;
    private float fps;
    /**
     * Constructor for VideoClip Object
     * @param id The id of the video clip
     * @param length the Length of the video clip
     */
    public VideoClip(int id, int length){
        this.id = id;
        this.length = length;
    }

    public int getId(){
        return id;
    }
    public int getLength(){
        return length;
    }
    public int getStartFrame(){
        return startFrame;
    }
    public int getEndFrame(){
        return endFrame;
    }
    public float getFps(){
        return fps;
    }
    public String toString(){
        return "Clip id=" + id + ", length=" + length;
    }
}