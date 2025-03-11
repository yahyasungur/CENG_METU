import java.awt.Color;
import java.awt.Graphics2D;

public class Salesperson extends Entity {
    private Strategy strategy;
    private Product type;
    private int stock;
    private Position destination;
    private static int moveInterval = 0;

    public enum Strategy {
        Random,
        MiddleGround,
    }

    public Salesperson(double x, double y, Strategy strategy,Product type, int stock) {
        super(x, y);
        this.type = type;
        this.stock = stock;
        this.strategy = strategy;
        this.destination = null;
    }

    @Override
    public void draw(Graphics2D g2d) {
        String text = type.abbreviate() + ","+String.valueOf(stock) + ",";
        switch (strategy) {
            case Random:
                text += "R";
                break;
            default:
                text += "M";
                break;
        }
        drawHelper(g2d,text,Color.BLUE);
    }

    public Product getType() {
        return type;
    }

    public void sell() throws IllegalStateException{
        if(stock == 0){
            throw new IllegalStateException("Out of Stock");
        }
        stock-=1;
        destination = null;
    }

    @Override
    public void step() {
        // if stock is 0, leave the area
        if(stock <= 0){
            if (position.getIntX() < Common.getWindowWidth() - position.getIntX()) {
                position.setX(position.getX() - Common.getCustomerMovementSpeed());
            } else {
                position.setX(position.getX() + Common.getCustomerMovementSpeed());
            }
        }else if(destination == null){
            switch (strategy) {
                case Random:
                    destination = new Position(Math.random() * Common.getWindowWidth(), Math.random() * Common.getWindowHeight());
                    break;
                default:
                    // Salesperson goes to the middle of all customers
                    double x = 0;
                    double y = 0;
                    for (Customer customer : Common.getCustomerList()) {
                        x += customer.getPosition().getX();
                        y += customer.getPosition().getY();
                    }
                    destination = new Position(x / Common.getCustomerList().size(), y / Common.getCustomerList().size());
                    break;
            }
        } else{
            // Move towards destination
            double x = destination.getX() - this.getPosition().getX();
            double y = destination.getY() - this.getPosition().getY();
            double dist = this.getPosition().distanceTo(destination.getX(), destination.getY());
            if (dist > Common.getSalespersonMovementSpeed()) {
                position.setX(getPosition().getX() + Common.getSalespersonMovementSpeed() * x / dist);
                position.setY(getPosition().getY() + Common.getSalespersonMovementSpeed() * y / dist);
            }
            // Otherwise do not change the location
            moveInterval++;

            // If the salesperson has been at the destination for a while, move to a new destination
            if (moveInterval >= Common.getSalespersonMoveInterval()) {
                moveInterval = 0;
                destination = null;
            }
        }

    }
    
}
