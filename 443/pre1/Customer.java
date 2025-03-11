import java.awt.Color;
import java.awt.Graphics2D;
import java.util.ArrayList;

public class Customer extends Entity{
    private Strategy strategy;
    private ArrayList<Product> shoppingList;
    private Store targetStore;
    private ArrayList<Store> visitedStores;
    

    public enum Strategy{
        Cheapest,
        Closest,
        Travelling,
    }

    public Customer(double x, double y, Strategy strategy, ArrayList<Product> shoppingList) {
        super(x, y);
        this.strategy = strategy;
        this.shoppingList = shoppingList;
        this.visitedStores = new ArrayList<Store>();
        targetStore = null;
    }

    @Override
    public void draw(Graphics2D g2d) {
        String text;
        switch(strategy){
            case Cheapest:
                text = "Ch";
                break;
            case Closest:
                text = "Cl";
                break;
            case Travelling:
            default:
                text = "Tr";
                break;
        }
        for(int i = 0; i < 3; i++){
            try{
                text += "," + shoppingList.get(i).getType();
            }catch(IndexOutOfBoundsException e){
                break;
            }
        }
        drawHelper(g2d, text, Color.GRAY);
    }

    @Override
    public void step() {

        // If the shopping list is empty, the customer should leave the window
        if(shoppingList.isEmpty()){
            // If customer is close to the left side of the window, move left
            if(position.getIntX() < Common.getWindowWidth()/2){
                position.setX(position.getX() - Common.getCustomerMovementSpeed());
            }
            // If customer is close to the right side of the window, move right
            else{
                position.setX(position.getX() + Common.getCustomerMovementSpeed());
            }
        }
        // If the customer does not have a target store, find one
        else if(targetStore == null){
            int cheapest = Integer.MAX_VALUE;
            double closest = Double.POSITIVE_INFINITY;
            double distance;

            switch(strategy){
                case Cheapest:
                    for(Store store : Common.getStores()){
                        if(store.getType() == shoppingList.get(0) && store.getPrice() < cheapest){
                            cheapest = store.getPrice();
                            targetStore = store;
                        }
                    }
                    break;
                case Closest:
                    for(Store store : Common.getStores()){
                        if(store.getType() == shoppingList.get(0) && !visitedStores.contains(store)){
                            distance = this.position.distanceTo(store.getPosition().getX(), store.getPosition().getY());
                            if(distance < closest){
                                closest = distance;
                                targetStore = store;
                            }
                        }
                    }
                    break;
                case Travelling:
                default:
                    for(Store store : Common.getStores()){
                        if(!visitedStores.contains(store)){
                            distance = this.position.distanceTo(store.getPosition().getX(), store.getPosition().getY());
                            if(distance < closest){
                                closest = distance;
                                targetStore = store;
                            }
                        }
                    }
                    if(closest == Double.POSITIVE_INFINITY){
                        visitedStores = new ArrayList<Store>();
                    }
                    break;
            }
        }
        // If the customer has a target store, move towards it
        else{
            double targetX = targetStore.getPosition().getX();
            double targetY = targetStore.getPosition().getY();
            double distance = this.position.distanceTo(targetX, targetY);
            // ıf cıstomer and store collide, remove the product from the shopping list
            if(distance <= 2* Common.getEntityDiameter()){
                switch(strategy){
                    case Cheapest:
                        try{
                            targetStore.sell();
                            shoppingList.remove(0);
                            targetStore = null;
                        } catch (IllegalStateException e){
                        }
                        break;
                    case Closest:
                        try{
                            targetStore.sell();
                            shoppingList.remove(0);
                        } catch (IllegalStateException e){
                            visitedStores.add(targetStore);
                            while(visitedStores.size() > 1){
                                visitedStores.remove(0);
                            }
                        }
                        targetStore = null;
                        break;
                    case Travelling:
                    default:
                        int index = shoppingList.indexOf(targetStore.getType());
                        if(index != -1){
                            try{
                                targetStore.sell();
                                shoppingList.remove(index);
                            } catch (IllegalStateException e){
                                visitedStores.add(targetStore);
                                targetStore = null;
                            }
                        }else {
                            visitedStores.add(targetStore);
                            targetStore = null;
                        }
                        break;
                }
            }
            // Move towards the store
            else{
                double angle = Math.atan2(targetY - position.getY(), targetX - position.getX());
                position.setX(position.getX() + Common.getCustomerMovementSpeed() * Math.cos(angle));
                position.setY(position.getY() + Common.getCustomerMovementSpeed() * Math.sin(angle));
            }
        }
    }

}
