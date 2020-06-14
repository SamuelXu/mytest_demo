import java.util.*;

public class Sample
{
    public static void main(String[] args)
    {
        Employee[] staff = new Employee[5];
        for (Employee e: staff) {
            System.out.println(e==null);
            break;
        }
    }
}

class Employee
{
    public Employee(String n, double s)
    {
        name = n;
        salary = s;
    }

    public String getName()
    {
        return name;
    }

    public double getSalary()
    {
        return salary;
    }

    private String name;
    private double salary;
}
