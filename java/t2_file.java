
import java.io.File;

public class t2 {
	public static void main(String[] args) {
//		File f = new File(args[0]);
//		System.out.println(f.getPath());
//		File[] f0 = f.listFiles();
		File[] f0 = new File(args[0]).listFiles();
		for (File tf: f0) {
		System.out.println(tf.getPath());
		System.out.println(tf.getName());
		}
	}
}


/*
import java.lang.String;
public class t2 {
	public static void main(String[] args) {
		File nf = new File(args[0]);
		String srcPath = args[1];

		File[] files = new File(nf.getPath()+File.separator + "files").listFiles();
		File tmpf = new File(nf.getPath() + File.separator + "files" + File.separator + srcPath);
		if( !tmpf.getParentFile().exists()) {
			System.out.println("not exists");
			tmpf.getParentFile().mkdirs();
			for(File tf:files) {
				tf.renameTo(new File(tmpf.getParent()+File.separator+tf.getName()));
			}
		} else {
			System.out.println("exists");
		}
	}
}
*/

/*
import java.io.ObjectOutputStream;
import java.io.FileOutputStream;

public class t2 {
	public static void main(String[] args) {
		try {
			FileOutputStream fos = new FileOutputStream("t.tmp");
			ObjectOutputStream oos = new ObjectOutputStream(fos);

			oos.writeObject("aa");

			oos.close();
		} catch (Throwable e) {
		}
	}
}
*/
