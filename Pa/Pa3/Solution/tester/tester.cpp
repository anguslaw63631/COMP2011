#include <iostream>
#include "file_sys.h"
#include "utils.h"
#include "cli.h"
using namespace std;

File *std_file_obj(const char *name, unsigned int size, Tag tag = OTHER, Dir *parent = NULL, File *next = NULL)
{
    File *file = new File();
    strcpy(file->name, name);
    file->size = size;
    file->tag = tag;
    file->parent = parent;
    file->next = next;
    return file;
}

Dir *std_dir_obj(const char *name, Dir *parent = NULL, Dir *subdir = NULL, File *subfile = NULL, Dir *next = NULL)
{
    Dir *dir = new Dir();
    strcpy(dir->name, name);
    dir->parent = parent;
    dir->subdir = subdir;
    dir->subfile = subfile;
    dir->next = next;
    return dir;
}

void std_sortArr(const File **arr, unsigned int length)
{
    if (length <= 1)
        return;
    const File *temp = NULL;
    for (int i = 1; i < length; ++i)
    {
        for (int j = i - 1; j >= 0; --j)
        {
            if (arr[j] != NULL && (arr[j + 1] == NULL || string(arr[j + 1]->name) < string(arr[j]->name)))
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

string std_arr2str(const File **arr, unsigned int length)
{
    string result = "";
    if (length == 0 && arr == NULL)
    {
        result += "NULL";
        return result;
    }
    if (length == 0 && arr != NULL)
    {
        result += "arr is not NULL but length is zero";
        return result;
    }
    std_sortArr(arr, length);
    for (int i = 0; i < length; ++i)
    {
        if (arr[i] == NULL)
            result += "NULL\n";
        else
            result += "name,\"" + string(arr[i]->name) + "\"\n";
    }
    size_t end = result.find_last_not_of(WHITESPACE);
    result = (end == std::string::npos) ? "" : result.substr(0, end + 1);
    return result;
}

int main()
{
    int testCase = 1;
    const string line = "============================================";
    const string rv = "Returned: ";
    const string fs = "File system: \n";
    const string len = "Length: ";

    cout << "Please enter the test case number: ";
    cin >> testCase;
    cout << endl;

    bool leak = false;
    if (testCase > 93)
    {
        testCase -= 93;
        leak = true;
    }

    if (testCase == 1)
    {
        string testname = "createFile_a.txt_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(root, "a.txt", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 2)
    {
        string testname = "createFile_a.txt_b.txt_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(root, "a.txt", 0, DOC);
        code = createFile(root, "b.txt", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 3)
    {
        string testname = "createFile_dirIsNull_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(NULL, "a.txt", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 4)
    {
        string testname = "createFile_dirIsNull_nameIsNull_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(NULL, NULL, 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 5)
    {
        string testname = "createFile_dirIsNull_illegalName_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(NULL, "..", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 6)
    {
        string testname = "createFile_dirIsNull_nameConflict_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(root, "a.txt", 0, OTHER);
        code = createFile(NULL, "a.txt", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 7)
    {
        string testname = "createFile_emptyName_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(root, "", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 8)
    {
        string testname = "createFile_illegalChar_whitespace_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(root, "  ", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 9)
    {
        string testname = "createFile_illegalChar_bracket_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(root, "abc[", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 10)
    {
        string testname = "createFile_illegalChar_lessThan_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(root, "<<", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 11)
    {
        string testname = "createFile_keywordName_dot_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(root, ".", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 12)
    {
        string testname = "createFile_keywordName_dotdot_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(root, "..", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 13)
    {
        string testname = "createFile_..._return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(root, "...", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 14)
    {
        string testname = "createFile__03_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(root, "_03", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 15)
    {
        string testname = "createFile_conflict_a.txt_return3_id0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(root, "a.txt", 0, OTHER);
        code = createFile(root, "a.txt", 10, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 16)
    {
        string testname = "createFile_conflict_abc_return3_id0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, NULL);
        int code = createFile(root, "abc", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 17)
    {
        string testname = "createFile_conflict_a.txt_return3_id1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createFile(root, "a.txt", 0, OTHER);
        code = createFile(root, "b.txt", 10, OTHER);
        code = createFile(root, "a.txt", 10, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 18)
    {
        string testname = "createFile_conflict_abc_return3_id1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, NULL);
        root->subdir = std_dir_obj("123", root, NULL, NULL, root->subdir);
        int code = createFile(root, "abc", 0, OTHER);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 19)
    {
        string testname = "createDir_download_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createDir(root, "download");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 20)
    {
        string testname = "createDir_lecture.video_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createDir(root, "download");
        code = createDir(root, "lecture.video");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 21)
    {
        string testname = "createDir_dirIsNull_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createDir(NULL, "download");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 22)
    {
        string testname = "createDir_dirIsNull_nameIsNull_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createDir(NULL, NULL);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 23)
    {
        string testname = "createDir_dirIsNull_illegalName_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createDir(NULL, ">>");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 24)
    {
        string testname = "createDir_illegalChar_biggerThan_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createDir(root, ">>");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 25)
    {
        string testname = "createDir_illegalChar_question_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createDir(root, "1_?_2");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 26)
    {
        string testname = "createDir_conflict_1_-_2_return3_id0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createDir(root, "1_-_2");
        code = createDir(root, "1_-_2");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 27)
    {
        string testname = "createDir_conflict_1_-_2_return3_id1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        int code = createDir(root, "1_-_2");
        code = createDir(root, "abc");
        code = createDir(root, "1_-_2");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 28)
    {
        string testname = "createDir_conflict_abc_return3";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subfile = std_file_obj("abc", 0, DOC, root, root->subfile);
        root->subfile = std_file_obj("123", 0, DOC, root, root->subfile);
        int code = createDir(root, "abc");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 29)
    {
        string testname = "deleteFile_abc_return0_id0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subfile = std_file_obj("abc", 0, DOC, root, root->subfile);
        int code = deleteFile(root, "abc");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 30)
    {
        string testname = "deleteFile_abc_return0_id1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subfile = std_file_obj("abc", 0, DOC, root, root->subfile);
        root->subfile = std_file_obj("123", 0, DOC, root, root->subfile);
        int code = deleteFile(root, "abc");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 31)
    {
        string testname = "deleteFile_123_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subfile = std_file_obj("abc", 0, DOC, root, root->subfile);
        root->subfile = std_file_obj("123", 0, DOC, root, root->subfile);
        root->subfile = std_file_obj("...", 0, DOC, root, root->subfile);
        int code = deleteFile(root, "123");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 32)
    {
        string testname = "deleteFile_dirIsNull_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subfile = std_file_obj("abc", 0, DOC, root, root->subfile);
        root->subfile = std_file_obj("123", 0, DOC, root, root->subfile);
        int code = deleteFile(NULL, "123");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 33)
    {
        string testname = "deleteFile_dirIsNull_nameIsNull_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subfile = std_file_obj("abc", 0, DOC, root, root->subfile);
        root->subfile = std_file_obj("123", 0, DOC, root, root->subfile);
        int code = deleteFile(NULL, NULL);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 34)
    {
        string testname = "deleteFile_dirIsNull_noSuchName_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subfile = std_file_obj("abc", 0, DOC, root, root->subfile);
        root->subfile = std_file_obj("123", 0, DOC, root, root->subfile);
        int code = deleteFile(NULL, "...");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 35)
    {
        string testname = "deleteFile_noSuchName_..._return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subfile = std_file_obj("abc", 0, DOC, root, root->subfile);
        root->subfile = std_file_obj("123", 0, DOC, root, root->subfile);
        int code = deleteFile(root, "...");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 36)
    {
        string testname = "deleteFile_noSuchName_emptyName_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subfile = std_file_obj("abc", 0, DOC, root, root->subfile);
        root->subfile = std_file_obj("123", 0, DOC, root, root->subfile);
        int code = deleteFile(root, "");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 37)
    {
        string testname = "deleteDir_abc_return0_id0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        int code = deleteDir(root, "abc");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 38)
    {
        string testname = "deleteDir_abc_return0_id1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        root->subdir = std_dir_obj("123", root, NULL, NULL, root->subdir);
        int code = deleteDir(root, "abc");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 39)
    {
        string testname = "deleteDir_123_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        root->subdir = std_dir_obj("123", root, NULL, NULL, root->subdir);
        root->subdir = std_dir_obj("...", root, NULL, NULL, root->subdir);
        int code = deleteDir(root, "123");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 40)
    {
        string testname = "deleteDir_abc_withSubfile_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        root->subdir->subfile = std_file_obj("123", 0, OTHER, root->subdir, NULL);
        int code = deleteDir(root, "abc", true);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 41)
    {
        string testname = "deleteDir_abc_withSubdir_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        root->subdir->subdir = std_dir_obj("123", root->subdir, NULL, NULL, NULL);
        int code = deleteDir(root, "abc", true);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 42)
    {
        string testname = "deleteDir_comp2011_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        int code = deleteDir(root, "comp2011", true);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 43)
    {
        string testname = "deleteDir_dirIsNull_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        int code = deleteDir(NULL, "abc");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 44)
    {
        string testname = "deleteDir_dirIsNull_nameIsNull_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        int code = deleteDir(NULL, NULL);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 45)
    {
        string testname = "deleteDir_dirIsNull_noSuchName_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        int code = deleteDir(NULL, "123");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 46)
    {
        string testname = "deleteDir_dirIsNull_nonEmpty_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        root->subdir->subdir = std_dir_obj("123", root->subdir, NULL, NULL, NULL);
        int code = deleteDir(NULL, "abc");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 47)
    {
        string testname = "deleteDir_noSuchName_123_return2_id0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        root->subdir->subdir = std_dir_obj("123", root->subdir, NULL, NULL, NULL);
        int code = deleteDir(root, "123");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 48)
    {
        string testname = "deleteDir_noSuchName_123_return2_id1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subfile = std_file_obj("123", 0, OTHER, root, root->subfile);
        int code = deleteDir(root, "123");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 49)
    {
        string testname = "deleteDir_nonEmpty_abc_return3_id0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        root->subdir->subdir = std_dir_obj("123", root->subdir, NULL, NULL, NULL);
        int code = deleteDir(root, "abc");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 50)
    {
        string testname = "deleteDir_nonEmpty_abc_return3_id1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        root->subdir->subfile = std_file_obj("123", 0, OTHER, root->subdir, NULL);
        int code = deleteDir(root, "abc");
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 51)
    {
        string testname = "getSize_abc_return0_id0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        root->subdir->subfile = std_file_obj("123", 0, OTHER, root->subdir, NULL);
        unsigned int size = getSize(root->subdir);
        if (!leak)
        {
            cout << rv << size << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 52)
    {
        string testname = "getSize_abc_return0_id1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        root->subdir = std_dir_obj("abc", root, NULL, NULL, root->subdir);
        root->subdir->subfile = std_file_obj("123", 0, OTHER, root->subdir, NULL);
        root->subdir->subdir = std_dir_obj("xyz", root->subdir, NULL, NULL, NULL);
        unsigned int size = getSize(root->subdir);
        if (!leak)
        {
            cout << rv << size << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 53)
    {
        string testname = "getSize_download_return777";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        unsigned int size = getSize(root->subdir);
        if (!leak)
        {
            cout << rv << size << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 54)
    {
        string testname = "getSize_comp2011_return65";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        unsigned int size = getSize(root->subdir->next);
        if (!leak)
        {
            cout << rv << size << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 55)
    {
        string testname = "getSize_root_return844";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        unsigned int size = getSize(root);
        if (!leak)
        {
            cout << rv << size << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 56)
    {
        string testname = "getSize_root_return1843";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subfile = std_file_obj("hello.txt", 999, OTHER, root, root->subfile);
        unsigned int size = getSize(root);
        if (!leak)
        {
            cout << rv << size << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 57)
    {
        string testname = "moveFile_hello.txt_download_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subfile = std_file_obj("hello.txt", 999, OTHER, root, root->subfile);
        int code = moveFile(root->subfile, root->subdir);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 58)
    {
        string testname = "moveFile_VSCODE_/_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subfile = std_file_obj("hello.txt", 999, OTHER, root, root->subfile);
        int code = moveFile(root->subdir->subfile, root);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 59)
    {
        string testname = "moveFile_lecture_3.mp4_/_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subfile = std_file_obj("hello.txt", 999, OTHER, root, root->subfile);
        int code = moveFile(root->subdir->subfile->next, root);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 60)
    {
        string testname = "moveFile_tgtIsNull_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subfile = std_file_obj("hello.txt", 999, OTHER, root, root->subfile);
        int code = moveFile(NULL, root);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 61)
    {
        string testname = "moveFile_destIsNull_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subfile = std_file_obj("hello.txt", 999, OTHER, root, root->subfile);
        int code = moveFile(root->subfile, NULL);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 62)
    {
        string testname = "moveFile_meaningless_hello.txt_/_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subfile = std_file_obj("hello.txt", 999, OTHER, root, root->subfile);
        int code = moveFile(root->subfile, root);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 63)
    {
        string testname = "moveFile_meaningless_lecture_3.mp4_download_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subfile = std_file_obj("hello.txt", 999, OTHER, root, root->subfile);
        int code = moveFile(root->subdir->subfile->next, root->subdir);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 64)
    {
        string testname = "moveFile_conflict_VSCODE_/_return3";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subfile = std_file_obj(root->subdir->subfile->name, 999, OTHER, root, root->subfile);
        int code = moveFile(root->subdir->subfile, root);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 65)
    {
        string testname = "moveFile_conflict_memo.txt_download_return3";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subdir->subfile = std_file_obj(root->subfile->name, 999, OTHER, root->subdir, root->subdir->subfile);
        int code = moveFile(root->subfile, root->subdir);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 66)
    {
        string testname = "moveDir_PA3_/_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        int code = moveDir(root->subdir->next->subdir, root);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 67)
    {
        string testname = "moveDir_download_comp2011_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        int code = moveDir(root->subdir, root->subdir->next);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 68)
    {
        string testname = "moveDir_comp2011_download_return0";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        int code = moveDir(root->subdir->next, root->subdir);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 69)
    {
        string testname = "moveDir_tgtIsNull_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        int code = moveDir(NULL, root);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 70)
    {
        string testname = "moveDir_destIsNull_return1";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        int code = moveDir(root, NULL);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 71)
    {
        string testname = "moveDir_meaningless_download_/_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        int code = moveDir(root->subdir, root);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 72)
    {
        string testname = "moveDir_meanlingless_PA3_comp2011_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        int code = moveDir(root->subdir->next->subdir, root->subdir->next);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 73)
    {
        string testname = "moveDir_meanlingless_comp2011_/_return2";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        int code = moveDir(root->subdir->next, root);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 74)
    {
        string testname = "moveDir_conflict_PA3_/_return3";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subdir = std_dir_obj(root->subdir->next->subdir->name, root, NULL, NULL, root->subdir);
        int code = moveDir(root->subdir->next->next->subdir, root);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 75)
    {
        string testname = "moveDir_conflict_comp2011_download_return3";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subdir->subdir = std_dir_obj(root->subdir->next->name, root->subdir, NULL, NULL, root->subdir->subdir);
        int code = moveDir(root->subdir->next, root->subdir);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 76)
    {
        string testname = "moveDir_/_toDescendant_download_return4";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        int code = moveDir(root, root->subdir);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 77)
    {
        string testname = "moveDir_comp2011_toDescendant_PA3_return4";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        int code = moveDir(root->subdir->next, root->subdir->next->subdir);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 78)
    {
        string testname = "moveDir_/_toDescendant_PA3_return4";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        int code = moveDir(root, root->subdir->next->subdir);
        if (!leak)
        {
            cout << rv << code << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 79)
    {
        string testname = "filesOfTag_/_IMAGE_return_null";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        unsigned int length = 100;
        const File **arr = filesOfTag(root, IMAGE, length);
        if (!leak)
        {
            cout << len << length << endl;
            cout << rv << std_arr2str(arr, length) << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            delete[] arr;
            root = delSystem(root);
        }
    }

    else if (testCase == 80)
    {
        string testname = "filesOfTag_/_OTHER_return_null";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        unsigned int length = 100;
        const File **arr = filesOfTag(root->subdir, OTHER, length);
        if (!leak)
        {
            cout << len << length << endl;
            cout << rv << std_arr2str(arr, length) << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            delete[] arr;
            root = delSystem(root);
        }
    }

    else if (testCase == 81)
    {
        string testname = "filesOfTag_/_DOC";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subfile = std_file_obj("abc", 0, DOC, root, root->subfile);
        unsigned int length = 100;
        const File **arr = filesOfTag(root, DOC, length);
        if (!leak)
        {
            cout << len << length << endl;
            cout << rv << endl
                 << std_arr2str(arr, length) << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            delete[] arr;
            root = delSystem(root);
        }
    }

    else if (testCase == 82)
    {
        string testname = "filesOfTag_download_VIDEO";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        unsigned int length = 100;
        const File **arr = filesOfTag(root->subdir, VIDEO, length);
        if (!leak)
        {
            cout << len << length << endl;
            cout << rv << endl
                 << std_arr2str(arr, length) << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            delete[] arr;
            root = delSystem(root);
        }
    }

    else if (testCase == 83)
    {
        string testname = "filesOfTag_comp2011_DOC";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        unsigned int length = 100;
        const File **arr = filesOfTag(root->subdir->next, DOC, length);
        if (!leak)
        {
            cout << len << length << endl;
            cout << rv << endl
                 << std_arr2str(arr, length) << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            delete[] arr;
            root = delSystem(root);
        }
    }

    else if (testCase == 84)
    {
        string testname = "filesOfTag_/_VIDEO";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        root->subdir->next->subfile = std_file_obj("abc", 0, VIDEO, root->subdir->next, root->subdir->next->subfile);
        unsigned int length = 100;
        const File **arr = filesOfTag(root, VIDEO, length);
        if (!leak)
        {
            cout << len << length << endl;
            cout << rv << endl
                 << std_arr2str(arr, length) << endl;
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            delete[] arr;
            root = delSystem(root);
        }
    }

    else if (testCase == 85)
    {
        string testname = "mkdir_abc";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        bool exit = false;
        char rest[] = "mkdir abc";
        execute(root, rest, exit);
        if (!leak)
        {
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 86)
    {
        string testname = "mkdir";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = emptySystem();
        bool exit = false;
        char rest[] = "mkdir";
        execute(root, rest, exit);
        if (!leak)
        {
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 87)
    {
        string testname = "rm_comp2011";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        bool exit = false;
        char rest[] = "rm comp2011";
        execute(root, rest, exit);
        if (!leak)
        {
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 88)
    {
        string testname = "rm_-r_comp2011";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        bool exit = false;
        char rest[] = "rm -r comp2011";
        execute(root, rest, exit);
        if (!leak)
        {
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 89)
    {
        string testname = "rm_VSCODE";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        bool exit = false;
        char rest[] = "rm VSCODE";
        execute(root->subdir, rest, exit);
        if (!leak)
        {
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 90)
    {
        string testname = "rm_abc";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        bool exit = false;
        char rest[] = "rm abc";
        execute(root, rest, exit);
        if (!leak)
        {
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 91)
    {
        string testname = "mv_download_comp2011";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        bool exit = false;
        char rest[] = "mv download comp2011";
        execute(root, rest, exit);
        if (!leak)
        {
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 92)
    {
        string testname = "mv_comp2011_download";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        bool exit = false;
        char rest[] = "mv comp2011 download";
        execute(root, rest, exit);
        if (!leak)
        {
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    else if (testCase == 93)
    {
        string testname = "mv_memo.txt_download";
        cout << "Name: " << testname << endl
             << line << endl;

        Dir *root = sampleSystem();
        bool exit = false;
        char rest[] = "mv memo.txt download";
        execute(root, rest, exit);
        if (!leak)
        {
            cout << fs << sys2str(root) << endl;
        }
        else
        {
            root = delSystem(root);
        }
    }

    return 0;
}