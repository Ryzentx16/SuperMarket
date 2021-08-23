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
map<int, int> currentCart;
int currentCartId=0;

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

void fixFileSpam(){
    vector<string> words = filter(numToStr(currentCartId)+".csv");
    vector<tuple<int, int>> cart;
    for(int i=0; i < words.size();){
        cart.push_back(make_tuple(strToInt(words[i]), strToInt(words[i+1])));
        i += 2;
    }

    ofstream tempFile;
    tempFile.open(numToStr(currentCartId) + "temp.csv", ios::app);
    for(auto product:cart){
        string toCart;
        toCart = get<0>(product) + ',' + get<1>(product);
        tempFile << toCart + '\n';
    }
}

void fixFileSpam(int Id){
    vector<string> words = filter(numToStr(Id)+".csv");
    //vector<tuple<int, int>> cart;
    map<int, int> cart;
    for(int i=0; i < words.size();){
        //cart.push_back(make_tuple(strToInt(words[i]), strToInt(words[i+1])));
        cart[strToInt(words[i])] = strToInt(words[i+1]);
        i += 2;
    }

    bool isDone=false;
    while(!isDone){

    }

    ofstream tempFile;
    tempFile.open(numToStr(Id) + "temp.csv", ios::app);
    /*for(auto product:cart){
        string toCart;
        toCart = get<0>(product) + ',' + get<1>(product);
        tempFile << toCart + '\n';
    }*/
    tempFile.close();
}

void updateCart(int ID, int newQuantity){
    vector<tuple<int, int>> newCart;

    for(auto product:currentCart){
        if(get<0>(product) == ID){
            newCart.push_back(make_tuple(ID, get<1>(product) + newQuantity));
        }else{
            newCart.push_back(product);
        }
    }

    for(auto product:newCart){
        cout << get<0>(product) << " " << get<1>(product) <<endl;
    }

// TODO (user#1#08/23/21): Update Cart
}

vector<tuple<int, string, double, int>> restoreCustomerMenu(vector<tuple<int, int>> customerCart){

    vector<tuple<int, string, double, int>> cart;

    vector<int> ides;
    vector<string> names;
    vector<double> prices;
    vector<int> quantities;

    for(auto product:customerCart){
        cart.push_back(make_tuple(get<0>(product), get<0>(getProductById(get<0>(product))), get<1>(getProductById(get<0>(product))), get<1>(product)));

        ides.push_back(get<0>(product));
        names.push_back(get<0>(getProductById(get<0>(product))));
        prices.push_back(get<1>(getProductById(get<0>(product))));
        quantities.push_back(get<1>(product));
    }





    int highestLen=0;
    for (auto name:names)
        if(name.size() > highestLen) highestLen = name.size();

    cout << "ID" << setw(10) << "Product" << setw(highestLen+5) << "Price" << setw(16) << "Quantity" << endl; // Header

    for(int i = 0; i < names.size(); i++){
        cout << left << ides[i] << right << setw(3+names[i].size());
        cout << trim(names[i]) << setw(37-names[i].size());

        if(numToStr(prices[i]).size() <= 3){
           cout << numToStr(prices[i])+'0' << setw(13);
        }else{
           cout << numToStr(prices[i]) << setw(13);
        }

        cout<< numToStr(quantities[i]) << endl;
    }

    cout << endl;
    return cart;
}

vector<tuple<int, int>> restoreCustomer(int ID){
    currentCartId = ID;
    vector<tuple<int, int>> output;
    map<int, int> cart;
    vector<string> words = filter(numToStr(ID) + ".csv");

    for(int i = 0; i < words.size();){
        output.push_back(make_tuple(strToInt(words[i]), strToInt(words[i+1])));
        cart[strToInt(words[i])] += strToInt(words[i+1]);
        i += 2;
    }

    cout << "This What You Have From Last Session" << endl;
    currentCart = cart;
    restoreCustomerMenu(output);
    cout << "End"<<endl;
    return output;
}

void pickNewCart(){
    ofstream newFile;
    string id=numToStr(getCustomerId());
    newFile.open(id + ".csv");

    currentCartId = strToInt(id);

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

    /*-----------Add To Cart-----------*/
    currentCart[ID] += Quantity;

    string toCart;
    for(auto product:currentCart){
        if(ID == product.first){

            toCart = product.first + ',' + product.second;
            cout << numToStr(product.first) + ',' + numToStr(product.second) << endl;
            break;
        }
    }

    ofstream cart;
    cart.open(numToStr(currentCartId) + ".csv" , ios::app);
    cart << '\n' + toCart;
    cout << "Product("<< ID <<") Has Been Added With Quantity: " << Quantity << " To Customer Id: " << currentCartId << endl;
    cart.close();
    /*-----------Add To Cart-----------*/

    return 0;
}

bool quantityCheck(int ID, int Quantity){
    vector<tuple<int, string, double, int>> storage = getStorage();
    vector<int> quantities = getProductsQuantity();
    vector<int> ides = getProductsId();

    for(auto id:ides){
        if(ID/*65*/ == id){
            tuple<string, double, int> product = getProductById(id);
            if(get<2>(product) >= Quantity){
                return true;
            }else if(get<2>(product) < Quantity){
                return false;
            }
        }
    }
    return false;
}

