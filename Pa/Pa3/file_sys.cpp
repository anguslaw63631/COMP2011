/**
 * This file contains the file system functions that you need to implement.
 * You can define helper functions in this file.
 *
 * Remember to remove the initial statements in the functions.
 * They are only used so that your semi-finished codes can compile.
 */

#include <iostream>
#include "file_sys.h"
#include "utils.h"
using namespace std;

bool containsOnlyLetters(std::string const &str)
{
    return str.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-_") ==
           std::string::npos;
}
bool checkNameVal(const char *name)
{
    int Size = strlen(name);
    if (Size < 1)
    {
        return true;
    }
    if ((Size == 1 && name[0] == '.') || (Size == 2 && name[0] == '.' && name[1] == '.'))
    {
        return true;
    }
    if (name[0] == '-')
    {
        return true;
    }
    if (!(containsOnlyLetters(name)))
    {
        return true;
    }
    return false;
}

void printFileInf(File *file)
{
    cout << "file name: " << file->name << endl;
    cout << "file size: " << file->size << endl;
    cout << "file tag: " << file->tag << endl;
    if (file->next != nullptr)
    {
        cout << "next file name: " << file->next->name << endl;
    }
    else
    {
        cout << "next file name: NULL" << endl;
    }

    cout << "file parent: " << file->parent->name << endl;
}

void printDirInf(Dir *dir)
{
    cout << "dir name: " << dir->name << endl;
    if (dir->next != nullptr)
    {
        cout << "dir next: " << dir->next->name << endl;
    }
    else
    {
        cout << "dir next: NULL" << endl;
    }

    cout << "dir parent: " << dir->parent->name << endl;
    if (dir->subfile != nullptr)
    {
        cout << "dir subfile: " << dir->subfile->name << endl;
    }
    else
    {
        cout << "dir subfile: NULL" << endl;
    }

    if (dir->subdir != nullptr)
    {
        cout << "dir subDir: " << dir->subdir->name << endl;
    }
    else
    {
        cout << "dir subDir: NULL" << endl;
    }
}

bool checkUnique(const Dir *dir, const char *name)
{
    Dir *dp = dir->subdir;
    while (dp != NULL)
    {
        if (!strcmp(dp->name, name))
        {
            return true;
        }
        dp = dp->next;
    }

    File *fp = dir->subfile;
    while (fp != NULL)
    {
        if (!strcmp(fp->name, name))
        {
            return true;
        }
        fp = fp->next;
    }

    return false;
}

