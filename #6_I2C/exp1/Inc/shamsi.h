
//const int           DaysToMonth[13] =     {  0,31,59,90,120,151,181,212,243,273,304,334,365};
const unsigned int  g_days_in_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const unsigned int  j_days_in_month[12] = {31, 31, 31, 31, 31, 31, 30, 30, 30, 30, 30, 29};

void M2Sh( int  g_y, int  g_m, int  g_d ,unsigned int *miladi_year ,unsigned int *miladi_month ,unsigned int *miladi_Date ) // Miladi To shamsi
    {
            unsigned  long gy, gm, gd;
            unsigned long jy, jm, jd;
            unsigned  long g_day_no, j_day_no;
            unsigned long j_np;
            unsigned long i;
            
            if(g_y<2000 || g_y>2100) g_y=2012;
            if(g_m==0   || g_m>12)   g_m=1;
            if(g_d==0   || g_d>31)   g_d=1;

               gy = g_y-1600;
               gm = g_m-1;
               gd = g_d-1;

               g_day_no = 365*gy+(gy+3)/4-(gy+99)/100+(gy+399)/400;
               for (i=0;i<gm;++i)
                  g_day_no += g_days_in_month[i];
               if (gm>1 && ((gy%4==0 && gy%100!=0) || (gy%400==0)))
                  /* leap and after Feb */
                  ++g_day_no;
               g_day_no += gd;

               j_day_no = g_day_no-79;

               j_np = j_day_no / 12053;
               j_day_no %= 12053;

               jy = 979+33*j_np+4*(j_day_no/1461);
               j_day_no %= 1461;

               if (j_day_no >= 366)
                {
                          jy += (j_day_no-1)/365;
                          j_day_no = (j_day_no-1)%365;
               }

               for (i = 0; i < 11 && j_day_no >= j_days_in_month[i]; ++i)
               {
                          j_day_no -= j_days_in_month[i];
               }

               jm = i+1;
               jd = j_day_no+1;
               *miladi_year = jy;
               *miladi_month = jm;
               *miladi_Date = jd;
    }

