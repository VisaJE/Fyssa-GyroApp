package com.movesense.mds.fyssagyro;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.support.annotation.Nullable;
import android.util.Log;

import java.io.Closeable;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import static android.content.Intent.FLAG_ACTIVITY_NEW_TASK;

/**
 * Utility class with some helper methods
 */
public final class Util {

    private static final String TAG = Util.class.getSimpleName();
    private static final long TOP_MASK_FOR_LONG = 0xffffffffL; // A constant to deal with printing
    private final static char[] HEX_ARRAY = "0123456789ABCDEF".toCharArray(); //NON-NLS

    private Util() {
        // Prevent construction
    }

    public static void safeClose(@Nullable Closeable closeable) {
        if (closeable == null) {
            return;
        }

        try {
            closeable.close();
        } catch (IOException e) {
            // ..
        }
    }

    public static String getVisibleSerial(String name) {
        String result = "";                                  //NON-NLS
        Pattern pattern;
        //if (BuildConfig.DEBUG) {
        // Everything after last whitespace and possible '#'
        pattern = Pattern.compile("([^\\s#]*)$"); // NON-NLS
        /*
        } else {
            // Digits at the end of the string, must be 8-14 digits.
            // The first digit can be replaced with P in prototype devices.
            pattern = Pattern.compile("(P?[0-9]{7,14}$)"); //NON-NLS
        }
        */

        Matcher matcher = pattern.matcher(name);
        boolean found = matcher.find();                      // Find the next match (there can be only one)
        if (found) {
            result = matcher.group();                        // Returns the input subsequence matched by the previous match.
        }
        return result;
    }

    /**
     * Convert a List of Strings into an String array
     *
     * @param list
     * @return
     */
    public static String[] toStringArray(List<String> list) {
        String[] ret = new String[list.size()];
        int i = 0;
        for (String e : list)
            ret[i++] = e;
        return ret;
    }

    /**
     * Encode input data bytes to the Suunto serial frame format
     *
     * @param srcData Data to encode
     * @return Encoded data as byte array
     */
    @SuppressWarnings({"ForLoopReplaceableByForEach", "PointlessArithmeticExpression"})
    public static byte[] sfEncode(byte[] srcData) {
        byte START_END_MARK = 0x7e; // Magic byte value indicating start and end of a packet
        byte CONTROL_MARK = 0x7d;   // Magic byte value used to escape 0x7e in the middle of the packet
        byte tmpByte;
        List<Byte> dstData = new ArrayList<>();

        dstData.add(START_END_MARK); // Start packet

        // Escape special bytes in source data
        for (int i = 0; i < srcData.length; i++) {
            tmpByte = srcData[i];
            if ((tmpByte == START_END_MARK) || (tmpByte == CONTROL_MARK)) {
                dstData.add(CONTROL_MARK);
                tmpByte ^= 0x20;
            }
            dstData.add(tmpByte);
        }

        // Generate CRC32 for the data
        long crcValue;
        byte[] crcBuff = new byte[4];
        crcValue = (crc32IEEE(srcData, srcData.length) & TOP_MASK_FOR_LONG);

        crcBuff[3] = (byte) ((crcValue >> (3 * 8)) & 0xff);
        crcBuff[2] = (byte) ((crcValue >> (2 * 8)) & 0xff);
        crcBuff[1] = (byte) ((crcValue >> (1 * 8)) & 0xff);
        crcBuff[0] = (byte) ((crcValue >> (0 * 8)) & 0xff);

        // Escape special bytes in CRC32
        for (int i = 0; i < crcBuff.length; i++) {
            tmpByte = crcBuff[i];
            if ((tmpByte == START_END_MARK) || (tmpByte == CONTROL_MARK)) {
                dstData.add(CONTROL_MARK);
                tmpByte ^= 0x20;
            }
            dstData.add(tmpByte);
        }

        dstData.add(START_END_MARK); // End packet

        return toByteArray(dstData);
    }

