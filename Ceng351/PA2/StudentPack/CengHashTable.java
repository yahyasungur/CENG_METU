import java.util.Vector;

public class CengHashTable {
	int global_depth = 0;
	Vector<CengHashRow> hash_table;
	int hashMod = CengPokeKeeper.getHashMod();
	int bucket_size = CengPokeKeeper.getBucketSize();

	public CengHashTable(){
		hash_table = new Vector<CengHashRow>(1);
		CengHashRow hashRow = new CengHashRow();
		CengBucket bucket = new CengBucket();
		bucket.setLocalDepth(0);
		//hashRow.set_hashPrefix("");
		hashRow.setBucket(bucket);
		hash_table.addElement(hashRow);
	}

	public void deletePoke(Integer pokeKey){
		int size = this.hash_table.size();
		for (int i = 0; i < size; i++){
			int num_of_poke = this.hash_table.get(i).getBucket().pokeCount();
			for (int j = num_of_poke-1; j >= 0 ; j--){
				if (this.hash_table.get(i).getBucket().pokeAtIndex(j).pokeKey() == pokeKey){
					this.hash_table.get(i).getBucket().deletePoke(pokeKey);
				}
			}
		}


		Integer number_of_empty_buckets = 0;

		for (int i = 0; i< this.hash_table.size();){
			int number_of_pointers = (int)Math.pow(2, global_depth - this.hash_table.get(i).getBucket().getLocalDepth());
			if (this.hash_table.get(i).getBucket().pokeCount() == 0){
				number_of_empty_buckets++;
			}
			i = i + number_of_pointers;
		}

		String json = "\"delete\": {\n\t\"emptyBucketNum\": " + number_of_empty_buckets.toString() + "\n}";

		System.out.println(json);
	}

	public void addPoke(CengPoke poke){
		int hashValue = poke.pokeKey() % hashMod;
		String binary = Integer.toBinaryString(hashValue);
		String binary_hashMod = Integer.toBinaryString(hashMod);
		int binary_length = binary.length();
		if (binary_length < binary_hashMod.length()){
			for (int i = 0; i < binary_hashMod.length()-binary_length-1; i++){
				binary = "0" + binary;
			}
		}
		if (binary.length() >= binary_hashMod.length()){
			binary = binary.substring(binary.length()-(binary_hashMod.length()-1));
		}
		poke.setHash(binary);

		String hashIndex;
		if (global_depth < binary.length()){
			hashIndex = binary.substring(0,global_depth);

		}else {
			hashIndex = binary;
		}

		if (hashIndex.length() == 0){
			hashIndex = "0";
		}

		int index = Integer.parseInt(hashIndex,2);
		int number_of_poke = this.hash_table.get(index).getBucket().pokeCount();

		if (number_of_poke < this.bucket_size){
			this.hash_table.get(index).getBucket().addPoke(poke);
		}
		else{
			CengBucket redistributeBucket = new CengBucket();
			for (int i = 0; i < this.hash_table.get(index).getBucket().pokeCount(); i++){
				redistributeBucket.addPoke(this.hash_table.get(index).getBucket().pokeAtIndex(i));
			}
			int local_depth = this.hash_table.get(index).getBucket().getLocalDepth();
			local_depth++;
			this.hash_table.get(index).getBucket().setLocalDepth(local_depth);
			CengBucket new_bucket = new CengBucket();
			new_bucket.setLocalDepth(local_depth);

			if (local_depth > this.global_depth){
				Vector<CengHashRow> new_hash_table = new Vector<CengHashRow>(this.hash_table.size()*2);
				this.global_depth++;
				int old_index = -1;
				int number_tracker = 0;
				int fill_with_new = 0;

				for (int i = 0; i < this.hash_table.size()*2; i++){
					if (number_tracker == 0){
						old_index++;
						if (fill_with_new == 1){
							fill_with_new = 2;
						}

						if (old_index == (index+1) && fill_with_new == 0){
							fill_with_new = 1;
							number_tracker = (int) Math.pow(2, global_depth- new_bucket.getLocalDepth());
							old_index--;
						}
						else if (old_index < this.hash_table.size()){
							int lcldpth = hash_table.get(old_index).getBucket().getLocalDepth();
							number_tracker = (int) Math.pow(2,global_depth-lcldpth);
						}
						else {
							number_tracker = (int) Math.pow(2, global_depth- new_bucket.getLocalDepth());
						}
					}else {
						number_tracker = (int) Math.pow(2, global_depth- new_bucket.getLocalDepth());
					}
					CengHashRow hashRow = new CengHashRow();
					// look here some changes applied...
					if (old_index < this.hash_table.size() && (fill_with_new != 1)){
						//hashRow.set_hashPrefix(this.hash_table.get(old_index).hashPrefix());
						hashRow.setBucket(this.hash_table.get(old_index).getBucket());
						if (old_index == index){
							int countofpoke = this.hash_table.get(old_index).getBucket().pokeCount();
							if (countofpoke != 0){
								for (int j = countofpoke-1; j>=0 ; j--){
									hashRow.getBucket().deletePoke(hashRow.getBucket().pokeAtIndex(j).pokeKey());
								}
							}
						}

					}else{
						hashRow.setBucket(new_bucket);
					}

					new_hash_table.addElement(hashRow);
					number_tracker--;
				}
				this.hash_table = new_hash_table;
			}
			else {
				// local depth is smaller
				int number_of_pointer = (int)Math.pow(2, global_depth-local_depth);
				String bnry = Integer.toBinaryString(index);
				int new_index = Integer.parseInt(bnry.substring(0,local_depth-1));

				int countofpoke = this.hash_table.get(index).getBucket().pokeCount();
				if (countofpoke != 0){
					for (int j = countofpoke-1; j>=0 ; j--){
						this.hash_table.get(index).getBucket().deletePoke(this.hash_table.get(index).getBucket().pokeAtIndex(j).pokeKey());
					}
				}

				for (int i = 0; i < number_of_pointer; i++){
					this.hash_table.get(new_index+i).setBucket(new_bucket);
				}


			}

			// redistribute the elements
			for (int i = 0; i < redistributeBucket.pokeCount(); i++){
				addPoke(redistributeBucket.pokeAtIndex(i));
			}

			// add new poke
			addPoke(poke);
		}
	}
	
