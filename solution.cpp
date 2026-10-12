#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int x, k, p;
    if (scanf("%d %d %d", &x, &k, &p) != 3) {
        return 0;
    }
    
    // Handle edge case: if x = 1, there are no segments
    if (x == 1) {
        // All orders must be from station 1 to station 1
        // Since there are no segments, any order can be fulfilled
        for (int order = 0; order < p; order++) {
            int u, v, n;
            scanf("%d %d %d", &u, &v, &n);
            printf("T\n");
        }
        return 0;
    }
    
    // We need to track seat usage for segments between stations
    // There are x-1 segments: segment i goes from station i to i+1
    vector<int> seat_usage(x + 1, 0);  // 1-indexed, seat_usage[i] = seats used on segment i
    
    for (int order = 0; order < p; order++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        // Check if order can be fulfilled
        bool can_fulfill = true;
        for (int station = u; station < v; station++) {
            if (seat_usage[station] + n > k) {
                can_fulfill = false;
                break;
            }
        }
        
        if (can_fulfill) {
            // Update seat usage for all segments in this journey
            for (int station = u; station < v; station++) {
                seat_usage[station] += n;
            }
            printf("T\n");
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}