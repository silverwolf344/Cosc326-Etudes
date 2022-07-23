import java.io.*;

public class ReadBinaryFile
{
  public static void main (String [] args) throws IOException
  {
    File inFile = new File ("test.bin");
    FileInputStream inStream = new FileInputStream (inFile);
    DataInputStream input = new DataInputStream (inStream);

    String name;
    long ssNum;
    double gpa;

    try
    {
      while (true)
      {
        name = input.readUTF();
        ssNum = input.readLong();
        gpa = input.readDouble();

        System.out.println (input);
      }
    }
    catch (EOFException e)
    {
      // Do nothing if it is the end of file.
    }
    catch (Exception e)
    {
      System.out.println (e.getMessage());
      e.printStackTrace();
      System.exit(0);
    }
    finally
    {
      inStream.close();
    }

  }
}