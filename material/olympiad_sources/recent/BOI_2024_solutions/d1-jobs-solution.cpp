#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int N_MAX = 300000;

struct block {
    // Minimum prefix sum of the block -> we need at least "requirement" money to take all of block's elements
    long long requirement;
    // Sum of all elements of the block
    long long sum;

    // Allows sorting blocks in non-decreasing order by "requirement"
    bool operator>(const block& other) const {
        return requirement > other.requirement || (requirement == other.requirement && sum > other.sum);
    }
};

int x[N_MAX + 1];
vector <int> children[N_MAX + 1];

// Index of the 'leader' vertex of a priority queue containing vertex i
int p_queue_index[N_MAX + 1];
// Structure allowing to extract block with the smallest "requirement" value
priority_queue <block, vector<block>, greater<block>> blocks[N_MAX + 1];


int merge_priority_queues(int id_a, int id_b) {
    if (blocks[id_b].size() > blocks[id_a].size()) {
        // Trick: merge smaller queue to a larger one
        swap(id_a, id_b);
    }
    while (blocks[id_b].size() > 0) {
        blocks[id_a].push(blocks[id_b].top());
        blocks[id_b].pop();
    }
    return id_a;
}


// Combine new_block with the current list of blocks at vertex v until the sum of the new_block becomes positive
void combine_blocks(int v, block new_block) {
    while (blocks[v].size() > 0) {
        block top_block = blocks[v].top();
        if (new_block.sum <= 0) {
            blocks[v].pop();
            new_block = {max(new_block.requirement, top_block.requirement - new_block.sum), new_block.sum + top_block.sum};
        }
        else {
            // If sum is positive, we want to keep "requirement" sorted in non-decreasing order
            if (new_block.requirement > top_block.requirement) {
                blocks[v].pop();
                new_block = {new_block.requirement, new_block.sum + top_block.sum};
            }
            else {
                // new_block satisfies the requirements, push it to the list of the blocks at vertex v.
                blocks[v].push(new_block);
                break;
            }
        }
    }
    if (blocks[v].size() == 0) {
        blocks[v].push(new_block);
    }
    if (blocks[v].size() == 1 && blocks[v].top().sum <= 0) {
        blocks[v].pop();
    }
}


void dfs(int v) {
    if (children[v].size() == 0) {
        // For a new priority queue, set the graph child node as the 'leader' of the priority queue
        p_queue_index[v] = v;
    }
    for (int i = 0; i < children[v].size(); i++) {
        int a = children[v][i];
        dfs(a);
        if (i == 0) {
            p_queue_index[v] = p_queue_index[a];
        }
        else {
            // Merge priority queues of children vertices
            p_queue_index[v] = merge_priority_queues(p_queue_index[v], p_queue_index[a]);
        }
    }
    // Add block formed by vertex v to the list of merged blocks from children of v
    combine_blocks(p_queue_index[v], {max(0, -x[v]), x[v]});
}


int main() {
    int N;
    long long s, profit = 0;  // Profit starts from 0, and not from s.
    cin >> N >> s;
    for (int i = 1; i <= N; i++) {
        int p;
        cin >> x[i] >> p;
        children[p].push_back(i);
    }

    // Perform dfs which constructs the order of blocks to be visited independently on the s.
    dfs(0);

    // Once the block order is set, take all blocks that we can with the given value of s.
    while (blocks[p_queue_index[0]].size() > 0) {
        long long min_requirement = blocks[p_queue_index[0]].top().requirement;
        long long sum = blocks[p_queue_index[0]].top().sum;
        blocks[p_queue_index[0]].pop();
        if (s + profit >= min_requirement) {
            profit += sum;
        }
    }

    cout << profit << endl;
    return 0;
}