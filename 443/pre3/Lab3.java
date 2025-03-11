/**
 * This class takes filename from command line and answers the questions accordingly
 *  
 * File has columns:
 * Age: Age of the customer on the purchase date.
 * Date: Date of purchase.
 * A, B, C, D, E: The price of five products that were purchased. If the product was not purchased, the value is empty.
 * 
 * Author: Yahya SUNGUR
 * Date: 31/05/2023
**/ 

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.stream.Stream;

public class Lab3 {

    // Question 1: What was the most vital product type between and including 1980 and 1990? 
    // (You can assume that the vital products are the ones bought on pay days,15th of every month.)
    public static void question1(Stream<String> lines){
        // Filter the lines between and including 1980 and 1990
        // Filter the lines with date has 15th day of the month
        // Count the not empty cell for each product
        // Return the index of the product with maximum count
        lines.skip(1)
        .filter(line -> {
            String[] columns = line.split(",");
            int year = Integer.parseInt(columns[1].split("-")[0]);
            return year >= 1980 && year <= 1990;
        }).filter(line -> {
            String[] columns = line.split(",");
            int day = Integer.parseInt(columns[1].split("-")[2]);
            return day == 15;
        }).map(line -> {
            String[] columns = line.split(",");
            int[] count = new int[5];
            for(int i = 2; i < columns.length; i++){
                if(!columns[i].equals("")){
                    count[i-2]++;
                }
            }
            return count;
        }).reduce((a, b) -> {
            for(int i = 0; i < a.length; i++){
                a[i] += b[i];
            }
            return a;
        }).ifPresent(count -> {
            int maxIndex = 0;
            for(int i = 1; i < count.length; i++){
                if(count[i] > count[maxIndex]){
                    maxIndex = i;
                }
            }
            System.out.println((char)('A' + maxIndex));
        });
    }

    // Question 2: How many purchases with 3 or more products include A or D?
    public static void question2(Stream<String> lines){
        // Filter the lines with 3 or more products
        // Filter the lines contains A or D
        // Count the lines
        // Print the count
        long countOfLines = lines.skip(1)
        .filter(line -> {
            String[] columns = line.split(",");
            int count = 0;
            for(int i = 2; i < columns.length; i++){
                if(!columns[i].equals("")){
                    count++;
                }
            }
            return count >= 3;
        }).filter(line -> {
            String[] columns = line.split(",");
            if((columns.length > 2 && !columns[2].equals("")) 
                || (columns.length > 5 && !columns[5].equals(""))) return true;
            return false;
        }).count();
        System.out.println(countOfLines);
    }

    // Question 3: How many products are purchased by elder people (age 55 or above) after and including 1995?
    public static void question3(Stream<String> lines){
        // Filter the lines after and including 1995
        // Filter the lines with age 55 or above
        // Count the not empty cell for each product
        // Return the sum of the counts
        lines.skip(1)
        .filter(line -> {
            String[] columns = line.split(",");
            int year = Integer.parseInt(columns[1].split("-")[0]);
            return year >= 1995;
        }).filter(line -> {
            String[] columns = line.split(",");
            int age = Integer.parseInt(columns[0]);
            return age >= 55;
        }).map(line -> {
            String[] columns = line.split(",");
            int[] count = new int[5];
            for(int i = 2; i < columns.length; i++){
                if(!columns[i].equals("")){
                    count[i-2]++;
                }
            }
            return count;
        }).reduce((a, b) -> {
            for(int i = 0; i < a.length; i++){
                a[i] += b[i];
            }
            return a;
        }).ifPresent(count -> {
            int sum = 0;
            for(int i = 0; i < count.length; i++){
                sum += count[i];
            }
            System.out.println(sum);
        });
    }

    // Question 4: What was the years that least and most B type products sold? Solve this question by
    // reading the stream only once. (Hint: Remember that the number of years in the dataset is finite.)
    // We know that here will be no purchases older than 1970 and newer than 2020.
    public static void question4(Stream<String> lines){
        // Filter the line which has B type product
        // Count the number of lines for each year
        // Find the year with minimum and maximum count
        // Print the years
        lines.skip(1).filter(line -> {
            String[] columns = line.split(",");
            if(columns.length > 3 && !columns[3].equals("")) return true;
            return false;
        }).map(line -> {
            String[] columns = line.split(",");
            int year = Integer.parseInt(columns[1].split("-")[0]);
            return year;
        }).map(year -> {
            int[] count = new int[51];
            count[year - 1970]++;
            return count;
        }).reduce((a, b) -> {
            for(int i = 0; i < a.length; i++){
                a[i] += b[i];
            }
            return a;
        }).ifPresent(count -> {
            int minIndex = 0;
            int maxIndex = 0;
            for(int i = 1; i < count.length; i++){
                if(count[i] < count[minIndex]){
                    minIndex = i;
                }
                if(count[i] > count[maxIndex]){
                    maxIndex = i;
                }
            }
            System.out.println(minIndex + 1970);
            System.out.println(maxIndex + 1970);
        });
    }


    // Read the file, drop first line and process it according to the question
    public static void answerQuestion(String filename, int question) throws IOException{
        try(Stream<String> lines = Files.lines(Paths.get(filename))){
            switch (question) {
                case 1:
                    question1(lines);
                    break;
                case 2:
                    question2(lines);
                    break;
                case 3:
                    question3(lines);
                    break;
                case 4:
                    question4(lines);
                    break;
                default:
                    System.out.println("Invalid question number");
                    System.exit(0);
            }
        }catch(IOException e){
            System.out.println("File not found");
            System.exit(0);
        }
    }


    public static void main(String[] args) throws IOException{
        // Take filename from command line
        if(args.length == 0){
            System.out.println("No filename given");
            System.exit(0);
        }
        String filename = args[0];
        
        // Take question number from command line
        if(args.length == 1){
            System.out.println("No question number given");
            System.exit(0);
        }
        int question = Integer.parseInt(args[1]);

        answerQuestion(filename, question);
    }
}
