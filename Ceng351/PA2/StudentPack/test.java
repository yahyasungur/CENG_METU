

public class test {
    static int hashMod = 8;

    public static void main(String[] args) throws Exception {
        CengPoke poke = new CengPoke(1,"Pikachu","100","Electric");
        CengBucket bucket = new CengBucket(2);
        CengHashRow hashRow = new CengHashRow();
        //bucket.addPoke(poke);
        hashRow.setBucket(bucket);
        String json = prepareRow(hashRow,0);
        System.out.println(json);
    }















    public static String preparePoke(CengPoke poke){

        int hashValue = poke.pokeKey() % hashMod;
        String binary = Integer.toBinaryString(hashValue);
        String binary_hashMod = Integer.toBinaryString(hashMod);

        if (binary.length() < binary_hashMod.length()){
            for (int i = 0; i < binary_hashMod.length()-binary.length(); i++){
                binary = "0" + binary;
            }
        }
        String json = "\"poke\": {\"hash\": " + binary + ",\"pokeKey\": " + poke.pokeKey().toString()+ ",\"pokeName\": "+
                poke.pokeName()+",\"pokePower\": " + poke.pokePower() + ",\"pokeType\": " + poke.pokeType() + "}";

        return json;
    }

    public static String prepareBucket(CengBucket bucket){

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

    public static String prepareRow(CengHashRow hashRow, Integer index){
        int number_of_bits = hashRow.getBucket().getLocalDepth();
        String binary = Integer.toBinaryString(index);
        String binary_hashMod = Integer.toBinaryString(hashMod);

        if (binary.length() < binary_hashMod.length()){
            for (int i = 0; i < binary_hashMod.length()-binary.length(); i++){
                binary = "0" + binary;
            }
        }

        String hashPrefix = binary.substring(0,number_of_bits);
        if (number_of_bits == 0){
            hashPrefix = "0";
        }

        String json = "\"row\": {\"hashPref\": " + hashPrefix + ",";
        String bucket_json = prepareBucket(hashRow.getBucket());
        json = json + bucket_json + "}";

        return json;
    }
}
