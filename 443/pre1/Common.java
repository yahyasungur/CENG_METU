import java.awt.*;
import java.util.concurrent.ThreadLocalRandom;
import java.util.List;
import java.util.ArrayList;

public class Common {
    private static final String title = "Economics 101";
    private static final int windowWidth = 1650;
    private static final int windowHeight = 1000;

    private static final int entityDiameter = 20; //diameter of drawn entity (customer or store)

    private static final int storeNo = 10; //number of stores in the simulation
    private static final int customerNo = 10; //number of customers

    private static final int stockReplenishmentFrequency = 3000; // number of stepAllEntities calls before replenishing all stores

    private static final int foodBottomPrice = 20;
    private static final int foodCeilingPrice = 50;
    private static final int electronicsBottomPrice = 200;
    private static final int electronicsCeilingPrice = 2000;
    private static final int LuxuryBottomPrice = 5000;
    private static final int LuxuryCeilingPrice = 10000;

    private static final int minimumShoppingListLength = 5;
    private static final int maximumShoppingListLength = 10;

    private static final int stockStorageMin = 15; //minimum size of storage available for a store
    private static final int stockStorageMax = 25; //maximum number of storage available for a store

    private static final int customerMovementSpeed = 2;
    private static final Font font =new Font("Verdana", Font.BOLD, 20);

    public static String getTitle() {
        return title;
    }

    public static int getWindowWidth() {
        return windowWidth;
    }

    public static int getWindowHeight() {
        return windowHeight;
    }

    public static int getEntityDiameter(){ return entityDiameter;}

    public static Font getFont() {return font;}

    public static int getCustomerMovementSpeed() {
        return customerMovementSpeed;
    }


    private static List<Store> stores = new ArrayList<Store>();
    private static List<Customer> customers = new ArrayList<Customer>();
    private static int lastRestock = 0;

    public static List<Store> getStores() {
        return stores;
    }

    public static List<Customer> getCustomers() {
        return customers;
    }

    public static Product chooseProduct(){
        switch(randInt(0,2)){
            case 0:
                //Food
                return Product.Food;
            case 1:
                //Electronics
                return Product.Electronics;
            case 2:
            default:
                //Luxury
                return Product.Luxury;
        }
    }

    public static Customer createCustomer(){
        double x = randInt(0,windowWidth-2*entityDiameter);
        double y = randInt(0,windowHeight-2*entityDiameter);
        Customer.Strategy strategy;

        switch(randInt(0, 2)){
            case 0:
                strategy = Customer.Strategy.Cheapest;
                break;
            case 1:
                strategy = Customer.Strategy.Closest;
                break;
            case 2:
            default:
                strategy = Customer.Strategy.Travelling;
                break;
        }
        ArrayList<Product> shoppingList = new ArrayList<Product>();
        for (int i = 0; i < randInt(minimumShoppingListLength, maximumShoppingListLength); i++){
            shoppingList.add(chooseProduct());
        }

        return new Customer(x, y, strategy, shoppingList);
    }

    private static int currentStoreType = 0;
    public static Store createStore() {
        double x = randInt(0, windowWidth - 2 * entityDiameter);
        double y = randInt(0, windowHeight - 2 * entityDiameter);
        int maxStock = randInt(stockStorageMin, stockStorageMax);
        int price;
        Product type;
        switch (currentStoreType) {
            case 0:
                type = Product.Food;
                price = randInt(foodBottomPrice, foodCeilingPrice);
                break;
            case 1:
                type = Product.Electronics;
                price = randInt(electronicsBottomPrice, electronicsCeilingPrice);
                break;
            default:
                type = Product.Luxury;
                price = randInt(LuxuryBottomPrice, LuxuryCeilingPrice);
                break;

        }
        currentStoreType = (currentStoreType + 1) % 3;
        return new Store(x, y, type, price, maxStock);
    }

    public static int randInt(int min, int max) {
        return ThreadLocalRandom.current().nextInt(min, max + 1);
    }

    // Create customers and stores
    // Hint: you can also use a static block for this
    // Also note that you should make sure there are about equal number of stores for all products
    // like 4 stores for food, 3 stores for electronics and 4 stores for luxury etc.
    // Otherwise your simulation may deadlock

    static {
        for (int i = 0; i < storeNo; i++) {
            stores.add(createStore());
        }

        for (int i = 0; i < customerNo; i++) {
            customers.add(createCustomer());
        }
    }

    public static void stepAllEntities() {
        // In the function, you should:
        //    Remove left customers and add new ones as needed
        //    Move entities
        //    Replenish stocks of all stores on interval (stockReplenishmentFrequency)

        // Note that you should NOT handle transaction logic between customers and stores in here.

        for (int i = 0; i < customerNo; i++) {
            Customer customer = customers.get(i);
            if (customer.getPosition().getX() < -2 * entityDiameter || customer.getPosition().getX() > windowWidth ||
                    customer.getPosition().getY() < -2 * entityDiameter || customer.getPosition().getY() > windowHeight) {
                customers.set(i, createCustomer());
            }
        }

        for (Store store : stores) {
            store.step();
        }

        for (Customer customer : customers) {
            customer.step();
        }

        lastRestock++;
        if (lastRestock == stockReplenishmentFrequency) {
            lastRestock = 0;
            for (Store store : stores) {
                store.restock();
            }
        }
    }
}
