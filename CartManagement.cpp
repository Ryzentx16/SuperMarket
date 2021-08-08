//
// Created by user on 6/28/2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>

using namespace std;

#include "CartManagement.h"
#include "StorageManagement.h"
#include "MainMenuManagement.h"
#include "ConvertionsSystem.h"

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

string addToCartById(vector<int> Ides, vector<int> Quantities){
    string toCart;
    for(int i=0; i<Ides.size();i++){
        if(Quantities[i] == 0)
            continue;
        //CurrentCart.push_back(make_tuple(trim(get<0>(getProductNameById(Ides[i]))) , trim(numToStr(get<1>(getProductNameById(Ides[i])) * Quantities[i])) , trim(numToStr(Quantities[i]))));
    }
    return "null";
}

bool quantityCheck(int ID, int Quantity){
    vector<tuple<int, string, double, int>> storage = getStorage();
    vector<int> quantities = getProductsQuantity();
    vector<int> ides = getProductsId();

    for(auto id:ides){
        if(ID == id){
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


