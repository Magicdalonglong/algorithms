#include<iostream>
#include<vector>
#include<cstdlib>
#include<string>
#include<cstdio>
#include <fstream>
#include <unistd.h>

using namespace std;

/*
 * Node Class Declaration
 */
typedef pair<string, int> Node;

/*
 * HashMap Class Declaration
 */
class HashMap
{
private:
    Node** table;
    int SIZE;
    int* len;
    int* used;
public:
    HashMap(Node data[], int size){
    
        SIZE = size;
        table = new Node*[SIZE];
        len = new int[SIZE];
        used = new int[SIZE];
        for(int i = 0; i < SIZE; ++i) {
            table[i] = NULL;
            len[i] = 0;
            used[i] = 0;
        }
        Load(data);
    }
   
    /*
     * Hash Function
     */
     int hash2(string key, int k){
        int sum = 0;
        for(auto c : key) sum = (sum + c) ^ (c>>13) ^ (c>>17);
        return (13*sum + 17) % k; 
     }
    int hash (string key)
    {
        int sum = 0;
        for(auto c : key) sum = (sum + c) ^ (c>>13) ^ (c>>17);
        return sum % SIZE;
    }
    
    /*
     * Insert Element with key
     */
    void Load(Node data[])
    {
        for(int i = 0; i < SIZE; i++){
            string key = data[i].first;
            int pos1 = hash(key);
            if(table[pos1] == NULL){
                table[pos1] = new Node[100];
                len[pos1] = 10;
                used[pos1] = 1;
                table[pos1][0] = data[i];
            }else{
                if(used[pos1] == len[pos1])
                    grow(pos1);
                table[pos1][used[pos1]] = data[i];
            }
        }

        for(int i = 0; i < SIZE; i++){
            Node* temp = table[i];
            len[i] = used[i]*used[i];
            table[i] = new Node[len[i]];
            for(int j = 0; j < used[i] ; ++j)
            {
                string key = temp[j].first;
                int pos2 = hash2(key,len[i]);
                table[i][pos2] = temp[j];
            }
            delete []temp;
        }
        
    }   
    void grow(int index){
        Node* temp = table[index];
        table[index] = new Node[len[index] * 2];
        for(int i = 0; i < len[index]; i++)
            table[index][i] = temp[i];
        len[index] *= 2;
    }
   
    /*
     * Search Element at a key
     */
    bool Search(string key)
    {
        int pos1 = hash(key);
        int pos2 = hash2(key, len[pos1]);
        return table[pos1][pos2].first == key;
    }
    
    int get(string key){
        
        int pos1 = hash(key);
        int pos2 = hash2(key, len[pos1]);
        return table[pos1][pos2].first == key ? table[pos1][pos2].second : -1;
    }
};

int main()
{
    
    

    return 0;
}