	public void searchPoke(Integer pokeKey){
		Vector<Integer> indexes = new Vector<Integer>();

		int size = this.hash_table.size();
		for (int i = 0; i < size ; i++){
			int pokeCount = this.hash_table.get(i).getBucket().pokeCount();
			for (int j = 0; j < pokeCount; j++){
				if (this.hash_table.get(i).getBucket().pokeAtIndex(j).pokeKey() == pokeKey){
					indexes.addElement(i);
				}
			}
		}

		if (indexes.size() == 0){
			System.out.println("\"search\": {\n}");
			return;
		}

		// print indexes daki indexlere ait rowları

		String json = "\"search\": {";
		for (int i = 0; i < indexes.size(); i++){
			Integer index = indexes.get(i);
			String row_json = prepareRow(this.hash_table.get(index),index);
			json = json + row_json + ",";
		}
		json = json.substring(0,json.length()-1);
		json = json + "}";

		// printing json

		int number_of_tabs = 0;
		String string = "";
		for (int i = 0; i < json.length() ;i++){
			string = string + json.charAt(i);
			if (json.charAt(i) == '{' || json.charAt(i) == '['){
				for (int j = 0; j < number_of_tabs; j++){
					string = "\t" + string;
				}
				number_of_tabs++;
				System.out.println(string);
				string = "";
			}
			else if (json.charAt(i) == '}' || json.charAt(i) == ']'){
				if (string.length() > 2){
					for (int j = 0; j < number_of_tabs; j++){
						string = "\t" + string;
					}
					System.out.println(string.substring(0,string.length()-1));
					number_of_tabs--;
					string = Character.toString(string.charAt(string.length()-1));
					if (i+1 < json.length() && json.charAt(i+1) == ','){
						continue;
					}
					for (int j = 0; j < number_of_tabs; j++){
						string = "\t" + string;
					}
					System.out.println(string);
					string = "";
				}
				else {
					if (i+1 < json.length() && json.charAt(i+1) == ','){
						number_of_tabs--;
						continue;
					}
					number_of_tabs--;
					for (int j = 0; j < number_of_tabs; j++){
						string = "\t" + string;
					}
					System.out.println(string);
					string = "";
				}
			}
			else if (json.charAt(i) == ','){
				for (int j = 0; j < number_of_tabs; j++){
					string = "\t" + string;
				}
				System.out.println(string);
				string = "";
			}
		}
	}
	
