public class PR1 {
    public static void main(String args[])
    {
        String dayName[] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    
        if(args.length < 3) {
            System.out.println("ERR: usage: <dd> <mm> <yy>");
            return;
        }
        int day   = Integer.parseInt(args[0]);
        int month = Integer.parseInt(args[1]);
        int year  = Integer.parseInt(args[2]);
        
        int days = (year-1900)*365 + (year-1900)/4 + tageDerVollstMonate(month)+ day;
        if(year%4==0 && month<3) days-=1; // falls jahr ein Schaltjahr ist
                                        // und der Schaltag noch nicht war
                                        // ziehen wir das ab
        System.out.println("days = " + days);
        System.out.println(dayName[days % 7]);
    }
    
    private static int tageDerVollstMonate(int m) {
        int res = 0;
        switch(m) {
            case 12: res+=30;
            case 11: res+=31;
            case 10: res+=30;
            case  9: res+=31;
            case  8: res+=31;
            case  7: res+=30;
            case  6: res+=31;
            case  5: res+=30;
            case  4: res+=31;
            case  3: res+=28;
            case  2: res+=31;
        }
        return res;
    }
}
