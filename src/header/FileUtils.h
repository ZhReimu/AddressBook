//
// Created by Mr.X on 2022-05-10-0010.
//

#ifndef CLIONPROJECTS_FILEUTILS_H
#define CLIONPROJECTS_FILEUTILS_H

#include "sstream"
#include "QDebug"
#include "iostream"
#include "fstream"
#include "cJSON.h"
#include "Student.h"

using namespace std;

class FileUtils {

public:
    /**
    * 将一个 Student 对象转换成 cJson 对象
    * @param student 要转换的 student
    * @return 转换后的 cJson
    */
    static cJSON *student2JSON(const Student &student);

    /**
     * 将 Student 数组序列化为 json 并保存到文件
     * @param students 要序列化的 json
     * @param num 数组长度
     * @param saveFile 保存的文件名
     */
    static void saveStudents(Student students[], unsigned int num, const QString &saveFile = "save.json");


    /**
     * 反序列化 Student 数组
     * @param size 反序列化后的 Student 数组长度
     * @param saveFile 保存的文件名
     * @return 反序列化后的 Student 数组
     */
    static Student *readStudents(unsigned int &size, const QString &saveFile = "save.json");

    static bool verifyFile(const QString &path);
};


#endif //CLIONPROJECTS_FILEUTILS_H