/*
int Day_Of_Year_Jalali(int  g_y, int  g_m, int  g_d) // 
{
          unsigned  long gy, gm, gd;
          //unsigned long jy, jm, jd;
          unsigned  long g_day_no, j_day_no;
          unsigned long j_np;
          unsigned long i;

          if(g_y<2000 || g_y>2100) g_y=2012;
          if(g_m==0   || g_m>12)   g_m=1;
          if(g_d==0   || g_d>31)   g_d=1;

             gy = g_y-1600;
             gm = g_m-1;
             gd = g_d-1;

             g_day_no = 365*gy+(gy+3)/4-(gy+99)/100+(gy+399)/400;
             for (i=0;i<gm;++i)
                g_day_no += g_days_in_month[i];
             if (gm>1 && ((gy%4==0 && gy%100!=0) || (gy%400==0)))
                // leap and after Feb 
                ++g_day_no;
             g_day_no += gd;

             j_day_no = g_day_no-79;

             j_np = j_day_no / 12053;
             j_day_no %= 12053;

             //jy = 979+33*j_np+4*(j_day_no/1461);
             j_day_no %= 1461;

             if (j_day_no >= 366)
              {
                       // jy += (j_day_no-1)/365;
                        j_day_no = (j_day_no-1)%365;
             }

             return j_day_no;

}



void Sh2M(int *g_y,int *g_m,int *g_d,int  j_y,int  j_m,int  j_d)// shamsi To Mildai
    {
       unsigned long gy, gm, gd;
       unsigned long jy, jm, jd;
       unsigned long g_day_no, j_day_no;
       unsigned long leap;

       unsigned long i;

       jy = j_y-979;
       jm = j_m-1;
       jd = j_d-1;

       j_day_no = 365*jy + (jy/33)*8 + (jy%33+3)/4;
       for (i=0; i < jm; ++i)
          j_day_no += j_days_in_month[i];

       j_day_no += jd;

       g_day_no = j_day_no+79;

       gy = 1600 + 400*(g_day_no/146097); // 146097 = 365*400 + 400/4 - 400/100 + 400/400 
       g_day_no = g_day_no % 146097;

       leap = 1;
       if (g_day_no >= 36525) // 36525 = 365*100 + 100/4 
       {
          g_day_no--;
          gy += 100*(g_day_no/36524); // 36524 = 365*100 + 100/4 - 100/100 
          g_day_no = g_day_no % 36524;

          if (g_day_no >= 365)
             g_day_no++;
          else
             leap = 0;
       }

       gy += 4*(g_day_no/1461); // 1461 = 365*4 + 4/4 
       g_day_no %= 1461;

       if (g_day_no >= 366) {
          leap = 0;

          g_day_no--;
          gy += g_day_no/365;
          g_day_no = g_day_no % 365;
       }

       for (i = 0; g_day_no >= g_days_in_month[i] + (i == 1 && leap); i++)
          g_day_no -= (unsigned long)g_days_in_month[i] + (i == 1 && leap);
       gm = i+1;
       gd = g_day_no+1;
       
       *g_y = gy;
       *g_m = gm;
       *g_d = gd;
    }    


unsigned int Day_Of_Year_Miladi(int tm_year,int tm_mon,int tm_mday)  // 
{

    unsigned  long gy, gm, gd;

            unsigned  long g_day_no;

            unsigned long i;

            if(tm_year<2000 || tm_year>2100) tm_year=2012;
            if(tm_mon==0   || tm_mon>12)   tm_mon=1;
            if(tm_mday==0   || tm_mday>31)   tm_mday=1;

               gy = tm_year-1600;
               gm = tm_mon-1;
               gd = tm_mday-1;

               g_day_no = 365*gy+(gy+3)/4-(gy+99)/100+(gy+399)/400;
               for (i=0;i<gm;++i)
                  g_day_no += g_days_in_month[i];
               if (gm>1 && ((gy%4==0 && gy%100!=0) || (gy%400==0)))
                  // leap and after Feb 
                  ++g_day_no;
               g_day_no += gd;

               gy = 1600 + 400*(g_day_no/146097); // 146097 = 365*400 + 400/4 - 400/100 + 400/400 
                      g_day_no = g_day_no % 146097;

                      if (g_day_no >= 36525) // 36525 = 365*100 + 100/4 
                      {
                         g_day_no--;
                         gy += 100*(g_day_no/36524); // 36524 = 365*100 + 100/4 - 100/100 
                         g_day_no = g_day_no % 36524;

                         if (g_day_no >= 365)
                            g_day_no++;

                      }

                      gy += 4*(g_day_no/1461); // 1461 = 365*4 + 4/4 
                      g_day_no %= 1461;

                      if (g_day_no >= 366) {


                         g_day_no--;
                         gy += g_day_no/365;
                         g_day_no = g_day_no % 365;
                      }

   return (int)g_day_no;
}
  

void M2Gh(int *year,int *month,int *Day,int y,int m,int d)//Miladi to ghamari
{
    unsigned long int jd,l,j,n;   
        
    
    if ((y>1582)||((y==1582)&&(m>10))||((y==1582)&&(m==10)&&(d>14)))
        jd=(1461*(y+4800+(m-14)/12))/4+(367*(m-2-12*((m-14)/12)))/12-(3*((y+4900+(m-14)/12)/100))/4+d-32075;

    else jd = 367*y-(7*(y+5001+(m-9)/7))/4+(275*m)/9+d+1729777;
        
                        l=jd-1948440+10632;
                                                
                    n=(l-1)/10631;
                    l=l-10631*n+354;
                    j=((10985-l)/5316)*((50*l)/17719)+(l/5670)*((43*l)/15238);
                    l=l-((30-j)/15)*((17719*j)/50)-(j/16)*((15238*j)/43)+29; 
                                        
                                        
//                    date1.dtMonth= m=(24*l)/709;
//                    date1.dtDay=d=l-(709*m)/24;
//                    date1.dtYear=y=30*n+j-30;   
                                        
                                        *month=m=(24*l)/709;
                    *year=y=30*n+j-30;
                                        *Day=d=l-(709*m)/24;
                    
}



const int    pnDaysBeforeMonth[] =
{
         0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365
};

        
//   flash char    aszWeekDayNames[][16] = {
//        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursay", "Friday", "Saturday"
//    };


int        CountOfFeb29( int nYear )
{
    int        nCount = 0;
    if( nYear > 0 ) {
        nCount = 1;    // Year 0 is a leap year 
        nYear--;// Year nYear is not in the period 
    }
    nCount += nYear / 4 - nYear / 100 + nYear / 400;

    return nCount;
}

char    IsLeapYear( int nYear )
{
    if( nYear % 4 != 0 )    return 0;
    if( nYear % 100 != 0 )    return 1;
    return ( nYear % 400 == 0 );
}


int    DayOfWeek( int nYear, int nMonth, int nDay )
{
    int            nDayOfWeek;
    

    nDayOfWeek = 6 + nYear % 7 + CountOfFeb29(nYear) % 7 + 14;/* + 14 : makes nDayOfWeek >= 0 
    

    nDayOfWeek += pnDaysBeforeMonth[ nMonth ];
    if( nMonth > 2 && IsLeapYear(nYear) )    nDayOfWeek++;
    

    nDayOfWeek += nDay - 1;
    nDayOfWeek %= 7;
        
        if(nDayOfWeek==0)   return 0;
        if(nDayOfWeek==1)   return 1;
        if(nDayOfWeek==2)   return 2;
        if(nDayOfWeek==3)   return 3;
        if(nDayOfWeek==4)   return 4;
        if(nDayOfWeek==5)   return 5;
        if(nDayOfWeek==6)   return 6;
        
        
    
    return 1;
}

*/