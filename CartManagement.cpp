//
// Created by user on 6/28/2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <map>
#include <list>
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

int getCustomerId(){
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

vector<tuple<int, int>> restoreCustomer(int ID){
    currentCart = ID;
    vector<tuple<int, int>> output;
    vector<string> words = filter(numToStr(ID) + ".csv");

    for(int i = 0; i < words.size();){
        output.push_back(make_tuple(strToInt(words[i]), strToInt(words[i+1])));
        i += 2;
    }
    return output;
}

void picNewCart(){
    ofstream newFile;
    string id=numToStr(getCustomerId());
    newFile.open(id + ".csv");

    currentCart = strToInt(id);

    cout << "New Cart Has Been Created ID(Save This For Future Using): " << id << endl;
}

int addToCartById(int ID, int Quantity){
    /*Error 2: Wrong ID*/
    /*Error 1: Quantity Request Over Storage Quantity*/
    vector<int> Ides = getProductsId();
    vector<int> Quantities = getProductsQuantity();
    bool error2=false;
    bool error1=false;

    for(auto id:Ides){
        if(id != ID){
            error2 = true;
        }else if(id == ID){
            error2 = false;
            break;
        }
    }

    if(quantityCheck(ID, Quantity)){
        error1=false;
    }else{
        error1=true;
    }

    if(error2){
        cout << "Error 2: Wrong ID";
        return 2;
    }else if(error1){
        cout << "Error 1: Quantity Request Over Storage Quantity";
        return 1;
    }

    string toCart = numToStr(ID) + ',' + numToStr(Quantity);

    /*-----------Add To Cart-----------*/
    ofstream cart;
    cart.open(numToStr(currentCart) + ".csv" , ios::app);
    cart << toCart + ',';
    cout << "Product("<< ID <<") Has Been Added With Quantity: " << Quantity << " To Customer Id: " << currentCart << endl;
    cart.close();
    /*-----------Add To Cart-----------*/
}

bool quantityCheck(int ID, int Quantity){
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


