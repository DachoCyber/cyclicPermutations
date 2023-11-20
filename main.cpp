#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool wellDefined(string cycle) {

    bool paranthesisOpen = false;
    bool paranthesisClosed = false;
 
    int numbers[100];
    int numCount = 0;
    for(int i = 0; cycle[i] != '\0'; i++) {
        if(cycle[i] == '(' && paranthesisOpen == true) {
            return false;
        }
        if(cycle[i] == ')' && paranthesisClosed == true) {
            return false;
        }
        if(cycle[i] == '(') {
            paranthesisOpen = true;
            paranthesisClosed = false;
        }    
        else if(cycle[i] == ')') {
            paranthesisClosed = true;
            paranthesisOpen = false;
            for(int i = 0; i <= numCount; i++) {
                numbers[i] = 0;
            }
            numCount = 0;
        }
        else {
            numbers[numCount++] = cycle[i] - '0';
            for(int j = 0; j < numCount - 1; j++) {
                if(numbers[j] == numbers[numCount - 1]) {
                    return false;
                }
            }
            numCount++;
        }
    }
    return true;
}

void fillWithZeros(int arr[][20]) {
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 20; j++) {
            arr[i][j] = 0;
        }
    }
}

bool isNumberChecker(char ch) {
    return ch >= '0' && ch <= '9';
}

int toInt(char num) {
    return num - '0';
}

int maxElement(int arr[][20], int numOfRows, int numOfColumns) {
    int max = 0;
    for(int i = 0; i < numOfRows; i++) {
        for(int j = 0; j < numOfColumns; j++) {
            if(arr[i][j] > max) {
                max = arr[i][j];
            }
        }
    }
    return max;
}

bool isElement(int x, int arr[], int n) {
    for(int i = 0; i < n; i++) {
        if(arr[i] == x) {
            return false;
        }
    }
    return true;
}

string getCyclesWithoutCommonElements(string cycle) {
    
    if(!wellDefined(cycle)) {
        return "There is a mistake!";
    }

    int arrayCycles[20][20], cycleCount = 0, indexCount = 0;
    fillWithZeros(arrayCycles);
    // (4568)(1245) -> (125)(3)(468)(7)	
    int i = 0;
    while(cycle[i] != '\0') {
        
        if(cycle[i] == ')') {
            indexCount = 0;
            cycleCount++;
        }
        bool isNumber = isNumberChecker(cycle[i]);
        if(isNumber) {
            arrayCycles[cycleCount][indexCount] = toInt(cycle[i]);
            indexCount++;
        }

        i++;
    }

    string resultCycle = "(";
    // (4568)(1245) -> (125)(3)(468)(7)	
    i = 1;
    for(i = 1; i <= maxElement(arrayCycles, 20, 20); i++) {

        int arr[20];
        arr[0] = i;
        int numOfCompositions = 0;
        cout << arr[0] << " ";
        
        for(int rows = 19; rows >= 0; rows--) {
            for(int col = 0; col <= 19; col++) {

                if(arrayCycles[rows][col] == arr[numOfCompositions]) {

                    if(arrayCycles[rows][col + 1] != 0) {
                        arr[numOfCompositions] = arrayCycles[rows][col + 1];
                        if(isElement(arr[numOfCompositions], arr, numOfCompositions) == true) {
                            cout << ")(" << " ";
                        }
                    }
                    else {
                        arr[numOfCompositions] = arrayCycles[rows][0];
                    }
                    numOfCompositions++;
                }
            }
        }
    
        cout << arr[numOfCompositions] << " ";
    }
    return resultCycle;
    
}

int main() {

    string cycle;
    cout << "Enter a cyclic permutations with paranthesis: " << endl;
    getline(cin, cycle);

    string resultCycle = getCyclesWithoutCommonElements(cycle);
    cout << resultCycle << endl;

    return 0;
}
