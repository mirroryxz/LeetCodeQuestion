/*
给定一个"HH:MM"格式的时间，重复使用这些数字，返回下一个最近的时间。每个数字可以被重复使用任意次。
保证输入的时间都是有效的。例如，"01:34"，"12:09" 都是有效的，而"1:34"，"12:9"都不是有效的时间。
*/
class Solution {
public:
    /**
     * @param time: the given time
     * @return: the next closest time
     */
    string nextClosestTime(string &time) {
        // write your code here
        vector<int> number {time[0]-'0', time[1]-'0', time[3]-'0', time[4]-'0'} ;
        vector<int> currTime(4, 0);
        int hour = number[0]*10 + number[1];
        int minute = number[2]*10 + number[3];
        int times = toMinute(hour, minute);
        int bestTime = times;
        dfs(number, 0, currTime, times, bestTime);
        string s = to_string(bestTime/60) + ":" + to_string(bestTime%60);
        char buff[5];
        sprintf(buff, "%02d:%02d", bestTime / 60, bestTime % 60);
        return string(buff);
    }
    void dfs(vector<int> &number, int deep, vector<int>& currTime, int times, int& bestTime){
        if(deep == 4){
            if(currTime[0]*10 + currTime[1] > 23 || currTime[2]*10 + currTime[3] > 59)
                return;
            int currMinutes = toMinute(currTime[0]*10 + currTime[1], currTime[2]*10 + currTime[3]);
            if(diff(times, currMinutes) < diff(times, bestTime)){
                bestTime = currMinutes;
            }
            return;
        }
        for(int i:number){
            currTime[deep] = i;
            dfs(number, deep+1, currTime, times, bestTime);
        }
        return;
    }
    int toMinute(int hour, int minute){
        return hour*60 + minute;
    }
    int diff(int time1, int time2){
        if(time1 == time2)
            return 1440;
        return ((1440 - time1) + time2) % 1440;
    }
};
