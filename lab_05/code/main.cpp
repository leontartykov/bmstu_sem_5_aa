#include <iostream>
#include <queue>
#include <thread>
#include <vector>
#include <mutex>
#include <stdlib.h>
#include <unistd.h>
#include <ctime>

using namespace std;

typedef string input_t;

FILE *f;

static queue<input_t> queue1;
static queue<input_t> queue2;
static queue<input_t> queue3;

static vector<input_t> objvec;
static vector<input_t> res;

static mutex m1, m2, m3, resm;

static int n = 10;

static clock_t main_time = clock();
static clock_t mtime = clock();

class Logger {
public:
    Logger() {}
    static void print(int step, string str, int i, clock_t time = 0){
        fprintf(f,"step: %d | item: %d | time: %ld (%ld) | value: %s\n", step, i, time, time - mtime, str.c_str());
        std::cout << "" << step << " | item " << i << " | " << "time: "<< time - main_time<<" | " << str << std::endl;
        mtime += time - mtime;
    }
};
Logger log;

// сдвиг на следующую букву алфавита
string caesar(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == 'z') s[i] = 'a';
        else if (s[i] == 'Z') s[i] = 'A';
        else s[i]++;
    }
    return s;
}


string upper_lower(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (islower(s[i])) s[i] = toupper(s[i]);
        else s[i] = tolower(s[i]);
    }
    return s;
}

string reverse(string s) {
    int shift = s.length() / 2;
    for (int i = 0; i < s.length() / 2; i++) {
        char st = s[i];
        s[i] = s[i + shift];
        s[i + shift] = st;
    }
    return s;
}


void conveyor1()
{
    int num = 0;
    while (1)
    {
        if (num == n)
            break;
        m1.lock();
        if (queue1.empty())
        {
            m1.unlock();
            continue;
        }
        input_t myObj = queue1.front();
        queue1.pop();
        m1.unlock();
        input_t newObj = caesar(myObj);
        m2.lock();
        queue2.push(newObj);
        sleep(1);
        clock_t time = clock();
        log.print(1, newObj, num, time);
        m2.unlock();
        num++;
    }
}

void conveyor2()
{
    int num = 0;
    while (1)
    {
        if (num == n)
            break;
        m2.lock();
        if (queue2.empty())
        {
            m2.unlock();
            continue;
        }
        input_t myObj = queue2.front();
        queue2.pop();
        m2.unlock();
        input_t newObj = upper_lower(myObj);
        m3.lock();
        queue3.push(newObj);
        sleep(3);
        clock_t time = clock();
        log.print(2, newObj, num, time);
        m3.unlock();
        num++;
    }
}

void conveyor3()
{
    int num = 0;
    while (1)
    {
        if (num == n)
            break;
        m3.lock();
        if (queue3.empty())
        {
            m3.unlock();
            continue;
        }
        input_t myObj = queue3.front();
        queue3.pop();
        m3.unlock();
        input_t newObj = reverse(myObj);
        resm.lock();
        res.push_back(newObj);
        sleep(1.5);
        clock_t time = clock();
        log.print(3, newObj, num, time);
        resm.unlock();
        num++;
    }
}

// Диапазон чисел: [min, max]
int get_random_number(int min, int max)
{
    // Получить случайное число - формула
    int num = min + rand() % (max - min + 1);
    return num;
}

string generate() {
    string s = "";
    int reg = 0;
    int code = 0;
    int min_low = 97;
    int max_low = 122;
    int min_upper = 65;
    int max_upper = 90;
    for (int i = 0; i < 50; i++) {
        reg = get_random_number(0, 1);
        if (reg) code = get_random_number(min_upper, max_upper);
        else code = get_random_number(min_low, max_low);
        s.push_back(code);
    }
    return s;
}

int main()
{

    f = fopen("log.txt", "w");
    n = 5;
    objvec.resize(n);

    thread t1(conveyor1);
    thread t2(conveyor2);
    thread t3(conveyor3);
    main_time = clock();

    for (int i = 0; i < n; i++)
    {
        string s = generate();
        objvec[i] = (s);
    }

    for (int i = 0; i < n; i++)
    {
        clock_t tm = clock();
        log.print(0, objvec[i], i, tm);
        m1.lock();

        queue1.push(objvec[i]);
        m1.unlock();
        sleep(2);
    }

    t1.join();
    t2.join();
    t3.join();
    fclose(f);
    printf("That's all folks!");
    return 0;
}