    /**
     * Decode input data bytes from the Suunto serial frame format to actual bytes
     *
     * @param srcData
     * @return
     */
    @SuppressWarnings("PointlessArithmeticExpression")
    public static List<Byte> sfDecode(List<Byte> srcData) {
        // Log.d(STAG, String.format(Locale.getDefault(), "XXX sfDecode: srcData.length: %d, bytes: %s", srcData.length, byteArrayToHexString(srcData))); //NON-NLS
        byte START_END_MARK = 0x7e;                     // Magic byte value indicating start and end of a packet
        byte CONTROL_MARK = 0x7d;                       // Magic byte value used to escape 0x7e in the middle of the packet
        byte tmpByte;                                   // Work on this byte
        List<Byte> emptyByteList = new ArrayList<>();   // Returning an empty array means the input data could not be decoded
        List<Byte> dstData = new ArrayList<>();         // Ultimately the result
        int pos = 0;                                    // Position in dstData
        boolean control = false;                        // true == processing an escaped byte

        if (srcData == null || srcData.size() < 2 || srcData.get(0) != START_END_MARK) {
            Log.d(TAG, "XXX sfDecode: Fail: no start character in the beginning, or too few bits"); //NON-NLS
            return emptyByteList; // no start character in the beginning, or too few bits
        }

        for (int i = 1; i < srcData.size(); i++) { // Skip the starting START_END_MARK
            tmpByte = srcData.get(i);

            if (control) { // There was a CONTROL_MARK before the current byte
                if ((tmpByte == START_END_MARK) || (tmpByte == CONTROL_MARK)) {
                    Log.d(TAG, "XXX sfDecode: Fail: start or control character in wrong place"); //NON-NLS
                    return emptyByteList; // start or control character in wrong place
                }
                tmpByte ^= 0x20;
                dstData.add(tmpByte);
                pos += 1;
                control = false;
            } else {
                if (tmpByte == START_END_MARK) {
                    // Check CRC
                    if (pos > 4) {
                        long calculatedCrc;
                        byte[] receivedCrc = new byte[4];
                        byte[] crcBuff = new byte[4];
                        byte[] tmpData = toByteArray(dstData);

                        //noinspection UnusedAssignment
                        pos -= 4; // The CRC value has 4 bytes
                        // Log.d(STAG, String.format(Locale.getDefault(), "XXX sfDecode: crc32IEEE for tmpData: %s, pos: %d, , len: %d", //NON-NLS
                        //        byteArrayToHexString(tmpData), pos, (tmpData.length - 4))); //NON-NLS
                        calculatedCrc = crc32IEEE(tmpData, (tmpData.length - 4));
                        crcBuff[3] = (byte) ((calculatedCrc >> (3 * 8)) & 0xff);
                        crcBuff[2] = (byte) ((calculatedCrc >> (2 * 8)) & 0xff);
                        crcBuff[1] = (byte) ((calculatedCrc >> (1 * 8)) & 0xff);
                        crcBuff[0] = (byte) ((calculatedCrc >> (0 * 8)) & 0xff);

                        // The CRC bytes are in inverse order in the packet
                        receivedCrc[0] = tmpData[(tmpData.length - 4)];
                        receivedCrc[1] = tmpData[(tmpData.length - 3)];
                        receivedCrc[2] = tmpData[(tmpData.length - 2)];
                        receivedCrc[3] = tmpData[(tmpData.length - 1)];

                        if (crcBuff[0] == receivedCrc[0] && crcBuff[1] == receivedCrc[1] &&
                                crcBuff[2] == receivedCrc[2] && crcBuff[3] == receivedCrc[3]) {
                            dstData.subList(dstData.size() - 4, dstData.size() - 0).clear(); // Remove last 4 bytes (the CRC32) from result
                            // Log.d(STAG, String.format(Locale.getDefault(), "XXX sfDecode: decoded to: %s", byteArrayToHexString(toByteArray(dstData)))); //NON-NLS
                            return dstData; // Success
                        } else {
                            Log.w(TAG, String.format(Locale.getDefault(), "XXX sfDecode: CRC Error in the read packet. calculated Crc: %s, received Crc: %s", //NON-NLS
                                    byteArrayToHexString(crcBuff), byteArrayToHexString(receivedCrc))); //NON-NLS
                            return emptyByteList; // crc check failed
                        }
                    }
                    Log.d(TAG, "XXX sfDecode: Fail: not enough (at all?) data to trigger decode"); //NON-NLS
                    return emptyByteList; // no data at all / crc check failed
                }

                if (tmpByte == CONTROL_MARK) {
                    control = true;
                } else {
                    dstData.add(tmpByte);
                    pos += 1;
                }
            }
        }

        // Log.d(STAG, "XXX sfDecode: Fail: incomplete message - this is normal for packets longer that one chunk"); //NON-NLS
        return emptyByteList; // incomplete message
    }

