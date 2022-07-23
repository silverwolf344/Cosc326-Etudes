import videomanager.core.VideoManager;
import videomanager.core.VideoClip;

public class Test{
    public static void main(String[] args){
        VideoManager test1 = VideoManager.getInstance();
        VideoManager test2 = VideoManager.getInstance();
        VideoManager test3 = VideoManager.getInstance();
        /* Test if the hashcode is all the same to makesure it is the same object */
        System.out.println("Hashcode of test1 is "+ test1.hashCode());
        System.out.println("Hashcode of test2 is "+ test2.hashCode());
        System.out.println("Hashcode of test3 is "+ test3.hashCode());
        VideoClip clip = new VideoClip(12345678, 50);
        test1.addClip(clip);
        /* Test adding to another pointer object to see if it is the same object */
        test2.addClip(clip);
        System.out.println("Clip: " + test1.receiveClip(12345678));
        /* Test again delete function */
        test1.deleteClip(clip.getId());
        test3.deleteClip(clip.getId());
        /* Mass test, test number is larger than size of hashmap to see if it will auto-allocate size */
        for (int i = 0; i < 2050; i++){
            /*Test adding lots of clips */
            clip = new VideoClip(i,50);
            test1.addClip(clip);
        }
        for (int i = 0; i < 2050; i++){
            System.out.println("Clip: " + i + test1.receiveClip(i));
        }

    }
}



