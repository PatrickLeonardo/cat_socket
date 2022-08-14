# Cat Socket

Socket made with c language to view .txt files in terminal on client side

## 💻 Requirements
- gcc compiler
- a linux distro

## 📨 Versions
(GCC) 12.1.1

## 📝 How to use
- compile and read server.c 
- compile and read client.c

#### if you want to change the file type to be read
#### just make the change on line 76 in the [server.c](https://github.com/PatrickLeonardo/cat-socket/blob/main/server.c) file

```c
if(strstr(buffer, ".txt"))    
```
