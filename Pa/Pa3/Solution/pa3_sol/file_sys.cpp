/** 
 * This file contains the file system functions that you need to implement.
 * You can define helper functions in this file.
*/

#include <iostream>
#include "file_sys.h"
#include "utils.h"
using namespace std;

/**
 * Check if a character is legal 
*/
bool isLegalChar(char c)
{
    const char charset[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890_-.";
    for (int i = 0; i < strlen(charset); ++i)
        if (c == charset[i])
            return true;
    return false;
}

/**
 * Check if a string is legal 
*/
bool isLegalChar(const char *s)
{
    if (s == NULL)
        return false;
    for (int i = 0; i < strlen(s); ++i)
        if (!isLegalChar(s[i]))
            return false;
    return true;
}

/**
 * Check if a name is legal
 * 1. It's non-empty 
 * 2. It only contains legal chracters
 * 3. It's not a keyword (. and ..)
*/
bool isLegalName(const char *name)
{
    if (name == NULL)
        return false;
    bool non_empty = strlen(name) > 0;
    bool legal_charset = isLegalChar(name);
    bool non_keyword = strcmp(name, ".") != 0 && strcmp(name, "..") != 0;
    bool legal_start = non_empty && name[0] != '-';
    return non_empty && non_keyword && legal_charset && legal_start;
}

/**
 * Check if a name is already taken under a directory
 * Go through all sub-directories and then all sub-files
*/
bool nameConflict(const Dir *dir, const char *name)
{
    if (dir == NULL || name == NULL)
        return false;
    const Dir *dp = dir->subdir;
    while (dp != NULL)
    {
        if (strcmp(dp->name, name) == 0)
            return true;
        dp = dp->next;
    }
    const File *fp = dir->subfile;
    while (fp != NULL)
    {
        if (strcmp(fp->name, name) == 0)
            return true;
        fp = fp->next;
    }
    return false;
}

/**
 * File constructor
*/
File *createFile(const char *name, unsigned int size, Tag tag = OTHER, Dir *parent = NULL, File *next = NULL)
{
    File *file = new File();
    strcpy(file->name, name);
    file->size = size;
    file->tag = tag;
    file->parent = parent;
    file->next = next;
    return file;
}

int createFile(Dir *dir, const char *name, unsigned int size, Tag tag)
{
    if (dir == NULL || name == NULL)
        return 1;
    if (!isLegalName(name))
        return 2;
    if (nameConflict(dir, name))
        return 3;

    dir->subfile = createFile(name, size, tag, dir, dir->subfile);
    return 0;
}

/**
 * Directory constructor
*/
Dir *createDir(const char *name, Dir *parent = NULL, Dir *subdir = NULL, File *subfile = NULL, Dir *next = NULL)
{
    Dir *dir = new Dir();
    strcpy(dir->name, name);
    dir->parent = parent;
    dir->subdir = subdir;
    dir->subfile = subfile;
    dir->next = next;
    return dir;
}

int createDir(Dir *dir, const char *name)
{
    if (dir == NULL || name == NULL)
        return 1;
    if (!isLegalName(name))
        return 2;
    if (nameConflict(dir, name))
        return 3;

    dir->subdir = createDir(name, dir, NULL, NULL, dir->subdir);
    return 0;
}

/**
 * Delete a single file, return the rest of the liked list
*/
File *deleteFile(File *file)
{
    if (file == NULL)
        return NULL;
    File *rest = file->next;
    delete file;
    return rest;
}

/**
 * Delete a file and it's siblings in the rest of the linked list
 * Return NULL for sure if the linked list is in fine
*/
File *deleteFiles(File *file)
{
    if (file == NULL)
        return NULL;
    File *rest = deleteFile(file);
    return deleteFiles(rest);
}

int deleteFile(Dir *dir, const char *name)
{
    if (dir == NULL || name == NULL)
        return 1;
    if (dir->subfile == NULL)
        return 2;
    if (strcmp(dir->subfile->name, name) == 0)
    {
        dir->subfile = deleteFile(dir->subfile);
        return 0;
    }
    File *prev = dir->subfile, *curr = prev->next;
    while (curr != NULL && strcmp(curr->name, name) != 0)
    {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL)
        return 2;
    prev->next = deleteFile(curr);
    return 0;
}

Dir *deleteDirs(Dir *);
/**
 * Delete a directory recursively
*/
Dir *deleteDir(Dir *dir)
{
    if (dir == NULL)
        return NULL;
    dir->subfile = deleteFiles(dir->subfile);
    dir->subdir = deleteDirs(dir->subdir);
    Dir *rest = dir->next;
    delete dir;
    return rest;
}

/**
 * Delete a directory and it's siblings in the rest of the linked list
 * Return NULL for sure if the linked list is in fine
*/
Dir *deleteDirs(Dir *dir)
{
    if (dir == NULL)
        return NULL;
    Dir *rest = deleteDir(dir);
    return deleteDirs(rest);
}

int deleteDir(Dir *dir, const char *name, bool recursive)
{
    if (dir == NULL || name == NULL)
        return 1;
    if (dir->subdir == NULL)
        return 2;
    if (strcmp(dir->subdir->name, name) == 0)
    {
        if (!recursive && (dir->subdir->subfile != NULL || dir->subdir->subdir != NULL))
            return 3;
        dir->subdir = deleteDir(dir->subdir);
        return 0;
    }
    Dir *prev = dir->subdir, *curr = prev->next;
    while (curr != NULL && strcmp(curr->name, name) != 0)
    {
        prev = curr;
        curr = curr->next;
    }
    if (curr == NULL)
        return 2;
    if (!recursive && (curr->subfile != NULL || curr->subdir != NULL))
        return 3;
    prev->next = deleteDir(curr);
    return 0;
}

/**
 * Get the size of a directory and it's siblings in the linked list
*/
unsigned int getSubSize(const Dir *dir)
{
    if (dir == NULL)
        return 0;
    return getSize(dir) + getSubSize(dir->next);
}

unsigned int getSize(const Dir *dir)
{
    if (dir == NULL)
        return 0;
    unsigned int size = 0;
    const File *p = dir->subfile;
    while (p != NULL)
    {
        size += p->size;
        p = p->next;
    }
    return size + getSubSize(dir->subdir);
}

/**
 * Count how many files of a certain tag
*/
int filesOfTag(const Dir *dir, Tag tag)
{   
    int count = 0;
    if (dir == NULL)
        return count;
    const File *fp = dir->subfile;
    while (fp != NULL)
    {
        if (fp->tag == tag)
            count++;
        fp = fp->next;
    }
    const Dir *dp = dir->subdir;
    while (dp != NULL)
    {
        count += filesOfTag(dp, tag);
        dp = dp->next;
    }
    return count;
}

/**
 * Add file pointers to an array starting from a given position
*/
void filesOfTag(const Dir *dir, Tag tag, const File **arr, int &idx)
{
    if (dir == NULL || arr == NULL)
        return;
    const File *fp = dir->subfile;
    while (fp != NULL)
    {
        if (fp->tag == tag)
        {
            arr[idx] = fp;
            idx++;
        }
        fp = fp->next;
    }
    const Dir *dp = dir->subdir;
    while (dp != NULL)
    {
        filesOfTag(dp, tag, arr, idx);
        dp = dp->next;
    }
}

const File **filesOfTag(const Dir *dir, Tag tag, unsigned int &length)
{
    length = filesOfTag(dir, tag);
    if (length == 0)
        return NULL;
    const File **arr = new const File *[length];
    int idx = 0;
    filesOfTag(dir, tag, arr, idx);
    return arr;
}

int moveFile(File *tgt, Dir *dest)
{
    if (tgt == NULL || dest == NULL)
        return 1;
    if (tgt->parent == dest)
        return 2;
    if (nameConflict(dest, tgt->name))
        return 3;
    Dir *src = tgt->parent;
    if (src->subfile == tgt)
        src->subfile = tgt->next;
    else
    {
        File *p = src->subfile;
        while (p->next != NULL && p->next != tgt)
            p = p->next;
        p->next = tgt->next;
    }
    tgt->next = dest->subfile;
    dest->subfile = tgt;
    tgt->parent = dest;
    return 0;
}

/**
 * Check if d1 is an ancestor of d2
*/
bool isAncestor(const Dir *d1, const Dir *d2)
{
    if (d1 == NULL || d2 == NULL)
        return false;
    while (d2->parent != d2)
    {
        if (d2->parent == d1)
            return true;
        d2 = d2->parent;
    }
    return false;
}

int moveDir(Dir *tgt, Dir *dest)
{
    if (tgt == NULL || dest == NULL)
        return 1;
    if (tgt->parent == dest)
        return 2;
    if (nameConflict(dest, tgt->name))
        return 3;
    if (isAncestor(tgt, dest) || tgt == dest)
        return 4;
    Dir *src = tgt->parent;
    if (src->subdir == tgt)
        src->subdir = tgt->next;
    else
    {
        Dir *p = src->subdir;
        while (p->next != NULL && p->next != tgt)
            p = p->next;
        p->next = tgt->next;
    }
    tgt->next = dest->subdir;
    dest->subdir = tgt;
    tgt->parent = dest;
    return 0;
}
