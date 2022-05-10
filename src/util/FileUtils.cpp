//
// Created by Mr.X on 2022-05-10-0010.
//
#include "iostream"
#include "fstream"
#include "cJSON.h"
#include "Student.h"

using namespace std;


/**
 * 将一个 Student 对象转换成 cJson 对象
 * @param student 要转换的 student
 * @return 转换后的 cJson
 */
cJSON *student2JSON(const Student &student) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "name", student.getCharName());
    cJSON_AddStringToObject(json, "address", student.getCharAddress());
    cJSON_AddStringToObject(json, "phone", student.getCharPhone());
    cJSON_AddStringToObject(json, "postCode", student.getCharPostCode());
    cJSON_AddStringToObject(json, "eMail", student.getCharEMail());
    return json;
}

/**
 * 将 Student 数组序列化为 json 并保存到文件
 * @param students 要序列化的 json
 * @param num 数组长度
 * @param saveFile 保存的文件名
 */
void saveStudents(Student students[], int num, const char *saveFile = "save.json") {
    // 打开并清空文件
    ofstream file(saveFile, ofstream::trunc);
    cJSON *json = cJSON_CreateObject();
    cJSON *array = cJSON_AddArrayToObject(json, "students");
    for (int i = 0; i < num; i++) {
        cJSON_AddItemToArray(array, student2JSON(students[i]));
    }
    file << cJSON_Print(json) << endl;
    file.close();
}


void test() {
    Student s[2];
    s[0].setName("asd");
    s[1].setName("bbb");
    saveStudents(s, 2);
}