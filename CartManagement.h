//
// Created by user on 6/28/2021.
//

#ifndef SUPERMARKET_WITHOUT_OOP__CARTMANAGEMENT_H
#define SUPERMARKET_WITHOUT_OOP__CARTMANAGEMENT_H

void restoreCustomerMenu(vector<tuple<int, int>> customerCart);
vector<tuple<int, int>> restoreCustomer(int ID);
void picNewCart();
int addToCartById(int ID, int Quantity);
bool quantityCheck(int ID, int Quantity);

#endif //SUPERMARKET_WITHOUT_OOP__CARTMANAGEMENT_H
