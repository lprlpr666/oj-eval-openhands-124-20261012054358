#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int x, k, p;
    scanf("%d %d %d", &x, &k, &p);
    
    // We need to track seat usage for each station
    // seat_usage[i] = seats used at station i (for boarding/alighting)
    vector<int> seat_usage(x + 1, 0);  // 1-indexed
    
    for (int order = 0; order < p; order++) {
        int u, v, n;
        scanf("%d %d %d", &u, &v, &n);
        
        // Check if order can be fulfilled
        // Need to check all stations from u to v (inclusive)
        bool can_fulfill = true;
        for (int station = u; station <= v; station++) {
            if (seat_usage[station] + n > k) {
                can_fulfill = false;
                break;
            }
        }
        
        if (can_fulfill) {
            // Update seat usage for all stations in this journey
            for (int station = u; station <= v; station++) {
                seat_usage[station] += n;
            }
            printf("T\n");
        } else {
            printf("N\n");
        }
    }
    
    return 0;
}