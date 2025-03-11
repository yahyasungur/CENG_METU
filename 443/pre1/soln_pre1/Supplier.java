import java.awt.Color;
import java.awt.Graphics2D;
import java.util.ArrayList;
import java.util.List;

public class Supplier extends Entity {
    private ArrayList<Store> visited;
    private Store target;

    public Supplier(double x, double y) {
        super(x, y);
        visited = new ArrayList<Store>();
    }

    @Override
    public void draw(Graphics2D g2d) {
        drawHelper(g2d,"",Color.GREEN);
    }

    @Override
    public void step() {
        List<Store> storeList = Common.getStoreList();
        if(visited.size() == storeList.size()){
            // Leave the area
            if (position.getIntX() < Common.getWindowWidth() - position.getIntX()) {
                position.setX(position.getX() - Common.getCustomerMovementSpeed());
            } else {
                position.setX(position.getX() + Common.getCustomerMovementSpeed());
            }
        } else if(target == null){
            // Find the next nearest store to visit
            double closest = Double.POSITIVE_INFINITY;
            double dist;
            for (Store store: storeList) {
                if (!visited.contains(store)) {
                    dist = this.getPosition().distanceTo(store.getPosition().getX(), store.getPosition().getY());
                    if (dist < closest) {
                        closest = dist;
                        target = store;
                    }
                }
            }
        } else{
            double targetX = target.getPosition().getX();
            double targetY = target.getPosition().getY();
            double dist = this.getPosition().distanceTo(targetX, targetY);

            if (dist <= 2 * Common.getEntityDiameter()) {
                // Arrived at the store
                target.replenish(); // Replenish the store
                visited.add(target); // Mark the store as visited
                target = null;
            } else {
                // Move towards the store
                double x = targetX - this.getPosition().getX();
                double y = targetY - this.getPosition().getY();;
                if (dist > Common.getSupplierMovementSpeed()) {
                    double vx = x / dist * Common.getSupplierMovementSpeed();
                    double vy = y / dist * Common.getSupplierMovementSpeed();
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
