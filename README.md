# C++ 课程设计 学生通讯录

## 基本功能

以本班同学的具体数据为背景, 设计一个本班同学通讯录。

## 实现功能

- [x] 通讯录的编辑 (增加、删除)
- [x] 按不同的项目进行查找
- [x] 对已存在的通讯录按不同的项排序
- [x] 将通讯录写入文件
- [x] 从文件读取通讯录
- [x] 通讯录至少应该有以下数据项: 姓名, 地址, 电话, 邮编, E-mail

## 额外功能

- [x] APP 图标
- [x] APP 打包

## 编译

- 使用 `Clion` 导入项目并使用 `Ninja` 构建项目
- 或 使用 `CMake` 构建项目 ~~建议使用 CMake GUI, 不然会报 找不到 Ninja~~

## 打包

- 使用 `QT` 自带工具 `windeployqt` 打包所有依赖到一个文件夹
- 或 先打包依赖, 再使用 `Enigmavb` 打包所有依赖到一个 `exe` 文件