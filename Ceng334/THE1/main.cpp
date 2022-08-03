#include "parser.h"
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

using namespace std;

typedef struct bundle{
    string name;
    char *input;
    char *output;
    vector<char **> processes;
}bundle;

vector<bundle> bundles;

int main(){
    int is_bundle_creation = 0;
    parsed_input *input = new parsed_input();
    bundle b;

    while (1){
        
        string ss;
        getline(cin, ss);
        string cmd = ss.substr(0, ss.find(" "));
        char s[ss.size()+1];
        strcpy(s , (ss+" ").c_str());
        if (ss.compare("") == 0){
            continue;
        }

        if (cmd.compare("quit") == 0){
            break;
        }
        else if (cmd.compare("pbc") == 0 && is_bundle_creation == 0){
            parse(s, 0, input);
            is_bundle_creation = 1;

            b.name = input->command.bundle_name;
        }
        else if (cmd.compare("pbs") == 0 && is_bundle_creation == 1){
            parse(s, 1, input);
            is_bundle_creation = 0;

            bundles.push_back(b);
            bundle b2;
            b = b2;
        }
        else{
            parse(s, is_bundle_creation, input);
            if (is_bundle_creation){
                b.processes.push_back(input->argv);
            }
            else{
                int number_of_bundles = input->command.bundle_count;
                bundle_execution *executed_bundles = input->command.bundles;
                int total_proc_num = 0;
                
                int p1[2];
                vector<pair<int, int>>p2;
                for (int i = 0; i < number_of_bundles; i++){
                    bundle bd, bd_n;
                    for (int k = 0; k < bundles.size(); k++){
                        if(executed_bundles[i].name == bundles[k].name){
                            bd = bundles[k];
                            bundles.erase(bundles.begin() + k);
                            break;
                        }
                    }
                    for (int k = 0; (k < bundles.size()) && ((i+1) < number_of_bundles); k++){
                        if (executed_bundles[i+1].name == bundles[k].name){
                            bd_n = bundles[k];
                            break;
                        }
                        
                    }
                    
                    if(bd.name == ""){
                        continue;
                    }
                    bd.input = executed_bundles[i].input;
                    bd.output = executed_bundles[i].output;
                    pipe(p1);
                    int process_number = bd.processes.size();
                    vector<int> pids;
                    //bu bundle'ı handle edeceğiz önce. Bunun process'lerini exec edeceğiz.
                    for (int k = 0; k < process_number; k++){
                        total_proc_num++;
                        

                        if (bd.input || i != 0){   
                            /* input redirection */
                            if(bd.input){
                                /* from file*/
                                int fdk = open(bd.input, O_RDONLY, 0600);
                                dup2(fdk, STDIN_FILENO);
                                close(fdk);
                            }
                            else{
                                /* from pipe*/
                            }
                        }

                        if (bd.output || i < number_of_bundles - 1){
                            /* output redirection */
                            if (bd.output){
                                /* to file */
                                int fdk = open(bd.output, O_APPEND|O_WRONLY|O_CREAT, 0666);
                                if(dup2(fdk, STDOUT_FILENO)== -1){
                                    printf(" errorr");
                                }
                                close(fdk);
                            }
                            else{
                                /* to pipe */
                            }
                        }
                        
                        pid_t pid = fork();
                        if (pid == 0) {
                            // Child process
                            if (i != 0){
                                dup2(p2[k].first, STDIN_FILENO);
                                for (int m = 0; m < p2.size(); m++){
                                    close(p2[m].first);
                                }
                            }

                            if (i < number_of_bundles -1){
                                dup2(p1[1], STDOUT_FILENO);
                                close(p1[0]);
                                close(p1[1]);
                            }
                            else{
                                close(p1[0]);
                                close(p1[1]);
                            }

                            execvp(bd.processes[k][0], bd.processes[k]);
                            break;
                        }
                        pids.push_back(pid);
                    }
                    close(p1[1]);

                    for (int m = 0; m < p2.size(); m++){
                        close(p2[m].first);
                        close(p2[m].second);
                    }
                    p2.clear();

                    if (i < number_of_bundles -1){
                        char line[512];
                        int number_of_bytes_readed;
                        for (int m = 0; m < bd_n.processes.size(); m++){
                            p2.push_back(make_pair(0,0));
                        }

                        for (int m = 0; m < bd_n.processes.size(); m++){
                            int pip2[2];
                            pipe(pip2);
                            p2[m].first = pip2[0];
                            p2[m].second = pip2[1];
                        }

                        while ((number_of_bytes_readed = read(p1[0], line, 512)) > 0){
                            for (int k = 0; k < p2.size(); k++){
                                write(p2[k].second, line, number_of_bytes_readed);
                            }
                        }

                        for (int m = 0; m < p2.size(); m++){
                            close(p2[m].second);
                        }
                    }

                    close(p1[0]);

                    for (int m = 0; m < pids.size(); m++){
                        waitpid(pids[m], NULL, 0);
                    }

                    pids.clear();
                }
            }
        }
    }   
    return 0;
}




/* vector<string> simple_tokenizer(string s){
    vector<string> v;
    stringstream ss(s);
    string word;

    while (ss >> word) {
        v.push_back(word);
    }
    return v;
} */


