#include "hw2_output.h"
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <pthread.h>

using namespace std;

int num_of_rows, num_of_colums;
vector<vector<int>> area;
vector<vector<int>> locks_on_area;
vector<vector<int>> locks_on_area_for_sneaky_smokers;
int num_of_privates = 0;
int num_of_sneaky_smokers = 0;

typedef struct proper_private{
    int gid;
    int si;
    int sj;
    int tg;
    int ng;
    vector<pair<int, int>> coordinates; 

} proper_private;

typedef struct sneaky_smoker{
    int sid;
    int ts;
    int ns;
    vector<pair<int, int>> coordinates;
    vector<int> cigarettes_num;

} sneaky_smoker;

vector<proper_private> privates;
vector<sneaky_smoker> sneaky_smokers;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t order_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t order_mutex_for_sneaky = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condition = PTHREAD_COND_INITIALIZER;
pthread_cond_t continue_condition = PTHREAD_COND_INITIALIZER;
pthread_cond_t order_condition = PTHREAD_COND_INITIALIZER;
pthread_cond_t order_condition_for_sneaky = PTHREAD_COND_INITIALIZER;

int num_of_orders = 0;
vector<pair<long, string>> orders;
enum order{NOTHING ,BREAK, CONTINUE, STOP};
enum order order_flag = NOTHING;


// take the inputs
void input_taker(){
    cin >> num_of_rows;
    cin >> num_of_colums;

    // taking cigbutt counts in cells and filling the area
    for (int i = 0; i < num_of_rows; i++){
        vector<int> row;
        for (int j = 0; j < num_of_colums; j++){
            int cigbutt_num = 0;
            cin >> cigbutt_num;
            row.push_back(cigbutt_num);
        }
        area.push_back(row);
        row.clear();
    }

    // taking information about proper privates and filling the privates vector
    cin >> num_of_privates;
    for (int i = 0; i < num_of_privates; i++){
        proper_private pp;
        cin >> pp.gid;
        cin >> pp.si;
        cin >> pp.sj;
        cin >> pp.tg;
        cin >> pp.ng;
        for (int j = 0; j < pp.ng; j++){
            pair<int, int> cord;
            cin >> cord.first;
            cin >> cord.second;
            pp.coordinates.push_back(cord);
        }
        privates.push_back(pp);
    }

    // control input availability and taking information about orders
    if (cin.peek() != EOF){
        cin >> num_of_orders;
        for (int i = 0; i < num_of_orders; i++){
            pair<int, string> ord;
            cin >> ord.first;
            cin >> ord.second;
            orders.push_back(ord);
        }
    }

    // taking information about sneaky smokers and filling the sneaky_smokers vector
    if (cin.peek() != EOF){
        cin >> num_of_sneaky_smokers;
        for (int i = 0; i < num_of_sneaky_smokers; i++){
            sneaky_smoker ss;
            cin >> ss.sid;
            cin >> ss.ts;
            cin >> ss.ns;
            for (int j = 0; j < ss.ns; j++){
                pair<int, int> cord;
                int num_of_cig;
                cin >> cord.first;
                cin >> cord.second;
                cin >> num_of_cig;
                ss.coordinates.push_back(cord);
                ss.cigarettes_num.push_back(num_of_cig);
            }
            sneaky_smokers.push_back(ss);
        }
        
    }
}

// initialize the locks on the area to "0" (unlock) at the begining
void initialize_the_locks(){
    for (int i = 0; i < num_of_rows; i++){
        vector<int> row(num_of_colums, 0);
        locks_on_area.push_back(row);
        locks_on_area_for_sneaky_smokers.push_back(row);
    }
}

// check the small area on the whole area, is it lock or not ?
bool check_the_area_locks(int row_cord, int column_cord, int si, int sj){
    for (int i = row_cord; i <  row_cord + si; i++){
        for (int j = column_cord; j < column_cord + sj; j++){
            if (locks_on_area[i][j] != 0){
                return false;
            }
        }
    }
    return true;
}

// check the small area on the whole area, is it lock or not ?
bool check_the_area_locks2(int row_cord, int column_cord, int si, int sj){
    for (int i = row_cord; i <  row_cord + si; i++){
        for (int j = column_cord; j < column_cord + sj; j++){
            if (locks_on_area[i][j] == 1){
                return false;
            }
        }
    }
    return true;
}

