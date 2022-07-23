# Etude 11 Video Manager

Cameron Moore-Carter 3270737
Remin Reji Matthew 2581103

Instructions to Run:

- import the videomanager library
  - using import videomanager.core.VideoManager;
  - import videomanager.core.VideoClip;
- Create the single instance of the Video Manager by using:
  - VideoManager test2 = VideoManager.getInstance();
  - VideoManager test2 = new VideoManager() WILL NOT WORK! As the constructor is private!
- Add or delete clips using the functions .addClip .deleteClip and .receiveClip
- There is already a test file attached which I have used to test both the implementation of the hash map and the singleton using .hashcode
- So run and edit the test file if you would like to do more testing on the class.

Included in this etude are:

- Test.java
  - The test file with correct syntax for editing and using the Video Manager and Video Clip classes
- VideoManager.java
- VideoClip.java
  - A quick proxy class for future teams to improve and implement

Singleton Discussion:
The way we have designed this class to be a singleton instance is by keeping the
constructor private so it isnt able to be called. The only way to get *the* instance of the class is by calling the getInstance method. The challenges that we faced when creating this
was the static methods and creating a very controlled class that is user safe.
The main challenge is making sure that the user cannot in any way accidentally or purposely
create a new instance of the class.
The purpose of the singleton is if hundreds upon
hundreds of video clips are added to the hashmap, there is one global instance that
hosts all of these video clips. Therefore if this was used in an organisation, the video
clips are all in one place and can't go missing.
