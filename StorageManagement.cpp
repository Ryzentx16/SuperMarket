//
// Created by user on 6/24/2021.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <tuple>
#include <map>

using namespace std;

#include "StorageManagement.h"
#include "ConvertionsSystem.h"

vector<string> filter() {
    string filename = "Product-Price.csv";
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

vector<tuple<int, string, double, int>> products(){

    vector<tuple<int, string, double, int>> output;
    vector<string> words = filter();

    for(int i = 0; i < words.size();){
        output.push_back(make_tuple(strToInt(words[i]), words[i+1], strToDouble(words[i+2]), strToInt(words[i+3])));
        i += 4;
    }

    return output;
}

vector<tuple<int, string, double, int>> getStorage(){
    /*for(auto tp : products()){
        storage.insert({get<0>(tp), make_tuple(get<1>(tp), get<2>(tp), get<3>(tp))});
    }*/
    return products();
}

vector<string> getProductsName(){
    vector<string> names;

    for(auto x : products()){
        names.push_back(get<1>(x));
    }
    return names;
}

vector<double> getProductsPrice(){
    vector<double> prices;

    for(auto x : products()){
        //cout << get<2>(x) << endl;
        prices.push_back(get<2>(x));
    }

    return prices;
}

vector<int> getProductsQuantity(){
    vector<int> quantities;

    for(auto x : products()){
        quantities.push_back(get<3>(x));
    }
    return quantities;
}

vector<int> getProductsId(){
    vector<int> Ides;

    for(auto x : products()){
        Ides.push_back(get<0>(x));
    }
    return Ides;
}

tuple<string, double, int> getProductNameById(int id){
    vector<tuple<int, string, double, int>> storage = getStorage();
    tuple<string, double, int> quickProduct;

    for(auto i : storage){
        if(id == get<0>(i)){
            //cout << get<1>(i) << endl;
            quickProduct = make_tuple(get<1>(i), get<2>(i), get<3>(i));
            break;
        }
    }

    return quickProduct;
}

void printProducts(){
    //fillStorage();
    /*for(auto product : storage){
        //cout << "Id: " << product.first << " | Product: " << get<0>(product.second) << " | Price: " << get<1>(product.second) << " | Quantity: " << get<2>(product.second) << endl;
    }*/

    vector<tuple<int, string, double, int>> product = products();

    for(auto x : product){
        cout << get<1>(x) << endl;
    }
}