// check the small area on the whole area, is it lock or not for smokers ?
bool check_the_area_locks_for_sneaky_smokers(int row_cord, int column_cord){
    return locks_on_area_for_sneaky_smokers[row_cord][column_cord] == 0;
}

// lock the small area on whole area
void lock_the_area(int row_cord, int column_cord, int si, int sj){
    for (int i = row_cord; i < row_cord + si; i++){
        for (int j = column_cord; j < column_cord+ sj; j++){
            locks_on_area[i][j] = 1;
        }
    }
}

// lock the small area on whole area
void lock_the_area2(int row_cord, int column_cord, int si, int sj){
    for (int i = row_cord; i < row_cord + si; i++){
        for (int j = column_cord; j < column_cord+ sj; j++){
            locks_on_area[i][j] = 2;
        }
    }
}

// unlock the small area on whole area
void unlock_the_area(int row_cord, int column_cord, int si, int sj){
    for (int i = row_cord; i < row_cord + si; i++){
        for (int j = column_cord; j < column_cord + sj; j++){
            locks_on_area[i][j] = 0;
        }
    }
}

// lock the small area on whole area for smokers
void lock_the_area_for_sneaky_smokers(int row_cord, int column_cord){
    locks_on_area_for_sneaky_smokers[row_cord][column_cord] = 1;
}

// unlock the small area on whole area for smokers
void unlock_the_area_for_sneaky_smokers(int row_cord, int column_cord){
    locks_on_area_for_sneaky_smokers[row_cord][column_cord] = 0;
}

// gather cigbutts one by one on an area and send notification through hw2_notify
void gather_cigbutts(int row_cord, int column_cord, int si, int sj, int tg, int gid){
    
    int second = tg / 1000;
    int milisecond = tg % 1000;

    struct timeval now;
    struct timespec tm;
    
    for (int i = row_cord; i < row_cord + si; i++){
        for (int j = column_cord; j < column_cord + sj; j++){
            int num_of_cigbutts = area[i][j];
            if (num_of_cigbutts == 0){
                continue;
            }
            else{
                for (int k = 0; k < num_of_cigbutts; k++){
                    
                    //usleep(1000*tg);
                    gettimeofday(&now, NULL);
                    tm.tv_sec = now.tv_sec + second;
                    tm.tv_nsec = (now.tv_usec + 1000*milisecond)*1000;
                    tm.tv_sec += tm.tv_nsec/1000000000;
                    tm.tv_nsec %= 1000000000;

                    pthread_mutex_lock(&order_mutex);
                    pthread_cond_timedwait(&order_condition, &order_mutex, &tm);
                    pthread_mutex_unlock(&order_mutex);

                    // check the order here, if present return
                    if (order_flag == BREAK){
                        return;
                    }
                    else if (order_flag == STOP){
                        return;
                    }

                    pthread_mutex_lock(&mutex2);
                    area[i][j]--;
                    pthread_mutex_unlock(&mutex2);
                    hw2_notify(PROPER_PRIVATE_GATHERED, gid, i, j); // notify the private gathered one cigbutt
                }
            }
        }
    }

    // check the order here, if present return
    if (order_flag == BREAK){
        return;
    }
    else if (order_flag == STOP){
        return;
    }
    hw2_notify(PROPER_PRIVATE_CLEARED, gid, 0, 0); // notify the area is complately cleared
}

