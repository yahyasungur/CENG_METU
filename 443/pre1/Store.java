import java.awt.Color;
import java.awt.Graphics2D;

public class Store extends Entity {
    private Product type;
    private int stock;
    private int price;
    private int maxStock;

    public Store(double x, double y, Product type, int price, int maxStock) {
        super(x, y);
        this.maxStock = maxStock;
        this.stock = maxStock;
        this.type = type;
        this.price = price;
    }

    @Override
    public void draw(Graphics2D g2d) {
        String text = type.getType() + "," + String.valueOf(stock) + "," + String.valueOf(price);
        drawHelper(g2d, text, Color.ORANGE);
    }

    public Product getType() {
        return type;
    }

    public int getPrice() {
        return price;
    }

    @Override
    public void step() {
    }

    public void sell() throws IllegalStateException {
        if (stock <= 0) {
            throw new IllegalStateException("Stock is empty");
        }
        stock--;
    }

    public void restock(){
        stock = maxStock;
    }
    
}
