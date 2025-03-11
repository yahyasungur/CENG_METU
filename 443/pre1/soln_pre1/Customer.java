import java.awt.*;
import java.util.ArrayList;

class Customer extends Entity {
    private Strategy strategy;
    private ArrayList<Product> shoppingList;
    private Store target;
    private ArrayList<Store> visited;

    public enum Strategy {
        Cheapest,
        Closest,
        Travelling,
    }

    public Customer(double x, double y, Strategy strategy, ArrayList<Product> shoppingList) {
        super(x, y);
        this.strategy = strategy;
        this.shoppingList = shoppingList;
        target = null;
        visited = new ArrayList<Store>();
    }

    @Override
    public void draw(Graphics2D g2d) {
        String text;
        switch (strategy) {
            case Closest:
                text = "Cl";
                break;
            case Cheapest:
                text = "Ch";
                break;
            default:
                text = "Tr";
                break;
        }
        for (int i = 0; i < 3; i++) {
            try {
                text += "," + shoppingList.get(i).abbreviate();
            } catch (IndexOutOfBoundsException e) {
                break;
            }
        }
        drawHelper(g2d,text,Color.GRAY);
    }

    @Override
    public void step() {

        if (shoppingList.isEmpty()) {
            if (position.getIntX() < Common.getWindowWidth() - position.getIntX()) {
                position.setX(position.getX() - Common.getCustomerMovementSpeed());
            } else {
                position.setX(position.getX() + Common.getCustomerMovementSpeed());
            }
        } else if (target == null) {
            int cheapest = Integer.MAX_VALUE;
            double closest = Double.POSITIVE_INFINITY;
            double dist;
            switch (strategy) {
                case Cheapest:
                    for (Store s : Common.getStoreList()) {
                        if (s.getType() == shoppingList.get(0) && s.getPrice() < cheapest) {
                            cheapest = s.getPrice();
                            target = s;
                        }
                    }
                    break;
                case Closest:
                    for (Store s : Common.getStoreList()) {
                        if (s.getType() == shoppingList.get(0) && !visited.contains(s)) {
                            dist = this.getPosition().distanceTo(s.getPosition().getX(), s.getPosition().getY());
                            if (dist < closest) {
                                closest = dist;
                                target = s;
                            }
                        }
                    }
                    break;
                case Travelling:
                    for (Store s : Common.getStoreList()) {
                        if (!visited.contains(s)) {
                            dist = this.getPosition().distanceTo(s.getPosition().getX(), s.getPosition().getY());
                            if (dist < closest) {
                                closest = dist;
                                target = s;
                            }
                        }
                    }
                    if (closest == Double.POSITIVE_INFINITY) {
                        visited = new ArrayList<Store>();
                    }
                    break;
            }
        } else {
            double targetX = target.getPosition().getX();
            double targetY = target.getPosition().getY();

            // Distance to closest salesperson
            double distToClosestSalesperson = Double.POSITIVE_INFINITY;
            Salesperson closestSalesperson = null;
            for (Salesperson s : Common.getSalespersonList()) {
                double dist = this.getPosition().distanceTo(s.getPosition().getX(), s.getPosition().getY());
                if (dist < distToClosestSalesperson && s.getType() == shoppingList.get(0)) {
                    distToClosestSalesperson = dist;
                    closestSalesperson = s;
                }
            }

            // If salesperson and customer are close enough, customer buys from salesperson
            if (distToClosestSalesperson <= 2 * Common.getEntityDiameter()) {
                try {
                    closestSalesperson.sell();
                    shoppingList.remove(0);
                    target = null;
                    return;
                } catch (IllegalStateException e) {
                }
            }

            // Distance to target store
            double dist = this.getPosition().distanceTo(targetX, targetY);
            if (dist <= 2 * Common.getEntityDiameter()) {
                switch (strategy) {
                    case Cheapest:
                        try {
                            target.sell();
                            shoppingList.remove(0);
                            target = null;
                        } catch (IllegalStateException e) {
                        }
                        break;
                    case Closest:
                        try {
                            target.sell();
                            shoppingList.remove(0);
                        } catch (IllegalStateException e) {
                            visited.add(target);
                            while (visited.size() > 1) {
                                visited.remove(0);
                            }
                        }
                        target = null;
                        break;
                    case Travelling:
                        int index = shoppingList.indexOf(target.getType());
                        if (index != -1) {
                            try {
                                target.sell();
                                shoppingList.remove(index);
                            } catch (IllegalStateException e) {
                                visited.add(target);
                                target = null;
                            }
                        } else {
                            visited.add(target);
                            target = null;
                        }
                        break;
                }
            } else {
                double x = targetX - this.getPosition().getX();
                double y = targetY - this.getPosition().getY();
                if (dist > Common.getCustomerMovementSpeed()) {
                    double vx = x / dist * Common.getCustomerMovementSpeed();
                    double vy = y / dist * Common.getCustomerMovementSpeed();
                    getPosition().setX(getPosition().getX() + vx);
                    getPosition().setY(getPosition().getY() + vy);
                } else {
                    getPosition().setX(x);
                    getPosition().setY(y);
                }
            }
        }
    }
}