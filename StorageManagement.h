//
// Created by user on 6/21/2021.
//

#ifndef SUPERMARKET_WITHOUT_OOP__STORAGEMANAGEMENT_H
#define SUPERMARKET_WITHOUT_OOP__STORAGEMANAGEMENT_H

vector<string> filter();
vector<tuple<int, string, double, int>> products();
vector<tuple<int, string, double, int>> getStorage();
vector<string> getProductsName();
vector<double> getProductsPrice();
vector<int> getProductsQuantity();
vector<int> getProductsId();
tuple<string, double, int> getProductNameById(int id);
void printProducts();

#endif //SUPERMARKET_WITHOUT_OOP__STORAGEMANAGEMENT_H
