#include <stdlib.h>
#include <stdio.h>

double frac;

void decimalToBinary(long a[],long length, long num){
    for(long i=0; i<length; i++){
        a[i] = num%2;
        num = num/2;
    }
}

double fractionBinary(double fraction){   //this code takes in a decimal fraction and turns it in to binary(as a double). For example, 0.625 = 0.101000
    double current = fraction * 2.0;
    double remainder = ((int)current) % 2;

    if(current == 1 || current == frac){
        return remainder / 10;
    }

    return fractionBinary(current - remainder)/10 + remainder/10;
}

void fractionToBinary(long a[], double num){  //takes the binary representation of a double and puts it in an array
    double binary = fractionBinary(num);
    for(int e=0; e<6; e++){
        binary = binary * 10;
        a[e] = (int)binary % 10; //now the binary of the number to the right of the decimal point is stored in int array[6]
    }
}

long power(long base, long exponent){
    long powerValue = 1;
    for(long i=0; i < exponent; i++){
        powerValue = powerValue * base;
    }
    return powerValue;
}

long bitsNeeded(long num){
    long x = 1;
    while (power(2,x) <= num){
        x++;
    } 
    long size = x;
    return size;
}

void reverse(long arr[], long n){
    long aux[n];
 
    for (int i = 0; i < n; i++) {
        aux[n - 1 - i] = arr[i];
    }
 
    for (int i = 0; i < n; i++) {
        arr[i] = aux[i];
    }
}

void final(double num, int bits){    //this function creates the final output. This outputs exactly what we are supposed to output for the assignment
    if(num < 1){
        long ar[6];
        fractionToBinary(ar, num);

        int index = 0;
        for(int c=0; c<6; c++){
            if(ar[c]==1){
                index = c;
                break; 
            }
        }

        if(bits == 0){
            printf("1 %d\n", index+1);
        }else{
            printf("1");
            printf(".");

            int remaining = 6 - (index + 1);
            if(bits>remaining){
                for(int b = index+1; b<6; b++){
                    printf("%li", ar[b]);
                }
                for(int v=0;v<6-remaining;v++){
                    printf("0");
                }
            }else{
                for(int o=index+1; o<index+(bits+1);o++){
                    printf("%li", ar[o]);
                }
            }
            printf(" -%d", index + 1);
            printf("\n");
        }

    }else{
        long size = bitsNeeded((long)num);
        long arr[size];
        decimalToBinary(arr, size, (long)num);
        reverse(arr, size);   // the left side of decimal point is stored in array[] now

        long left = (long)num;
        frac = num - (double)left; // this gets us just the fraction part of the double (whatever is on the right side of the decimal point)

        long array[6];
        fractionToBinary(array, frac);

        if(bits<0){  // if the number of bits is an invalid number, we do nothing
            printf("\n");
        }else if(bits == 0){  // the bits just tells us how many numbers to output after the decimal. If it is 0, just output arr[0] + " " + size-1
            printf("%li ", arr[0]);
            printf("%li", size-1);
            printf("\n");
        }else{
            if(size-1 > bits){
                printf("%li", arr[0]);
                printf(".");
                for(long n=1; n<bits+1; n++){
                    printf("%li", arr[n]);
                }
                printf(" %li", size-1);
                printf("\n");
            }else{
                printf("%li", arr[0]);
                printf(".");
                for(long n=1; n<size; n++){
                    printf("%li", arr[n]);
                }
                int len = bits - (size-1);
                for(int c=0; c<len; c++){
                    printf("%li", array[c]);
                }
                printf(" %li", size-1);
                printf("\n");
            }
        }
    }
    
}

int main(int argc, char* argv[argc+1]){
    double number;
    int bits;
    FILE* fp = fopen(argv[1], "r");
    while(fscanf(fp, "%lf %d\n", &number, &bits) != EOF){
        final(number, bits);
    }
    fclose(fp);
    return 0;
}
