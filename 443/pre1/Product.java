public enum Product {
    Food,
    Electronics,
    Luxury;

    public char getType(){
        switch(this){
            case Food:
                return 'F';
            case Electronics:
                return 'E';
            case Luxury:    
            default:
                return 'L';
        }
    }
}
