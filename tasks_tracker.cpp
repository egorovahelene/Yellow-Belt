#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <iomanip>
#include<math.h>
#include <fstream>
#include <sstream> 
using namespace std;


enum class TaskStatus {
    NEW,
    IN_PROGRESS,
    TESTING,
    DONE
};


using TasksInfo = map<TaskStatus, int>;



TaskStatus Next_status(TaskStatus ts) {
    if (ts == TaskStatus::NEW) {
        return TaskStatus::IN_PROGRESS;
    }
    else if (ts == TaskStatus::IN_PROGRESS) {
        return TaskStatus::TESTING;
    }
    else if (ts == TaskStatus::TESTING) {
        return TaskStatus::DONE;
    }
    else { return TaskStatus::DONE; }

}



TaskStatus Find_not_null(TasksInfo temp) {
    TaskStatus a = TaskStatus::DONE;
    if (temp.count(TaskStatus::NEW)) {
        a = TaskStatus::NEW;
        return a;
    }
    else if (temp.count(TaskStatus::IN_PROGRESS)) {
        a = TaskStatus::IN_PROGRESS;
        return a;
    }
    else if (temp.count(TaskStatus::TESTING)) {
        a = TaskStatus::TESTING;
        return a;
    }
    else { return a; }
}

TaskStatus Find_next_not_null(TasksInfo temp, TaskStatus ts) {
    TaskStatus cs = ts;
    while (cs != TaskStatus::DONE) {
        if (temp[Next_status(cs)] != 0) {
            cs = Next_status(cs);
            break;
        }
        else {
            cs = Next_status(cs);
        }
    }
    return cs;
}

void DeleteZeros(TasksInfo& temp) {

    if (temp[TaskStatus::NEW]==0) {
        temp.erase(TaskStatus::NEW);
    }
    if (temp[TaskStatus::IN_PROGRESS] == 0) {
        temp.erase(TaskStatus::IN_PROGRESS);
    }
    if (temp[TaskStatus::TESTING] == 0) {
        temp.erase(TaskStatus::TESTING);
    }
    if (temp[TaskStatus::DONE] == 0) {
        temp.erase(TaskStatus::DONE);
    }
}

void makeZeros(TasksInfo& temp) {

    if (!temp.count(TaskStatus::NEW)) {
        temp[TaskStatus::NEW] = 0;
    }
    if (!temp.count(TaskStatus::IN_PROGRESS)) {
        temp[TaskStatus::IN_PROGRESS] = 0;
    }
    if (!temp.count(TaskStatus::TESTING)) {
        temp[TaskStatus::TESTING] = 0;
    }
    if (!temp.count(TaskStatus::DONE)) {
        temp[TaskStatus::DONE] = 0; 
    }

}

class TeamTasks {
public:

    const TasksInfo& GetPersonTasksInfo(const string& person) const {
        return team_inf.at(person);

    }


    void AddNewTask(const string& person) {
        if (team_inf.count(person)) {
            team_inf[person][TaskStatus::NEW]++;
        }
        else {
            team_inf[person][TaskStatus::NEW] = 1;
        }
    }


    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count) {

        TasksInfo nouvelle; //updated
        TasksInfo old;
        TasksInfo temp;

        if (team_inf.count(person)) {
            

            temp = team_inf.at(person);

            makeZeros(temp);
            makeZeros(nouvelle);
            old = temp;


            int tasks_overall;

            int n = 0, p = 0, t = 0, d = 0;
            n = temp.at(TaskStatus::NEW);
            p = temp.at(TaskStatus::IN_PROGRESS);
            t = temp.at(TaskStatus::TESTING);
            d = temp.at(TaskStatus::DONE);

            tasks_overall = n + t + p;

            if (tasks_overall < task_count) { task_count = tasks_overall; }



            TaskStatus cs = Find_not_null(temp);
            TaskStatus ns = Next_status(cs);




            do {
                int val = min(temp[cs], task_count);
                nouvelle[ns] = val;
                old[cs] = temp[cs] - val;
                task_count = task_count - val;
                team_inf.at(person)[cs] = team_inf.at(person)[cs] - val;
                team_inf.at(person)[ns] = team_inf.at(person)[ns] + val;
                cs = Find_next_not_null(temp, cs);
                ns = Next_status(cs);

            } while (task_count != 0);

            DeleteZeros(team_inf.at(person));
            DeleteZeros(old);
            DeleteZeros(nouvelle);

            old.erase(TaskStatus::DONE);
            
        }
        return tie(nouvelle, old);
    }

private:
    map<string, TasksInfo>  team_inf;
};


void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
        ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
        ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
        ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    tie(updated_tasks, untouched_tasks) =
        tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);

    return 0;
}
