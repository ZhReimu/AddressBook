//
// Created by Mr.X on 2022-05-10-0010.
//
#include "iostream"
#include "fstream"
#include "cJSON.h"

using namespace std;

void test() {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "Name", "Value");
    cout << cJSON_Print(json) << endl;
}