    /**
     * Convert a List of Bytes into byte array
     *
     * @param list List of bytes
     * @return Array containing all bytes in the list
     */
    public static byte[] toByteArray(List<Byte> list) {
        byte[] ret = new byte[list.size()];
        int i = 0;
        for (Byte b : list)
            ret[i++] = b;
        return ret;
    }

    public static String byteArrayToHexString(byte[] bytes) {
        if (bytes == null)
            return "null"; //NON-NLS

        char[] hexChars = new char[bytes.length * 2];
        for (int j = 0; j < bytes.length; j++) {
            int v = bytes[j] & 0xFF;
            hexChars[j * 2] = HEX_ARRAY[v >>> 4];
            hexChars[j * 2 + 1] = HEX_ARRAY[v & 0x0F];
        }
        return new String(hexChars);
    }

    // Return the IEEE 802.3 CRC32 over given input data with given initial value
    private static long crc32IEEEWithInitial(long initial, byte[] pBuffer, int byteCount) {
        // Log.d(STAG, String.format(Locale.getDefault(), "XXX crc32IEEEWithInitial: pBuffer: %s, byteCount: %d", //NON-NLS
        //   byteArrayToHexString(pBuffer), byteCount)); //NON-NLS
        // 4-bit to 32-bit CRC LUT (compromise between compactness and performance)
        long[] aCrc32Table = {
                0x4DBDF21CL, 0x500AE278L, 0x76D3D2D4L, 0x6B64C2B0L,
                0x3B61B38CL, 0x26D6A3E8L, 0x000F9344L, 0x1DB88320L,
                0xA005713CL, 0xBDB26158L, 0x9B6B51F4L, 0x86DC4190L,
                0xD6D930ACL, 0xCB6E20C8L, 0xEDB71064L, 0xF0000000L};

        long crc = (initial & TOP_MASK_FOR_LONG);
        byte b;

        for (int i = 0; i < byteCount; i++) {
            b = pBuffer[i];
            // Log.d(STAG, String.format(Locale.getDefault(), "XXX crc32IEEEWithInitial: b: %s, bottom i: %d, top i: %d", //NON-NLS
            //    byteToHex(b),                     //NON-NLS
            //    (int)((crc ^ (b >> 0)) & 0x0F),   //NON-NLS
            //    (int)((crc ^ (b >> 4)) & 0x0F))); //NON-NLS
            crc = ((crc & TOP_MASK_FOR_LONG) >> 4) ^ aCrc32Table[(int) (((crc & TOP_MASK_FOR_LONG) ^ (b >> 0)) & 0x0F)] & TOP_MASK_FOR_LONG;
            crc = ((crc & TOP_MASK_FOR_LONG) >> 4) ^ aCrc32Table[(int) (((crc & TOP_MASK_FOR_LONG) ^ (b >> 4)) & 0x0F)] & TOP_MASK_FOR_LONG;
            // Log.d(STAG, String.format(Locale.getDefault(), "XXX crc32IEEEWithInitial: crc: %s", Long.toHexString(crc))); //NON-NLS
        }
        return (TOP_MASK_FOR_LONG & crc);
    }

    // Return the IEEE 802.3 CRC32 over given input data
    private static long crc32IEEE(byte[] pBuffer, int byteCount) {
        // Log.d(STAG, "XXX crc32IEEE: pBuffer: " + byteArrayToHexString(pBuffer) + ", byteCount: " + byteCount); //NON-NLS
        return (TOP_MASK_FOR_LONG & crc32IEEEWithInitial(0, pBuffer, byteCount));
    }

    public static void triggerRebirth(Context context, Class<?> clazz ) {
        Intent intent = new Intent(context, clazz);
        intent.addFlags(FLAG_ACTIVITY_NEW_TASK);
        context.startActivity(intent);
        if (context instanceof Activity) {
            ((Activity) context).finish();
        }

        Runtime.getRuntime().exit(0);
    }
}
