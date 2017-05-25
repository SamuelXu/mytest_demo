
import java.nio.ByteBuffer;
import java.util.*;

public class Main {
	public static void main(String[] args) {

		Hello sample = new Hello();
		int     square = sample.intMethod(5);
		boolean bool   = sample.booleanMethod(true);
		String  text   = sample.stringMethod("hello java");
		int[] arr = new int[]{1,1,2,3,5,8,13};
		int     sum    = sample.intArrayMethod(arr);
		byte[] barr = "usbserial".getBytes();
		sample.byteArrayMethod(barr);
		ByteBuffer buf = ByteBuffer.allocateDirect(16);// ByteBuffer.wrap(barr); cannot work
		buf.put(barr);
		sample.bytebufferMethod(buf);
		sample.bytebufferMethod(buf);
		sample.bytebufferMethod(buf);
		sample.bytebufferMethod(buf);
		sample.bytebufferMethod(buf);

		System.out.println("intMethod: " + square);
		System.out.println("booleanMethod: " + bool);
		System.out.println("stringMethod: " + text);
		System.out.println("intArrayMethod: " + sum);
		System.out.println("intArrayMethod: " + Arrays.toString(arr));
//		System.out.println("bytebufferMethod: " + new String(buf.array()));
	}
}
