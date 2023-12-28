/*
 * Cheapest Flights Within K Stops
 * -------------------------------
 * There are n cities and m edges connected by some number of flights. 
 * You are given an array flights where flights[i] = [fromi, toi, pricei] indicates that there is a flight from the city fromi to city toi with cost price(i).
 * 
 * You are also given three integers src, dst, and k, return the cheapest price from src to dst with at most k stops. If there is no such route, return -1.
*/

// Queue can be better than set when traversal cost is constant

// Solution 1: using 1D distance array
class Solution{
    public:
    // Since, it'll be sorted by stops - it is effectively like PQ - T(n) = O(KV(c+ Ea*c)) = O(KE)
    // keeps track of minimum price to reach any city w.r.t. stops count (0 -> K)
    int CheapestFLight(int n, vector<vector<int>>& flights, int src, int dst, int K)  {
        vector<vector<pair<int,int>>> flightGraph(n);
        for(vector<int> vec: flights){
            flightGraph[vec[0]].push_back({vec[1], vec[2]});
        }
        
        vector<int> priceToReachCity(n, INT_MAX);
        priceToReachCity[src] = 0;
        
        queue<pair<int, pair<int, int>>> pending; //stops, price to reach, city
        pending.push({0, {priceToReachCity[src], src}});
        while(!pending.empty()){
            auto it = pending.front();
            pending.pop();
            
            int stops = it.first;
            int price = it.second.first;
            int city = it.second.second;
            
            if(city == dst){
                continue;
            }
            //Works for k=0
            for(pair<int, int> flight: flightGraph[city]){
                int toCity = flight.first;
                int flightCost = flight.second;
                if(stops == K && toCity != dst)
                        continue;
                if(priceToReachCity[toCity] > price + flightCost){
                    priceToReachCity[toCity] = price + flightCost;
                    pending.push({stops + 1, {priceToReachCity[toCity], toCity}});
                }
            }
        }
        return priceToReachCity[dst] == INT_MAX ? -1 : priceToReachCity[dst];
    }
};

// Solution 2: keeps track of minimum price to reach any city w.r.t. stops count (0 -> K)
// priceToReachCityPerStop[city][K+1] is kept to solve and compare price when K stops is completed - src and dest are not counted as stops
class Solution {
  public:
    // T(n) = O(KV(logV + Ea2*logV)) ~KElogV
    // S(n) = O((V + E) + VK) = O(VK + E)
    int CheapestFLight(int n, vector<vector<int>>& flights, int src, int dst, int K)  {
        vector<vector<pair<int,int>>> flightGraph(n);
        for(vector<int> vec: flights){
            flightGraph[vec[0]].push_back({vec[1], vec[2]});
        }
        // K+2 solves stops=0 and stops=K problem
        vector<vector<int>> priceToReachCityPerStop(n, vector<int>(K+2, INT_MAX)); // stop=0 will not come for any city except src
        priceToReachCityPerStop[src] = vector<int>(K+2, 0);
        
        int ans = INT_MAX;
        
        set<pair<int, pair<int, int>>> pending; //stops, price to reach, city
        pending.insert({0, {priceToReachCityPerStop[src][0], src}});
        while(!pending.empty()){
            auto it = pending.begin();
            pending.erase(it);
            
            int stops = it->first;
            int price = it->second.first;
            int city = it->second.second;
            
            if(city == dst){
                ans = min(ans, price);
                continue;
            }
            //Works for k=0
            for(pair<int, int> flight: flightGraph[city]){
                int toCity = flight.first;
                int flightCost = flight.second;
                if(stops == K && toCity != dst)
                        continue;
                if(priceToReachCityPerStop[toCity][stops+1] > price + flightCost){
                    if(priceToReachCityPerStop[toCity][stops+1] != INT_MAX){ //caching minimum price per stop for a city
                        pending.erase({stops + 1, {priceToReachCityPerStop[toCity][stops+1], toCity}});
                    }
                    priceToReachCityPerStop[toCity][stops+1] = price + flightCost;
                    pending.insert({stops + 1, {priceToReachCityPerStop[toCity][stops+1], toCity}});
                }
            }
        }
        // for(int i=0; i<n; i++){
        //     for(int j=0; j<K+2; j++){
        //         cout<<priceToReachCityPerStop[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }
        return (ans == INT_MAX?-1:ans);
    }
};