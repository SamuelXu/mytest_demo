import java.util.*;

import java.util.concurrent.locks.ReentrantLock;

public class t1 {
	public static void main(String[] args) {
		ReentrantLock lock = new ReentrantLock();
		try {
		lock.lock();
		lock.lock();
		lock.unlock();
		if (lock.isHeldByCurrentThread()) {
			System.out.println("still held lock");
		}
		} catch (Throwable e) {
		System.out.println(e);
		}
	}
}

/*
public class t1 {
	public static void main(String[] args) {
		try {
		lock.lock();
		lock.lock();
		double num = 0.800338958916741818D;
		boolean b = true;

		byte c = 2;

		System.out.printf( "boolean:%b num:%f %d\n", b, Math.ceil(num * 10.0) / 10, (long)123456789);

		List a1 = new ArrayList();
		a1.add("Zara");
		a1.add("Mahnaz");
		a1.add("Ayan");      
		List a2 = a1;
		a2.set(1, "Samuel");
		System.out.println("ArrayList Elements-->");
		System.out.print("\t" + a1 + "\t" + a2);

		System.out.print("\t" + c);
		System.out.print("\n");
		} catch (Throwable e) {
		System.out.println("throwable");
		}
	}
}
*/