// litter cigarettes one by one in a circular manner on an area and send notification through hw2_notify
void litter_cigarettes(int row_cord, int column_cord, int ts, int sid, int cigarettes_count){
    int second = ts / 1000;
    int milisecond = ts % 1000;

    struct timeval now;
    struct timespec tm;

    for (int i = 0; i < cigarettes_count; i++){
        //usleep(1000*ts);

        gettimeofday(&now, NULL);
        tm.tv_sec = now.tv_sec + second;
        tm.tv_nsec = (now.tv_usec + 1000*milisecond)*1000;
        tm.tv_sec += tm.tv_nsec/1000000000;
        tm.tv_nsec %= 1000000000;

        pthread_mutex_lock(&order_mutex_for_sneaky);
        pthread_cond_timedwait(&order_condition_for_sneaky, &order_mutex_for_sneaky, &tm);
        pthread_mutex_unlock(&order_mutex_for_sneaky); 

        // check the order here, if present return
        if (order_flag == STOP){
            return;
        }

        switch (i%8){
            case 0:
                pthread_mutex_lock(&mutex2);
                area[row_cord-1][column_cord-1]++;
                pthread_mutex_unlock(&mutex2);
                hw2_notify(SNEAKY_SMOKER_FLICKED, sid, row_cord-1, column_cord-1);
                break;
            case 1:
                pthread_mutex_lock(&mutex2);
                area[row_cord-1][column_cord]++;
                pthread_mutex_unlock(&mutex2);
                hw2_notify(SNEAKY_SMOKER_FLICKED, sid, row_cord-1, column_cord);
                break;
            case 2:
                pthread_mutex_lock(&mutex2);
                area[row_cord-1][column_cord+1]++;
                pthread_mutex_unlock(&mutex2);
                hw2_notify(SNEAKY_SMOKER_FLICKED, sid, row_cord-1, column_cord+1);
                break;
            case 3:
                pthread_mutex_lock(&mutex2);
                area[row_cord][column_cord+1]++;
                pthread_mutex_unlock(&mutex2);
                hw2_notify(SNEAKY_SMOKER_FLICKED, sid, row_cord, column_cord+1);
                break;
            case 4:
                pthread_mutex_lock(&mutex2);
                area[row_cord+1][column_cord+1]++;
                pthread_mutex_unlock(&mutex2);
                hw2_notify(SNEAKY_SMOKER_FLICKED, sid, row_cord+1, column_cord+1);
                break;
            case 5:
                pthread_mutex_lock(&mutex2);
                area[row_cord+1][column_cord]++;
                pthread_mutex_unlock(&mutex2);
                hw2_notify(SNEAKY_SMOKER_FLICKED, sid, row_cord+1, column_cord);
                break;
            case 6:
                pthread_mutex_lock(&mutex2);
                area[row_cord+1][column_cord-1]++;
                pthread_mutex_unlock(&mutex2);
                hw2_notify(SNEAKY_SMOKER_FLICKED, sid, row_cord+1, column_cord-1);
                break;
            case 7:
                pthread_mutex_lock(&mutex2);
                area[row_cord][column_cord-1]++;
                pthread_mutex_unlock(&mutex2);
                hw2_notify(SNEAKY_SMOKER_FLICKED, sid, row_cord, column_cord-1);
                break;
        }
    }
    
    // check the order here, if present return
    if (order_flag == STOP){
        return;
    }
    hw2_notify(SNEAKY_SMOKER_LEFT, sid, 0, 0); // notify the area is complately cleared
}

