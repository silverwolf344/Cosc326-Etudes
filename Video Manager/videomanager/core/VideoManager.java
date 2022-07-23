package videomanager.core;
import java.util.HashMap;
public class VideoManager {

    private static VideoManager staticInstance = null; 
    /* Max Amount of values in this Hashmap is 2^11, 2048 entries, which should be enough and may be auto increased if needed */
    private static HashMap<Integer, VideoClip> videoLibrary = new HashMap<Integer, VideoClip>(2048);
    private VideoManager() {
        //Constructor, only callable by the object itself since it is private
        //This prevents others from creating new instances
        
        
        
    }

    /**
     * Gets the singleton instance of the Video Manger Object,
     * if the object hasnt been created yet it creates it, otherwise
     * it will return the static Video Manager object.
     * @return Singleton VideoManger
     */
    public static VideoManager getInstance() {
    
        if (staticInstance == null){
            // No instance of VideoManager, create one
            staticInstance = new VideoManager();
        }
        return staticInstance;
    }
    /**
     * Returns a specified clip searched via id of the clip
     * @param id The ID of the clip to return
     * @return Returns either the correct clip or a console message replying no video clip is found.
     */
    public static VideoClip receiveClip(int id){
        if (videoLibrary.containsKey(id)){
            return videoLibrary.get(id);
        } else {
            System.out.println("No video clip found with id: " + id);
            return null;
        }
        
    }
    /**
     * Deletes a clip from the video library using the specified id
     * @param id The ID of the clip to delete
     */
    public static void deleteClip(int id){
        if (videoLibrary.containsKey(id)){
            videoLibrary.remove(id);
            System.out.println("Video Clip Deleted with Id:" + id);
        } else {
            System.out.println("No video clip found for Id: " + id);
        }
    }
    /**
     * Adds a clip to the video library
     * @param clip The clip itself
     */
    public static void addClip(VideoClip clip){
        if (videoLibrary.containsKey(clip.getId())){
            System.out.println("Id already exists in video library. Id: " + clip.getId());
        } else {
            videoLibrary.put(clip.getId(), clip);
            System.out.println("Video Clip Added with Id: "+ clip.getId());
        }
    }
    
}

