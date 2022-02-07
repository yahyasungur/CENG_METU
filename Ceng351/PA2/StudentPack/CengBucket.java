import java.util.Vector;

public class CengBucket {

	// GUI-Based Methods
	// These methods are required by GUI to work properly.
	private int bucketSize;
	private Vector<CengPoke> bucketElements;
	private int local_depth = 0;

	public CengBucket() {
		this.bucketSize = CengPokeKeeper.getBucketSize();
		this.bucketElements = new Vector<CengPoke>(this.bucketSize);
	}
// geçici
	public CengBucket(int bucketSize) {
		this.bucketSize = bucketSize;
		this.bucketElements = new Vector<CengPoke>(this.bucketSize);
	}
	
	public int pokeCount()
	{
		// TODO: Return the pokemon count in the bucket.
		return this.bucketElements.size();
	}
	
	public CengPoke pokeAtIndex(int index)
	{
		// TODO: Return the corresponding pokemon at the index.
		return this.bucketElements.get(index);
	}
	
	public int getHashPrefix()
	{
		// TODO: Return hash prefix length.
		return this.local_depth;
	}
	
	public Boolean isVisited()
	{
		// TODO: Return whether the bucket is found while searching.
		return false;		
	}
	
	// Own Methods
	public int getLocalDepth(){
		return this.local_depth;
	}

	public void setLocalDepth(int local_depth){
		this.local_depth = local_depth;
	}

	public int getBucketSize(){
		return this.bucketSize;
	}

	public void addPoke(CengPoke poke){
		this.bucketElements.addElement(poke);
	}

	public void deletePoke(int pokeKey){
		for(int i=0; i< this.bucketElements.size(); i++){
			if (this.bucketElements.get(i).pokeKey() == pokeKey){
				this.bucketElements.remove(i);
			}
		}
	}
}
