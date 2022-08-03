#include "parser.h"
#include <iostream>
#include <vector>
#include <string>
#include <unistd.h>
#include <sys/wait.h>
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

                    for (int k = 0; k < process_number; k++){
                        
                        pid_t pid = fork();
                        if (pid == 0) {
                            // Child process
                            if (i != 0){
                                dup2(p2[k].first, STDIN_FILENO);
                                for (int m = 0; m < p2.size(); m++){
                                    close(p2[m].first);
                                }
                            }

                            if (bd.input && i == 0){   
                                /* input redirection */
                                int fdk = open(bd.input, O_RDONLY, 0600);
                                dup2(fdk, STDIN_FILENO);
                                close(fdk);
                            }

                            if (i < number_of_bundles -1){
                                dup2(p1[1], STDOUT_FILENO);
                                close(p1[0]);
                                close(p1[1]);
                            }
                            else{
                                close(p1[0]);
                                close(p1[1]);

                                if (bd.output){
                                    /* output redirection */
                                    int fdk = open(bd.output, O_CREAT|O_APPEND|O_WRONLY, 0666);
                                    dup2(fdk, STDOUT_FILENO);
                                    close(fdk);
                                }
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
