#define what_is(x) cerr << #x << " = " << x << endl;
#define deb(...) logger(#__VA_ARGS__, __VA_ARGS__)
template<typename ...Args>
void logger(string vars, Args&&... values) {
    cout << "{" << vars << " } = {";
    string delim = "";
    (..., (cout << delim << values << "}", delim = ", "));
}