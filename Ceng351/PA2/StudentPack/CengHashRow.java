public class CengHashRow {

	// GUI-Based Methods
	// These methods are required by GUI to work properly.

	private String prefix;
	private CengBucket bucket;

	public String hashPrefix()
	{
		// TODO: Return row's hash prefix (such as 0, 01, 010, ...)
		return this.prefix;
	}
	
	public CengBucket getBucket()
	{
		// TODO: Return the bucket that the row points at.
		return this.bucket;
	}
	
	public boolean isVisited()
	{
		// TODO: Return whether the row is used while searching.
		return false;		
	}

	// Own Methods

	public void set_hashPrefix(String prefix){
		this.prefix = prefix;
	}

	public void  setBucket(CengBucket bucket){
		this.bucket = bucket;
	}
}
