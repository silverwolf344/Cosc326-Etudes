import java.io.BufferedOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.math.BigInteger;
import java.util.BitSet;
import java.util.HexFormat;
import java.util.Scanner;



/**
 * https://stackoverflow.com/questions/9333681/java-bitset-example
 */
public class IbmTo754 {
    public static void main(String[] args) {
        File ibm = new File("ibm.txt");
        Scanner scan = new Scanner(System.in);
        System.out.println("Please Enter the Output Filename");
        String output = scan.nextLine();
        System.out.println("Please Enter the speicified presicion (single/double)");
        String presicion = scan.nextLine();
        scan.close();
        readLines(ibm, presicion, output);
        
    }
    /**
     * Left Pads the inputted string with 0's to a specified length.
     * @param s The string to pad
     * @param length The length to pad to
     * @return The padded string
     */
    public static String zfill(String s, int length) {
        if (s.length() >= length) {
            return s;
        }
        StringBuilder sb = new StringBuilder();
        while (sb.length() < length - s.length()) {
            sb.append('0');
        }
        sb.append(s);
    
        return sb.toString();
    }
    /**
     * Reads lines out of ibm.txt, converts them and then writes them to the speified output file.
     * @param ibm The file with the ibm floating point numbers
     * @param precision Single or Double
     * @param output The name of the file to output too.
     */
    private static void readLines(File ibm, String precision, String output) {
        String line;
        float ibmSingle;
        int intbits;
        try {
            Scanner scan = new Scanner(ibm);
            RandomAccessFile r = new RandomAccessFile(new File(output), "rw");
            
            while (scan.hasNextLine()) {
                line = scan.nextLine();
                String sign = line.substring(0, 1);
                String characteristic = line.substring(1, 8);
                String fraction = line.substring(8);
                // Convert into BitSets
                BitSet characteristic_bits  = fromString(characteristic);
                BitSet fraction_bits = fromString(fraction);
                // Print out Double Value
                System.out.println(convert(Integer.parseInt(sign), characteristic_bits,fraction_bits));
                double ibmDouble = convert(Integer.parseInt(sign), characteristic_bits,fraction_bits);
                
                // Write to new file
                if(precision.equals("single")){
                    // Single Precision Cast to float
                    ibmSingle = (float)ibmDouble;
                    intbits = Float.floatToIntBits(ibmSingle);
                    line = Integer.toBinaryString(intbits);
                    line = zfill(line,32);
                    String hexString = new BigInteger(line, 2).toString(16);
                    byte[] hexBytes = HexFormat.of().parseHex(hexString);
                    r.write(hexBytes);
                } else {
                    // Convert to IEEE754 Double Precision
                    line = Long.toBinaryString(Double.doubleToRawLongBits(ibmDouble));
                    line = zfill(line,64);
                    String hexString = new BigInteger(line, 2).toString(16);
                    byte[] hexBytes = HexFormat.of().parseHex(hexString);
                    r.write(hexBytes);

                }

            }
            r.close();
            scan.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException f) {
            f.printStackTrace();
        }
    }
    /**
     * Taken from link referenced at the top. Converts a string of binary to a Bitset array.
     * @param s The string of binary to be converted.
     * @return The Bitset array.
     */
    private static BitSet fromString(final String s) {
        return BitSet.valueOf(new long[] { Long.parseLong(s, 2) });
    }
    /**
     * Taken from link referenced at the top. Converts the BitSet array back into a string.
     * @param bs The Bitset array.
     * @return A string representation of the BitSet
     */
    private static String toString(BitSet bs) {
        return Long.toString(bs.toLongArray()[0], 2);
    }

    
    /**
     * Converts the IBM floating point representation to a double.
     * Follows the equation of ibm_float = (sign bit (-1 or 1)) * (16 ^ (exponent - 64)) * (fraction)
     * @param sign The sign of the floating point value. 1 or 0.
     * @param characteristic The characteristic of the floating point value. Also called the exponent.
     * @param fraction The fraction of the floating point value. Also called the mantissa.
     * @return The converted double.
     */
    private static double convert(int sign, BitSet characteristic, BitSet fraction){
        double fractionDouble = 0f;
        double decreasingExponent = 0; // In binary terms, 2 ^ 1....2 ^ -5, along to -22 (size of fraction 24 bits for single 55 for double)
        int characteristicDouble = 0;

        if (fraction.length() <= 24) { //BitSet issue removing leading 0's, account for this via decreasing one for the 0.
            decreasingExponent -= 24-fraction.length();
        } else if (fraction.length() <=56) {
            decreasingExponent -= 56-fraction.length();
        }
        if (fraction.length() != 0){
            for (int i = 0; i <= fraction.length(); i++){
                // For ever bit in the fraction, times it by 2 to the power of a decreasing exponent
                // Then add it to the fraction double
                // Have to get bits in reverse as thats the way BitSet stores them
                fractionDouble += (fraction.get(fraction.length() - i) ? 1:0) * Math.pow(2, decreasingExponent);
                decreasingExponent--;
            }
        }
        if(characteristic.length() != 0){
            // Convert characteristic to int
            characteristicDouble = Integer.parseInt(toString(characteristic),2);
        }
        // If sign is 0, return positive number
        if(sign == 0){
            return (Math.pow(16,(characteristicDouble - 64)) * fractionDouble);
        } else { // If sign is 1, return negative number
            return -1 * (Math.pow(16,(characteristicDouble - 64)) * fractionDouble);
        }
    }    
}