package neilson;

import org.apache.commons.daemon.Daemon;
import org.apache.commons.daemon.DaemonContext;
import org.apache.commons.daemon.DaemonInitException;

import java.util.concurrent.locks.ReentrantLock;

public class MyDaemon implements Daemon {

	private Thread myThread; 
	private boolean stopped = false;
	private boolean lastOneWasATick = false;

	private final ReentrantLock lock = new ReentrantLock();

	@Override
	public void init(DaemonContext daemonContext) throws DaemonInitException, Exception {
		/*
		 * Construct objects and initialize variables here.
		 * You can access the command line arguments that would normally be passed to your main() 
		 * method as follows:
		 */
		String[] args = daemonContext.getArguments(); 

		myThread = new Thread(){
			private long lastTick = 0;

			@Override
			public synchronized void start() {
				MyDaemon.this.stopped = false;
				super.start();
			}

			@Override
			public void run() {             
				lock.lock();
				while(!stopped){
					long now = System.currentTimeMillis();
					if(now - lastTick >= 1000){
						System.out.println(!lastOneWasATick ? "tick" : "tock");
						lastOneWasATick = !lastOneWasATick;
						lastTick = now; 
					}
				}

				lock.unlock();
				if (lock.isHeldByCurrentThread()) {
					System.out.println("still held lock");
				}
			}
		};
	}

	@Override
	public void start() throws Exception {
		myThread.start();
	}

	@Override
	public void stop() throws Exception {
		stopped = true;
		try{
			myThread.join(1000);
		}catch(InterruptedException e){
			System.err.println(e.getMessage());
			throw e;
		}
	}

	@Override
	public void destroy() {
		myThread = null;
	}
}

/*
public class MyDaemon implements Daemon, Runnable{

	@Override
	public void init(DaemonContext arg0) throws DaemonInitException, Exception {
		setup(arg0.getArguments());

	}

	@Override
	public void start() throws Exception {
		MountMDFS sd = new MountMDFS();
		Thread th = new Thread(sd);
		th.start();
	}

	@Override
	public void stop() throws Exception {
		MDFSLogger.getLog().info("Please Wait while shutting down MDFS");
		MDFSLogger.getLog().info("Data Can be lost if this is interrupted");
		mdfsService.stop();
		MDFSLogger.getLog().info("All Data Flushed");
		try {
			Process p = Runtime.getRuntime().exec("umount " + mountOptions);
			p.waitFor();
		} catch (Exception e) {
		}
		MDFSLogger.getLog().info("MDFS Shut Down Cleanly");

	}

	@Override
	public void run() {
		try {

			FuseMount.mount(sFal, new MDFSFileSystem(Main.volume.getPath(),
						Main.volumeMountPoint), log);
			shutdownHook.shutdown();
			System.exit(0);
		} catch (Exception e) {
			e.printStackTrace();
		}

	}

}
*/
