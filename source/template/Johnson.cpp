struct Job {   int a, b, idx; bool operator<(Job o) const {    return min(a, b) < min(o.a, o.b);    }   };
vector<Job> johnsons_rule(vector<Job> jobs) {
    sort(jobs.begin(), jobs.end());
    vector<Job> a, b;
    for (Job j : jobs) { if (j.a < j.b) a.push_back(j); else b.push_back(j);  }
    a.insert(a.end(), b.rbegin(), b.rend());
    return a;
}