	public void print(){
		String json = "\"table\": {";
		for (int i = 0; i < this.hash_table.size(); i++){
			String row_json = prepareRow(this.hash_table.get(i),i);
			json = json + row_json + ",";
		}
		json = json.substring(0,json.length()-1);
		json = json + "}";

		//printing the json file

		int number_of_tabs = 0;
		String string = "";
		for (int i = 0; i < json.length() ;i++){
			string = string + json.charAt(i);
			if (json.charAt(i) == '{' || json.charAt(i) == '['){
				for (int j = 0; j < number_of_tabs; j++){
					string = "\t" + string;
				}
				number_of_tabs++;
				System.out.println(string);
				string = "";
			}
			else if (json.charAt(i) == '}' || json.charAt(i) == ']'){
				if (string.length() > 2){
					for (int j = 0; j < number_of_tabs; j++){
						string = "\t" + string;
					}
					System.out.println(string.substring(0,string.length()-1));
					number_of_tabs--;
					string = Character.toString(string.charAt(string.length()-1));
					if (i+1 < json.length() && json.charAt(i+1) == ','){
						continue;
					}
					for (int j = 0; j < number_of_tabs; j++){
						string = "\t" + string;
					}
					System.out.println(string);
					string = "";
				}
				else {
					if (i+1 < json.length() && json.charAt(i+1) == ','){
						number_of_tabs--;
						continue;
					}
					number_of_tabs--;
					for (int j = 0; j < number_of_tabs; j++){
						string = "\t" + string;
					}
					System.out.println(string);
					string = "";
				}
			}
			else if (json.charAt(i) == ','){
				for (int j = 0; j < number_of_tabs; j++){
					string = "\t" + string;
				}
				System.out.println(string);
				string = "";
			}
		}

	}

	// GUI-Based Methods
	// These methods are required by GUI to work properly.
	
	public int prefixBitCount()
	{
		// TODO: Return table's hash prefix length.
		return 0;		
	}
	
	public int rowCount()
	{
		// TODO: Return the count of HashRows in table.
		return 0;		
	}
	
	public CengHashRow rowAtIndex(int index)
	{
		// TODO: Return corresponding hashRow at index.
		return null;
	}
	
	// Own Methods

	public String preparePoke(CengPoke poke){

		String binary = poke.pokeHash();

		String json = "\"poke\": {\"hash\": " + binary + ",\"pokeKey\": " + poke.pokeKey().toString()+ ",\"pokeName\": "+
				poke.pokeName()+",\"pokePower\": " + poke.pokePower() + ",\"pokeType\": " + poke.pokeType() + "}";

		return json;
	}

	public String prepareBucket(CengBucket bucket){

		String json = "\"bucket\": {\"hashLength\": " + bucket.getLocalDepth() + ",\"pokes\": [";
		for (int i = 0; i < bucket.pokeCount(); i++){
			String poke_json = preparePoke(bucket.pokeAtIndex(i));
			json = json + poke_json + ",";
		}
		if (json.charAt(json.length()-1) == ','){
			json = json.substring(0,json.length()-1);
		}
		json = json + "]}";

		return  json;
	}

	public String prepareRow(CengHashRow hashRow, Integer index){
		int number_of_bits = hashRow.getBucket().getLocalDepth();
		String binary = Integer.toBinaryString(index);
		String binary_hashMod = Integer.toBinaryString(hashMod);

		if (binary.length() < binary_hashMod.length()){
			int num_of_times = this.global_depth-binary.length();
			for (int i = 0; i < num_of_times ; i++){
				binary = "0" + binary;
			}
		}

		String hashPrefix = binary.substring(0,this.global_depth);
		if (number_of_bits == 0){
			hashPrefix = "0";
		}

		String json = "\"row\": {\"hashPref\": " + hashPrefix + ",";
		String bucket_json = prepareBucket(hashRow.getBucket());
		json = json + bucket_json + "}";

		return json;
	}

}