File *getPreSubfile(Dir *dir, const char *name)
{
    if (dir == NULL)
        return NULL;
    File *p = dir->subfile;
    while (p != NULL)
    {
        if (strcmp(p->next->name, name) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

Dir *getPreSubdir(Dir *dir, const char *name)
{
    if (dir == NULL)
        return NULL;
    if (strcmp(name, "..") == 0)
        return dir->parent;
    if (strcmp(name, ".") == 0)
        return dir;
    Dir *p = dir->subdir;
    while (p != NULL)
    {
        if (strcmp(p->next->name, name) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

int createFile(Dir *dir, const char *name, unsigned int size, Tag tag)
{
    if (dir == nullptr || name == nullptr)
    {
        return 1;
    }
    if (checkNameVal(name))
    {
        return 2;
    }
    // check same name
    if (checkUnique(dir, name))
    {
        return 3;
    }

    File *newFile = new File();
    strcpy(newFile->name, name);
    newFile->parent = dir;
    newFile->size = size;
    newFile->tag = tag;

    if (dir->subfile == nullptr)
    {
        newFile->next = nullptr;
    }
    else
    {
        newFile->next = dir->subfile;
    }
    dir->subfile = newFile;
    // printFileInf(newFile);
    newFile = nullptr;
    delete (newFile);
    return 0;
}

int createDir(Dir *dir, const char *name)
{
    if (dir == nullptr || name == nullptr)
    {
        return 1;
    }
    if (checkNameVal(name))
    {
        return 2;
    }
    // check same name
    if (checkUnique(dir, name))
    {
        return 3;
    }

    Dir *newDir = new Dir();
    strcpy(newDir->name, name);
    newDir->parent = dir;
    newDir->subdir = nullptr;
    newDir->subfile = nullptr;
    if (dir->subdir == nullptr)
    {
        newDir->next = nullptr;
    }
    else
    {
        newDir->next = dir->subdir;
    }
    dir->subdir = newDir;
    // printDirInf(newDir);
    newDir = nullptr;
    delete (newDir);
    return 0;
}

int deleteFile(Dir *dir, const char *name)
{
    if (dir == nullptr || name == nullptr)
    {
        return 1;
    }
    File *waitForDel = getSubfile(dir, name);
    if (waitForDel == nullptr)
    {
        return 2;
    }

    if (waitForDel == dir->subfile)
    {
        dir->subfile = waitForDel->next;
    }
    else
    {
        File *preFile = getPreSubfile(dir, name);
        preFile->next = waitForDel->next;
    }
    delete (waitForDel);
    waitForDel = nullptr;
    return 0;
}

int deleteDir(Dir *dir, const char *name, bool recursive)
{
    if (dir == nullptr || name == nullptr)
    {
        return 1;
    }
    Dir *waitForDel = getSubdir(dir, name);
    if (waitForDel == nullptr)
    {
        return 2;
    }
    if (recursive == 0 && (waitForDel->subfile != nullptr || waitForDel->subdir != nullptr))
    {
        return 3;
    }

    if (waitForDel->parent->subdir == waitForDel)
    {
        waitForDel->parent->subdir = waitForDel->next;
    }
    else
    {
        Dir *preDir = getPreSubdir(dir, name);
        preDir->next = waitForDel->next;
    }

    while (waitForDel->subdir != nullptr)
    {
        if (deleteDir(waitForDel, waitForDel->subdir->name, recursive) == 3)
            return 3;
    }
    while (waitForDel->subfile != nullptr)
    {
        deleteFile(waitForDel, waitForDel->subfile->name);
    }

    delete (waitForDel);
    waitForDel = nullptr;

    return 0;
}

unsigned int getSize(const Dir *dir)
{
    unsigned int totalSize = 0;

    File *fp = dir->subfile;
    while (fp != NULL)
    {
        totalSize += fp->size;
        fp = fp->next;
    }
    Dir *dp = dir->subdir;
    while (dp != NULL)
    {
        totalSize += getSize(dp);
        dp = dp->next;
    }
    return totalSize;
}
const File **filesOfTag(const Dir *dir, Tag tag, unsigned int &length, const File **tempArray)
{
    Dir *tagDir = dir->subdir;
    File *tagFile = dir->subfile;
    while (tagFile != nullptr)
    {
        if (tagFile->tag == tag)
        {
            tempArray[length] = tagFile;
            length++;
        }
        tagFile = tagFile->next;
    }
    while (tagDir != nullptr)
    {
        filesOfTag(tagDir, tag, length, tempArray);
        tagDir = tagDir->next;
    }
    if (length < 1)
    {
        return nullptr;
    }
    return tempArray;
}

const File **filesOfTag(const Dir *dir, Tag tag, unsigned int &length)
{
    length = 0;
    const File **tagFileList = new const File *[1000];
    const File **tagFileList2 = filesOfTag(dir, tag, length, tagFileList);
    if (length < 1)
    {
       if (tagFileList != nullptr)
            delete[] tagFileList;
        tagFileList = nullptr;
        if (tagFileList2 != nullptr)
            delete[] tagFileList2;
        tagFileList2 = nullptr;
    }
     
        
    return tagFileList2;
}

int moveFile(File *tgt, Dir *dest)
{
    if (tgt == nullptr || dest == nullptr)
    {
        return 1;
    }
    if (dest == tgt->parent)
    {
        return 2;
    }
    if (getSubdir(dest, tgt->name) != nullptr || getSubfile(dest, tgt->name) != nullptr)
    {
        return 3;
    }

    createFile(dest, tgt->name, tgt->size, tgt->tag);
    deleteFile(tgt->parent, tgt->name);
    return 0;
}

File *findLastFile(const Dir *dir)
{
    File *tempFile = dir->subfile;
    while (tempFile != nullptr)
    {
        if (tempFile->next == nullptr)
        {
            return tempFile;
        }
        tempFile = tempFile->next;
    }
    return nullptr;
}

int moveDir(Dir *tgt, Dir *dest)
{
    if (tgt == nullptr || dest == nullptr)
    {
        return 1;
    }
    if (dest == tgt->parent)
    {
        return 2;
    }
    if (getSubdir(dest, tgt->name) != nullptr || getSubfile(dest, tgt->name) != nullptr)
    {
        return 3;
    }
    if (dest == tgt->subdir || dest == tgt)
    {
        return 4;
    }

    createDir(dest, tgt->name);
    while (tgt->subfile != nullptr)
    {

        moveFile(findLastFile(tgt), dest->subdir);
    }
    while (tgt->subdir != nullptr)
    {
        moveDir(tgt->subdir, dest->subdir);
        deleteDir(tgt, tgt->subdir->name, true);
    }

    deleteDir(tgt->parent, tgt->name, true);
    return 0;
}