//-------------------------------------
/* 
int parse(char *line, int is_bundle_creation, parsed_input *parsedInput) {
    if ( !parsedInput )
        return 0;
    int is_quoted;
    char buffer[256];
    int argument_count, argument_index;
    int index;
    
    memset(buffer, 0, sizeof(char)*256); 
    if ( is_bundle_creation ) {
        is_quoted = 0;
        index = 0;
        argument_index = 0;
        argument_count = 0;
        for ( char *current = line; *current ; current++) {
            if ( is_quoted ) {
                if ( *current == '"' ) {
                    is_quoted = 0;
                }
                else
                    index++;
            }
            else {
                if (*current == '"')
                    is_quoted = 1;
                else if (isspace(*current)) {
                    if ( index == 0 ) continue;
                    argument_count++;
                    index = 0;
                }
                else
                    index++;
            }
        }

        parsedInput->argv = (char **)calloc(argument_count+1, sizeof(char*));
        parsedInput->argv[argument_count] = NULL;

        is_quoted = 0;
        index = 0;
        for ( char *current = line; *current ; current++) {
            if ( is_quoted ) {
                if ( *current == '"' )
                    is_quoted = 0;
                else
                    buffer[index++] = *current;
            }
            else {
                if ( *current == '"' )
                    is_quoted = 1;
                else if ( isspace(*current) ) {
                    if ( index == 0 ) continue;
                    else if ( strcmp(buffer, "pbs") == 0 ) {
                        parsedInput->command.type = PROCESS_BUNDLE_STOP;
                        return 1;
                    }
                    buffer[index++] = '\0';
                    parsedInput->argv[argument_index] = (char*) calloc(index, sizeof(char));
                    strcpy(parsedInput->argv[argument_index], buffer);
                    index = 0;
                    argument_index++;
                }
                else
                    buffer[index++] = *current;
            }
        }
    }
    else {
        is_quoted = 0;
        argument_count = 1;
        for ( char *current = line; *current ; current++) {
            if (is_quoted) {
                if (*current == '"')
                    is_quoted = 0;
            }
            else {
                if (*current == '"')
                    is_quoted = 1;
                else if ( *current == '|' )
                    argument_count++;
            }
        }
        is_quoted = 0;
        index = 0;
        argument_index = 0;
        int is_next_input, is_next_output, executable_index;
        for ( char *current = line; *current ; current++) {
            if (is_quoted) {
                if (*current == '"')
                    is_quoted = 0;
                else
                    buffer[index++] = *current;
            } else {
                if (*current == '"')
                    is_quoted = 1;
                else if (isspace(*current)) {
                    if ( index == 0 ) continue;
                    buffer[index++] = '\0';
                    if (!argument_index) {
                        if ( strcmp(buffer, "pbc") == 0 )
                            parsedInput->command.type = PROCESS_BUNDLE_CREATE;
                        else if ( strcmp(buffer, "pbs") == 0 ) {
                            parsedInput->command.type = PROCESS_BUNDLE_STOP;
                            return 1;
                        }
                        else if ( strcmp(buffer, "quit") == 0 ) {
                            parsedInput->command.type = QUIT;
                            return 0;
                        }
                        else {
                            parsedInput->command.type = PROCESS_BUNDLE_EXECUTION;
                            parsedInput->command.bundle_count = argument_count;
                            parsedInput->command.bundles = (bundle_execution*) calloc(argument_count, sizeof(bundle_execution));

                            is_next_input = 0;
                            is_next_output = 0;
                            executable_index = 0;

                            parsedInput->command.bundles[executable_index].name = (char*)calloc(index, sizeof(char));
                            strcpy(parsedInput->command.bundles[executable_index].name, buffer);

                            parsedInput->command.bundles[executable_index].input = NULL;
                            parsedInput->command.bundles[executable_index].output = NULL;

                        }
                    }
                    else {
                        if ( parsedInput->command.type == PROCESS_BUNDLE_CREATE ) {
                            parsedInput->command.bundle_name = (char*) calloc(index, sizeof(char));
                            strcpy(parsedInput->command.bundle_name, buffer);
                            return 0;
                        }
                        else {
                            if ( argument_index % 2 == 1 ) {
                                if ( strcmp(buffer, "<") == 0 )
                                    is_next_input = 1;
                                else if ( strcmp(buffer, ">") == 0 )
                                    is_next_output = 1;
                                else if ( strcmp(buffer, "|") == 0 )
                                    executable_index++;
                            }
                            else {
                                if ( is_next_input ) {
                                    parsedInput->command.bundles[executable_index].input = (char*)calloc(index, sizeof(char));
                                    strcpy(parsedInput->command.bundles[executable_index].input, buffer);
                                    is_next_input = 0;
                                }
                                else if ( is_next_output ) {
                                    parsedInput->command.bundles[executable_index].output = (char*)calloc(index, sizeof(char));
                                    strcpy(parsedInput->command.bundles[executable_index].output, buffer);
                                    is_next_output = 0;
                                }
                                else {
                                    parsedInput->command.bundles[executable_index].name = (char*)calloc(index, sizeof(char));
                                    strcpy(parsedInput->command.bundles[executable_index].name, buffer);
                                }
                            }
                        }
                    }
                    index = 0;
                    argument_index++;
                } else
                    buffer[index++] = *current;
            }
        }
    }
} */