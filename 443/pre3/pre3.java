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

public class pre3{

    // Question 1: What was the price of most expensive product sold?
    public static void question1(Stream<String> lines){
        // Find the maximum price of each line and return the maximum of them
        double maxPrice = lines.skip(1).map(line -> {
            String[] columns = line.split(",");
            double maxPriceOfLine = 0;
            for(int i = 2; i < columns.length; i++){
                if(!columns[i].equals("")){
                    double price = Double.parseDouble(columns[i]);
                    if(price > maxPriceOfLine){
                        maxPriceOfLine = price;
                    }
                }
            }
            return maxPriceOfLine;
        }).max(Double::compareTo).get();
        System.out.println("The price of most expensive product sold: " + maxPrice);
    }

    // Question 2: What was the date of the highest paid purchase by a customer?
    public static void question2(Stream<String> lines){
        // Find the total purchase for each line
        // Return the date of the line with maximum total purchase
        lines.skip(1).map(line -> {
            String[] columns = line.split(",");
            double totalPurchase = 0;
            for(int i = 2; i < columns.length; i++){
                if(!columns[i].equals("")){
                    totalPurchase += Double.parseDouble(columns[i]);
                }
            }
            return new String[]{columns[1], String.valueOf(totalPurchase)};
        }).max((a, b) -> {
            double totalPurchaseA = Double.parseDouble(a[1]);
            double totalPurchaseB = Double.parseDouble(b[1]);
            return Double.compare(totalPurchaseA, totalPurchaseB);
        }).ifPresent(line -> {
            System.out.println("The date of the highest paid purchase by a customer: " + line[0]);
        });
    }

    // Question 3: What was the most popular product before 2000?
    public static void question3(Stream<String> lines){
        // Filter the lines before 2000
        // Find the not empty cell count for each product
        // Return the index of the product with maximum count
        lines.skip(1)
        .filter(line -> {
            String[] columns = line.split(",");
            int year = Integer.parseInt(columns[1].split("-")[0]);
            return year < 2000;
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
            System.out.println("The most popular product before 2000: " + (char)('A' + maxIndex));
        });
    }

    // Question 4: What was the least popular product after and including 2000?
    public static void question4(Stream<String> lines){
        // Filter the lines after and including 2000
        // Find the not empty cell count for each product
        // Return the index of the product with minimum count
        lines.skip(1)
        .filter(line -> {
            String[] columns = line.split(",");
            int year = Integer.parseInt(columns[1].split("-")[0]);
            return year >= 2000;
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
            int minIndex = 0;
            for(int i = 1; i < count.length; i++){
                if(count[i] < count[minIndex]){
                    minIndex = i;
                }
            }
            System.out.println("The least popular product after and including 2000: " + (char)('A' + minIndex));
        });
    }

    // Question 5: What was the most popular product among teens? (Hint: find the product with the smallest average customer age)
    public static void question5(Stream<String> lines){
        // Find the not empty cell count for each product
        // Find the sum of the ages for the rows with not empty cells for each product
        // Find the average age for each product
        // Return the index of the product with minimum average age
        lines.skip(1).map(line -> {
            String[] columns = line.split(",");
            double[] count = new double[5];
            double[] sum = new double[5];
            for(int i = 2; i < columns.length; i++){
                if(!columns[i].equals("")){
                    count[i-2]++;
                    sum[i-2] += Double.parseDouble(columns[0]);
                }
            }
            return new double[][]{count, sum};
        }).reduce((a, b) -> {
            for(int i = 0; i < a[0].length; i++){
                a[0][i] += b[0][i];
                a[1][i] += b[1][i];
            }
            return a;
        }).ifPresent(countAndSum -> {
            double[] average = new double[5];
            for(int i = 0; i < countAndSum[0].length; i++){
                average[i] = countAndSum[1][i] / countAndSum[0][i];
            }
            int minIndex = 0;
            for(int i = 1; i < average.length; i++){
                if(average[i] < average[minIndex]){
                    minIndex = i;
                }
            }
            System.out.println("The most popular product among teens: " + (char)('A' + minIndex));
        });
    }

    // Question 6: What was the most inflated product on the data? When calculating only consider the
    // oldest and the newest purchase and not the purchases between.
    public static void question6(Stream<String> lines, Stream<String> lines2){
        // Sort the lines by date
        // Find the oldest and the newest purchase for each product
        // Find the difference between the prices of the oldest and the newest purchase for each product
        // Find the ratio of the difference to the oldest purchase price for each product
        // Return the index of the product with maximum ratio
        lines.skip(1).sorted((a, b) -> {
            String[] columnsA = a.split(",");
            String[] columnsB = b.split(",");
            return columnsA[1].compareTo(columnsB[1]);
        }).map(line -> {
            String[] columns = line.split(",");
            double[] min = new double[5];
            double[] max = new double[5];
            for(int i = 2; i < columns.length; i++){
                if(!columns[i].equals("")){
                    if(min[i-2] == 0){
                        min[i-2] = Double.parseDouble(columns[i]);
                    }
                    max[i-2] = Double.parseDouble(columns[i]);
                }
            }
            return new double[][]{min, max};
        }).reduce((a, b) -> {
            for(int i = 0; i < a[0].length; i++){
                if(a[0][i] == 0){
                    a[0][i] = b[0][i];
                }
                if(b[0][i] != 0){
                    a[0][i] = Math.min(a[0][i], b[0][i]);
                }
                a[1][i] = Math.max(a[1][i], b[1][i]);
            }
            return a;
        }).ifPresent(minAndMax -> {
            double[] ratio = new double[5];
            for(int i = 0; i < minAndMax[0].length; i++){
                ratio[i] = (minAndMax[1][i] - minAndMax[0][i]) / minAndMax[0][i];
            }
            int maxIndex = 0;
            for(int i = 1; i < ratio.length; i++){
                if(ratio[i] > ratio[maxIndex]){
                    maxIndex = i;
                }
            }
            System.out.println("The most inflated product on the data: " + (char)('A' + maxIndex) + " with ratio: " + ratio[maxIndex]);
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
                case 5:
                    question5(lines);
                    break;
                case 6:
                    // Copy the stream to be able to use it twice
                    Stream<String> linesCopy = Files.lines(Paths.get(filename));
                    question6(lines, linesCopy);
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
