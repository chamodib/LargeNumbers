// Natural.h

// Name : Chamodi Basnayake


#include "cmpt_error.h"  // don't add any more #includes
#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Natural {

private:

    int number;
    string numStr;

    vector<int> numVec;

    //Helper function implemented to check that the string only contains digits (returns true)
   
    bool hasNum(string s){
        for(int i = 0;i < s.length();i++) {
            if(s[i] >= '0' && s[i] <= '9') {
                continue;
            } else {
                return false;
                break;
            }
        }
        return true;
   }


public:
    // Pre-condition:
    //    none
    // Post-condition:
    //    constructs a new Natural with value 0
    Natural() {  // default constructor
        number = 0;
        numStr = "0";
        numVec.push_back(0);
    }

    // Pre-condition:
    //    n >= 0
    //    (call cmpt:error if this is not satisfied)
    // Post-condition:
    //    constructs a new Natural with value n
    Natural(int n) {
        if (n < 0){
            cmpt::error ("invalid number");
        } else if((n==0)){

            number = n;

            numVec.push_back(0);
            
        }else if(n>0){
            number = n;
        
        //Loop implemented to extract each digit of the int    
            while (n!=0){
                int lastDigit = n%10;
                n = n/10;

//Referred to following website for accessing last digit of an int: http://www.cplusplus.com/forum/beginner/49775/

                numVec.push_back(lastDigit);
            }
        }

        reverse(numVec.begin(),numVec.end());

//Referred to following website for using reverse function: http://www.cplusplus.com/reference/algorithm/reverse/
    }

    // Pre-condition:
    //    s consists of 1, or more, digit characters
    //    (call cmpt:error if this is not satisfied)
    // Post-condition:
    //    constructs a Natural representation of s so that
    //    this->to_string() == s
    Natural(const string& s) {
        
        int corNum = 0;

        if (s.length() == 0){
            cmpt::error ("string has no charcters");
        } else {

        //Call helper function defined in private part. Return 1, if the strin contains only digits   
            if(hasNum(s)== 1){
                for (int i = s.length()-1; i >=0; i--){
                    corNum = (s[i]) - '0';
                    numVec.push_back(corNum); 
                }         
                                        
            } else {
                cmpt::error ("string contains non-digits");
            }

        }

        reverse(numVec.begin(),numVec.end());
            
    }   
        

    // Pre-condition:
    //    none
    // Post-condition:
    //    constructs a new Natural whose value is the same as other
    Natural(const Natural& other) {  // copy constructor
        number = other.number;
        numStr = other.numStr;

    //Creating a deep copy     
        for (int i=0; i<other.numVec.size(); i++){
            numVec[i] = other.numVec[i];
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns the number of digits in this Natural
    int num_digits() const {

        return numVec.size();
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns true if this Natural is 0, and false otherwise
    bool is_zero() const {

        if(numVec[0] == 0){
            return true;
        }
    }

    // Pre-condition:
    //    none
    // Post-condition:
    //    returns a new Natural equal to the sum of a and this Natural
    Natural operator+(const Natural& a) const {

    //Creating soft copy of the vectors of each Natural object, so vectors can be reversed for summing purposes
        vector<int>aReverse = a.numVec;
        vector<int>thisReverse = numVec;

    //Reversing the copies of Natural's vectors, so addition is performed easily
        reverse(thisReverse.begin(),thisReverse.end());
        reverse(aReverse.begin(),aReverse.end());

    //Creating a new Natural object to be returned at the end
        Natural returnSum;

        int thisSize = thisReverse.size();
        int aSize = aReverse.size();
        

        int max = 0;
        int min =0;

    //Determining the sizes of the numbers
        if(thisSize > aSize){
            max = thisSize;
            min = aSize;

        }else if(aSize > thisSize){
            max = aSize;
            min = thisSize;
        }else{
            max = thisSize;
            min = aSize;
        }
    
        
        //Initializin a vector to store the sum of the two numbers
        vector<int>sum(max+1,0);
        int carry = 0;

    //Implement if loop to see if the two numbers are of same size    
        //If numbers are different sizes, proceed
        if(min != max){
            
            //Running a loop till the size of smaller number, and adding the values of the two numbers    
            for(int i=0; i< min; i++){
                sum[i]= (thisReverse[i] + aReverse[i] + carry)%10;
                
                if((thisReverse[i] + aReverse[i] + carry) >= 10){
                    carry = 1;
                }else{
                    carry = 0;
                }
            }

            //Running a loop from size of smallest number to the size of larger number, and only taking to account the values of the larger number (since smaller number has 0s)
            for (int i=min; i<max; i++){

                //If else loop determines which number is bigger of the two
                if (aSize==max){

                    sum[i]= (aReverse[i] + carry)%10;
                
                    if((aReverse[i] + carry) >= 10){
                        carry = 1;
                    }else{
                        carry = 0;
                    }

                        sum[max] = carry;

                }else if(thisSize == max){
                    sum[i]= (thisReverse[i] + carry)%10;
                
                    if((thisReverse[i] + carry) >= 10){
                        carry = 1;
                    }else{
                        carry = 0;
                    }
                        //Add the last carry over to the last index of sum
                        sum[max] = carry;
                }
            }
        //If numbers are the same size, proceed       
        }else{
            for(int i=0; i<max;i++){

                sum[i] = (aReverse[i]+thisReverse[i]+carry)%10;

                if((aReverse[i]+thisReverse[i]+carry) >= 10){
                    carry = 1;
                }else{
                    carry = 0;
                }
            }
                
                sum[max] = carry;
        }

        //If there's any zeros at the beginning of a number, delete them
            // eg. 0004560 -> 4560

            for (int i=sum.size()-1; i>=1;i--){
                if (sum[i] == 0){
                    sum.pop_back();
                }else if(sum[i] >0){
                    break;
                }
            }
        
        //Reverse sum vector,so it's in right order
        reverse(sum.begin(),sum.end());

        //Creating soft copy of sum into vector of Natural object returnSum
        returnSum.numVec = sum;
        
        return returnSum;
    }


    // Pre-condition:
    //    none
    // Post-condition:
    //    returns a new Natural equal to the product of a and this Natural
     Natural operator*(const Natural& a) const {
        
        //Creating soft copy of the vectors of each Natural object, so vectors can be reversed for summing purposes
        vector<int>aReverse = a.numVec;
        vector<int>thisReverse = numVec;

        //Reversing the copies of Natural's vectors, so addition is performed easily
        reverse(thisReverse.begin(),thisReverse.end());
        reverse(aReverse.begin(),aReverse.end());;

        //Create a Natural object to be returned
        Natural tempMulti;

        int thisSize = thisReverse.size();
        int aSize = aReverse.size();

        //Initializin a vector to store the multiplication of the two numbers
        vector<int>multi(thisSize + aSize,0);

        //Create int to keep track of place within the multi vector
        int vecPlace = 0;

        //Create ints to store digits of the numbers through the iterations
        int thisNum =0;
        int aNum = 0;

        //Store the carry over values
        int carry =0;

        //Create int to store the value of the multiple for each iteration
        int multiCellValue = 0;

        //For loop to iterate through values of numVec
        for (int i=0; i <thisSize; i++){

            thisNum = thisReverse[i];
            carry = 0;

            //Increment value of place, through each iteration of the for loop
            vecPlace = i;

            //For loop to iterate through values of a.numvec
            for(int i=0; i<aSize; i++){

                aNum = aReverse[i];
                //add carry over value from previous iteration, current multiple of the two numbers, and previous numbers stored at multi[vecPlace]
                multiCellValue = (carry + (thisNum*aNum) + multi[vecPlace]);

                if(multiCellValue >=10){
                    carry = multiCellValue/10;
                }else{
                    carry = 0;
                }

                multi[vecPlace] = multiCellValue % 10;
                //Increment value for the next iteration within for loop
                vecPlace++;
                
            }

            if(carry>0){
                multi[vecPlace] += carry;
            }

            //Increment value for next iteration within for loop
            vecPlace++;
        }

//If there's any zeros at the beginning of a number, delete them
            // eg. 0004560 -> 4560
        for (int i=multi.size()-1; i>=1;i--){
            if (multi[i] == 0){
                multi.pop_back();
            }else if(multi[i] >0){
                break;
            }
        }
// Referred to following website on implementing pop_back: http://www.cplusplus.com/reference/vector/vector/pop_back/        

        //Revert vector to correct form
        reverse(multi.begin(),multi.end());

        tempMulti.numVec = multi;

        return tempMulti;

    }


    // Pre-condition:
    //    none
    // Post-condition:
    //    returns a string representation of this Natural
    string to_string() const {
        if(numVec.size() ==0){
            return " ";
        } else if (numVec.size()==1){
            return  std::to_string(numVec[0]);
        }else{
            string str = std::to_string(numVec[0]);
            for (int i=1; i< numVec.size(); i++){
                str += std::to_string(numVec[i]);
            }
            return str;
        }
    }


}; // class Natural

//
// the following methods are provided for convenience
//

ostream& operator<<(ostream& os, const Natural& b) {
    os << b.to_string();
    return os;
}

bool operator==(const Natural& a, const Natural& b) {
    return a.to_string() == b.to_string();
}

bool operator!=(const Natural& a, const Natural& b) {
    return !(a == b);
}

bool operator==(const Natural& a, const string& b) {
    return a.to_string() == b;
}

bool operator!=(const Natural& a, const string& b) {
    return !(a == b);
}


/////////////////////////////////////////////////////////////////////////
//
// CITATIONS
// ------------

// - Received helped from the TA on the following:
//        -Through consulting him, I got the idea of creating a vector object in my private
//        -Helped implement is_zero function, as he confirmed my undestanding of the method is correct
//        -Helped debugg my +operator, which lead me to use many "reverse" functions throughout the program

// - Referred to code provided by the professor through class website for following:
//        - Implementing the to_string function

// - I discussd the assignment with fellow classmate "Praneet Singh":
//        - We went over on what the class should do, and briefly on what each function does
//        - I was instructed to return a Natural object for each of the + and * operators by him 
//        - Checking for digits in a string with loop "if(s[i] >= '0' && s[i] <= '9')" after my idea or using "isdigit" failed
//        - Did not at any point share code
//
// - For implementing the +operator method, I referred to following video: https://www.youtube.com/watch?v=pP6GWIaiELM
//        - I got the idea of creating "int carry" instead of my idea to creat a "vector<int>carry"
//        - Other aspects were implemented by me
//
// - For implementing *operator method, I referred to following websites:
//        -https://www.geeksforgeeks.org/multiply-large-numbers-represented-as-strings/
//        - Was able to successfully implement my "int vecPlace" after seeing their use of "int i_n1" and "int i_n2"
//        - My initial implementation of vectors for each layer of multiplication and adding them together to get the answer proved to be difficult, and therefore adopted the idea of using 1 vector and adding each layer to the same vector
//        - All other aspects of the method was completed before this detail was added
///////////////////////////////////////////////////////////////////////
