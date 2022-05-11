//
// Created by Mr.X on 2022-05-10-0010.
//
#include "FileUtils.h"

using namespace std;

/**
* 将一个 Student 对象转换成 cJson 对象
* @param student 要转换的 student
* @return 转换后的 cJson
*/
cJSON *FileUtils::student2JSON(const Student &student) {
    // 创建 JSON 对象
    cJSON *json = cJSON_CreateObject();
    // 将 Student 属性作为 key 存入 JSON
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
void FileUtils::saveStudents(Student students[], unsigned int num, const char *saveFile) {
    // 打开并清空文件
    ofstream file(saveFile, ios::trunc);
    // 创建 JSON 对象
    cJSON *json = cJSON_CreateObject();
    // 存入一个 Array 对象, key 为 students
    cJSON *array = cJSON_AddArrayToObject(json, "students");
    // 遍历 students 数组
    for (int i = 0; i < num; i++) {
        // 将 序列化后的 student 对象存入 array
        cJSON_AddItemToArray(array, student2JSON(students[i]));
    }
    // 将 JSON 数据写入到文件
    file << cJSON_Print(json) << endl;
    // 释放资源
    file.close();
    cJSON_free(array);
    cJSON_free(json);
}


/**
 * 反序列化 Student 数组
 * @param size 反序列化后的 Student 数组长度
 * @param saveFile 保存的文件名
 * @return 反序列化后的 Student 数组
 */
Student *FileUtils::readStudents(int &size, const char *saveFile) {
    // 打开文件
    ifstream file(saveFile, ios::in);
    // 使用 stringStream 一次性将所有内容读入内存
    stringstream buffer;
    buffer << file.rdbuf();
    string contents(buffer.str());
    // 解析 JSON 字符串
    cJSON *json = cJSON_Parse(contents.c_str());
    // 取出 students 数组
    cJSON *array = cJSON_GetObjectItem(json, "students");
    // 获取 students 长度并将其赋值给 size
    size = cJSON_GetArraySize(array);
    // 创建 size 个 Student 对象
    auto *students = new Student[size];
    // 遍历 JSON 节点, 并给 student 赋值
    for (int i = 0; i < size; ++i) {
        students[i] << cJSON_GetArrayItem(array, i);
    }
    return students;
}
