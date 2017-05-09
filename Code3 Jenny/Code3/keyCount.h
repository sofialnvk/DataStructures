//
//  keyCount.h
//  Code3
//
//  Created by Jenny Tellne on 2017-05-08.
//  Copyright © 2017 Jenny Tellne. All rights reserved.
//

#ifndef keyCount_h
#define keyCount_h
#include <iomanip>

using namespace std;

class keyCount
{
public:
    keyCount(string in_key = "", int in_counter = 0)
    : key{in_key}, counter{in_counter}
    {
    }
    
    bool operator<(const keyCount& rhs) const
    {
        if(key < rhs.key)
            return true;
        return false;
    }
    
    friend ostream& operator<<(ostream& os, const keyCount& kc)
    {
        os << kc.key << setw(10) << kc.counter << endl;
        return os;
    }
    
    void increment_counter(keyCount& kc)
    {
        kc.counter++;
    }
    
private:
    string key;
    int counter;
    
};


#endif /* keyCount_h */
