import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Scanner;

public class CengPokeParser {

	public static ArrayList<CengPoke> parsePokeFile(String filename)
	{
		ArrayList<CengPoke> pokeList = new ArrayList<CengPoke>();

		// You need to parse the input file in order to use GUI tables.
		// TODO: Parse the input file, and convert them into CengPokes

		return pokeList;
	}
	
	public static void startParsingCommandLine() throws IOException
	{
		// TODO: Start listening and parsing command line -System.in-.
		// There are 5 commands:
		// 1) quit : End the app. Print nothing, call nothing.
		// 2) add : Parse and create the poke, and call CengPokeKeeper.addPoke(newlyCreatedPoke).
		// 3) search : Parse the pokeKey, and call CengPokeKeeper.searchPoke(parsedKey).
		// 4) delete: Parse the pokeKey, and call CengPokeKeeper.removePoke(parsedKey).
		// 5) print : Print the whole hash table with the corresponding buckets, call CengPokeKeeper.printEverything().

		// Commands (quit, add, search, print) are case-insensitive.

		Scanner scanner = new Scanner(System.in);
		String cmd;

		while (true){
			cmd = scanner.nextLine();
			String[] tokens = cmd.split("\t");
			if ("quit".equalsIgnoreCase(tokens[0])){
				break;
			}
			else if ("add".equalsIgnoreCase(tokens[0])){
				int pokeKey = Integer.parseInt(tokens[1]);
				String pokeName = tokens[2];
				String pokePower = tokens[3];
				String pokeType = tokens[4];
				CengPoke poke = new CengPoke(pokeKey, pokeName, pokePower, pokeType);
				CengPokeKeeper.addPoke(poke);

			}
			else if ("search".equalsIgnoreCase(tokens[0])){
				int pokeKey = Integer.parseInt(tokens[1]);
				CengPokeKeeper.searchPoke(pokeKey);
			}
			else if ("delete".equalsIgnoreCase(tokens[0])){
				int pokeKey = Integer.parseInt(tokens[1]);
				CengPokeKeeper.deletePoke(pokeKey);
			}
			else if ("print".equalsIgnoreCase(tokens[0])){
				CengPokeKeeper.printEverything();
			}
		}
		scanner.close();
	}
}
