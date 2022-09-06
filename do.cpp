#include<iostream>
#include<cstring>
#include<math.h>
using namespace std;
int main(){
    float A=0,B=0,i,j,z[1760];
    char b[1760];//canvas 80*22
    char brightness[12]={'.',',','-','~',':',';','!','=','$','&','#','@'};
     cout<<"\x1b[2J";
    for(;;){
        
        memset(b,32,1760);//32 for blank space and 1760 is size 
        memset(z,0,7040);//0 to for blank and 7040 is size i.e 1760*size_of_float =7040
        for(j=0;j<6.28;j+=0.05)
       {
            for(i=0;i<6.28;i+=0.02)
            {
                //precompute sin and cosine values
                    float sini=sin(i),
                      cosj=cos(j),
                      sinA=sin(A),
                      sinj=sin(j),
                      cosA=cos(A),
                      cosj2=cosj+2,
                      mess=1/(sini*cosj2*sinA+sinj*cosA+5),
                     //mess=1/z+5,where 5 is constant k2 which is distance from viewer
                      cosi=cos(i),
                      cosB=cos(B),
                      sinB=sin(B),
                      //matrix multiplications
                      t=sini*cosj2*cosA-sinj* sinA;
                      //getting x and y coordinates and representing in 1D array(80*22)
                    int x=40+30*mess*(cosi*cosj2*cosB-t*sinB);
                    //x=40+k1*mess*x,where is 30 is constant for wide buffering in 2D screen along x axis
                    int y= 11+15*mess*(cosi*cosj2*sinB +t*cosB);
                   //y=40+k1*mess*y,where is 15 is constant for wide buffering in 2D screen along y axis
                    int o=x+80*y;//representing two coordinate as index of 1D array
                    /**Calculating shades
                     * we take unit vectors of the points on the  circle and rotate 
                     * along three axes and take the dot product with the fixed
                     * light in this case (0,1,-1),The range of the unit normal is [0,root(2)]
                     * we multiply this with 8 to get values between
                     * [0,11] higher this value higher is the brightness**/
                    int N=8*((sinj*sinA-sini*cosj*cosA)*cosB-sini*cosj*sinA-sinj*cosA-cosi *cosj*sinB);
                    //check for z-buffer
                    if(22>y&&y>0&&x>0&&80>x&&mess>z[o]){
                    z[o]=mess;
                    b[o]=brightness[N>0?N:0];
            }
        }
        }
         cout<<"\x1b[d";
        for(int k=0;k<1761;k++)
        {
            putchar(k%80!=0?b[k]:10);
        }
        A=A+0.04;
 	    B=B+0.02;      
   }
    return 0;
}
