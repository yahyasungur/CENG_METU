public class CengPoke {

	private String hash;
	private Integer pokeKey;
	private String pokeName;
	private String pokePower;
	private String pokeType;
	
	public CengPoke(Integer pokeKey, String pokeName, String pokePower, String pokeType)
	{
		this.pokeKey = pokeKey;
		this.pokeName = pokeName;
		this.pokePower = pokePower;
		this.pokeType = pokeType;
	}
	
	// Getters
	
	public Integer pokeKey()
	{
		return pokeKey;
	}
	public String pokeName()
	{
		return pokeName;
	}
	public String pokePower()
	{
		return pokePower;
	}
	public String pokeType()
	{
		return pokeType;
	}
	public String pokeHash(){return hash;}
	public void setHash(String hash){
		this.hash = hash;
	}
		
	// GUI method - do not modify
	public String fullName()
	{
		return "" + pokeKey() + "\t" + pokeName() + "\t" + pokePower() + "\t" + pokeType;
	}
		
	// Own Methods
}