// all the operations related to privates thread will be done in this function
void * privates_thread_function(void *tid){
    int n = * (int *)tid;
    proper_private p_private = privates[n];

    // check the order break here, if present wait
    if (order_flag == BREAK){
        hw2_notify(PROPER_PRIVATE_TOOK_BREAK, p_private.gid, 0, 0);
        pthread_cond_wait(&continue_condition, &mutex);
        if (order_flag == CONTINUE){
            hw2_notify(PROPER_PRIVATE_CONTINUED, p_private.gid, 0, 0);
        }
    }
    else if (order_flag == STOP){
        hw2_notify(PROPER_PRIVATE_STOPPED, p_private.gid, 0, 0);
        pthread_exit(NULL);
    }
    
    hw2_notify(PROPER_PRIVATE_CREATED, p_private.gid, 0 ,0); // notify the creation of thread

    for (int i = 0; i < p_private.ng; i++){
        int row_cord = p_private.coordinates[i].first;
        int column_cord = p_private.coordinates[i].second;

        pthread_mutex_lock(&mutex);

        // check the order break here, if present unlock
        if (order_flag == BREAK){
            hw2_notify(PROPER_PRIVATE_TOOK_BREAK, p_private.gid, 0, 0);
            pthread_cond_wait(&continue_condition, &mutex);
            if (order_flag == CONTINUE){
                hw2_notify(PROPER_PRIVATE_CONTINUED, p_private.gid, 0, 0);
            }
            pthread_mutex_unlock(&mutex);
            i--;
            continue;
        }
        else if (order_flag == STOP){
            hw2_notify(PROPER_PRIVATE_STOPPED, p_private.gid, 0, 0);
            pthread_mutex_unlock(&mutex);
            pthread_exit(NULL);
        }
        
        bool can_be_locked = check_the_area_locks(row_cord, column_cord, p_private.si, p_private.sj);
        if (can_be_locked){
            lock_the_area(row_cord, column_cord, p_private.si, p_private.sj);
            pthread_mutex_unlock(&mutex);
            hw2_notify(PROPER_PRIVATE_ARRIVED, p_private.gid, row_cord, column_cord); // notify the private lock the area
        }
        else{
            pthread_cond_wait(&condition, &mutex);
            pthread_mutex_unlock(&mutex);
            i--;
            continue;
        }

        // gathering cigbutts from left-top to rigth bottom
        gather_cigbutts(row_cord, column_cord, p_private.si, p_private.sj, p_private.tg, p_private.gid);

        // check the order break here, if present unlock
        if (order_flag == BREAK){
            pthread_mutex_lock(&mutex);
            unlock_the_area(row_cord, column_cord, p_private.si, p_private.sj);
            hw2_notify(PROPER_PRIVATE_TOOK_BREAK, p_private.gid, 0, 0);
            pthread_cond_wait(&continue_condition, &mutex);
            if (order_flag == CONTINUE){
                hw2_notify(PROPER_PRIVATE_CONTINUED, p_private.gid, 0, 0);
            }
            pthread_mutex_unlock(&mutex);
            i--;
            continue;
        }
        else if (order_flag == STOP){
            hw2_notify(PROPER_PRIVATE_STOPPED, p_private.gid, 0, 0);
            pthread_exit(NULL);
        }
        
        pthread_mutex_lock(&mutex);
        unlock_the_area(row_cord, column_cord, p_private.si, p_private.sj);
        pthread_cond_broadcast(&condition); // unblock all the threads and allow them to retry to lock
        pthread_mutex_unlock(&mutex);
    }
    hw2_notify(PROPER_PRIVATE_EXITED, p_private.gid, 0, 0); // notify the private cleared all of his areas and exiting
    pthread_exit(NULL);
}

// all the operations related to smoker thread will be done in this function
void * smokers_thread_function(void *tid){
    int n = * (int *)tid;
    sneaky_smoker s_smoker = sneaky_smokers[n];

    // check the order stop here, if present quit
    if (order_flag == STOP){
        hw2_notify(SNEAKY_SMOKER_STOPPED, s_smoker.sid, 0, 0);
        pthread_exit(NULL);
    }
    
    hw2_notify(SNEAKY_SMOKER_CREATED, s_smoker.sid, 0 ,0); // notify the creation of thread

    for (int i = 0; i < s_smoker.ns; i++){
        int row_cord = s_smoker.coordinates[i].first;
        int column_cord = s_smoker.coordinates[i].second;

        // check the order stop here, if present quit
        if (order_flag == STOP){
            hw2_notify(SNEAKY_SMOKER_STOPPED, s_smoker.sid, 0, 0);
            pthread_exit(NULL);
        }

        pthread_mutex_lock(&mutex);
        bool can_be_locked = check_the_area_locks2(row_cord-1, column_cord-1, 3, 3);
        bool can_be_locked_for_smokers = check_the_area_locks_for_sneaky_smokers(row_cord, column_cord);
        if (can_be_locked && can_be_locked_for_smokers){
            lock_the_area2(row_cord-1, column_cord-1, 3, 3);
            lock_the_area_for_sneaky_smokers(row_cord, column_cord);
            pthread_mutex_unlock(&mutex);
            hw2_notify(SNEAKY_SMOKER_ARRIVED, s_smoker.sid, row_cord, column_cord); // notify the private lock the area
        }
        else{
            pthread_cond_wait(&condition, &mutex);
            pthread_mutex_unlock(&mutex);
            i--;
            continue;
        }

        // littering cigarettes in a circular manner
        litter_cigarettes(row_cord, column_cord, s_smoker.ts, s_smoker.sid,s_smoker.cigarettes_num[i]);

        // check the order break here, if present unlock
        if (order_flag == STOP){
            hw2_notify(SNEAKY_SMOKER_STOPPED, s_smoker.sid, 0, 0);
            pthread_exit(NULL);
        }
        
        pthread_mutex_lock(&mutex);
        unlock_the_area(row_cord-1, column_cord-1, 3, 3);
        unlock_the_area_for_sneaky_smokers(row_cord, column_cord);
        pthread_cond_broadcast(&condition); // unblock all the threads and allow them to retry to lock
        pthread_mutex_unlock(&mutex);
    }
    hw2_notify(SNEAKY_SMOKER_EXITED, s_smoker.sid, 0, 0); // notify the smoker finished all of his cigarettes and exiting
    pthread_exit(NULL);
}

