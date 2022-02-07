package ceng.ceng351.cengvacdb;

import java.sql.*;
import java.util.Vector;

public class CENGVACDB implements ICENGVACDB{

    private static final String user = "e2375723"; // TODO: Your userName
    private static final String password = "IspqVb$Bxoa!"; //  TODO: Your password
    private static final String host = "144.122.71.121"; // host name
    private static final String database = "db2375723"; // TODO: Your database name
    private static final int port = 8080; // port
    Connection connection = null;
    Statement statement;
    ResultSet rs;
    int number_of_tables = 5;

    @Override
    public void initialize() {
        String url = "jdbc:mysql://" + host + ":" + port + "/" + database;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection =  DriverManager.getConnection(url, user, password);
        }
        catch (SQLException | ClassNotFoundException e) {
            e.printStackTrace();
        }
    }

    @Override
    public int createTables() {
        try {
            String query1 = "CREATE TABLE User(" +
                    "userID INT," +
                    "userName VARCHAR(30)," +
                    "age INT," +
                    "address VARCHAR(150)," +
                    "password VARCHAR(30)," +
                    "status VARCHAR(15)," +
                    "PRIMARY KEY(userID))";

            String query2 = "CREATE TABLE Vaccine(" +
                    "code INT," +
                    "vaccinename VARCHAR(30)," +
                    "type VARCHAR(30)," +
                    "PRIMARY KEY(code))";

            String query3 = "CREATE TABLE Vaccination(" +
                    "code INT," +
                    "userID INT," +
                    "dose INT," +
                    "vacdate DATE," +
                    "PRIMARY KEY(code,userID,dose),"+
                    "FOREIGN KEY(code) REFERENCES Vaccine(code)," +
                    "FOREIGN KEY(userID) REFERENCES User(userID))";

            String query4 = "CREATE TABLE AllergicSideEffect(" +
                    "effectcode INT," +
                    "effectname VARCHAR(50)," +
                    "PRIMARY KEY(effectcode))";

            String query5 = "CREATE TABLE Seen(" +
                    "effectcode INT," +
                    "code INT," +
                    "userID INT," +
                    "date DATE," +
                    "degree VARCHAR(30)," +
                    "PRIMARY KEY(effectcode,code,userID),"+
                    "FOREIGN KEY(effectcode) REFERENCES AllergicSideEffect(effectcode)," +
                    "FOREIGN KEY(code) REFERENCES Vaccination(code) ON DELETE CASCADE," +
                    "FOREIGN KEY(userID) REFERENCES User(userID))";

            statement = connection.createStatement();
            statement.executeUpdate(query1);
            statement.executeUpdate(query2);
            statement.executeUpdate(query3);
            statement.executeUpdate(query4);
            statement.executeUpdate(query5);

            String query = "SELECT COUNT(*) AS total FROM information_schema.tables WHERE table_schema = 'db2375723'";

            rs = statement.executeQuery(query);
            rs.next();
            number_of_tables = rs.getInt("total");

        }catch (Exception e){
            e.printStackTrace();
        }
        return number_of_tables;
    }

    @Override
    public int dropTables() {
        int result = 5;
        try {
            String query1 = "DROP TABLE User, Vaccine, Vaccination, AllergicSideEffect, Seen";
            String query2 = "SELECT COUNT(*) AS total FROM information_schema.tables WHERE table_schema = 'db2375723'";

            statement = connection.createStatement();
            statement.executeUpdate(query1);

            rs = statement.executeQuery(query2);
            rs.next();

            result = number_of_tables - rs.getInt("total");

        }catch (Exception e){
            e.printStackTrace();
        }

        return result;
    }

    @Override
    public int insertUser(User[] users) {
        int result = 0;
        try {
            String query1 = "SELECT COUNT(*) AS total FROM User";
            statement = connection.createStatement();
            rs = statement.executeQuery(query1);
            rs.next();
            int before_insertion = rs.getInt("total");
            int size = users.length;
            for (int i = 0; i < size ; i++ ){
                String query = "INSERT INTO User VALUES("+
                        "'"+Integer.toString(users[i].getUserID())+"'"+
                        ","+"'"+ users[i].getUserName()+"'"+
                        ","+"'"+ Integer.toString(users[i].getAge())+"'"+
                        ","+"'"+ users[i].getAddress()+"'"+
                        ","+"'"+ users[i].getPassword()+"'"+
                        ","+"'"+ users[i].getStatus()+"'"+")";
                statement.executeUpdate(query);
            }

            rs = statement.executeQuery(query1);
            rs.next();
            int after_insertion = rs.getInt("total");
            result = after_insertion - before_insertion;
        }catch (Exception e){
            e.printStackTrace();
        }
        return result;
    }

    @Override
    public int insertAllergicSideEffect(AllergicSideEffect[] sideEffects) {
        int result = 0;
        try {
            String query1 = "SELECT COUNT(*) AS total FROM AllergicSideEffect";
            statement = connection.createStatement();
            rs = statement.executeQuery(query1);
            rs.next();
            int before_insertion = rs.getInt("total");
            int size = sideEffects.length;
            for (int i = 0; i < size ; i++ ){
                String query = "INSERT INTO AllergicSideEffect VALUES("+
                        "'"+Integer.toString(sideEffects[i].getEffectCode())+"'"+
                        ","+"'"+ sideEffects[i].getEffectName()+"'"+")";
                statement.executeUpdate(query);
            }

            rs = statement.executeQuery(query1);
            rs.next();
            int after_insertion = rs.getInt("total");
            result = after_insertion - before_insertion;
        }catch (Exception e){
            e.printStackTrace();
        }
        return result;
    }

    @Override
    public int insertVaccine(Vaccine[] vaccines) {
        int result = 0;
        try {
            String query1 = "SELECT COUNT(*) AS total FROM Vaccine";
            statement = connection.createStatement();
            rs = statement.executeQuery(query1);
            rs.next();
            int before_insertion = rs.getInt("total");
            int size = vaccines.length;
            for (int i = 0; i < size ; i++ ){
                String query = "INSERT INTO Vaccine VALUES("+
                        "'"+Integer.toString(vaccines[i].getCode())+"'"+
                        ","+"'"+ vaccines[i].getVaccineName()+"'"+
                        ","+"'"+ vaccines[i].getType()+"'"+")";
                statement.executeUpdate(query);
            }

            rs = statement.executeQuery(query1);
            rs.next();
            int after_insertion = rs.getInt("total");
            result = after_insertion - before_insertion;
        }catch (Exception e){
            e.printStackTrace();
        }
        return result;
    }

    @Override
    public int insertVaccination(Vaccination[] vaccinations) {
        int result = 0;
        try {
            String query1 = "SELECT COUNT(*) AS total FROM Vaccination";
            statement = connection.createStatement();
            rs = statement.executeQuery(query1);
            rs.next();
            int before_insertion = rs.getInt("total");
            int size = vaccinations.length;
            for (int i = 0; i < size ; i++ ){
                String query = "INSERT INTO Vaccination VALUES("+
                        "'"+Integer.toString(vaccinations[i].getCode())+"'"+
                        ","+"'"+Integer.toString(vaccinations[i].getUserID())+"'"+
                        ","+"'"+Integer.toString(vaccinations[i].getDose())+"'"+
                        ","+"'"+vaccinations[i].getVacdate()+"'"+")";
                statement.executeUpdate(query);
            }

            rs = statement.executeQuery(query1);
            rs.next();
            int after_insertion = rs.getInt("total");
            result = after_insertion - before_insertion;
        }catch (Exception e){
            e.printStackTrace();
        }
        return result;
    }

    @Override
    public int insertSeen(Seen[] seens) {
        int result = 0;
        try {
            String query1 = "SELECT COUNT(*) AS total FROM Seen";
            statement = connection.createStatement();
            rs = statement.executeQuery(query1);
            rs.next();
            int before_insertion = rs.getInt("total");
            int size = seens.length;
            for (int i = 0; i < size ; i++ ){
                String query = "INSERT INTO Seen VALUES("+
                        "'"+Integer.toString(seens[i].getEffectcode())+"'"+
                        ","+"'"+ Integer.toString(seens[i].getCode())+"'"+
                        ","+"'"+ seens[i].getUserID()+"'"+
                        ","+"'"+ seens[i].getDate()+"'"+
                        ","+"'"+ seens[i].getDegree()+"'"+")";
                statement.executeUpdate(query);
            }

            rs = statement.executeQuery(query1);
            rs.next();
            int after_insertion = rs.getInt("total");
            result = after_insertion - before_insertion;
        }catch (Exception e){
            e.printStackTrace();
        }
        return result;
    }

    @Override
    public Vaccine[] getVaccinesNotAppliedAnyUser() {
        Vector<Vaccine> vaccineVector = new Vector<Vaccine>(1000);

        try {
            String query = "SELECT DISTINCT V.code,V.vaccinename,V.type " +
                    "FROM Vaccine V " +
                    "WHERE V.code NOT IN (SELECT V2.code " +
                                          "FROM Vaccination V2) " +
                    "ORDER BY V.code ASC";

            statement = connection.createStatement();
            rs = statement.executeQuery(query);

            while (rs.next()){
                Vaccine e = new Vaccine(rs.getInt(1),rs.getString(2),rs.getString(3));
                vaccineVector.add(e);
            }
            vaccineVector.trimToSize();
            
        }catch (Exception e){
            e.printStackTrace();
        }

        return vaccineVector.toArray(new Vaccine[0]);
    }

    @Override
    public QueryResult.UserIDuserNameAddressResult[] getVaccinatedUsersforTwoDosesByDate(String vacdate) {
        Vector<QueryResult.UserIDuserNameAddressResult> results = new Vector<>(1000);
        try {
            String query = "SELECT DISTINCT U.userID,U.userName,U.address " +
                    "FROM User U " +
                    "WHERE U.userID IN (SELECT V2.userID " +
                                       "FROM Vaccination V1, Vaccination V2 " +
                                       "WHERE V1.userID = V2.userID AND V1.dose = 1 AND" +
                                       " V2.dose = 2 AND V1.vacdate > '"+vacdate+"' AND V2.vacdate > '"+vacdate+"') " +
                    "ORDER BY U.userID ASC";
            statement = connection.createStatement();
            rs = statement.executeQuery(query);

            while (rs.next()){
                QueryResult.UserIDuserNameAddressResult e;
                e = new QueryResult.UserIDuserNameAddressResult(Integer.toString(rs.getInt(1))
                        ,rs.getString(2),rs.getString(3));
                results.add(e);
            }
            results.trimToSize();

        }catch (Exception e){
            e.printStackTrace();
        }

        return results.toArray(new QueryResult.UserIDuserNameAddressResult[0]);
    }

    @Override
    public Vaccine[] getTwoRecentVaccinesDoNotContainVac() {
        Vector<Vaccine> vaccineVector = new Vector<Vaccine>(2);
        Vector<Vaccine> vaccineVector2 = new Vector<Vaccine>(2);

        try {
            String query = "SELECT DISTINCT V.code,V.vaccinename,V.type,V1.vacdate " +
                    "FROM Vaccine V , Vaccination V1 " +
                    "WHERE V.code = V1.code AND V.vaccinename NOT LIKE '%vac%' " +
                    "ORDER BY V1.vacdate DESC;";

            statement = connection.createStatement();
            rs = statement.executeQuery(query);
            int first_vaccine_code = 0,i = 0;
            while (rs.next()){
                if (i == 0){
                    first_vaccine_code = rs.getInt(1);
                    Vaccine e = new Vaccine(rs.getInt(1),rs.getString(2),rs.getString(3));
                    vaccineVector.add(e);
                    i++;
                    continue;
                }
                if (rs.getInt(1) == first_vaccine_code){
                    continue;
                }
                else {
                    Vaccine e = new Vaccine(rs.getInt(1),rs.getString(2),rs.getString(3));
                    vaccineVector.add(e);
                    break;
                }
            }

        }catch (Exception e){
            e.printStackTrace();
        }
        if (vaccineVector.get(0).getCode() > vaccineVector.get(1).getCode()){
            vaccineVector2.add(vaccineVector.get(1));
            vaccineVector2.add(vaccineVector.get(0));
            return vaccineVector2.toArray(new Vaccine[0]);
        }

        return vaccineVector.toArray(new Vaccine[0]);
    }

    @Override
    public QueryResult.UserIDuserNameAddressResult[] getUsersAtHasLeastTwoDoseAtMostOneSideEffect() {
        Vector<QueryResult.UserIDuserNameAddressResult> results = new Vector<>(1000);

        try {
            String query = "SELECT DISTINCT U.userID,U.userName,U.address " +
                    "FROM User U " +
                    "WHERE U.userID IN (SELECT V.userID " +
                    "                   FROM Vaccination V " +
                    "                   WHERE V.dose > 1 AND V.userID NOT IN( SELECT S.userID " +
                                                "FROM Seen S " +
                                                "WHERE S.userID IN(SELECT S2.userID " +
                                                    "FROM Seen S2 " +
                                                    "WHERE S.userID = S2.userID AND S.effectcode <> S2.effectcode)))" +
                    "ORDER BY U.userID ASC";
            statement = connection.createStatement();
            rs = statement.executeQuery(query);

            while (rs.next()){
                QueryResult.UserIDuserNameAddressResult e;
                e = new QueryResult.UserIDuserNameAddressResult(Integer.toString(rs.getInt(1))
                        ,rs.getString(2),rs.getString(3));
                results.add(e);
            }
            results.trimToSize();

        }catch (Exception e){
            e.printStackTrace();
        }

        return results.toArray(new QueryResult.UserIDuserNameAddressResult[0]);
    }

    @Override
    public QueryResult.UserIDuserNameAddressResult[] getVaccinatedUsersWithAllVaccinesCanCauseGivenSideEffect(String effectname) {
        Vector<QueryResult.UserIDuserNameAddressResult> results = new Vector<>(1000);

        try {
            String query = "SELECT DISTINCT U.userID,U.userName,U.address " +
                    "FROM User U " +
                    "WHERE NOT EXISTS (SELECT V.userID " +
                                    "FROM Vaccination V " +
                                    "WHERE V.code IN(SELECT S.code " +
                                                    "FROM Seen S, AllergicSideEffect Al " +
                                                    "WHERE S.effectcode = Al.effectcode AND Al.effectname = '"+effectname+"') " +
                                    "AND V.userID NOT IN (SELECT V2.userID " +
                                                        "FROM Vaccination V2 " +
                                                        "WHERE V2.userID = U.userID))" +
                    "ORDER BY U.userID ASC";
            statement = connection.createStatement();
            rs = statement.executeQuery(query);

            while (rs.next()){
                QueryResult.UserIDuserNameAddressResult e;
                e = new QueryResult.UserIDuserNameAddressResult(Integer.toString(rs.getInt(1))
                        ,rs.getString(2),rs.getString(3));
                results.add(e);
            }
            results.trimToSize();

        }catch (Exception e){
            e.printStackTrace();
        }

        return results.toArray(new QueryResult.UserIDuserNameAddressResult[0]);
    }

    @Override
    public QueryResult.UserIDuserNameAddressResult[] getUsersWithAtLeastTwoDifferentVaccineTypeByGivenInterval(String startdate, String enddate) {
        Vector<QueryResult.UserIDuserNameAddressResult> results = new Vector<>(1000);

        try {
            String query = "SELECT DISTINCT U.userID,U.userName,U.address " +
                    "FROM User U " +
                    "WHERE U.userID IN(SELECT V1.userID " +
                                    "FROM Vaccination V1, Vaccination V2 " +
                                    "WHERE V1.userID = V2.userID AND V1.code <> V2.code" +
                                    " AND V1.vacdate >= '"+startdate+"' AND V2.vacdate >= '"+startdate+"'" +
                                    " AND  V1.vacdate <= '"+enddate+"' AND V2.vacdate <= '"+enddate+"') " +
                    "ORDER BY U.userID ASC";
            statement = connection.createStatement();
            rs = statement.executeQuery(query);

            while (rs.next()){
                QueryResult.UserIDuserNameAddressResult e;
                e = new QueryResult.UserIDuserNameAddressResult(Integer.toString(rs.getInt(1))
                        ,rs.getString(2),rs.getString(3));
                results.add(e);
            }
            results.trimToSize();

        }catch (Exception e){
            e.printStackTrace();
        }

        return results.toArray(new QueryResult.UserIDuserNameAddressResult[0]);
    }

    @Override
    public AllergicSideEffect[] getSideEffectsOfUserWhoHaveTwoDosesInLessThanTwentyDays() {
        Vector<AllergicSideEffect> results = new Vector<>(1000);

        try {
            String query = "SELECT DISTINCT Al.effectcode, Al.effectname " +
                    "FROM AllergicSideEffect Al " +
                    "WHERE Al.effectcode IN(SELECT S.effectcode " +
                    "                       FROM Seen S " +
                    "                       WHERE S.userID IN (SELECT V1.userID " +
                    "                                          FROM Vaccination V1, Vaccination V2 " +
                    "                                          WHERE V1.userID = V2.userID AND V1.code = V2.code AND V1.dose <> V2.dose AND DATEDIFF(V2.vacdate,V1.vacdate) < 20 AND DATEDIFF(V2.vacdate,V1.vacdate) >= 0)) " +
                    "ORDER BY Al.effectcode ASC";
            statement = connection.createStatement();
            rs = statement.executeQuery(query);

            while (rs.next()){
                AllergicSideEffect e;
                e = new AllergicSideEffect(rs.getInt(1),rs.getString(2));
                results.add(e);
            }
            results.trimToSize();

        }catch (Exception e){
            e.printStackTrace();
        }

        return results.toArray(new AllergicSideEffect[0]);
    }

    @Override
    public double averageNumberofDosesofVaccinatedUserOverSixtyFiveYearsOld() {
        double avg = 0.0;
        try {
            String query = "SELECT COUNT(DISTINCT V.userID) " +
                    "FROM Vaccination V " +
                    "WHERE V.dose = 1 AND V.userID IN(SELECT U.userID " +
                    "                                 FROM User U " +
                    "                                 WHERE U.age > 65) " +
                    "     AND V.userID NOT IN(SELECT V2.userID " +
                    "                         FROM Vaccination V2 " +
                    "                         WHERE V2.dose = 2)";
            statement = connection.createStatement();
            rs = statement.executeQuery(query);
            rs.next();
            int number_of_1_dose = rs.getInt(1);

            query = "SELECT COUNT(DISTINCT V.userID) " +
                    "FROM Vaccination V " +
                    "WHERE V.dose = 2 AND V.userID IN(SELECT U.userID " +
                    "                                 FROM User U " +
                    "                                 WHERE U.age > 65) " +
                    "     AND V.userID NOT IN(SELECT V2.userID " +
                    "                         FROM Vaccination V2 " +
                    "                         WHERE V2.dose = 3)";

            rs = statement.executeQuery(query);
            rs.next();
            int number_of_2_dose = rs.getInt(1);

            query = "SELECT COUNT(DISTINCT V.userID) " +
                    "FROM Vaccination V " +
                    "WHERE V.dose = 3 AND V.userID IN(SELECT U.userID " +
                    "                                 FROM User U " +
                    "                                 WHERE U.age > 65) " +
                    "     AND V.userID NOT IN(SELECT V2.userID " +
                    "                         FROM Vaccination V2 " +
                    "                         WHERE V2.dose = 4)";

            rs = statement.executeQuery(query);
            rs.next();
            int number_of_3_dose = rs.getInt(1);

            avg = Double.valueOf(1*number_of_1_dose+2*number_of_2_dose+3*number_of_3_dose)/Double.valueOf(number_of_1_dose+number_of_2_dose+number_of_3_dose);
        }catch (Exception e){
            e.printStackTrace();
        }

        return avg;
    }

    @Override
    public int updateStatusToEligible(String givendate) {
        int number = 0;
        try {
            String query = "SELECT V.userID " +
                    "FROM Vaccination V,User U " +
                    "WHERE U.userID = V.userID AND U.status = 'Not_Eligible' AND V.vacdate >= ALL (SELECT V2.vacdate " +
                    "                                                                              FROM Vaccination V2 " +
                    "                                                                              WHERE V.userID = V2.userID) " +
                    "        AND DATEDIFF('"+givendate+"',V.vacdate) >= 120 " +
                    "ORDER BY V.userID";
            statement = connection.createStatement();
            rs = statement.executeQuery(query);
            Statement statement2 = connection.createStatement();

            while (rs.next()){
                number++;
                String query2 = "UPDATE User U " +
                        "SET U.status = 'Eligible' " +
                        "WHERE U.userID = '"+rs.getString(1)+"'";
                statement2.executeUpdate(query2);
            }
        }catch (Exception e){
            e.printStackTrace();
        }
        return number;
    }

    @Override
    public Vaccine deleteVaccine(String vaccineName) {
        Vaccine v = null;
        try {
            String query1 = "SELECT * FROM Vaccine V WHERE V.vaccinename = '"+vaccineName+"'";
            String query2 = "DELETE FROM Vaccine V WHERE V.vaccinename = '"+vaccineName+"'";

            statement = connection.createStatement();
            rs = statement.executeQuery(query1);
            rs.next();
            v = new Vaccine(rs.getInt(1),rs.getString(2), rs.getString(3));
            String query3 = "SELECT S.effectcode FROM Seen S WHERE S.code = '"+v.getCode()+"'";

            rs = statement.executeQuery(query3);
            Statement statement2 = connection.createStatement();

            while (rs.next()){
                String query = "DELETE FROM AllergicSideEffect Al WHERE Al.effectcode = '"+rs.getInt(1)+"'";
                statement2.executeUpdate(query);
            }

            statement2.executeUpdate(query2);

        }catch (Exception e){
            e.printStackTrace();
        }
        return v;
    }
}
