//
// Created by user on 6/28/2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <bits/stdc++.h>
#include <winuser.h>

using namespace std;

#include "CartManagement.h"
#include "StorageManagement.h"
#include "MainMenuManagement.h"
#include "ConvertionsSystem.h"

vector<int> customeresId;
int currentCart=0;

vector<string> filter(string filename) {
    int val;
    ifstream myFile(filename);
    string line="";
    vector<string> words;
    string word;

    while(getline(myFile, line)){
        bool _reading = false /*switch between reading word or not if there (") or (,)*/ , first = false;

        for(int i = 0; i < line.size(); i++){
            if(line[i] == '"' and !first){ // make _reading true if there (") in another char excpet first char
                _reading = true;
                first = true;
                continue;//jump to next char
            }else if(line[i] == '"' and first){ // make _reading false if there (") in first char
                _reading = false;
                first = false;
                continue;//jump to next char
            }



            if(_reading){
                word += line[i];
            }else{
                bool reading = false /*switch between reading word or not if there (") and (,)*/;

                if(line[i] != '"' and line[i] != ',') // make reading true unless there (") and (,)
                    reading = true;

                if(line[i] == ','){
                    words.push_back(word);
                    word = "";
                }

                if(reading == true){
                    word += line[i];
                    reading = false;
                    if(i+1 == line.size()){
                        words.push_back(word);
                        word = "";
                    }
                }
            }
        }

    }

    return words;
}

int customerId(){
    ifstream customeresFile;
    customeresFile.open("Customers.csv");

    while(customeresFile.good()){
        string ID="";
        getline(customeresFile, ID, ',');
        customeresId.push_back(strToInt(ID));
    }
    customeresFile.close();
    auto Id = *max_element(begin(customeresId), end(customeresId));//here
    customeresId.push_back(Id + 1);

    ofstream CustomeresFile;
    CustomeresFile.open("Customers.csv", ios::app);
    CustomeresFile << Id + 1 << ',';
    CustomeresFile.close();

    return Id + 1;
}

void picNewCart(){
    ofstream newFile;
    string id=numToStr(customerId());
    newFile.open(id + ".csv");

    currentCart = strToInt(id);

    cout << "Current Cart:" << id << endl;
}

void addToCartById(int ID, int Quantity){
    if(quantityCheck(ID, Quantity)){
        string toCart = numToStr(ID) + ',' + numToStr(Quantity);

        /*-----------Add To Cart-----------*/
        ofstream cart;
        cart.open(numToStr(currentCart) + ".csv" , ios::app);
        cart << toCart + ',';
        cout << "Product("<< ID <<") Has Been Added With Quantity: " << Quantity << endl;
        cart.close();
        /*-----------Add To Cart-----------*/

    }else{
        cout << "Adding Process Failed" << endl;
        int msgboxID=MessageBox(NULL, (LPCSTR)"The Quantity Request is Over Then in Storage.\n(Nothing Added)", (LPCSTR)"WARNING", MB_ICONWARNING | MB_OK);
    }
}

bool quantityCheck(int ID/*65*/, int Quantity/*10*/){
    vector<tuple<int, string, double, int>> storage = getStorage();
    vector<int> quantities = getProductsQuantity();
    vector<int> ides = getProductsId();

    for(auto id:ides){
        if(ID/*65*/ == id){
            tuple<string, double, int> product = getProductNameById(id);
            if(get<2>(product) >= Quantity){
                return true;
            }else if(get<2>(product) < Quantity){
                return false;
            }
        }
    }
    return false;
}


