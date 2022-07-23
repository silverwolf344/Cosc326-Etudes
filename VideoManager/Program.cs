// Uses NET6.0
Video clip1 = new Video(5127382, 326);
Video clip2 = new Video(123456, 326);
Video clip3 = new Video(2222222,12);

VideoManager test1 = VideoManager.Instance;
VideoManager test2 = VideoManager.Instance;
VideoManager test3 = VideoManager.Instance;

Console.WriteLine("The hashcode of test1 is:" + test1.GetHashCode());
Console.WriteLine("The hashcode of test2 is:" + test2.GetHashCode());
Console.WriteLine("The hashcode of test3 is:" + test3.GetHashCode());

test1.addVideo(clip1.getID(), clip1);
test2.addVideo(clip2.getID(), clip2);
test1.addVideo(clip3.getID(), clip3);
// These lines give errors, which are expected.
//VideoManager.addVideo(clip2.getID(), clip2);
//VideoManager.addVideo(clip1.getID(), clip1);
test1.deleteVideo(clip2.getID());
