// C++ program to find the longest repeated
// non-overlapping substring
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>
#include <cstring>

#ifdef __APPLE__
#include <mach/mach_host.h>
#include <mach/mach_init.h>
#endif

using namespace std;
/*
 .-.                     ,.,_,.
 | |                  ,.''     \
 | |                 '          '         So that's what things would be like if I'd
 | |               /'           |         invented the fing-longer. [Sigh].
 | |             /_-            |         A man can dream though. A man can dream...
 | |           .'__      _-_    :           - Prof. Hubert J. Farnsworth
 | |          /__        _-_    :
 | |         ,_,._     ,_,._~   |___
 | |       .'-_ '.'.-.'-_ '.'._-^_  '.
 | |       |  -_ |.| |  -_ | | / |
 | |        ',_,' /  _',_,'_'  /|/
 | |         .  .|    ',. ._-^  |'
 | |          ' '.   .'  '.    '/|
 | |.,.,    ,'    '''    __'.  \/ -_
 | | | |., '_=-..--..--'^  '', : \. '.
_|     ` |      ',    .  ,   ,' \/ |  |-_
\`\       ;     / ',.. '. '. ,../  |  |  '-_
 \        |   ,'  . \'.:.''''    .''. '.    \.
  \      /  ,'    | |\       ,../   |  |      ',
   |    |   |    ,' ''.,.''''       ', ',       |
   |    |   |    |                   |  |       '\
*/

// Returns the longest repeating non-overlapping
// substring in file 'input.txt'
string longestRepeatedSubstring(const char *buffer)
{
    //buffer.str().c_str().length
    // find size of stringstream buffer
    //buffer->seekg(0, ios::end);
    //int n = buffer->tellg();
    // seek back to beginning
    //buffer->seekg(0, ios::beg);
    std::string str = buffer;
    //int n = strlen(buffer);
    int n = str.length();
    // Declare 2D vector & set all to 0
    vector< vector<int> > LCSRe(n+1, std::vector<int>(n+1, 0));

    //int LCSRe[n+1][n+1];

    // Setting all to 0
    //memset(LCSRe, 0, sizeof(LCSRe));

    string res; // To store result
    int res_length  = 0; // To store length of result

    // building table in bottom-up manner
    int i, index = 0;
    for (i=1; i<=n; i++)
    {
        for (int j=i+1; j<=n; j++)
        {
            // (j-i) > LCSRe[i-1][j-1] to remove
            // overlapping
            if (str[i-1] == str[j-1] &&
                LCSRe[i-1][j-1] < (j - i))
            {
                LCSRe[i][j] = LCSRe[i-1][j-1] + 1;

                // updating maximum length of the
                // substring and updating the finishing
                // index of the suffix
                if (LCSRe[i][j] > res_length)
                {
                    res_length = LCSRe[i][j];
                    index = max(i, index);
                }
            }
            else
                LCSRe[i][j] = 0;
        }
    }

    // If we have non-empty result, then insert all
    // characters from first character to last
    // character of string
    if (res_length > 0)
        for (i = index - res_length + 1; i <= index; i++)
            res.push_back(str[i-1]);

    return res;
}

#ifdef __APPLE__
uint64_t mac_os_x_get_total_memory() {
    struct host_basic_info hostinfo;
    mach_msg_type_number_t host_basic_info_count = HOST_BASIC_INFO_COUNT;

    int result = host_info(mach_host_self(), HOST_BASIC_INFO, (host_info_t)&hostinfo, &host_basic_info_count);
    if (result != KERN_SUCCESS) {
        return -1;
    }
    const uint64_t system_memory_bytes = hostinfo.max_mem;
    return system_memory_bytes;
}
#else
    const long system_memory_pages = sysconf(_SC_PHYS_PAGES);
    const long system_page_size = sysconf(_SC_PAGE_SIZE);
    const long available_pages = sysconf(_SC_AVPHYS_PAGES);
#endif

unsigned long long getTotalSystemMemory()
{
#ifdef __APPLE__
    return mac_os_x_get_total_memory();
#else
    return system_memory_pages * system_page_size;
#endif
}

unsigned long long getAvailableSystemMemory()
{
#ifdef __APPLE__
    return 0; // Not implemented yet...
#else
    return available_pages * system_page_size;
#endif
}


// Driver program to test the above function
int main()
{
    std::ifstream t("input.txt");
    std::filebuf* pbuf = t.rdbuf();
    // get file size using buffer's members
    std::size_t size = pbuf->pubseekoff (0,t.end,t.in);
    pbuf->pubseekpos (0,t.in);

    // allocate memory to contain file data
    char* buffer=new char[size];
    // get file data
    pbuf->sgetn (buffer,size);
    cout << "File size: " << size << endl;
    cout << "Buffer size: " << strlen(buffer) << endl;
    std::string str = buffer;
    int n_c = strlen(buffer);
    int n_cpp = str.length();
    cout << "C str size: " << n_c << endl;
    cout << "Cpp str size: " << n_cpp << endl;
    unsigned long long totalMem = getTotalSystemMemory();
    cout << "Total Memory: " << totalMem << endl;
    unsigned long long freeMem = getAvailableSystemMemory();
    cout << "Available Memory: " << freeMem << endl;
    cout << "Sizeof vector<int>: " << sizeof(vector<int>) << endl;
    cout << "Sizeof NxN vector<int>: " << n_cpp * n_cpp * sizeof(vector<int>) << endl;
    // Handle OOM condition before we impact the system
    if (n_cpp * n_cpp * sizeof(vector<int>) > freeMem) {
        cout << "ERROR: Input string is too long to process with NxN matrix algorithm!" << endl;
        cout << n_cpp << "x" << n_cpp << " vector<int> would require " << n_cpp * n_cpp * sizeof(vector<int>) << " bytes!" << endl;
        exit(EXIT_FAILURE);
    } else {
        cout << "Finding longest repeated substring..." << endl;
        cout << longestRepeatedSubstring(buffer) << endl;
    }
    return 0;
}