// gives the time passed from begining of the game
static struct timeval start_time;
static long get_timestamp1(void){
    struct timeval cur_time1;
    gettimeofday(&cur_time1, NULL);
    long t = (cur_time1.tv_sec - start_time.tv_sec) * 1000000 + (cur_time1.tv_usec - start_time.tv_usec);
    t = t/1000;
    return t;
}


int main(){
    hw2_init_notifier(); // start the hw2_notifier
    input_taker(); // take the inputs
    initialize_the_locks(); // unlock all the area
    gettimeofday(&start_time, NULL);

    pthread_t pptid[num_of_privates]; // proper privates thread ids
    int t_num[num_of_privates];

    // create the threads (proper privates)
    for (int i = 0; i < num_of_privates; i++){
        t_num[i] = i;
        pthread_create(&pptid[i], NULL, privates_thread_function, (void *)&t_num[i]);
    }

    pthread_t sstid[num_of_sneaky_smokers]; // sneaky smokers thread ids
    int st_num[num_of_sneaky_smokers];

    // create the threads (sneaky smokers)
    for (int i = 0; i < num_of_sneaky_smokers; i++){
        st_num[i] = i;
        pthread_create(&sstid[i], NULL, smokers_thread_function, (void *)&st_num[i]);
    }

    // order checking and delivery
    int order_index = 0;
    while (order_index < num_of_orders){
        usleep(10000);
        long time = get_timestamp1();
        if (time >= orders[order_index].first){
            string ordr = orders[order_index].second;
            if (ordr == "break"){
                if (order_flag == CONTINUE || order_flag == NOTHING){
                    hw2_notify(ORDER_BREAK, 0, 0, 0);
                    order_flag = BREAK;
                    pthread_cond_broadcast(&order_condition);
                    pthread_cond_broadcast(&condition);
                }
                else if (order_flag == STOP || order_flag == BREAK){
                    hw2_notify(ORDER_BREAK, 0, 0, 0);
                }
            }
            else if (ordr == "continue"){
                if ( order_flag == BREAK && check_the_area_locks2(0, 0, num_of_rows, num_of_colums)){
                    hw2_notify(ORDER_CONTINUE, 0, 0, 0);
                    order_flag = CONTINUE;
                    pthread_cond_broadcast(&continue_condition);
                }
                else if (order_flag == CONTINUE || order_flag == STOP || order_flag == NOTHING){
                    hw2_notify(ORDER_CONTINUE, 0, 0, 0);
                }
                else{
                    continue;
                }
            }
            else if (ordr == "stop"){
                if ( order_flag == BREAK && check_the_area_locks2(0, 0, num_of_rows, num_of_colums)){
                    hw2_notify(ORDER_STOP, 0, 0, 0);
                    order_flag = STOP;
                    pthread_cond_broadcast(&continue_condition);
                    pthread_cond_broadcast(&condition);
                    pthread_cond_broadcast(&order_condition);
                    pthread_cond_broadcast(&order_condition_for_sneaky);
                }
                else if (order_flag == CONTINUE || order_flag == STOP || order_flag == NOTHING){
                    hw2_notify(ORDER_STOP, 0, 0, 0);
                    order_flag = STOP;
                    pthread_cond_broadcast(&condition);
                    pthread_cond_broadcast(&order_condition);
                    pthread_cond_broadcast(&order_condition_for_sneaky);
                }
                else{
                    continue;
                }
            }
            order_index++;
        }
    }
    
    // join threads (proper privates)
    for (int i = 0; i < num_of_privates; i++){
        pthread_join(pptid[i], NULL);
    }

    // join threads (sneaky smokers)
    for (int i = 0; i < num_of_sneaky_smokers; i++){
        pthread_join(sstid[i], NULL);
    }

    return 0;
}
