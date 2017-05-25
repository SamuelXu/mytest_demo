
import java.nio.ByteBuffer;

public class Hello {
	static {
		System.loadLibrary("hello"); // Load native library at runtime
	}

	public native int intMethod(int n);
	public native boolean booleanMethod(boolean bool);
	public native String stringMethod(String text);
	public native int intArrayMethod(int[] intArray);
	public native void byteArrayMethod(byte[] byteArray);
	public native void bytebufferMethod(ByteBuffer buff);

}
